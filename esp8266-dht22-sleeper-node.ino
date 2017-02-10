#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include "DHT.h"
// Don't forget to rename config.example.h to config.h in your project folder
// and fill in the SSID/password for your WiFi network
#include "config.h"

DHT dht;
ESP8266WebServer server(WEBSERVER_PORT);
float temperature;
float humidity;

unsigned long prevMillis = 0;

void serve_root() {
  String contents = "ESP8266 DHT Node. Read individual values from /temp or /humidity\n\nTemperature: " + String((int)temperature) + " °C\nHumidity: " + String((int)humidity) + " %REH";
  server.send(200, "text/plain", contents);
}

void serve_temp() {
  char buf[12];
  dtostrf(temperature, 8, 4, buf);
  String contents = "Temperature: " + String(buf) + " °C";
  server.send(200, "text/plain", contents);
}

void serve_humidity() {
  char buf[12];
  dtostrf(humidity, 8, 4, buf);
  String contents = "Humidity: " + String(buf) + " %REH";
  server.send(200, "text/plain", contents);
}

void readTemperature() {
  temperature = dht.getTemperature();
}

void readHumidity() {
  humidity = dht.getHumidity();
}

void setup()
{

  Serial.begin(115200);
  Serial.println();
  dht.setup(DHTPIN, DHT::DHT22);
  Serial.println(dht.getMinimumSamplingPeriod());
  Serial.println(dht.getStatusString());

  WiFi.begin(SSID, PASSWORD);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(150);
    yield();
  }
  Serial.println("");
  Serial.print("IP Address of Node: ");
  Serial.print(WiFi.localIP());

  server.on("/", serve_root);
  server.on("/temp", serve_temp);
  server.on("/humidity", serve_humidity);
  server.begin();

  Serial.println("HTTP Server started");
}

void loop()
{
  server.handleClient();

  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= INTERVAL) {
    // Perhaps didn't have to be in seperate methods
    readTemperature();
    readHumidity();
  }
}

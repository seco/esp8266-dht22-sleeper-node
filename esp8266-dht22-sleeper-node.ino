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
float temperature = 0;
float humidity = 0;

unsigned long prevMillis = 0;

void serve_root() {
  String contents = "<h3>ESP8266 DHT Node</h3>";
  contents += "Read individual values<ul>";
  contents += "<li><a href=\"/temp\">/temp</a></li>";
  contents += "<li><a href=\"/humidity\">/humidity</a></li></ul><hr>";
  contents += "Temperature: " + String(temperature) + " °C<br>";
  contents += "Humidity: " + String(humidity) + " %REH<br>";
  server.send(200, "text/html", contents);
}

void serve_temp() {
  String contents = String(temperature);
  server.send(200, "text/plain", contents);
}

void serve_humidity() {
  String contents = String(humidity);
  server.send(200, "text/plain", contents);
}

void readTemperature() {
  temperature = dht.getTemperature();
  //dtostrf(temp, 8, 2, temperature);
}

void readHumidity() {
  humidity = dht.getHumidity();
  //dtostrf(hum, 8, 2, humidity);
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

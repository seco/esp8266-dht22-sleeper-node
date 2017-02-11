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
  String contents = "<DOCTYPE html>";
  contents += "<html>";
  contents += "<head>";
  contents += "<meta charset=\"utf-8\">";
  contents += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">";
  contents += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  contents += "<meta http-equiv=\"refresh\" content=\"10\">";
  contents += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">";
  contents += "<title>DHT22 ESP8266 Node</title>";
  contents += "</head><body>";
  contents += "<div class=\"container\">";
  contents += "<header class=\"page-header\">";
  contents += "<div class=\"btn-toolbar pull-right\">";
  contents += "<button type=\"button\" class=\"btn btn-primary refresh\"><i class=\"glyphicon glyphicon-refresh\"></i></button>";
  contents += "</div>";
  contents += "<h1>ESP8266 DHT22 Node</h1>";
  contents += "</header>";
  contents += "Temperature: " + String(temperature) + " °C<br>";
  contents += "Humidity: " + String(humidity) + " %REH<br><br>";
  contents += "<span class=\"seconds-ago\"><small><i class=\"glyphicon glyphicon-time\"></i> Last reading: " + String((int)(millis() - prevMillis) / 1000) + " seconds ago.</small></span><hr>";
  contents += "<h3>Read individual values</h3>";
  contents += "<ul><li><a href=\"/temp\">/temp</a></li>";
  contents += "<li><a href=\"/humidity\">/humidity</a></li></ul>";
  contents += "</div>";
  contents += "<script src=\"https://code.jquery.com/jquery-3.1.1.slim.min.js\" integrity=\"sha256-/SIrNqv8h6QGKDuNoLGA4iret+kyesCkHGzVUUV0shc=\" crossorigin=\"anonymous\"></script>";
  contents += "<script>$('.refresh').on('click', function(e){ e.preventDefault(); location.reload(true);});</script>";
  contents += "</body></html>";
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

  readTemperature();
  readHumidity();
  delay(10);
}

void loop()
{
  server.handleClient();

  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= INTERVAL) {
    prevMillis = currentMillis;
    // Perhaps didn't have to be in seperate methods
    readTemperature();
    readHumidity();
  }
}

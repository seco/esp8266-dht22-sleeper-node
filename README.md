# esp8266-dht22-sleeper-node

Software for an ESP8266 WiFi module to read data from a DHT22 sensor module, do something with it like publishing it to a server, and then going into DeepSleep.

DeepSleep on a ESP-01 module requires a hack to the module because not all pins of the ESP8266 chip are exposed. See [this article on hackaday.com](http://hackaday.com/2015/02/08/hack-allows-esp-01-to-go-to-deep-sleep/) on how to accomplish this hack (at your own risk).

## Dependencies

Make sure you have installed the ESP8266 Arduino core from https://github.com/esp8266/Arduino. Their project describes how to install those dependencies.

### Libraries

- Adafruit's Arduino library for the DHT sensors: https://github.com/adafruit/DHT-sensor-library
- Tzapu's WiFiManager: https://github.com/tzapu/WiFiManager
- More to come during development

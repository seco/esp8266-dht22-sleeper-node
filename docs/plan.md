Overview of total architecture, including devices (nodes) with endpoints (sensors/actuators), and software.

# Devices

## End Points
### Sensors

- Temperature and humidity with for example DHT22 sensors
- Door/Window sensors with KaKu protocol
- Weather station (via 433Mhz)
- Doorbell
- Washing machine/Dryer status
- Household electricity consumption
- Household gas consumption
- Household water consumption
- Smoke and CO detector

### Actuators

- Opening and closing of curtains
- Opening and closing of window blinds
- Controlling lights (Philips Hue, KaKu, and others)
- Central Ventilation Unit

# Architecture

Sensor end points publish their data to their end point topics via their corresponding node to a MQTT broker. Actuator end points listen to their corresponding control topics and publish their status on an end point status topic.

Node-red subscribes to topics and allows for easy setup, maintenance, and scalability of connecting different end points to eachother and different internal and external data streams/storage platforms.

# Current plan d'Attack

## 1. Setup test environment

- Setup the MQTT broker. This does not require much horsepower, so a dedicated Raspberry Pi could be used for this end. 
- Setup node-red. This could be on the same device as the MQTT Broker. 
- Setup simple node with sensoric end points to publish messages to the MQTT Broker. Could be simulated by a small script to keep focus on MQTT broker/gateway.
- Read data into node-red via the debug console for example.
- Setup mongodb storage. For testing, this could be on the Raspberry Pi. Could also be on a dedicated server/machine that is always on. Same goes for the Broker and Node-red.


## 2. Create UI to visualize data



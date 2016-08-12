#include <SPI.h>
#include <Ethernet.h>
#include <ThingSpeak.h>

ThingSpeak thingSpeak;

// declare input pins
int sensorPin = A0;

// change this to a valid MAC address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup() {
  // wait for an IP address
  while (Ethernet.begin(mac) == 0);

  // declare field names
  thingSpeak.addField("sensor");

  // configure ThingSpeak channel key
  thingSpeak.setChannel("ABC");
}

long lastUpdate;

void loop() {
  long currentTime = millis();

  // check if 15 seconds have passed
  if (currentTime - lastUpdate >= 15000) {
    // read from the input pins
    int sensorValue = analogRead(sensorPin);

    // update the channel
    thingSpeak.setField("sensor", sensorValue);
    thingSpeak.update();

    lastUpdate = currentTime;
  }

  delay(100);
}

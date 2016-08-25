#include "Arduino.h"
#include "ThingSpeak.h"

// Consturctors

ThingSpeak::ThingSpeak()
{
  _address = "api.thingspeak.com";
}

ThingSpeak::ThingSpeak(String address)
{
  _address = address;
}

// Sets the Channel API KEY

void ThingSpeak::setChannel(String key)
{
  _channelKey = key;
}

// Sets the TalkBack ID and API KEY

void ThingSpeak::setTalkBack(int id, String key)
{
  // Overload
  setTalkBack(String(id), key);
}

void ThingSpeak::setTalkBack(String id, String key)
{
  _talkBackId = id;
  _talkBackKey = key;
}

// Sets the ThingTweet API KEY

void ThingSpeak::setThingTweet(String key)
{
  _thingTweetKey = key;
}

// Adds a custom field name (order is important!)
// A max of 8 field names can be defined

void ThingSpeak::addField(String name)
{
  // Save the field name and increment the total count
  _fields[_fieldCount++] = name;
}

// Sets a field value

void ThingSpeak::setField(int field, int value)
{
  // Overload
  setField(field, String(value));
}

void ThingSpeak::setField(int field, long value)
{
  // Overload
  setField(field, String(value));
}

void ThingSpeak::setField(int field, double value)
{
  // Overload
  setField(field, String(value));
}

void ThingSpeak::setField(int field, String value)
{
  // Bypass the field name lookup
  _setField("field" + String(field), value);
}

void ThingSpeak::setField(String name, int value)
{
  // Overload
  setField(name, String(value));
}

void ThingSpeak::setField(String name, long value)
{
  // Overload
  setField(name, String(value));
}

void ThingSpeak::setField(String name, double value)
{
  // Overload
  setField(name, String(value));
}

void ThingSpeak::setField(String name, String value)
{
  // Try to resolve the field name
  for (int index = 0; index < _fieldCount; index++) {
    if (_fields[index] == name) {
      name = "field" + String(index + 1);
      break;
    }
  }

  _setField(name, value);
}

void ThingSpeak::_setField(String field, String value)
{
  String entry = field + "=" + value;

  // Build a query string
  if (_values.length() == 0) {
    _values = entry;
  } else {
    _values += "&" + entry;
  }
}

// Updates a Channel using the current field values

void ThingSpeak::update()
{
  String location = "/update";
  String data = _values + "&api_key=" + _channelKey;

  // Reset the field values
  _values = "";

  _send(location, data);
}

// Executes the next TalkBack command

String ThingSpeak::nextCommand()
{
  String location = "/talkbacks/" + _talkBackId + "/commands/execute";
  String data = "api_key=" + _talkBackKey;

  return _send(location, data);
}

// Sends a new TalkBack command

void ThingSpeak::addCommand(String command)
{
  String location = "/talkbacks/" + _talkBackId + "/commands";
  String data = "api_key=" + _talkBackKey + "&command_string=" + command;

  _send(location, data);
}

// Tweets a new status update

void ThingSpeak::tweet(String status)
{
  String location = "/apps/thingtweet/1/statuses/update";
  String data = "api_key=" + _thingTweetKey + "&status=" + status;

  _send(location, data);
}

// Makes a new POST request to ThingSpeak

String ThingSpeak::_send(String location, String data)
{
  String response = "";
  EthernetClient client;

  if (client.connect(_address.c_str(), 80)) {
    // Send a post request with form data
    client.println("POST " + location + " HTTP/1.1");
    client.println("Host: " + _address);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(data.length()));

    client.println();
    client.print(data);

    // Skip the response headers
    for (char prev, curr; client.connected();) {
      if (client.available()) {
        // Ignore carriage returns
        if (curr != '\r') prev = curr;
        curr = client.read();

        // The header ends with two new lines
        if (prev == '\n' && curr == '\n') break;
      }
    }

    // Save the response content
    while (client.connected()) {
      if (client.available()) {
        response += (char) client.read();
      }
    }

    client.stop();
  }

  return response;
}

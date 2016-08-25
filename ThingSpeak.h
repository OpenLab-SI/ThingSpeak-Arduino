#ifndef ThingSpeak_h
#define ThingSpeak_h

#include "Arduino.h"
#include "SPI.h"
#include "Ethernet.h"

class ThingSpeak
{
  public:
    ThingSpeak();
    ThingSpeak(String address);

    void setChannel(String key);
    void setTalkBack(int id, String key);
    void setTalkBack(String id, String key);
    void setThingTweet(String key);

    void addField(String name);

    void setField(int field, int value);
    void setField(int field, long value);
    void setField(int field, double value);
    void setField(int field, String value);

    void setField(String name, int value);
    void setField(String name, long value);
    void setField(String name, double value);
    void setField(String name, String value);

    void _setField(String field, String value);

    void update();

    String nextCommand();
    void addCommand(String command);

    void tweet(String status);

  private:
    String _address;

    int _fieldCount;
    String _fields[8];

    String _values;

    String _channelKey;
    String _talkBackId;
    String _talkBackKey;
    String _thingTweetKey;

    String _send(String location, String data);
};

#endif

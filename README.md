# ThingSpeak

Library for easy communication with ThingSpeak servers.

## Features

  - Channels
    - Updating channels
  - TalkBack
    - Executing the next command

## API

### Constructor

```cpp
ThingSpeak client();
```

Creates a new ThingSpeak instance using the default API endpoints.

```cpp
ThingSpeak client(String address);
```

Creates a new ThingSpeak instance using a custom address.

### setChannel

```cpp
client.setChannel(String key);
```

Sets the channel API key.

### setTalkBack

```cpp
client.setTalkBack(int id, String key);
```

```cpp
client.setTalkBack(String id, String key);
```

Sets the TalkBack ID and API key.

### addField

```cpp
client.addField(String name);
```

Assigns a name to the next field. These names can then be used when setting
a field value.

A maximum of 8 fields are supported. The first name added will map to `field1`,
the next to `field2`... up to `field8`.

### setField

```cpp
client.setField(int field, any value);
```

Sets a field value for the next update. The field can be any number from
`1` to `8`.

```cpp
client.setField(String name, any value);
```

Sets a field value for the next update. The field name can be any added field
name or anything from `field1` to `field8`.

### update

```cpp
client.update();
```

Updates the channel using the current values.

### nextCommand

```cpp
String command = client.nextCommand();
```

Fetches/executes the next TalkBack command.

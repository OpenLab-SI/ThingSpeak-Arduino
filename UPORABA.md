# ThingSpeak

Knjižnica za enostavno komunikacijo s ThingSpeak strežniki.

## Zmogljivosti

  - Kanali
    - Posodabljanje kanalov
  - TalkBack
    - Izvajanje naslednjega ukaza

## Vmesnik

### Konstruktor

```cpp
ThingSpeak klient();
```

Ustvari novo ThingSpeak instacno s privzetimi naslovi.

```cpp
ThingSpeak klient(String naslov);
```

Ustvari novo ThingSpeak instacno s poljubnim naslovom.

### setChannel

```cpp
klient.setChannel(String kljuc);
```

Nastavi API ključ kanala.

### setTalkBack

```cpp
klient.setTalkBack(int id, String kljuc);
```

```cpp
klient.setTalkBack(String id, String kljuc);
```

Nastavi ID in API ključ TalkBack-a.

### setThingTweet

```cpp
klient.setThingTweet(String kljuc);
```

Nastavi API ključ za ThingTweet.

### addField

```cpp
klient.addField(String ime);
```

Nastavi ime naslednjega polja. Ta imena se lahko uporabi ob nastavljanju
vrednosti nekega polja.

Podprtih je do 8 polj. Prvo ime je dodoljeno polju `field1`, itd. vse do
polja `field8`.

### setField

```cpp
klient.setField(int polje, any vrednost);
```

Nastavi vrednost polja za naslednjo posodobitev. Polje je lahko poljubno
število med `1` in `8`.


```cpp
klient.setField(String ime, any vrednost);
```

Nastavi vrednost polja za naslednjo posodobitev. Ime polja je lahko katerokoli
dodano polje oz. eno izmed polj med `field1` in `field8`.

### update

```cpp
klient.update();
```

Posodobi kanal s trenutnimi vrednostmi.

### nextCommand

```cpp
String ukaz = klient.nextCommand();
```

Prenese oz. izvede naslednji TalkBack ukaz.

### addCommand

```cpp
klient.addCommand(String ukaz);
```

Pošlje oz. doda nov TalkBack ukaz.

### tweet

```cpp
klient.tweet(String status);
```

Objavi novo stanje na Twitterju.

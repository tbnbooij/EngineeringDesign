Oké, dit is een testscript voor de communicatie.

[Script openen]
1. Extract deze .zip
2. Open LEDTest.ino (in /LEDTest)

[Library importeren]
3. Klik op Sketch > Include library > Add .ZIP library
4. Kies Regexp.zip in deze map
5. Linksboven zijn er twee ronde knoppen. Klik op de eerste (het vinkje). 
   Als je geen errormeldingen krijgt, heb je de library goed geïmporteerd.

[Board setup]
6. Klik op Tools > Board > "Arduino Yún"
7. Klik op Tools > Port > COM X (weet het nummer nu niet)
   Zorg ervoor dat de Arduino is aangesloten!!! Anders is deze knop niet bruikbaar.
8. Klik op Tools > Programmer > "AVR ISP"

[Uploaden]
9. Nu zou alles klaar moeten zijn om te uploaden naar de Arduino. Klik op de pijl-knop
   naast het vinkje waar je bij stap 5 hebt geklikt. Nu gaat de IDE het programma compilen
   en uploaden naar de Arduino.

[Testen via serial]
10. Als het uploaden klaar is, kun je op het vergrootglas in de rechterbovenhoek klikken.
    ("Serial Monitor")
11. Zorg ervoor dat je in de dropdown-balk waarin gewoonlijk "9600 baud" staat "115200 baud"
    wordt gekozen.
    (afbeelding: https://cdn.instructables.com/FR2/1V4Y/HU7GE879/FR21V4YHU7GE879.MEDIUM.jpg)
12. Nu heb je een directe serial-communicatie met de Arduino! Tik in de inputbalk het volgende
    commando: #l@0@0! (LED OFF) of #l@1@0! (LED ON). Als de Arduino het commando begrijpt
    zal hij een message in de serial monitor printen ("Turned LED ON" of "Turned LED OFF")
    en de interne LED respectievelijk aan of uit gaan.

Als de communicatie werkt voor de LED zal hij ook werken voor de rest van de actuators.

# MiniSerre

In dit project delen we de Arduinocode en een beschrijving hoe je met een Arduino Uno, temperatuursensor (DS18b20) en een mini servo een miniserre kan besturen.  
Deze miniserre kan men binnen voor een raam in het zonlicht plaatsen.  Bij een bepaalde temperatuur (instelbaar in code) zal de miniserre bovenaan geopend worden met de mini servo.

Als uitbreiding kan je ook een LCD 1602 met I2C module aansluiten, zodat je de temperatuur en de hoek van de servo kan controlleren.

[![Filmje MiniSerre](https://img.youtube.com/vi/UeEgPPbJhDw/0.jpg)](https://youtu.be/UeEgPPbJhDw)



## Aansluiting zonder LCD
![MiniSerre](https://github.com/moeskopsjan/MiniSerre/blob/main/ArduinoUnoTempSensServo.PNG)

## Aansluiting met LCD
![MiniSerreMetLCD](https://github.com/moeskopsjan/MiniSerre/blob/main/ArduinoUnoTempSensServoLCD_labels.PNG)


## Libraries
De Arduinocode gebaseerd is op de voorbeeldprogramma's die bij de libraries inbegrepen zit.
#### De Temperatuursensor DS18B20
* OneWire
* DallasTemperature (van Miles Burton, Tim Newsome, Guil Barros, Rob Tillaart)

#### LCD-I2C
* wire  (is standaard aanwezig in Arduino IDE)
* LiquidCrystal_I2C  (van Frank de Brabander)

#### Servo
Deze is standaard aanwezig in Arduino IDE


## Temperatuur of hoek aanpassen
In de code kan je de temperatuur of hoek aanpassen, na het map commando

`waarde = map(temperatuur,19,30,90,170); `

In dit voorbeeld zie je de min. en max. inputwaarde voor temperatuur  (van 19 tot 30°C). 
De waarde wordt gemapt naar min. en max. outputwaarde voor de hoek van de servo (van 90 tot 170°)

/*  Jan Moeskops - mei 2021

Project Miniserre
Benodigdheden:  Arduino Uno, Temperatuursensor DS18b20, mini servo SG 90, LCD 1602 met I2C module
                MiniSerre, gemaakt met doorzichtige CD-doosjes

Meer info op https://github.com/moeskopsjan/MiniSerre

De temperatuur wordt getoond op de LCD. 
Aan de hand van deze temperatuur wordt het dak van de miniserre meer of minder geopend.
De informatie (hoek en temperatuur) wordt zowel op de LCD als in de seriële monintor getoond

Aansluitingen:  

 Standaard LCD:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)


  Temperatuursensor:  is in TinkerCAD vervangen door een LDR in serie met weerstand van 5K Ohm
  
  Servomotor:  voeding:  5Volt (rode draad) en GND (bruine draad bij sommige servo's) aansluiten 
               PWM data via pin D9  
         

*/

// Volgende libraries zijn reeds aanwezig:
#include <Servo.h>
#include <LiquidCrystal.h>

// Volgende libraries dienen geïnstalleerd te worden:


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo myservo;  // create servo object to control a servo  (zie voorbeeldprogramma in Arduino IDE - servo - sweep
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

const int ServoPin = 9;  // hier bepaal je met welke digitale pin aansluiting de servo aangestuurd wordt.  


// Maak het character voor graden symbool ° :
byte graden[8] = {
  0b01000,
  0b10100,
  0b01000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
int temperatuur;     // globale variabele aanmaken
int waarde;

// ------------------------- SchrijfMachine effect ----------------------------
void SchrijfMachine(char* text)
{ 
  char *msgptr = text;
  lcd.setCursor(0,0);
  while (*msgptr) 
  {
   lcd.write(*msgptr++);   //deze tekst op LCD
   delay(300);  
  }
}



// ----------------------------------- S E T U P -----------------------------------------------------
void setup()
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  lcd.begin(16, 2);          // de grootte van het scherm: 16 characters over 2 lijnen
  lcd.createChar(0, graden);   //Zet character graden klaar voor LCD
  //lcd.setCursor(3,0);          //Zet cursor op 5e plaats op 1e lijn (voor machine's is dit lijn 0)
  //lcd.print("Miniserre");      //Print deze tekst
  SchrijfMachine("...Miniserre...");   //Toon de tekst character voor character op de LCD
  delay(2000);  // 2 seconden om de titel op het scherm te houden
  lcd.clear();     // maak LCD leeg
  myservo.attach(ServoPin);  
    
}

// ------------------------------------ L O O P ------------------------------------------------------
void loop()
{ 
  temperatuur= map(analogRead(A0),0,1023,18,30);
  Serial.print("Temperature simulatie van A0:");
  Serial.println(temperatuur);                   // print waarde in seriële monitor als integer (geheel getal)
  lcd.setCursor(3,0);
  lcd.print("T=");
  lcd.print(temperatuur);
  lcd.write(byte(0));
  lcd.print("C");
  lcd.print("  "); // Indien het getal groter dan 100 wordt (5 getallen: 100.00) en terug naar 99 spring(99.00) dan wordt het laatste character gewist
  lcd.setCursor(0,1);
  lcd.print("Hoek servo=");

  // In de volgende lijn map je de temperatuur, begin waarde temp, eind waarde temp, begin waarde hoek, eind waarde hoek
  //   Zoals in dit voorbeeld  de waarde van de temperatuur tussen 19°c en 30°C wordt gemapt naar een hoek tussen 90 en 170°
  //   waarde = map(temperatuur,19,30,90,170);           
  waarde = map(temperatuur,18,30,90,170);           
  lcd.print(waarde);                   // toon de waarde op LCD
  lcd.write(byte(0));
  lcd.print("  ");
  myservo.write(waarde);              // tell servo to go to position in variable 'pos'
  delay(30); 
  Serial.print("hoek = ");            // toon hoek en waarde in de seriële monitor 
  Serial.println(waarde); 
  
}

/*  Jan Moeskops - mei 2021

Project Miniserre
Benodigdheden:  Arduino Uno, Temperatuursensor DS18b20, mini servo SG 90, LCD 1602 met I2C module

Meer info op https://github.com/moeskopsjan/MiniSerre

Aansluitingen:  
  LCD-I2C  voeding 5 Volt en Grond
           SCL (Serial Clock) op Analog pin 5  (A5)
		   SDA (Serial Data) op Analog pin 4  (A4)
  Temperatuursensor:  voeding en grond
                      datapin met pullup weerstand van 4k7 Ohm verbinden met digitale pin 2  (D2)
  Servomotor:  voeding:  5Volt (rode draad) en GND (bruine draad bij sommige servo's) aansluiten 
               PWM data via pin D9  
			   

*/

// Volgende libraries dienen geïnstalleerd te worden:
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo  (zie voorbeeldprogramma in Arduino IDE - servo - sweep
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position



// In volgende lijn wordt het adres 0x27 of 0x3F, alsook de grootte van het LCD ingesteld 16 characters over 2 lijnen
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Dataverbinding temperatuur sensor wordt verbonden met D2 op Arduino Uno
#define ONE_WIRE_BUS 2


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Maak het character voor graden :
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
int temperatuur;
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
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  lcd.begin();
  lcd.createChar(0, graden);   //Zet character graden klaar voor LCD
  //lcd.setCursor(3,0);          //Zet cursor op 5e plaats op 1e lijn (voor machine's is dit lijn 0)
  //lcd.print("Miniserre");      //Print deze tekst
  SchrijfMachine("...Miniserre...");
  delay(2000);  // 2 seconden om de titel op het scherm te houden
  lcd.clear();
  sensors.begin();
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  // Start up the library
  
}

// ------------------------------------ L O O P ------------------------------------------------------
void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  temperatuur= sensors.getTempCByIndex(0);
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));    //print waarde als floating point
  Serial.println(temperatuur);                   // print waarde als integer
  lcd.setCursor(3,0);
  lcd.print("T=");
  
  //lcd.print(temperatuur);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.write(0);
  lcd.print("C");
  lcd.print("  "); // Indien het getal groter dan 100 wordt (5 getallen: 100.00) en terug naar 99 spring(99.00) dan wordt het laatste character gewist
  lcd.setCursor(0,1);
  lcd.print("Hoek servo=");
  waarde = map(temperatuur,19,30,90,170);
  lcd.print(waarde);
  lcd.write(0);
  lcd.print("  ");
  myservo.write(waarde);              // tell servo to go to position in variable 'pos'
  delay(30); 
  
}

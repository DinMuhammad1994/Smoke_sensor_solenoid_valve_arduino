#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


int thershold = 60;

int smokesensor = A0;
int smokevalue; 
int fan = 3;
int gasvalve = 2;
int buzz = 9;


void setup() {
  Serial.begin(9600);  // Initialize serial
  Serial.print("Code Start");
  Wire.begin();
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  delay(100);
  lcd.clear();
  lcd.print("Device On..");
  delay(2000);
  pinMode(smokesensor, INPUT);
  pinMode(fan, OUTPUT);
  pinMode(gasvalve, OUTPUT);
  pinMode(buzz, OUTPUT);
  
  digitalWrite(fan, HIGH);
  digitalWrite(gasvalve, HIGH);
  digitalWrite(buzz, LOW);
 lcd.clear();
lcd.print("Calibrating");
delay(10000);

 

}

void loop() {

 
smokevalue = analogRead(smokesensor);
Serial.print("Gas Value adc "); Serial.println(smokevalue);
smokevalue = map(smokevalue, 0, 1024, 0, 100);
Serial.print("Smoke Sensor value : "); Serial.println(smokevalue);
lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("GAS sensor %: "); lcd.print(smokevalue);
 delay(1000);
if (smokevalue >  thershold)
{
  lcd.setCursor(0,1);
  lcd.print("FAN:ON|VALVE:OFF"); 
  digitalWrite(gasvalve, LOW); // gas valve off
  delay(1000);
  digitalWrite(fan, LOW); // fan on
  digitalWrite(buzz, HIGH);
  delay(10000);
  digitalWrite(buzz, LOW);
  delay(5000);

}
else 
{
  lcd.setCursor(0,1);
  lcd.print("FAN:OFF|VALVE:ON");
  digitalWrite(fan, HIGH); //  fan  off
  delay(1000);
  digitalWrite(gasvalve, HIGH); // gasvalve on
  digitalWrite(buzz, HIGH);
  delay(10);
  digitalWrite(buzz, LOW);
}

delay(500);
 
}

#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,6,7,8,9,10,11,12,13);

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);

  lcd.print("Ola Mundo");
  delay(1000);
}

void loop(){
  
}


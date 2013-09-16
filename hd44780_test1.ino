#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd sheild kit http://www.switch-science.com/catalog/724/
uint32_t last_t;

void setup() {
  lcd.begin(16, 2);  
  last_t = micros();
}

void loop() {
  uint32_t now_t = micros();
  uint32_t diff = now_t - last_t; // approximately 9.6 milliseconds
  
  lcd.setCursor(0, 0);
  lcd.print("HD44780 test");

  lcd.setCursor(0, 1);
  lcd.print(diff);

  lcd.setCursor(7, 1);
  lcd.print("micro sec");

  last_t = now_t;
}


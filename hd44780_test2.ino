#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd sheild kit http://www.switch-science.com/catalog/724/
uint32_t last_t;

unsigned char c;

void setup() {
  lcd.begin(16, 2);  
  last_t = micros();
  c = 0;
}

void loop() {
  char str0[16];
  memset(str0, 0, 16);
  snprintf(str0, 15, "c=0x%02x", c);

  char str1[2];
  str1[0] = c;
  str1[1] = 0;

  lcd.setCursor(0, 0);
  lcd.print(str0);

  lcd.setCursor(0, 1);
  lcd.print(str1);

  delay(300);
  c ++;
}


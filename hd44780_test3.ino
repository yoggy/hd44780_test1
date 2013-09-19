#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

unsigned char val = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  lcd.begin(16, 2);  
  setup_barchart();
}

void loop() {
  char str[17];
  snprintf(str, 16, "val=%3d", val);
  lcd.setCursor(0, 0);
  lcd.print(str);

  draw_barchart(val, 0, 1, 16);

  val ++;
  if (val > 100) {
    val = 0;
  }
  
  delay(30);
}

void setup_barchart() {
  // create original font (0x01-0x06)
  int n, i;
  byte l;
  byte font[8];  
  for (int n = 0; n < 6; ++n) {
    l = 0x00;
    for (i = 0; i < n; ++i) {
      l = l | (0x01 << (4-i));
    }

    for (i = 0; i < 8; ++i) {
      font[i] = l;
    }
    lcd.createChar(n+1, font);
  }
}

void draw_barchart(int val, int x, int y, int l) {
  char bar_str[17];
  memset(bar_str, 0x20, 16);
  bar_str[16] = 0;
  float unit = 100 / l;

  if (val < 0) val = 0;
  if (val > 100) val = 100;

  int n0 = val / unit;

  for (int i = 0; i < n0; ++i) {
    bar_str[i] = 0x06;
  }
  if (n0 < l) {
    float d = val - n0 * unit;
    float p = d / unit;
    char c = (p * 5) + 1;
    bar_str[n0] = c;
  }

  lcd.setCursor(x, y);
  lcd.print(bar_str);
}

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensor_pin = 0;
int volume_pin = 1;

int led_pin = 13;

void setup() {
  pinMode(led_pin, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {
  }

  lcd.begin(16, 2);  
  setup_barchart();
}

void loop() {
  int sensor_val = read_analog_avg(sensor_pin);
  int volume_val = read_analog_avg(volume_pin);
  
  char str[17];
  snprintf(str, 16, "val=%3d,thr=%3d", sensor_val, volume_val);
  lcd.setCursor(0, 0);
  lcd.print(str);

  draw_barchart(sensor_val/10, 0, 1, 16);

  if (sensor_val > volume_val) {
    digitalWrite(led_pin, HIGH);
  }
  else {
    digitalWrite(led_pin, LOW);
  }

  delay(30);
}

int read_analog_avg(int pin) {
  int32_t total = 0;
  int avg = 0;
  int read_count = 5;

  for (int i = 0; i < read_count; ++i) {
    int val = analogRead(pin);
    total += val;
  }
  avg = total / read_count;

  return avg;
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

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensor_pin = 0;
int volume_pin = 1;

int led_pin = 13;

void setup() {
  pinMode(led_pin, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {
  }

  lcd.begin(16, 2);  
  setup_barchart();
}

void loop() {
  int sensor_val = read_analog_avg(sensor_pin);
  int volume_val = read_analog_avg(volume_pin);
  volume_val = volume_val * 2; // resistor divider

  char str[17];
  snprintf(str, 16, "val=%3d,thr=%3d", sensor_val, volume_val);
  lcd.setCursor(0, 0);
  lcd.print(str);

  draw_barchart(sensor_val/10, 0, 1, 16);

  if (sensor_val > volume_val) {
    digitalWrite(led_pin, HIGH);
  }
  else {
    digitalWrite(led_pin, LOW);
  }

  delay(30);
}

int read_analog_avg(int pin) {
  int32_t total = 0;
  int avg = 0;
  int read_count = 5;

  for (int i = 0; i < read_count; ++i) {
    int val = analogRead(pin);
    total += val;
  }
  avg = total / read_count;

  return avg;
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


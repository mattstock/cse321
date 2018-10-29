#include <Wire.h>

char x = 'A';

/* Very simple I2C master that sends a few bytes of data. */

void setup() {
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(8);
  Wire.write('C');
  Wire.write(x);
  Wire.endTransmission();
  x = (x == 'Z' ? 'A' : x + 1);
  delay(1000);
}

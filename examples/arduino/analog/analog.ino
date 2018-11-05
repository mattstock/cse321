#include <Wire.h>

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  analogReadResolution(12); // default is 10, but we can do 12
}

void printNum(uint16_t x) {
  char buf[5];
  int i=0;
  
  while (x > 0) {
    buf[i++] = '0' + (x % 10);
    x = x / 10;  
  }

  Wire.beginTransmission(0x72);
  while (i > 0) {
    Wire.write(buf[i-1]);
    delay(10);
    i--;
  }
  Wire.endTransmission();
}

void loop() {
  uint16_t x = analogRead(A1);
  Wire.beginTransmission(0x72);
  Wire.write('|');
  Wire.write('-');
  Wire.endTransmission();
  printNum(x);
  Wire.beginTransmission(0x72);
  Wire.print("            ");
  delay(10);
  Wire.endTransmission();  
  float v = 3300*x/(4*1024);
  printNum((int)v);

  delay(2000);
}

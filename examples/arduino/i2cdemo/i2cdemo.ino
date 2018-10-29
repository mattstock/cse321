#include <Wire.h>
#include <SPI.h>

#define CS 10

/* Listens for a message from the I2C bus, and then retransmits it as the SPI master
 * to the SPI LCD device.
 */

volatile char buffer[10];
volatile int msg = 0;

void clearLCD() { 
  digitalWrite(CS, LOW);
  SPI.transfer('|');
  delay(10);
  SPI.transfer('-');
  delay(10);
  digitalWrite(CS, HIGH);
}

void setup() {
  Wire.begin(8); // listen as device 8 on the bus
  Wire.onReceive(i2cReceive);  // set interrupt handler
  pinMode(CS, OUTPUT); // define the slave select for SPI
  digitalWrite(CS, HIGH); // and disable the device initially
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  clearLCD();
}

/* The Arduino version of an ISR. */
void i2cReceive(int cnt) {
  int l = 0;
  while (cnt != 0) {
    char c = Wire.read();
    buffer[l++] = c;
    cnt--;
  }
  buffer[l] = '\0';
  msg = 1;
}

/* Print a null-terminated string to the LCD */
void printLCD(char *s) {
  digitalWrite(CS, LOW);
  while (*s != '\0') {
    SPI.transfer(*s++);
    delay(10);
  }
  digitalWrite(CS, HIGH);
}

void loop() {
  if (msg) {
    clearLCD();
    printLCD((char *)buffer);
    msg = 0;
  }
  delay(250);
}

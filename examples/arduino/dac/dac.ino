uint16_t sinvals[36];

void makeSinTable() {
  for (int i=0; i < 36; i++)
    sinvals[i] = (uint16_t)(512*sin((i*10*3.14159)/180)+512);
}

void setup() {
  makeSinTable(); 
  analogWriteResolution(10); // probably not needed, but whatever
}

int i=0;
void loop() {
  analogWrite(A0, sinvals[i]);
  i = (i+1)%36;
}

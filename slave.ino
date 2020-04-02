#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4,5);
int motion = 2;

void setup() {
  pinMode(motion, INPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  int sensor = digitalRead(motion);
  if (sensor == HIGH) {
    BTSerial.write("O");
    Serial.write("O\n");
  }
}

//if(BTSerial.available())
//Serial.write(BTSerial.read());

//if(Serial.available())
//BTSerial.write(Serial.read());

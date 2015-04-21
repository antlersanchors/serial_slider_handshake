#include <spi4teensy3.h>
#include<EEPROM.h>
#include<M3T3.h>

float k = 10.0f;
float m = 2.0f;
float d = 0.0f;

float x;
float v;
float f;

long tick = 0;
int last_pos = 0;
int c = 0;
int val;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  MotorA.init();
  tick = millis();
  last_pos = analogRead(A1);

  establishContact();
}

void loop() {
  // put your main code here, to run repeatedly:

  long tick_now = millis();
  float dt = (float) (tick_now - tick) / 100.0f;
  int current_pos = analogRead(A1);
  int dx = last_pos - current_pos;

  f = k * (dx - x) - (d * v);
  v += (f / m) * dt;
  x += v * dt;

  if (Serial.available() > 0) {
      
      Serial.read(); // think this was critical; println doesn't clear the buffer, but this does
      Serial.println(f, BYTE);
   }

  MotorA.torque(f);
  tick = millis();
  last_pos = current_pos;

}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("Hello");   // send an initial string
    delay(300);
  }
}

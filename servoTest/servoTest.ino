#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MAX_ANGLE  430 // This is the 'maximum' pulse length count (out of 4096)
#define MIN_ANGLE  184 // This is the 'minimum' pulse length count (out of 4096)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int pos = MIN_ANGLE;
bool direction = true;


void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  delay(10);
}



void loop() {
  // pos = Serial.parseInt();
  pwm.setPWM(8, 0, pos);
  pos = direction ? pos + 1 : pos - 1;
  direction ^= pos == MIN_ANGLE || pos == MAX_ANGLE;
  delay(15);
}



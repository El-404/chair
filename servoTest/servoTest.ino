#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MAX_HORIZONTAL_ANGLE  550 // pulse lengths
#define MIN_HORIZONTAL_ANGLE  160

#define MAX_VERTICAL_ANGLE 420
#define MIN_VERTICAL_ANGLE 270

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
float pos = 0;
bool direction = true;


void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  pinMode(13, OUTPUT);

  delay(10);
}



void loop() {
  if(Serial.available()){
    digitalWrite(13, HIGH);  
    delay(100);                      
    digitalWrite(13, LOW);  
    delay(100); 
    pos = Serial.parseFloat();
  }

  pwm.setPWM(8, 0, pos * (MAX_VERTICAL_ANGLE - MIN_VERTICAL_ANGLE) + MIN_VERTICAL_ANGLE);
  pwm.setPWM(0, 0, pos * (MAX_HORIZONTAL_ANGLE - MIN_HORIZONTAL_ANGLE) + MIN_HORIZONTAL_ANGLE);

  // pos += direction ? 0.01 : -0.01;
  // direction ^= pos <= 0 || pos >= 1;

  delay(25);

  Serial.println(pos);
}



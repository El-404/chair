#include <Wire.h>
//required library for the servo board I am using (makes setting the servo angles weird)
#include <Adafruit_PWMServoDriver.h>

//different pulse widths that the servos have
//I want to combine these into a servoInterval class or set of numbers - I'll figure that out later, this works for now
#define MAX_HORIZONTAL_ANGLE  550
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
  // flash an led on port 13 when data is recieved
  // also sets the pos element to whatever data was recieved
  // [In the future I will create a way to move all the servos at different times]  
  if(Serial.available()){
    digitalWrite(13, HIGH);  
    delay(100);                      
    digitalWrite(13, LOW);  
    delay(100); 
    pos = Serial.parseFloat();
  }

  //sets the (port, idk what 0 does, and the pulse length that it should go to)
  //pos * (max-min) + min -->> maps inputs on the interval [0,1] to the interval [min,max]
  pwm.setPWM(8, 0, pos * (MAX_VERTICAL_ANGLE - MIN_VERTICAL_ANGLE) + MIN_VERTICAL_ANGLE);
  pwm.setPWM(0, 0, pos * (MAX_HORIZONTAL_ANGLE - MIN_HORIZONTAL_ANGLE) + MIN_HORIZONTAL_ANGLE);

  //oscillates the servos between the min and max angles
  
  // pos += direction ? 0.01 : -0.01;
  // direction ^= pos <= 0 || pos >= 1;

  delay(25);

  //debugging
  Serial.println(pos);
}



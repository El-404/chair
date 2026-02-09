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
double posy = 0;
double posx = 0;
bool direction = true;


void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  pinMode(13, OUTPUT);

  delay(10);
}

int a = 0;

void loop() {
  if(Serial.available()){
    String temp = Serial.readString();
    
    if(temp.charAt(0) == 'x') {
      posx = temp.substring(1).toFloat();
    }

    if(temp.charAt(0) == 'y') {
      posy = temp.substring(1).toFloat();
    }

    Serial.print(posx); Serial.print("     "); Serial.print(posy);
  }

  //sets the (port, idk what 0 does, and the pulse length that it should go to)
  //pos * (max-min) + min -->> maps inputs on the interval [0,1] to the interval [min,max]
  pwm.setPWM(8, 0, posy * (MAX_VERTICAL_ANGLE - MIN_VERTICAL_ANGLE) + MIN_VERTICAL_ANGLE);
  pwm.setPWM(0, 0, posx * (MAX_HORIZONTAL_ANGLE - MIN_HORIZONTAL_ANGLE) + MIN_HORIZONTAL_ANGLE);

  //oscillates the servos between the min and max angles
  
  // pos += direction ? 0.01 : -0.01;
  // direction ^= pos <= 0 || pos >= 1;

  //delay(25);

  //debugging
  // Serial.print(posx); Serial.print(" --- "); Serial.println(posy);
}



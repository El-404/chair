#include "el.h"
#include <algorithm>

class Drivetrain {
private:
    void leftMotor(double speed) {

    }
    void rightMotor(double speed) {

    }
    
public:
    void drive(double driveSpeed, double rotationSpeed) {
        driveSpeed = std::clamp(driveSpeed, -1.0, 1.0);
        rotationSpeed = std::clamp(rotationSpeed, -1.0, 1.0);

        double maximum = std::max(std::abs(driveSpeed), std::abs(rotationSpeed));
        double total = driveSpeed + rotationSpeed;
        double difference =  driveSpeed - rotationSpeed;

        if (driveSpeed >= 0) {
            if (rotationSpeed >= 0) { 
                leftMotor(maximum);
                rightMotor(difference);
            } else {
                leftMotor(total);
                rightMotor(maximum);
            }
        } else {
            if (rotationSpeed >= 0){  
                leftMotor(total);
                rightMotor(-maximum);
            } else {            
                leftMotor(-maximum);
                rightMotor(difference);
            }
        }
    }
}
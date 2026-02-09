#include <LeapC.h>
#include "el.h"
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <cmath>
#include <unistd.h>


#define BUADRATE 9600
#define PORT "/dev/ttyACM0"

LEAP_CONNECTION connectionHandle;
LEAP_CONNECTION_MESSAGE msg;

int fd = -1;
struct termios config;

float masterYaw = 0;
float masterRot = 0;
bool running = true;


//compilation command
//g++ main.cpp $(find src -name "*.cc") -o chair -I include -L /usr/lib/ultraleap-hand-tracking-service/ -lLeapC 
//may have to run:
//export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

//https://github.com/hollanderski/EEG-StarWars?tab=readme-ov-file
//link for the brainwave reader

//https://github.com/hollanderski/EEG-StarWars?tab=readme-ov-file
//link for the brainwave reader

LEAP_HAND getHand(LEAP_CONNECTION_MESSAGE message) {
    LEAP_HAND *pHands = message.tracking_event->pHands;
    LEAP_HAND best = pHands[0];

    for(int i = 0; i < sizeof(pHands); i++) {
        if(best.visible_time >= pHands[i].visible_time) {
            continue;
        }

        best = pHands[i];
    }

    return best;
}

int main() {
    if(el::serialStart(&fd, &config) == -1) {
        return -1;
    }


    eLeapRS result = LeapCreateConnection(NULL, &connectionHandle);
    if(result != eLeapRS_Success) {
        std::cout << "Failed to create the connection";
        return -1;
    }

    result = LeapOpenConnection(connectionHandle);
    if(result != eLeapRS_Success) {
        std::cout << "Failed to open the connection";
        return -1;
    }

    std::cout << controller.isConnected() << std::endl;
    controller.setPolicy(Controller::POLICY_BACKGROUND_FRAMES);



    while (running) {
        recentFrame = controller.frame(0);
        hands = recentFrame.hands();
        std::cout << "num of hands: " << hands.count() << std::endl;


        Hand hand = getHand(recentFrame);
        double rotation = atan(hand.direction().z / hand.direction().x ) * 180 / M_PI;
        rotation = rotation < 0 ? rotation + 180 : rotation;

        bool closed = hand.grabStrength() > 0.25;
        

        printf("rot: %f --- closed: %d --- yaw: %f\n",
            rotation,
            closed,
            hand.direction().y * 90
        );
    }

    controller.removeListener(listener);
}

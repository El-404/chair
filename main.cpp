#include <LeapC.h>
#include "el.h"
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <cmath>
#include <unistd.h>
#include <cstring>


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
//g++ main.cpp $(find src -name "*.cc") $(find include -name "*.cpp") -o chair -I include -L /usr/lib/ultraleap-hand-tracking-service/ -lLeapC;./chair 
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
    // if(el::serialStart(&fd, &config) == -1) {
        // return -1;
    // }


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

    LEAP_CONNECTION_MESSAGE msg;


    while(running) {
        result = LeapPollConnection(connectionHandle, 0, &msg);
        if(result != eLeapRS_Success || msg.tracking_event->nHands < 1) {
            continue;
        }

        float rot = (msg.tracking_event->pHands->palm.direction.x + 1) / 2; //bound between 0->1 (not -1->1)
        bool closed = msg.tracking_event->pHands->grab_strength > 0.25;
        float yaw = (msg.tracking_event->pHands->palm.direction.y + 1) / 2;


        std::cout << std::to_string(std::abs(yaw)) + "y" + std::to_string(rot) + "x" << std::endl;

        if(std::abs(yaw - masterYaw) > 0.1 || std::abs(rot - masterRot) > 0.1) {
            masterYaw = yaw;
            masterRot = rot;    
            
            //uint8_t data[] = {
            //    static_cast<uint8_t>( std::max(std::min(yaw, 1.0f), 0.0f) * 255.0f ), 
            //    static_cast<uint8_t>( std::max(std::min(rot, 1.0f), 0.0f) * 255.0f ), 
            //};

            // el::serialWrite(&fd, std::to_string(std::abs(yaw)) + "y" + std::to_string(rot) + "x");
        }

    } // while(running)
}
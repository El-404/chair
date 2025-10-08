#include "Leap.h"
#include <iostream>
using namespace Leap;

//compilation command
//clear;g++ main.cpp -o test -I include -L lib/x64 -l Leap  

int main() {
    std::string errorMessage = "";
    Controller controller;
    Listener listener;
    Frame recentFrame;
    
    if(!controller.addListener(listener)) {
        errorMessage = "failed to apply a listener";
        goto err;
    }

    std::cout << controller.isConnected() << std::endl;


    recentFrame = controller.frame(0);

    return 0;

err:
    std::cout << errorMessage << std::endl;
    controller.removeListener(listener);

    return -1;
}

/*
LEAP_HAND getHand(LEAP_CONNECTION_MESSAGE msg) {
    LEAP_HAND mainHand = msg.tracking_event->pHands[0];
    //default

    for(int i = 0; i < msg.tracking_event->nHands; i++) {
        if(msg.tracking_event->pHands[i].visible_time > mainHand.visible_time)
            //if the hand is visible for longer
            mainHand = msg.tracking_event->pHands[i];
            //set it to the one to return/use
    }
    return mainHand;
}


int main() {
    LEAP_CONNECTION connection = NULL;
    eLeapRS result;
    bool running = true;

    result = LeapCreateConnection(NULL, &connection);
    if (result != eLeapRS_Success) {
        printf("Error creating Leap connection\n");
        running = false;
    }
    result = LeapOpenConnection(connection);
    if (result != eLeapRS_Success) {
        printf("Error opening Leap connection\n");
        running = false;
    }



    //start: main loop
    while (running) {
        LEAP_CONNECTION_MESSAGE msg;
        result = LeapPollConnection(connection, 100, &msg);
        //get data
        if (result != eLeapRS_Success || msg.type != eLeapEventType_Tracking || msg.tracking_event->nHands <= 0) 
            continue;
        //don't calculate if something happened or there are no hands to track
        LEAP_HAND mainHand = getHand(msg);
        //end: setup



        double rotation = atan(mainHand.palm.direction.z / mainHand.palm.direction.x ) * 180 / M_PI;
        rotation = rotation < 0 ? rotation + 180 : rotation;

        bool closed = mainHand.grab_strength > 0.25;
        

        printf("rot: %f --- closed: %d --- yaw: %f\n",
            rotation,
            closed,
            mainHand.palm.direction.y * 90
        );
    }

cleanup:
    // Clean up
    LeapCloseConnection(connection);
    LeapDestroyConnection(connection);
    return 0;
}

*/
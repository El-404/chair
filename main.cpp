#include "Leap.h"
#include "el.h"
#include <iostream>
using namespace Leap;

//compilation command
//g++ main.cpp $(find src -name "*.cc") -o chair -I include -L lib/x64 -l Leap  
//
//may have to run:
//export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

Hand getHand(Frame frame) {
    Hand best = frame.hand(0);
    for (int i = 0; i < frame.hands().count(); i++) {
        if (!best.isValid() || best.timeVisible() < frame.hand(i).timeVisible()) 
            best = frame.hand(i);
    }
    
    return best;
}

int main() {
    bool running = true;
    Controller controller;
    Listener listener;
    Frame recentFrame;
    HandList hands;
    
    if(!controller.addListener(listener)) {
        std::cout << "failed to apply a listener" << std::endl;
        controller.removeListener(listener);

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
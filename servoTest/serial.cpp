//command I am using to compile (I am using linux; I forgot to mention that in the email)
// g++ servoTest/serial.cpp $(find src -name "*.cc") -I include -L lib 

#include <string>
#include <iostream>
#include <cstdio>
//now it might be obvious that I am using linux (did I mention this will be on a 32-bit machine ￢_￢)
#include <unistd.h>
//imported from the wjwood library ⌄⌄⌄
#include "serial/serial.h"
//currently holds nothing important ⌄⌄⌄
#include "el.cpp"

#define BUAD 9600
#define PORT "/dev/ttyACM0"

int run(int argc, char **argv) {
  // port, baudrate, timeout in milliseconds
  // I think timeout is just how long it waits after sending a signal and how long its willing to wait to read a signal 
  // idk for sure, I just am using it as a black box
  serial::Serial my_serial(PORT, BUAD, serial::Timeout::simpleTimeout(500));

  // this might be the problem, I haven't tried hard coding it yet.
  my_serial.write(argv[1]);
  
  return 0;
}

// this is what they did in the example, so I just kept it
int main(int argc, char **argv) {
  try {
    return run(argc, argv);
  } catch (std::exception &e) {
    std::cerr << "Unhandled Exception: " << e.what() << std::endl;
  }
}

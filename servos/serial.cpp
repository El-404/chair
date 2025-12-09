//command I am using to compile (I am using linux; I forgot to mention that in the email)
// g++ serial.cpp $(find src -name "*.cc") -I include -L lib -o SerialTest

#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "el.h"

#define BUADRATE 9600
#define PORT "/dev/ttyACM0"

//file destination
int fd = -1;

int run(int argc, char **argv) {
  
  fd = open(PORT, O_WRONLY);


  // Check if the file descriptor is pointing to a TTY device or not.
  if(!isatty(fd)) { 
    return 1;
  }
  if(fd == -1) {
    return 1;
  }

  return 0;
}

// this is what they did in the example, so I just kept it
int main(int argc, char **argv) {
  try {
    return run(argc, argv);
  } catch (std::exception &e) {
    std::cerr << "Unhandled Exception: " << e.what() << std::endl;
  }

  close(fd);
}

//command I am using to compile (I am using linux; I forgot to mention that in the email)
// g++ servos/serial.cpp $(find src -name "*.cc") include/el.cpp -I include -L lib -o SerialTest  

#include <string>
#include <cstring>
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
struct termios config;

int run(int argc, char **argv) {

  fd = open(PORT, O_RDWR);
  if(fd == -1) {
    std::cerr << "Failed to open file: " << PORT;
    return -1;
  }

  if(!isatty(fd)) { 
    std::cerr << "Program did not open a TTY device";
    return -1;
  }

  if(tcgetattr(fd, &config) == -1) {
    std::cerr << "Failed to get attributes";
    return -1;
  }

  if( cfsetispeed(&config, B9600) == -1 || cfsetospeed(&config, B9600) == -1) {
    std::cerr << "Failed to set the buadrate";
    return -1;
  }

  float position = 0.5;
  std::string output = std::to_string(position);

  if(write(fd, &output, sizeof(output)) == -1) {
    std::cerr << "Failed to write to serial";
    return -1;
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

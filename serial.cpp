//g++ serial.cpp $(find src -name "*.cc") -I include -L lib   

#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include "serial/serial.h"
#include "el.cpp"

#define BUAD 9600
#define PORT "/dev/ttyUSB0"

int run(int argc, char **argv) {
  // port, baudrate, timeout in milliseconds
  serial::Serial my_serial(PORT, BUAD, serial::Timeout::simpleTimeout(500));
  // std::cout << "A";

  my_serial.write(argv[1]);
  // std::cout << "B";
  sleep(2.0);
  return 0;
}

int main(int argc, char **argv) {
  try {
    return run(argc, argv);
  } catch (std::exception &e) {
    std::cerr << "Unhandled Exception: " << e.what() << std::endl;
  }
}

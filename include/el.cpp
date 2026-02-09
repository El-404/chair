#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>

#define BUADRATE 9600
#define PORT "/dev/ttyACM0"

namespace el {
  void sleep(double seconds) {
    usleep(seconds * 1000 * 1000);
  }

  int serialWrite(int *fd, std::string msg) {
    if(write(*fd, &msg, sizeof(msg)) == -1) {
      std::cerr << "Failed to write to serial";
      return -1;
    }
    return 0;
  }

  int serialStart(int *fd, termios *config) {
    *fd = open(PORT, O_RDWR);
    if(*fd == -1) {
      std::cerr << "Failed to open file: " << PORT;
      return -1;
    }

    if(!isatty(*fd)) { 
      std::cerr << "Program did not open a TTY device";
      return -1;
    }
    

    if(tcgetattr(*fd, config) == -1) {
      std::cerr << "Failed to get attributes";
      return -1;
    }

    if( cfsetispeed(config, B9600) == -1 || cfsetospeed(config, B9600) == -1) {
      std::cerr << "Failed to set the buadrate";
      return -1;
    }


    return 0;
  } 

}
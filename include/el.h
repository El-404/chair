#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <stdint.h>

namespace el {
    void sleep(double seconds);
    int serialWrite(int *fd, const std::string& data);
    int serialStart(int *fd, termios *config);
}
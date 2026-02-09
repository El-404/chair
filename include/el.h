#include <unistd.h>
#include <iostream>
#include <termios.h>

namespace el {
    void sleep(double seconds);
    int serialWrite(int *fd, std::string msg);
    int serialStart(int *fd, termios *config);
}
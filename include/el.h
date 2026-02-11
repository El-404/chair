#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <stdint.h>

namespace el {
    void sleep(double seconds);
    int serialWrite(int *fd, uint8_t data[]);
    int serialStart(int *fd, termios *config);
}
#include <unistd.h>


void sleep(double seconds) {
  usleep(seconds * 1000);
}
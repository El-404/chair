#include <unistd.h>
#include <iostream>

namespace el {
  void sleep(double seconds) {
    usleep(seconds * 1000 * 1000);
  }
int i = 0;
  //debug print
  void dp() {
    std::cout << i++ << std::endl;
  }
}
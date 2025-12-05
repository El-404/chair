#include <unistd.h>

namespace el {
  void sleep(double seconds) {
    usleep(seconds * 1000);
  }
}
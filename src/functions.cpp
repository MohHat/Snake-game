#include "../include/functions.h"

namespace SnakeGame {
    int rngRange(const int& a, const int& b) { return rand() % b + a; }
}

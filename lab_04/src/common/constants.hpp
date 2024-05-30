#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <chrono>

#define FLOOR_COUNT 10

#define FLOOR_PASS_TIME std::chrono::milliseconds(1000)
#define DOOR_WAIT_TIME std::chrono::milliseconds(500)
#define PEOPLE_WAIT_TIME std::chrono::milliseconds(500)
#define NO_DELAY std::chrono::milliseconds(0)

#define START_FLOOR 1 - 1
#define NO_TARGET -1

#endif

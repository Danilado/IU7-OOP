#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <boost/chrono/chrono.hpp>

#define FLOOR_COUNT 10

#define FLOOR_PASS_TIME boost::chrono::milliseconds(1500)
#define DOOR_WAIT_TIME boost::chrono::milliseconds(1500)
#define PEOPLE_WAIT_TIME boost::chrono::milliseconds(1500)

#define START_FLOOR 1
#define NO_TARGET -1

#endif

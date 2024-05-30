#ifndef USINGS_HPP
#define USINGS_HPP

#include <boost/signals2/signal.hpp>

enum class Direction { DOWN = -1, IDLE = 0, UP = 1 };
enum class FloorWaitDirecton { NONE, DOWN, UP, BOTH };

using void_signal = boost::signals2::signal<void()>;
using void_dir_signal = boost::signals2::signal<void(Direction)>;

#endif

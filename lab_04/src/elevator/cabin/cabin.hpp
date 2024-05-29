#ifndef CABIN_HPP
#define CABIN_HPP

#include "doors.hpp"
#include "usings.hpp"
#include <boost/asio.hpp>

class Cabin {
private:
  enum class State { IDLE, MOVING, LOCKED, UNLOCKED, CHANGING };
  State state;
  Doors doors;

  boost::asio::io_service svc;
  boost::asio::high_resolution_timer floor_pass_timer{svc};

  void floor_pass_handler(const boost::system::error_code &error);

public:
  explicit Cabin();
  ~Cabin() = default;

  void runFloorPassTimer();
  void cancelFloorPassTimer();

  // signals
  void_signal unlocked;
  void_signal requestDoorsOpen;
  void_signal cabinFloorPassSlotCallback;

  // slots
  void locking();

  void unlocking();

  void preparing();

  void moving();

  void stopping();
};

#endif

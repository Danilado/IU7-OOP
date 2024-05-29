#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include "cabin.hpp"
#include "controller.hpp"

class Elevator {
private:
  Cabin cabin;
  Controller controller;

public:
  Elevator();
  ~Elevator() = default;

  void cabin_button_pressed(int floor);
  void floor_button_pressed(int floor, Controller::FloorWaitDirecton floor_dir);
};

#endif

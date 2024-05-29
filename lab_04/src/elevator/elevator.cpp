#include "elevator.hpp"
#include <boost/thread/thread.hpp>
#include <boost/thread/thread_guard.hpp>

Elevator::Elevator() {
  controller.requestCabinContinue.connect(
      // cabin.moving
      [this](void) { this->cabin.moving(); });

  controller.requestCabinPrep.connect(
      // cabin.preparing
      [this](void) { this->cabin.preparing(); });

  controller.requestCabinStop.connect(
      // cabin.stopping
      [this](void) { this->cabin.stopping(); });

  controller.requestCabinOpen.connect(
      // cabin.requestDoorsOpen
      [this](void) { this->cabin.requestDoorsOpen(); });

  cabin.unlocked.connect(
      // controller.updatingTarget
      [this](void) { this->controller.updatingTarget(); });

  cabin.cabinFloorPassSlotCallback.connect(
      // controller.handleMoving
      [this](void) { this->controller.handleMoving(); });
}

void Elevator::cabin_button_pressed(int floor) {
  boost::thread([this, floor]() { this->controller.floorUpdateCabin(floor); });
}

void Elevator::floor_button_pressed(int floor,
                                    Controller::FloorWaitDirecton floor_dir) {
  boost::thread([this, floor, floor_dir]() {
    this->controller.floorUpdate(floor, floor_dir);
  });
}

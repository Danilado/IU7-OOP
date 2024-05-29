#include "elevator.hpp"

#include "usings.hpp"
#include <boost/signals2/signal.hpp>
#include <boost/thread/thread.hpp>

Elevator::Elevator() {
  controller.requestCabinContinue.connect(cabin.moving);
  controller.requestCabinPrep.connect(cabin.prepare);
  controller.requestCabinStop.connect(cabin.stopping);
  controller.requestCabinOpen.connect(cabin.requestDoorsOpen);

  cabin.unlocked.connect(controller.updatingTarget);

  cabin.cabinFloorPassSlotCallback.connect(controller.handleMoving);
}

void Elevator::cabin_button_pressed(int floor) {
  controller.floorUpdateCabin(floor);
}

void Elevator::floor_button_pressed(int floor,
                                    Controller::FloorWaitDirecton floor_dir) {
  controller.floorUpdate(floor, floor_dir);
}

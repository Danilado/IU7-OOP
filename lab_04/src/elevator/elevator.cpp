#include "elevator.hpp"

using namespace boost::placeholders;

Elevator::Elevator() {
  controller.requestCabinContinue.connect(
      // cabin.continueMoving
      // [this](void) { this->cabin.continueMoving(); }
      boost::bind(&Cabin::continueMoving, &cabin));

  controller.requestCabinPrep.connect(
      // cabin.preparing
      // [this](void) { this->cabin.preparing(); }
      boost::bind(&Cabin::preparing, &cabin));

  controller.requestCabinStop.connect(
      // cabin.stopping
      // [this](void) { this->cabin.stopping(); }
      boost::bind(&Cabin::stopping, &cabin));

  controller.requestCabinOpen.connect(
      // cabin.requestDoorsOpen
      // [this](void) { this->cabin.requestDoorsOpen(); }
      boost::bind(&Cabin::requestDoorsOpen, &cabin));

  controller.tellCabinToMove.connect(
      // cabin.startMoving
      // [this](Direction dir) { this->cabin.startMoving(dir); }
      boost::bind(&Cabin::startMoving, &cabin, _1));

  cabin.readyToMove.connect(
      // controller.handleCabinReady
      // [this](void) { this->controller.handleCabinReady(); }
      boost::bind(&Controller::handleCabinReady, &controller));

  cabin.unlocked.connect(
      // controller.updatingTarget
      // [this](void) { this->controller.updatingTarget(); }
      boost::bind(&Controller::updatingTarget, &controller));

  cabin.cabinFloorPassSlotCallback.connect(
      // controller.handleMoving
      // [this](void) { this->controller.handleMoving(); }
      boost::bind(&Controller::handleMoving, &controller));
}

void Elevator::cabin_button_pressed(int floor) {
  boost::thread([this, floor]() { this->controller.floorUpdateCabin(floor); });
}

void Elevator::floor_button_pressed(int floor, FloorWaitDirecton floor_dir) {
  boost::thread([this, floor, floor_dir]() {
    this->controller.floorUpdate(floor, floor_dir);
  });
}

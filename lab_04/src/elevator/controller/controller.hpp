#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "constants.hpp"
#include "usings.hpp"
#include <QDebug>
#include <QString>
#include <cmath>
#include <vector>

class Controller {
public:
private:
  enum class State {
    IDLE,
    MOVING,
    UPDATING_TARGET,
    TARGET_REACHED,
    TARGET_FOUND
  };
  State state;

  Direction dir;
  Direction prev_dir;

  int cur_floor = START_FLOOR;
  int target = NO_TARGET;

  std::vector<FloorWaitDirecton> floor_states;

  const std::map<Direction, FloorWaitDirecton> dirmap = {
      {Direction::IDLE, FloorWaitDirecton::NONE},
      {Direction::UP, FloorWaitDirecton::UP},
      {Direction::DOWN, FloorWaitDirecton::DOWN},
  };
  const std::map<Direction, QString> verbosedirmap = {
      {Direction::IDLE, "На месте"},
      {Direction::UP, "Вверх"},
      {Direction::DOWN, "Вниз"},
  };
  const std::map<Direction, QString> verbosedirmapen = {
      {Direction::IDLE, "Staying"},
      {Direction::UP, "Up"},
      {Direction::DOWN, "Down"},
  };

  int findClosest();
  int findAccordingToDirection();
  int findTarget();
  Direction findDirection(int floor);
  void arrive();

  void updateTargetIdle();
  void updateTargetMoving();
  void handleTargetFound();

public:
  Controller();
  ~Controller() = default;

  void floorUpdate(int floor, FloorWaitDirecton dir);
  void floorUpdateCabin(int floor);

  // signals
  void_signal requestCabinStop;
  void_signal requestCabinOpen;
  void_signal requestCabinPrep;
  void_dir_signal tellCabinToMove;
  void_signal requestCabinContinue;

  // slots

  void updatingTarget();

  void handleCabinReady();

  void handleMoving();

  void handleIdle();

  void targetReached();
};

#endif

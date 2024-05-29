#include "controller.hpp"

Controller::Controller() {
  cur_floor = START_FLOOR;
  target = NO_TARGET;
  state = State::IDLE;
  dir = Direction::IDLE;
  prev_dir = Direction::IDLE;

  floor_states = std::vector(FLOOR_COUNT, FloorWaitDirecton::NONE);
}

int Controller::findClosest() {
  int result = NO_TARGET;
  int min_distance = FLOOR_COUNT + 1;

  for (size_t i = 0; i < FLOOR_COUNT; ++i)
    if (floor_states[i] != FloorWaitDirecton::NONE) {
      int dist = abs(cur_floor - int(i));
      if (dist < min_distance) {
        min_distance = dist;
        result = i;
      }
    }

  return result;
}

int Controller::findAccordingToDirection() {
  if (prev_dir == Direction::IDLE)
    return NO_TARGET;

  int result = NO_TARGET;
  int min_distance = FLOOR_COUNT + 1;
  FloorWaitDirecton rel_dir = dirmap.at(prev_dir);

  for (size_t i = cur_floor + int(prev_dir); i > 0 and i < FLOOR_COUNT;
       i += int(prev_dir))
    if (floor_states[i] == FloorWaitDirecton::BOTH ||
        floor_states[i] == rel_dir) {
      int dist = abs(cur_floor - int(i));
      if (dist < min_distance) {
        min_distance = dist;
        result = i;
      }
    }

  return result;
}

int Controller::findTarget() {
  int tmp = findAccordingToDirection();
  if (tmp == NO_TARGET)
    tmp = findClosest();
  return tmp;
}

void Controller::floorUpdate(int floor, FloorWaitDirecton floor_dir) {
  if (floor_states[floor] == FloorWaitDirecton::NONE)
    floor_states[floor] = floor_dir;
  else if (floor_states[floor] != floor_dir)
    floor_states[floor] = FloorWaitDirecton::BOTH;

  if (state == State::TARGET_REACHED && floor == cur_floor) {
    floor_states[floor] = FloorWaitDirecton::NONE;
    requestCabinOpen();
  } else {
    updatingTarget();
  }
}

void Controller::floorUpdateCabin(int floor) {
  floorUpdate(floor, findDirection(floor));
}

Direction Controller::findDirection(int floor) {
  if (floor == cur_floor)
    return Direction::IDLE;

  if (floor < cur_floor)
    return Direction::DOWN;

  return Direction::UP;
}

void Controller::updateTargetIdle() {
  if (state != State::IDLE and state != State::TARGET_REACHED)
    return;
  state = State::UPDATING_TARGET;

  qDebug() << "Лифт стоит на этаже " << cur_floor + 1 << std::endl;
  qDebug() << "Ищем новую цель..." << std::endl;

  int new_target = findTarget();
  if (new_target == NO_TARGET) {
    qDebug() << "Новой цели не найдено" << std::endl << std::endl;
    handleIdle();
  } else {
    target = new_target;
    prev_dir = dir;
    dir = findDirection(target);

    qDebug() << "Контроллер выбрал новой целью этаж " << target + 1 << std::endl
             << std::endl;

    requestCabinPrep();
  }
}

void Controller::updateTargetMoving() {
  qDebug() << "Движемся мимо этажа " << cur_floor + 1 << " в направлении "
           << verbosedirmap.at(dir) << std::endl;
  qDebug() << "Проверяем ближайшую цель в направлении движения..." << std::endl;

  prev_dir = dir;

  int new_target = findTarget();
  if (new_target == target)
    qDebug() << "Цель не изменилась, продолжаем движение..." //
             << std::endl
             << std::endl;
  else {
    qDebug() << "В качестве новой цели выбран этаж " << new_target + 1
             << std::endl;
    if (cur_floor != new_target && state == State::MOVING) {
      target = new_target;
      qDebug() << std::endl;
    } else {
      qDebug() << "...Но лифт уже его проехал, так что цель не изменилась, увы"
               << std::endl
               << std::endl;
    }
  }
}

void Controller::updatingTarget() {
  if (state == State::MOVING)
    updateTargetMoving();
  else
    updateTargetIdle();
}

void Controller::handleMoving() {
  if (state != State::UPDATING_TARGET and state != State::MOVING)
    return;
  state = State::MOVING;

  cur_floor += int(dir);
  qDebug() << "Лифт приехал на этаж " << cur_floor + 1 << std::endl
           << std::endl;

  if (cur_floor == target)
    targetReached();
  else
    requestCabinContinue();
}

void Controller::handleIdle() {
  if (state != State::UPDATING_TARGET)
    return;

  state = State::IDLE;
  qDebug() << "Отдыхаем на этаже" << cur_floor + 1 << std::endl << std::endl;
}

void Controller::arrive() {
  if (floor_states[floor] == FloorWaitDirecton::NONE)
    return;

  if (floor_states[floor] == FloorWaitDirecton::BOTH)
    floor_states[floor] =
        dir == Direction::UP ? FloorWaitDirecton::DOWN : FloorWaitDirecton::UP;
  else
    floor_states[floor] = FloorWaitDirecton::NONE;
}

void Controller::targetReached() {
  if (state != State::MOVING)
    return;
  state = State::TARGET_REACHED;

  arrive(cur_floor);

  qDebug() << "Контроллер обработал прибытие" << cur_floor + 1 << std::endl
           << std::endl;
  requestCabinStop();
}

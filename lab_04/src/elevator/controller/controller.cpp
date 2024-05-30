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

  if ((state == State::TARGET_REACHED || state == State::IDLE) &&
      floor == cur_floor) {
    floor_states[floor] = FloorWaitDirecton::NONE;
    requestCabinOpen();
  } else {
    updatingTarget();
  }
}

void Controller::floorUpdateCabin(int floor) {
  floorUpdate(floor, dirmap.at(findDirection(floor)));
}

Controller::Direction Controller::findDirection(int floor) {
  if (floor == cur_floor)
    return Direction::IDLE;

  if (floor < cur_floor)
    return Direction::DOWN;

  return Direction::UP;
}

void Controller::updateTargetIdle() {
  if (state != State::IDLE and state != State::TARGET_REACHED)
    return;

  if (state == State::IDLE)
    qDebug() << "Controller IDLE -> UPDATING_TARGET";
  else
    qDebug() << "Controller TARGET_REACHED -> UPDATING_TARGET";

  state = State::UPDATING_TARGET;

  // qDebug() << "Лифт стоит на этаже " << cur_floor + 1;
  // qDebug() << "Ищем новую цель...";
  qDebug() << "Elevator resting at floor " << cur_floor + 1;
  qDebug() << "Searching for new target...";

  int new_target = findTarget();
  if (new_target == NO_TARGET) {
    // qDebug() << "Новой цели не найдено";
    qDebug() << "New target not found";

    handleIdle();
  } else {
    target = new_target;
    prev_dir = dir;
    dir = findDirection(target);

    // qDebug() << "Контроллер выбрал новой целью этаж " << target + 1;
    qDebug() << "Controller determined new target: " << target + 1;
    handleTargetFound();
  }
}

void Controller::handleTargetFound() {
  if (state != State::TARGET_FOUND) {
    if (state != State::UPDATING_TARGET)
      return;

    if (state != State::TARGET_FOUND)
      qDebug() << "Controller UPDATING_TARGET -> TARGET_FOUND";

    state = State::TARGET_FOUND;
  }

  requestCabinPrep();
}

void Controller::updateTargetMoving() {
  // qDebug() << "Движемся мимо этажа " << cur_floor + 1 << " в направлении "
  //          << verbosedirmap.at(dir);
  // qDebug() << "Проверяем ближайшую цель в направлении движения...";
  qDebug() << "Moving through floor " << cur_floor + 1 << " heading "
           << verbosedirmapen.at(dir);
  qDebug() << "Checking closest target in direction of movement...";

  prev_dir = dir;

  int new_target = findTarget();
  if (new_target == target)
    // qDebug() << "Цель не изменилась, продолжаем движение...";
    qDebug() << "Target did not change, continuing to move...";

  else {
    // qDebug() << "В качестве новой цели выбран этаж " << new_target + 1;
    qDebug() << "New target determined: " << new_target + 1;
    if (cur_floor != new_target) {
      target = new_target;
      handleTargetFound();
    } else {
      // qDebug() << "...Но лифт уже его проехал, так что цель не изменилась,
      // увы";
      qDebug() << "...But has been already passed, so the target did not "
                  "change. Yikes";
    }
  }
}

void Controller::updatingTarget() {
  if (state == State::TARGET_FOUND)
    handleTargetFound();
  else if (state == State::IDLE || state == State::TARGET_REACHED)
    updateTargetIdle();
  else
    updateTargetMoving();
}

void Controller::handleMoving() {
  if (state != State::TARGET_FOUND and state != State::MOVING)
    return;

  if (state == State::TARGET_FOUND)
    qDebug() << "Controller TARGET_FOUND -> MOVING";

  state = State::MOVING;

  cur_floor += int(dir);
  // qDebug() << "Лифт приехал на этаж " << cur_floor + 1;
  qDebug() << "Elevator arrived at floor " << cur_floor + 1;

  if (cur_floor == target)
    targetReached();
  else
    requestCabinContinue();
}

void Controller::handleIdle() {
  if (state != State::UPDATING_TARGET)
    return;

  state = State::IDLE;

  qDebug() << "Controller UPDATING_TARGET -> IDLE";
  // qDebug() << "Отдыхаем на этаже" << cur_floor + 1;
  qDebug() << "Resting at floor " << cur_floor + 1;
}

void Controller::arrive() {
  if (floor_states[cur_floor] == FloorWaitDirecton::NONE)
    return;

  if (floor_states[cur_floor] == FloorWaitDirecton::BOTH)
    floor_states[cur_floor] =
        dir == Direction::UP ? FloorWaitDirecton::DOWN : FloorWaitDirecton::UP;
  else
    floor_states[cur_floor] = FloorWaitDirecton::NONE;
}

void Controller::targetReached() {
  if (state != State::MOVING)
    return;
  state = State::TARGET_REACHED;

  qDebug() << "Controller MOVING -> TARGET_REACHED";

  arrive();

  // qDebug() << "Контроллер обработал прибытие" << cur_floor + 1;
  qDebug() << "Controller processed ariival at floor " << cur_floor + 1;
  requestCabinStop();
}

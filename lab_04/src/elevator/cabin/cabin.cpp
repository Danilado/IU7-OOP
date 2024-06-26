#include "cabin.hpp"

using namespace boost::placeholders;

Cabin::Cabin() : m_worker(boost::asio::make_work_guard(svc)) {
  state = State::UNLOCKED;

  requestDoorsOpen.connect(
      // doors.opening
      // [this](void) { this->doors.opening(); }
      boost::bind(&Doors::opening, &doors));

  doors.closed.connect(
      // unlocking
      // [this](void) { this->unlocking(); }
      boost::bind(&Cabin::unlocking, this));
}

void Cabin::runFloorPassTimer() {
  floor_pass_timer.expires_from_now(FLOOR_PASS_TIME);
  floor_pass_timer.async_wait(
      // floor_pass_handler()
      // [this](const boost::system::error_code &error) {
      //   this->floor_pass_handler(error);
      // }
      boost::bind(&Cabin::floor_pass_handler, this, _1));
  svc.run();
}

void Cabin::cancelFloorPassTimer() {
  floor_pass_timer.expires_from_now(NO_DELAY);
}

void Cabin::floor_pass_handler(const boost::system::error_code &error) {
  if (!error) {
    cabinFloorPassSlotCallback();
  }
}

void Cabin::locking() {
  if (state != State::IDLE)
    return;

  state = State::LOCKED;
  qDebug() << "Cabin IDLE -> LOCKED";

  // qDebug() << "Движение кабины заблокировано";
  qDebug() << "Cabin movement locked";

  requestDoorsOpen();
}

void Cabin::unlocking() {
  if (this->state != State::LOCKED)
    return;

  this->state = State::UNLOCKED;
  qDebug() << "Cabin LOCKED -> UNLOCKED";

  // qDebug() << "Движение кабины разблокировано";
  qDebug() << "Cabin movement unlocked";

  unlocked();
}

void Cabin::preparing() {
  if (state != State::UNLOCKED)
    return;

  state = State::CHANGING;
  qDebug() << "Cabin UNLOCKED -> CHANGING";

  // qDebug() << "Кабина готовится двигаться";
  qDebug() << "Cabin ready to move";

  readyToMove();
}

void Cabin::continueMoving() {
  if (state != State::CHANGING && state != State::MOVING)
    return;

  if (state == State::CHANGING)
    qDebug() << "Cabin CHANGING -> MOVING";

  state = State::MOVING;

  runFloorPassTimer();
}

void Cabin::stopping() {
  if (state != State::MOVING)
    return;

  qDebug() << "Cabin MOVING -> IDLE";

  state = State::IDLE;
  // qDebug() << "Кабина остановилась";
  qDebug() << "Cabin stopped";

  locking();
}

void Cabin::startMoving(Direction dir) {
  if (state != State::CHANGING)
    return;

  state = State::MOVING;
  qDebug() << "Cabin CHANGING -> MOVING";
  qDebug() << "Cabing moving in direction" << int(dir)
           << "<--------------------";

  continueMoving();
}

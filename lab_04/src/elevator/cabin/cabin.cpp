#include "cabin.hpp"

Cabin::Cabin() {
  state = State::UNLOCKED;

  requestDoorsOpen.connect(doors.opening);
  doors.closed.connect(boost::bind(&Cabin::unlocking, this));
}

void Cabin::runFloorPassTimer() {
  floor_pass_timer.expires_from_now(FLOOR_PASS_TIME);
  floor_pass_timer.async_wait(floor_pass_handler);
  svc.run();
}

void Cabin::cancelFloorPassTimer() {
  floor_pass_timer.expires_from_now(boost::chrono::milliseconds(0));
  floor_pass_timer.async_wait();
}

void Cabin::floor_pass_handler(const boost::system::error_code &error) {
  if (!error) {
    cabinFloorPassSlotCallback();
  }
}

void Cabin::locking() {
  if (this->state != State::STOPPED)
    return;

  this->state = State::LOCKED;
  qDebug() << "Движение кабины заблокировано";

  requestDoorsOpen();
}

void Cabin::unlocking() {
  if (this->state != State::LOCKED)
    return;

  this->state = State::UNLOCKED;
  qDebug() << "Движение кабины разблокировано";

  unlocked();
}

void Cabin::preparing() {
  if (state != State::UNLOCKED)
    return;

  state = State::PREPARING;

  qDebug() << "Кабина готовится двигаться";

  moving();
}

void Cabin::moving() {
  if (state != State::CHANGING && state != State::MOVING)
    return;

  if (state == State::CHANGING)
    state = State::MOVING;

  runFloorPassTimer();
}

void Cabin::stopping() {
  if (state != State::MOVING)
    return;

  state = State::IDLE;
  qDebug() << "Кабина остановилась";

  locking();
}

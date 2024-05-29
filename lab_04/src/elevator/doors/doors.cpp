#include "doors.hpp"

Doors::Doors() {
  state = State::CLOSED;

  opened.connect(boost::bind(&Doors::userWaitingTimeoutCallback, this));
}

void Doors::open_handler(const boost::system::error_code &error) {
  if (!error) {
    open();
  }
}

void Doors::close_handler(const boost::system::error_code &error) {
  if (!error) {
    close();
  }
}

void Doors::wait_handler(const boost::system::error_code &error) {
  if (!error) {
    closing();
  }
}

void Doors::runOpenTimer() {
  qDebug() << "Двери открываются" << std::endl;
  open_timer.expires_from_now(DOOR_WAIT_TIME);
  open_timer.async_wait(open_handler);
  svc.run();
}

void Doors::runCloseTimer() {
  qDebug() << "Двери закрываются" << std::endl;
  close_timer.expires_from_now(DOOR_WAIT_TIME);
  close_timer.async_wait(close_handler);
  svc.run();
}

void Doors::runWaitTimer() {
  qDebug() << "Ожидание пассажиров" << std::endl;
  wait_timer.expires_from_now(PEOPLE_WAIT_TIME);
  wait_timer.async_wait(wait_handler);
  svc.run();
}

void Doors::cancelOpenTimer() {
  qDebug() << "Открытие дверей прервано" << std::endl;
  open_timer.expires_from_now(boost::chrono::milliseconds(0));
  open_timer.async_wait();
}

void Doors::cancelCloseTimer() {
  qDebug() << "Закрытие дверей прервано" << std::endl;
  close_timer.expires_from_now(boost::chrono::milliseconds(0));
  close_timer.async_wait();
}

void Doors::cancelWaitTimer() {
  qDebug() << "Ожидание пассажиров прервано" << std::endl;
  wait_timer.expires_from_now(boost::chrono::milliseconds(0));
  wait_timer.async_wait();
}

void Doors::opening() {
  if (state != State::CLOSING && state != State::CLOSED)
    return;

  if (state == State::CLOSED) {
    state = State::OPENING;
    runOpenTimer();
  } else {
    state = State::OPENING;

    cancelCloseTimer();
    runOpenTimer();
  }
}

void Doors::closing() {
  if (state != State::OPEN)
    return;

  state = State::CLOSING;

  runCloseTimer();
}

void Doors::open() {
  if (state != State::OPENING)
    return;

  state = State::OPEN;
  qDebug() << "Двери открыты" << std::endl << std::endl;

  opened();
}

void Doors::close() {
  if (state != State::CLOSING)
    return;

  state = State::CLOSED;
  qDebug() << "Двери закрыты" << std::endl << std::endl;

  closed();
}

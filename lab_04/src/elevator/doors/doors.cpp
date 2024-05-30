#include "doors.hpp"

#include <boost/bind/bind.hpp>
#include <boost/bind/placeholders.hpp>
using namespace boost::placeholders;

Doors::Doors() : m_worker(boost::asio::make_work_guard(svc)) {
  state = State::CLOSED;

  opened.connect(
      // closing()
      boost::bind(&Doors::runWaitTimer, this));
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
  // qDebug() << "Двери открываются";
  qDebug() << "Doors opening";
  open_timer.expires_from_now(DOOR_WAIT_TIME);
  open_timer.async_wait(
      // open_handler()
      // [this](const boost::system::error_code &error) {
      //   this->open_handler(error);
      // }
      boost::bind(&Doors::open_handler, this, _1));
  svc.run();
}

void Doors::runCloseTimer() {
  // qDebug() << "Двери закрываются";
  qDebug() << "Doors closing";
  close_timer.expires_from_now(DOOR_WAIT_TIME);
  close_timer.async_wait(
      // close_handler()
      // [this](const boost::system::error_code &error) {
      //   this->close_handler(error);
      // }
      boost::bind(&Doors::close_handler, this, _1));
  svc.run();
}

void Doors::runWaitTimer() {
  // qDebug() << "Ожидание пассажиров";
  qDebug() << "Waiting for passengers";
  wait_timer.expires_from_now(PEOPLE_WAIT_TIME);
  wait_timer.async_wait(
      // wait_handler()
      // [this](const boost::system::error_code &error) {
      //   this->wait_handler(error);
      // }
      boost::bind(&Doors::wait_handler, this, _1));
  svc.run();
}

void Doors::cancelOpenTimer() {
  // qDebug() << "Открытие дверей прервано";
  qDebug() << "Doors opening interrrupted";
  open_timer.expires_from_now(NO_DELAY);
}

void Doors::cancelCloseTimer() {
  // qDebug() << "Закрытие дверей прервано";
  qDebug() << "Doors closing interrrupted";
  close_timer.expires_from_now(NO_DELAY);
}

void Doors::cancelWaitTimer() {
  // qDebug() << "Ожидание пассажиров прервано";
  qDebug() << "Waiting for passengers interrrupted";
  wait_timer.expires_from_now(NO_DELAY);
}

void Doors::opening() {
  if (state != State::CLOSING && state != State::CLOSED)
    return;

  if (state == State::CLOSED) {
    qDebug() << "Doors CLOSED -> OPENING";
    state = State::OPENING;
    runOpenTimer();
  } else {
    qDebug() << "Doors CLOSING -> OPENING";
    state = State::OPENING;

    cancelCloseTimer();
    runOpenTimer();
  }
}

void Doors::closing() {
  if (state != State::OPEN)
    return;

  qDebug() << "Doors OPEN -> CLOSING";
  state = State::CLOSING;

  runCloseTimer();
}

void Doors::open() {
  if (state != State::OPENING)
    return;

  qDebug() << "Doors OPENING -> OPEN";
  state = State::OPEN;
  // qDebug() << "Двери открыты";
  qDebug() << "Doors open";

  opened();
}

void Doors::close() {
  if (state != State::CLOSING)
    return;

  qDebug() << "Doors CLOSING -> CLOSED";
  state = State::CLOSED;
  // qDebug() << "Двери закрыты";
  qDebug() << "Doors closed";

  closed();
}

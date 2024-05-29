#ifndef DOORS_HPP
#define DOORS_HPP

#include "constants.hpp"
#include "usings.hpp"
#include <QDebug>
#include <boost/asio.hpp>
#include <boost/asio/executor_work_guard.hpp>

class Doors {
private:
  enum class State { CLOSED, OPEN, CLOSING, OPENING };
  State state;

  boost::asio::io_service svc;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
      m_worker;
  boost::asio::high_resolution_timer open_timer{svc};
  boost::asio::high_resolution_timer close_timer{svc};
  boost::asio::high_resolution_timer wait_timer{svc};

  void open_handler(const boost::system::error_code &error);
  void close_handler(const boost::system::error_code &error);
  void wait_handler(const boost::system::error_code &error);

public:
  Doors();
  ~Doors() = default;

  void runOpenTimer();
  void runCloseTimer();
  void runWaitTimer();

  void cancelOpenTimer();
  void cancelCloseTimer();
  void cancelWaitTimer();

  // signals
  void_signal closed;
  void_signal opened;

  // slots
  void opening();

  void closing();

  void open();

  void close();
};

#endif

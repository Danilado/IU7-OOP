#include "mainwindow.hpp"

#include <QDebug>
#include <QKeyEvent>

void MainWindow::keyPressEvent(QKeyEvent *e) {
  Qt::Key key = Qt::Key(e->key());
  handleKey(key);
}

using Qt::Key;

void MainWindow::handleKey(Qt::Key key) {
  switch (key) {
  case (Key::Key_W): {
    qDebug() << "W";
  } break;
  case (Key::Key_D): {
    qDebug() << "D";
  } break;
  case (Key::Key_S): {
    qDebug() << "S";
  } break;
  case (Key::Key_A): {
    qDebug() << "A";
  } break;
  case (Key::Key_Shift): {
    qDebug() << "Shift";
  } break;
  case (Key::Key_Space): {
    qDebug() << "Space";
  } break;
  case (Key::Key_I): {
    qDebug() << "I";
  } break;
  case (Key::Key_L): {
    qDebug() << "L";
  } break;
  case (Key::Key_K): {
    qDebug() << "K";
  } break;
  case (Key::Key_J): {
    qDebug() << "J";
  } break;
  case (Key::Key_Z): {
    qDebug() << "Z";
  } break;
  case (Key::Key_C): {
    qDebug() << "C";
  } break;
  default: {
  } break;
  }
}

#include "mainwindow.hpp"

#include "RotateObjectCommand.hpp"
#include "ScaleObjectCommand.hpp"
#include "TranslateObjectCommand.hpp"
#include <QDebug>
#include <QKeyEvent>

void MainWindow::zoomCamera(double coeff) {
  Point3D origin = Point3D();
  Point3D scale = Point3D(coeff, coeff, coeff);
  std::shared_ptr<ScaleObjectCommand> cmd =
      std::make_shared<ScaleObjectCommand>(origin, scale, getCamId());
  application.exec(cmd);
  updateScene();
}

void MainWindow::moveCamera(double dx, double dy, double dz) {
  Point3D translation = Point3D(dx, dy, dz);
  std::shared_ptr<TranslateObjectCommand> cmd =
      std::make_shared<TranslateObjectCommand>(translation, getCamId());
  application.exec(cmd);
  updateScene();
}

void MainWindow::rotateCamera(double ax, double ay, double az) {
  Point3D origin = Point3D();
  Point3D rotation = Point3D(ax, ay, az);
  std::shared_ptr<RotateObjectCommand> cmd =
      std::make_shared<RotateObjectCommand>(origin, rotation, getCamId(), true);
  application.exec(cmd);
  updateScene();
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
  Qt::Key key = Qt::Key(e->key());
  handleKey(key);
}

using Qt::Key;

void MainWindow::handleKey(Qt::Key key) {
  switch (key) {
  case (Key::Key_W): {
    qDebug() << "W";
    moveCamera(0, 0, -10);
  } break;
  case (Key::Key_D): {
    qDebug() << "D";
    moveCamera(-10, 0, 0);
  } break;
  case (Key::Key_S): {
    qDebug() << "S";
    moveCamera(0, 0, 10);
  } break;
  case (Key::Key_A): {
    qDebug() << "A";
    moveCamera(10, 0, 0);
  } break;
  case (Key::Key_B): {
    qDebug() << "B";
    moveCamera(0, -10, 0);
  } break;
  case (Key::Key_Space): {
    qDebug() << "Space";
    moveCamera(0, 10, 0);
  } break;
  case (Key::Key_I): {
    qDebug() << "I";
    rotateCamera(-5, 0, 0);
  } break;
  case (Key::Key_L): {
    qDebug() << "L";
    rotateCamera(0, -5, 0);
  } break;
  case (Key::Key_K): {
    qDebug() << "K";
    rotateCamera(5, 0, 0);
  } break;
  case (Key::Key_J): {
    qDebug() << "J";
    rotateCamera(0, 5, 0);
  } break;
  case (Key::Key_Z): {
    qDebug() << "Z";
    zoomCamera(1.1);
  } break;
  case (Key::Key_C): {
    qDebug() << "C";
    zoomCamera(0.9);
  } break;
  case (Key::Key_U): {
    qDebug() << "U";
    undo();
  } break;
  case (Key::Key_R): {
    qDebug() << "R";
    redo();
  } break;
  default: {
  } break;
  }
}

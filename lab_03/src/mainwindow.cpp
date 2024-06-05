#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "DrawManager.hpp"
#include "DrawerSolution.hpp"
#include "Point3D.hpp"
#include "QtDrawerFactory.hpp"
#include "RenderCommand.hpp"
#include "SingletonTemplate.hpp"

#include <cstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->setFocusPolicy(Qt::StrongFocus);
  ui->setupUi(this);
  setupScene();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupScene() {
  ui->graphicsView->setFrameShape(QFrame::NoFrame);

  int screenWidth = ui->graphicsView->width();
  int screenHeight = ui->graphicsView->height();
  scene =
      std::make_shared<QGraphicsScene>(0, 0, screenWidth, screenHeight, this);

  // scene->addRect(scene->sceneRect());

  ui->graphicsView->setScene(scene.get());
  ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

  std::shared_ptr<BaseDrawer> drawer =
      DrawerSolution::create<QtDrawerFactory>(scene);

  DrawManager &drawManager = Singleton<DrawManager>::instance();
  drawManager.setDrawer(drawer);
  drawManager.renderScene();
}

void MainWindow::updateScene() {
  auto cmd = std::make_shared<RenderCommand>();
  application.exec(cmd);
}

Point3D MainWindow::getOrigin() {
  return Point3D(ui->ox->value(), ui->oy->value(), ui->oz->value());
}

Point3D MainWindow::getRotation() {
  return Point3D(ui->ax->value(), ui->ay->value(), ui->az->value());
}

Point3D MainWindow::getScale() {
  return Point3D(ui->kx->value(), ui->ky->value(), ui->kz->value());
}

Point3D MainWindow::getTranslation() {
  return Point3D(ui->dx->value(), ui->dy->value(), ui->dz->value());
}

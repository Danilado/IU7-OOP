#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "DrawManager.hpp"
#include "DrawerSolution.hpp"
#include "Point3D.hpp"
#include "QtDrawerFactory.hpp"
#include "RenderCommand.hpp"
#include "SingletonTemplate.hpp"
#include <QMessageBox>

#include <cstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), sdh(this) {
  this->setFocusPolicy(Qt::StrongFocus);
  ui->setupUi(this);
  setupScene();
  sdh.addCamera(1, "Camera 1");
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
  try {
    auto cmd = std::make_shared<RenderCommand>();
    application.exec(cmd);
  } catch (const std::exception &e) {
    showError(e.what());
  }
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

void MainWindow::addModelToBox(size_t id, const std::string &name) {
  ui->modelbox->addItem(QString::fromStdString(name), id);
  ui->modelbox->setCurrentIndex(ui->modelbox->count() - 1);
}

void MainWindow::addCameraToBox(size_t id, const std::string &name) {
  ui->cambox->addItem(QString::fromStdString(name), id);
  ui->cambox->setCurrentIndex(ui->cambox->count() - 1);
}

void MainWindow::removeModelFromBox() {
  ui->modelbox->removeItem(ui->modelbox->currentIndex());
}

void MainWindow::removeCameraFromBox() {
  ui->cambox->removeItem(ui->cambox->currentIndex());
}

size_t MainWindow::getObjId() { return ui->modelbox->currentData().toInt(); }

size_t MainWindow::getCamId() { return ui->cambox->currentData().toInt(); }

void MainWindow::showError(const char *str) {
  QMessageBox::critical(nullptr, "Ошибка", QString(str));
}

#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

#include "DrawManager.hpp"
#include "DrawerSolution.hpp"
#include "QtDrawerFactory.hpp"
#include "SingletonTemplate.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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

  scene->addRect(scene->sceneRect());

  ui->graphicsView->setScene(scene.get());
  ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

  std::shared_ptr<BaseDrawer> drawer =
      DrawerSolution::create<QtDrawerFactory>(scene);

  DrawManager &drawManager = Singleton<DrawManager>::instance();
  drawManager.setDrawer(drawer);
  drawManager.renderScene();
}

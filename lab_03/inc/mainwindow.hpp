#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Scene.hpp"
#include "app.hpp"
#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  App application;
  std::shared_ptr<QGraphicsScene> scene;

  void setupScene();
  void keyPressEvent(QKeyEvent *e) override;
  void handleKey(Qt::Key key);
};
#endif // MAINWINDOW_H

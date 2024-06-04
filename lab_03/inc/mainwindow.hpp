#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Point3D.hpp"
#include "Scene.hpp"
#include "app.hpp"
#include <QErrorMessage>
#include <QFileDialog>
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
  void updateScene();
  void keyPressEvent(QKeyEvent *e) override;
  void handleKey(Qt::Key key);

  Point3D getOrigin();
  Point3D getRotation();
  Point3D getScale();
  Point3D getTranslation();

private slots:
  void on_load_model_clicked();
  void on_translate_clicked();
  void on_translate_all_clicked();
  void on_scale_clicked();
  void on_scale_all_clicked();
  void on_rotate_clicked();
  void on_rotate_all_clicked();
  void on_save_model_clicked();
};
#endif // MAINWINDOW_H

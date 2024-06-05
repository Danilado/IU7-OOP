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

  void zoomCamera(double coeff);
  void moveCamera(double dx, double dy, double dz);
  void rotateCamera(double ax, double ay, double az);

private slots:
  void on_load_model_clicked();
  void on_translate_clicked();
  void on_translate_all_clicked();
  void on_scale_clicked();
  void on_scale_all_clicked();
  void on_rotate_clicked();
  void on_rotate_all_clicked();
  void on_save_model_clicked();
  void on_cam_tl_clicked();
  void on_cam_t_clicked();
  void on_cam_tr_clicked();
  void on_cam_r_clicked();
  void on_cam_br_clicked();
  void on_cam_b_clicked();
  void on_cam_bl_clicked();
  void on_cam_l_clicked();
};
#endif // MAINWINDOW_H

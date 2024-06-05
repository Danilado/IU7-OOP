#include "LoadCameraCommand.hpp"
#include "LoadModelCommand.hpp"
#include "SaveCameraCommand.hpp"
#include "SaveModelCommand.hpp"
#include "SetCameraCommand.hpp"
#include "mainwindow.hpp"

#include "RotateObjectCommand.hpp"
#include "ScaleObjectCommand.hpp"
#include "TranslateObjectCommand.hpp"

void MainWindow::on_save_model_clicked() {
  if (!getObjId())
    return;
  QString filename = QFileDialog::getSaveFileName(this, tr("Выбрать файл"),
                                                  "../models/", tr("*.json"));
  if (filename.isNull())
    return;

  char *buf = (char *)calloc(filename.length() + 1, sizeof(char));
  if (buf == nullptr)
    return;

  strcpy(buf, filename.toLocal8Bit().data());

  auto cmd = std::make_shared<SaveModelCommand>(std::string(buf), getObjId());
  application.exec(cmd);
}

void MainWindow::on_load_model_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Выбрать файл"), "../models/", tr("*.txt, *.json"));
  if (filename.isNull())
    return;

  char *buf = (char *)calloc(filename.length() + 1, sizeof(char));
  if (buf == nullptr)
    return;

  strcpy(buf, filename.toLocal8Bit().data());

  size_t resid;

  auto cmd = std::make_shared<LoadModelCommand>(std::string(buf), resid);
  // auto cmd = std::make_shared<LoadModelCommand>(
  //     "D:\\develop\\IU7-OOP\\lab_03\\models\\cubeincude.json");

  application.exec(cmd);

  sdh.addModel(resid, "WireframeModel " + std::to_string(resid));

  updateScene();
}

void MainWindow::on_translate_clicked() {
  Point3D translation = getTranslation();
  std::shared_ptr<TranslateObjectCommand> cmd =
      std::make_shared<TranslateObjectCommand>(translation, getObjId());
  application.exec(cmd);
  updateScene();
}

void MainWindow::on_translate_all_clicked() {
  Point3D translation = getTranslation();
  std::shared_ptr<TranslateObjectCommand> cmd =
      std::make_shared<TranslateObjectCommand>(translation, 0);
  application.exec(cmd);
  updateScene();
}

void MainWindow::on_scale_clicked() {
  Point3D origin = getOrigin();
  Point3D scale = getScale();
  std::shared_ptr<ScaleObjectCommand> cmd =
      std::make_shared<ScaleObjectCommand>(origin, scale, getObjId());
  application.exec(cmd);
  updateScene();
}

void MainWindow::on_scale_all_clicked() {
  Point3D origin = getOrigin();
  Point3D scale = getScale();
  std::shared_ptr<ScaleObjectCommand> cmd =
      std::make_shared<ScaleObjectCommand>(origin, scale, 0);
  application.exec(cmd);
  updateScene();
}

void MainWindow::on_rotate_clicked() {
  Point3D origin = getOrigin();
  Point3D rotation = getRotation();
  std::shared_ptr<RotateObjectCommand> cmd =
      std::make_shared<RotateObjectCommand>(origin, rotation, getObjId(), true);
  application.exec(cmd);
  updateScene();
}

void MainWindow::on_rotate_all_clicked() {
  Point3D origin = getOrigin();
  Point3D rotation = getRotation();
  std::shared_ptr<RotateObjectCommand> cmd =
      std::make_shared<RotateObjectCommand>(origin, rotation, 0, true);
  application.exec(cmd);
  updateScene();
}

void MainWindow::on_cam_tl_clicked() { rotateCamera(-5, 5, 0); }

void MainWindow::on_cam_t_clicked() { rotateCamera(-5, 0, 0); }

void MainWindow::on_cam_tr_clicked() { rotateCamera(-5, -5, 0); }

void MainWindow::on_cam_r_clicked() { rotateCamera(0, -5, 0); }

void MainWindow::on_cam_br_clicked() { rotateCamera(5, -5, 0); }

void MainWindow::on_cam_b_clicked() { rotateCamera(5, 0, 0); }

void MainWindow::on_cam_bl_clicked() { rotateCamera(5, 5, 0); }

void MainWindow::on_cam_l_clicked() { rotateCamera(0, 5, 0); }

void MainWindow::on_remove_model_clicked() {}

void MainWindow::on_save_cam_clicked() {
  if (!getCamId())
    return;
  QString filename = QFileDialog::getSaveFileName(this, tr("Выбрать файл"),
                                                  "../cameras/", tr("*.json"));
  if (filename.isNull())
    return;

  char *buf = (char *)calloc(filename.length() + 1, sizeof(char));
  if (buf == nullptr)
    return;

  strcpy(buf, filename.toLocal8Bit().data());

  auto cmd = std::make_shared<SaveCameraCommand>(std::string(buf), getCamId());
  application.exec(cmd);
}

void MainWindow::on_load_cam_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Выбрать файл"), "../cameras/", tr("*.txt, *.json"));
  if (filename.isNull())
    return;

  char *buf = (char *)calloc(filename.length() + 1, sizeof(char));
  if (buf == nullptr)
    return;

  strcpy(buf, filename.toLocal8Bit().data());

  size_t resid;

  auto cmd = std::make_shared<LoadCameraCommand>(std::string(buf), resid);

  application.exec(cmd);

  sdh.addCamera(resid, "Camera " + std::to_string(resid));

  updateScene();
}

void MainWindow::on_remove_cam_clicked() {}

void MainWindow::on_cambox_currentIndexChanged(int index) {
  auto cmd = std::make_shared<SetCameraCommand>(getCamId());
  application.exec(cmd);
  updateScene();
}

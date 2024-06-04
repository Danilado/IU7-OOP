#include "LoadModelCommand.hpp"
#include "SaveModelCommand.hpp"
#include "mainwindow.hpp"

#include "RotateObjectCommand.hpp"
#include "ScaleObjectCommand.hpp"
#include "TranslateObjectCommand.hpp"

void MainWindow::on_save_model_clicked() {}

void MainWindow::on_load_model_clicked() {
  // QString filename = QFileDialog::getOpenFileName(this, tr("Выбрать файл"),
  // "",
  //                                                 tr("*.txt, *.json"));
  // if (filename.isNull())
  //   return;

  // char *buf = (char *)calloc(filename.length() + 1, sizeof(char));
  // if (buf == nullptr)
  //   return;

  // strcpy(buf, filename.toLocal8Bit().data());

  // auto cmd = std::make_shared<LoadModelCommand>(std::string(buf));
  auto cmd = std::make_shared<LoadModelCommand>(
      "D:\\develop\\IU7-OOP\\lab_03\\models\\cubeincude.json");

  application.exec(cmd);

  updateScene();
}

void MainWindow::on_translate_clicked() {
  Point3D translation = getTranslation();
  std::shared_ptr<TranslateObjectCommand> cmd =
      std::make_shared<TranslateObjectCommand>(translation, 2);
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
      std::make_shared<ScaleObjectCommand>(origin, scale, 2);
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
      std::make_shared<RotateObjectCommand>(origin, rotation, 2, true);
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

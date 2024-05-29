#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_elevator_btn_10_clicked() {
  elevator.cabin_button_pressed(9);
}

void MainWindow::on_elevator_btn_9_clicked() {
  elevator.cabin_button_pressed(8);
}

void MainWindow::on_elevator_btn_8_clicked() {
  elevator.cabin_button_pressed(7);
}

void MainWindow::on_elevator_btn_7_clicked() {
  elevator.cabin_button_pressed(6);
}

void MainWindow::on_elevator_btn_6_clicked() {
  elevator.cabin_button_pressed(5);
}

void MainWindow::on_elevator_btn_5_clicked() {
  elevator.cabin_button_pressed(4);
}

void MainWindow::on_elevator_btn_4_clicked() {
  elevator.cabin_button_pressed(3);
}

void MainWindow::on_elevator_btn_3_clicked() {
  elevator.cabin_button_pressed(2);
}

void MainWindow::on_elevator_btn_2_clicked() {
  elevator.cabin_button_pressed(1);
}

void MainWindow::on_elevator_btn_1_clicked() {
  elevator.cabin_button_pressed(0);
}

void MainWindow::on_floor_10_up_clicked() {
  elevator.floor_button_pressed(9, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_9_up_clicked() {
  elevator.floor_button_pressed(8, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_8_up_clicked() {
  elevator.floor_button_pressed(7, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_7_up_clicked() {
  elevator.floor_button_pressed(6, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_6_up_clicked() {
  elevator.floor_button_pressed(5, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_5_up_clicked() {
  elevator.floor_button_pressed(4, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_4_up_clicked() {
  elevator.floor_button_pressed(3, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_3_up_clicked() {
  elevator.floor_button_pressed(2, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_2_up_clicked() {
  elevator.floor_button_pressed(1, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_1_up_clicked() {
  elevator.floor_button_pressed(0, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_10_down_clicked() {
  elevator.floor_button_pressed(9, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_9_down_clicked() {
  elevator.floor_button_pressed(8, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_8_down_clicked() {
  elevator.floor_button_pressed(7, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_7_down_clicked() {
  elevator.floor_button_pressed(6, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_6_down_clicked() {
  elevator.floor_button_pressed(5, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_5_down_clicked() {
  elevator.floor_button_pressed(4, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_4_down_clicked() {
  elevator.floor_button_pressed(3, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_3_down_clicked() {
  elevator.floor_button_pressed(2, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_2_down_clicked() {
  elevator.floor_button_pressed(1, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_1_down_clicked() {
  elevator.floor_button_pressed(0, Controller::FloorWaitDirecton::DOWN);
}

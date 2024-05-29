#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  // qDebug() << "Лифт на этаже 1";
  // qDebug() << "Движение кабины разблокировано";
  // qDebug() << "Двери закрыты";
  qDebug() << "Elevator at floor 1";
  qDebug() << "Cabin movement unlocked";
  qDebug() << "Doors closed";

  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::print_cabin_click(int floor) {
  // qDebug() << "Нажата кнока этажа " << floor << " в кабине";
  qDebug() << "Button for floor " << floor << " pressed in cabin";
}

void MainWindow::print_floor_click_up(int floor) {
  // qDebug() << "Нажата кнопка вверх на этаже " << floor;
  qDebug() << "Button UP pressed at floor " << floor;
}

void MainWindow::print_floor_click_down(int floor) {
  // qDebug() << "Нажата кнопка вниз на этаже " << floor;
  qDebug() << "Button DOWN pressed at floor " << floor;
}

void MainWindow::on_elevator_btn_10_clicked() {
  print_cabin_click(10);
  elevator.cabin_button_pressed(9);
}

void MainWindow::on_elevator_btn_9_clicked() {
  print_cabin_click(9);
  elevator.cabin_button_pressed(8);
}

void MainWindow::on_elevator_btn_8_clicked() {
  print_cabin_click(8);
  elevator.cabin_button_pressed(7);
}

void MainWindow::on_elevator_btn_7_clicked() {
  print_cabin_click(7);
  elevator.cabin_button_pressed(6);
}

void MainWindow::on_elevator_btn_6_clicked() {
  print_cabin_click(6);
  elevator.cabin_button_pressed(5);
}

void MainWindow::on_elevator_btn_5_clicked() {
  print_cabin_click(5);
  elevator.cabin_button_pressed(4);
}

void MainWindow::on_elevator_btn_4_clicked() {
  print_cabin_click(4);
  elevator.cabin_button_pressed(3);
}

void MainWindow::on_elevator_btn_3_clicked() {
  print_cabin_click(3);
  elevator.cabin_button_pressed(2);
}

void MainWindow::on_elevator_btn_2_clicked() {
  print_cabin_click(2);
  elevator.cabin_button_pressed(1);
}

void MainWindow::on_elevator_btn_1_clicked() {
  print_cabin_click(1);
  elevator.cabin_button_pressed(0);
}

void MainWindow::on_floor_10_up_clicked() {
  print_floor_click_up(10);
  elevator.floor_button_pressed(9, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_9_up_clicked() {
  print_floor_click_up(9);
  elevator.floor_button_pressed(8, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_8_up_clicked() {
  print_floor_click_up(8);
  elevator.floor_button_pressed(7, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_7_up_clicked() {
  print_floor_click_up(7);
  elevator.floor_button_pressed(6, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_6_up_clicked() {
  print_floor_click_up(6);
  elevator.floor_button_pressed(5, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_5_up_clicked() {
  print_floor_click_up(5);
  elevator.floor_button_pressed(4, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_4_up_clicked() {
  print_floor_click_up(4);
  elevator.floor_button_pressed(3, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_3_up_clicked() {
  print_floor_click_up(3);
  elevator.floor_button_pressed(2, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_2_up_clicked() {
  print_floor_click_up(2);
  elevator.floor_button_pressed(1, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_1_up_clicked() {
  print_floor_click_up(1);
  elevator.floor_button_pressed(0, Controller::FloorWaitDirecton::UP);
}

void MainWindow::on_floor_10_down_clicked() {
  print_floor_click_down(10);
  elevator.floor_button_pressed(9, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_9_down_clicked() {
  print_floor_click_down(9);
  elevator.floor_button_pressed(8, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_8_down_clicked() {
  print_floor_click_down(8);
  elevator.floor_button_pressed(7, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_7_down_clicked() {
  print_floor_click_down(7);
  elevator.floor_button_pressed(6, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_6_down_clicked() {
  print_floor_click_down(6);
  elevator.floor_button_pressed(5, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_5_down_clicked() {
  print_floor_click_down(5);
  elevator.floor_button_pressed(4, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_4_down_clicked() {
  print_floor_click_down(4);
  elevator.floor_button_pressed(3, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_3_down_clicked() {
  print_floor_click_down(3);
  elevator.floor_button_pressed(2, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_2_down_clicked() {
  print_floor_click_down(2);
  elevator.floor_button_pressed(1, Controller::FloorWaitDirecton::DOWN);
}

void MainWindow::on_floor_1_down_clicked() {
  print_floor_click_down(1);
  elevator.floor_button_pressed(0, Controller::FloorWaitDirecton::DOWN);
}

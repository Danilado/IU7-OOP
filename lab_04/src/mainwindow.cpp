#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_elevator_btn_10_clicked() {}

void MainWindow::on_elevator_btn_9_clicked() {}

void MainWindow::on_elevator_btn_8_clicked() {}

void MainWindow::on_elevator_btn_7_clicked() {}

void MainWindow::on_elevator_btn_6_clicked() {}

void MainWindow::on_elevator_btn_5_clicked() {}

void MainWindow::on_elevator_btn_4_clicked() {}

void MainWindow::on_elevator_btn_3_clicked() {}

void MainWindow::on_elevator_btn_2_clicked() {}

void MainWindow::on_elevator_btn_1_clicked() {}

void MainWindow::on_floor_10_up_clicked() {}

void MainWindow::on_floor_9_up_clicked() {}

void MainWindow::on_floor_8_up_clicked() {}

void MainWindow::on_floor_7_up_clicked() {}

void MainWindow::on_floor_6_up_clicked() {}

void MainWindow::on_floor_5_up_clicked() {}

void MainWindow::on_floor_4_up_clicked() {}

void MainWindow::on_floor_3_up_clicked() {}

void MainWindow::on_floor_2_up_clicked() {}

void MainWindow::on_floor_1_up_clicked() {}

void MainWindow::on_floor_10_down_clicked() {}

void MainWindow::on_floor_9_down_clicked() {}

void MainWindow::on_floor_8_down_clicked() {}

void MainWindow::on_floor_7_down_clicked() {}

void MainWindow::on_floor_6_down_clicked() {}

void MainWindow::on_floor_5_down_clicked() {}

void MainWindow::on_floor_4_down_clicked() {}

void MainWindow::on_floor_3_down_clicked() {}

void MainWindow::on_floor_2_down_clicked() {}

void MainWindow::on_floor_1_down_clicked() {}

#include "mainwindow.h"
#include "controller.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    filename.clear();

    scene = new QGraphicsScene();
    ui->setupUi(this);

    req_data_t data;
    data.scene = scene;
    handle(SET_SCENE, &data);
    data.ui = ui;
    handle(SET_UI, &data);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    handle(EXIT, nullptr);
}

void MainWindow::update_filename()
{
    ui->filename_box->setText(this->filename.isNull() ? QString("Файл не выбран") : this->filename);
}

void MainWindow::on_choose_file_clicked()
{
    this->filename = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("*.txt"));
    this->update_filename();
}

void MainWindow::on_file_load_clicked()
{
    if (this->filename.isNull())
        this->filename = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("*.txt"));

    if (this->filename.isNull())
        return;

    this->update_filename();

    FILE *f = fopen(this->filename.toLocal8Bit().data(), "r");
    if (f == nullptr)
        return;

    req_data_t data;
    data.f = f;
    handle(LOAD, &data);

    fclose(f);

    draw_graph();
}

void MainWindow::on_file_save_clicked()
{
    if (this->filename.isNull())
        this->filename = QFileDialog::getSaveFileName(this, tr("Выбрать файл"), "", tr("*.txt"));

    if (this->filename.isNull())
        return;

    this->update_filename();

    FILE *f = fopen(this->filename.toLocal8Bit().data(), "r");
    if (f == nullptr)
        return;

    req_data_t data;
    data.f = f;
    handle(SAVE, &data);

    fclose(f);
}

void MainWindow::draw_graph()
{
    handle(DRAW, nullptr);
}

void MainWindow::on_do_scale_clicked()
{
    handle(SCALE, nullptr);
    draw_graph();
}

void MainWindow::on_do_shift_clicked()
{
    handle(SHIFT, nullptr);
    draw_graph();
}

void MainWindow::on_do_rotate_clicked()
{
    handle(ROTATE, nullptr);
    draw_graph();
}

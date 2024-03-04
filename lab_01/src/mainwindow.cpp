#include "mainwindow.h"
#include "controller.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    scene = new QGraphicsScene();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    handle({EXIT, nullptr});
}

void MainWindow::on_file_load_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("*.txt"));
    if (filename.isNull())
        return;

    char *buf = (char *)calloc(filename.length() + 1, sizeof(char));
    if (buf == nullptr)
        return;

    strcpy(buf, filename.toLocal8Bit().data());

    request_t req = {LOAD, nullptr};
    req.io_data = {buf};

    int rc = handle(req);
    free(buf);

    if (!rc)
        draw_graph();
}

void MainWindow::on_file_save_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Выбрать файл"), "", tr("*.txt"));
    if (filename.isNull())
        return;

    char *buf = (char *)calloc(filename.length() + 1, sizeof(char));
    if (buf == nullptr)
        return;

    strcpy(buf, filename.toLocal8Bit().data());

    request_t req = {SAVE, nullptr};
    req.io_data = {buf};

    int rc = handle(req);
    free(buf);

    if (!rc)
        draw_graph();
}

void MainWindow::draw_graph()
{
    draw_data_t data = {ui, scene};
    request_t req = {DRAW, nullptr};
    req.d_data = data;

    handle(req);
}

void MainWindow::on_do_scale_clicked()
{
    request_t req = {SCALE, nullptr};

    point_t origin = create_point(ui->scale_Cx->value(),
                                  ui->scale_Cy->value(),
                                  ui->scale_Cz->value());
    if (origin == nullptr)
        return;
    point_t coeffs = create_point(ui->scale_Kx->value(),
                                  ui->scale_Ky->value(),
                                  ui->scale_Kz->value());
    if (coeffs == nullptr)
    {
        destroy_point(origin);
        return;
    }

    req.t_data = {origin, coeffs};
    int rc = handle(req);

    destroy_point(origin);
    destroy_point(coeffs);

    if (!rc)
        draw_graph();
}

void MainWindow::on_do_shift_clicked()
{
    request_t req = {SHIFT, nullptr};

    point_t shifts = create_point(ui->shift_Dx->value(),
                                  ui->shift_Dy->value(),
                                  ui->shift_Dz->value());
    if (shifts == nullptr)
        return;

    req.t_data = {nullptr, shifts};
    int rc = handle(req);

    destroy_point(shifts);

    if (!rc)
        draw_graph();
}

void MainWindow::on_do_rotate_clicked()
{
    request_t req = {ROTATE, nullptr};

    point_t origin = create_point(ui->rotate_Cx->value(),
                                  ui->rotate_Cy->value(),
                                  ui->rotate_Cz->value());
    if (origin == nullptr)
        return;
    point_t angles = create_point(ui->rotate_Ax->value(),
                                  ui->rotate_Ay->value(),
                                  ui->rotate_Az->value());
    if (angles == nullptr)
    {
        destroy_point(origin);
        return;
    }

    req.t_data = {origin, angles};
    int rc = handle(req);

    destroy_point(origin);
    destroy_point(angles);

    if (!rc)
        draw_graph();
}

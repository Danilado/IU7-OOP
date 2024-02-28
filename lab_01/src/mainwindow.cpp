#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    dx = 0.0;
    dy = 0.0;
    dz = 0.0;

    s_cx = 0.0;
    s_cy = 0.0;
    s_cz = 0.0;
    kx = 0.0;
    ky = 0.0;
    kz = 0.0;

    r_cx = 0.0;
    r_cy = 0.0;
    r_cz = 0.0;
    ax = 0.0;
    ay = 0.0;
    az = 0.0;

    graph = nullptr;
    filename.clear();

    scene = new QGraphicsScene();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    destroy_graph(&graph);
    delete scene;
}

void MainWindow::update_filename()
{
    ui->filename_box->setText(this->filename.isNull() ? QString("Файл не выбран") : this->filename);
}

void MainWindow::on_choose_file_clicked()
{
    this->filename = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "..\\..", tr("*.txt"));
    this->update_filename();
}

void MainWindow::on_file_load_clicked()
{
    if (graph != nullptr)
        destroy_graph(&graph);

    if (this->filename.isNull())
        this->filename = QFileDialog::getOpenFileName(this,
                                                      tr("Выбрать файл"),
                                                      "..\\..",
                                                      tr("*.txt"));

    if (this->filename.isNull())
        return;

    this->update_filename();

    graph = create_graph_from_file(filename);

    ctx_draw_graph();
}

void MainWindow::on_file_save_clicked()
{
    if (this->graph == nullptr)
        return;

    if (this->filename.isNull())
        this->filename = QFileDialog::getSaveFileName(this,
                                                      tr("Выбрать файл"),
                                                      "..\\..",
                                                      tr("*.txt"));

    if (this->filename.isNull())
        return;

    this->update_filename();

    write_graph_to_file(graph, filename);
}

void MainWindow::ctx_draw_graph()
{
    if (graph == nullptr)
        return;

    QImage img = QImage(ui->canvas->width(), ui->canvas->height(), QImage::Format_RGB32);
    QPainter p(&img);

    p.fillRect(0, 0, ui->canvas->width(), ui->canvas->height(), QColor(255, 255, 255));

    draw_graph(graph,
               &p,
               QColor(0, 0, 0),
               QColor(200, 0, 0),
               ui->canvas->width() / 2,
               ui->canvas->height() / 2);

    QPixmap pixmap = QPixmap::fromImage(img);
    scene->clear();
    scene->addPixmap(pixmap);
    ui->canvas->setScene(scene);
}

void MainWindow::on_do_scale_clicked()
{
    if (graph == nullptr)
        return;

    point_t origin = create_point(s_cx, s_cy, s_cz);
    if (origin == nullptr)
        return;

    graph_apply_scale(graph, origin, kx, ky, kz);

    destroy_point(&origin);

    ctx_draw_graph();
}

void MainWindow::on_do_shift_clicked()
{
    if (graph == nullptr)
        return;

    graph_apply_shift(graph, dx, dy, dz);

    ctx_draw_graph();
}

void MainWindow::on_do_rotate_clicked()
{
    if (graph == nullptr)
        return;

    point_t origin = create_point(r_cx, r_cy, r_cz);
    if (origin == nullptr)
        return;

    graph_apply_rotate(graph, origin, ax, ay, az);

    destroy_point(&origin);

    ctx_draw_graph();
}

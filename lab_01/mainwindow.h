#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QErrorMessage>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>

#include "my_graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    qreal dx = 0.0, dy = 0.0, dz = 0.0, s_cx = 0.0, s_cy = 0.0, s_cz = 0.0, r_cx = 0.0, r_cy = 0.0,
          r_cz = 0.0, ax = 0.0, ay = 0.0, az = 0.0, kx = 0.0, ky = 0.0, kz = 0.0;

    graph_t graph;

    QString filename;

    QGraphicsScene *scene;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void update_filename();

    void on_choose_file_clicked();

    void ctx_draw_graph();

    void on_shift_Dz_valueChanged(double arg1);

    void on_shift_Dx_valueChanged(double arg1);

    void on_shift_Dy_valueChanged(double arg1);

    void on_scale_Cz_valueChanged(double arg1);

    void on_scale_Cx_valueChanged(double arg1);

    void on_scale_Cy_valueChanged(double arg1);

    void on_rotate_Cx_valueChanged(double arg1);

    void on_rotate_Cy_valueChanged(double arg1);

    void on_rotate_Cz_valueChanged(double arg1);

    void on_scale_Kx_valueChanged(double arg1);

    void on_scale_Ky_valueChanged(double arg1);

    void on_scale_Kz_valueChanged(double arg1);

    void on_rotate_Ax_valueChanged(double arg1);

    void on_rotate_Ay_valueChanged(double arg1);

    void on_rotate_Az_valueChanged(double arg1);

    void on_do_scale_clicked();

    void on_file_load_clicked();

    void on_file_save_clicked();

    void on_do_shift_clicked();

    void on_do_rotate_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QErrorMessage>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QGraphicsScene *scene;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void draw_graph();

    void on_do_scale_clicked();

    void on_file_load_clicked();

    void on_file_save_clicked();

    void on_do_shift_clicked();

    void on_do_rotate_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef DRAW_HANDLERS_H
#define DRAW_HANDLERS_H

#include "my_error.h"
#include "my_graph.h"

#include <QGraphicsScene>
#include <QPainter>
#include "mainwindow.h"

typedef struct
{
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
} draw_data_t;

int handle_draw(draw_data_t data, const graph_t gr);

#endif

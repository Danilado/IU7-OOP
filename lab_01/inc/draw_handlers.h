#ifndef DRAW_HANDLERS_H
#define DRAW_HANDLERS_H

#include "my_error.h"
#include "my_model.h"

#include "mainwindow.h"
#include <QGraphicsScene>
#include <QPainter>

typedef struct {
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
} draw_data_t;

int handle_draw(const model_t gr, draw_data_t data);

#endif

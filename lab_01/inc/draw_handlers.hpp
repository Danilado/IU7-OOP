#ifndef DRAW_HANDLERS_H
#define DRAW_HANDLERS_H

#include "model.hpp"
#include "model_error.hpp"

#include "mainwindow.hpp"
#include <QGraphicsScene>
#include <QPainter>

typedef struct {
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
} draw_data_t;

int handle_draw(const model_t model, draw_data_t &data);

#endif

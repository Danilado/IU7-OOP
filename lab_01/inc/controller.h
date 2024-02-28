#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ui_mainwindow.h"
#include <qstring.h>

typedef enum {
    EXIT,
    LOAD,
    SAVE,
    SCALE,
    ROTATE,
    SHIFT,
    DRAW,
    SET_UI,
    SET_SCENE,
} request_t;

enum controller_errors {
    ALL_OK, // :)
    NO_GRAPH,
    BAD_ARGS,
    NO_MEMORY,
};

typedef union {
    FILE *f;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
} req_data_t;

int handle(request_t req, req_data_t *req_data);

#endif // CONTROLLER_H

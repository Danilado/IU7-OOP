#ifndef MODEL_CONVERTERS_H
#define MODEL_CONVERTERS_H

#include "draw_model.h"
#include "model.h"

#include <QColor>
#include <QLineF>
#include <QPainter>
#include <QPointF>
#include <QString>

QPointF *point_to_QPointF(point_t pt, offset_t offset);
QLineF *connection_to_QLineF(connection_t con, offset_t offset);

#endif

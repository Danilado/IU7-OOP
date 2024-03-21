#include "model_converters.hpp"

QPointF *point_to_QPointF(point_t pt, offset_t &offset) {
  if (pt == nullptr)
    return nullptr;

  return new QPointF(pt->x + offset.offset_x, pt->y + offset.offset_y);
}

QLineF *connection_to_QLineF(connection_t con, offset_t &offset) {
  if (con == nullptr)
    return nullptr;

  point_t p1 = con->p1;
  point_t p2 = con->p2;

  if (p1 == nullptr || p2 == nullptr)
    return nullptr;

  return new QLineF(p1->x + offset.offset_x, p1->y + offset.offset_y,
                    p2->x + offset.offset_x, p2->y + offset.offset_y);
}

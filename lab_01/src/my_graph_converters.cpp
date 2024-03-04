#include "my_graph_converters.h"

QPointF *point_to_QPointF(point_t pt, offset_t offset)
{
  if (pt == nullptr)
    return nullptr;

  return new QPointF(point_get_x(pt) + offset.offset_x, point_get_y(pt) + offset.offset_y);
}

QLineF *connection_to_QLineF(connection_t con, offset_t offset)
{
  if (con == nullptr)
    return nullptr;

  point_t p1 = connection_get_p1(con);
  point_t p2 = connection_get_p2(con);

  if (p1 == nullptr || p2 == nullptr)
    return nullptr;

  return new QLineF(point_get_x(p1) + offset.offset_x, point_get_y(p1) + offset.offset_y,
                    point_get_x(p2) + offset.offset_x, point_get_y(p2) + offset.offset_y);
}

#include "controller.hpp"
#include <QDebug>

int handle(request_t req)
{
  static model_t graph = nullptr;
  int rc = 0;

  switch (req.option)
  {
  case (EXIT):
    destroy_model(graph);
    break;

  case (LOAD):
    rc = handle_load(graph, req.io_data);
    break;

  case (SAVE):
    rc = handle_save(graph, req.io_data);
    break;

  case (SCALE):
    rc = handle_scale(graph, req.t_data);
    break;

  case (SHIFT):
    rc = handle_shift(graph, req.t_data);
    break;

  case (ROTATE):
    rc = handle_rotate(graph, req.t_data);
    break;

  case (DRAW):
    rc = handle_draw(graph, req.d_data);
    break;

  default:
    rc = UNKNOWN_COMMAND;
    break;
  }

  qDebug() << rc;

  return rc;
}

#include "controller.h"

int handle(request_t req)
{
    static graph_t graph = nullptr;
    int rc = 0;

    switch (req.option)
    {
    case (EXIT):
        destroy_graph(graph);
        break;

    case (LOAD):
        rc = handle_load(req.io_data, graph);
        break;

    case (SAVE):
        rc = handle_save(req.io_data, graph);
        break;

    case (SCALE):
        rc = handle_scale(req.t_data, graph);
        break;

    case (SHIFT):
        rc = handle_shift(req.t_data, graph);
        break;

    case (ROTATE):
        rc = handle_rotate(req.t_data, graph);
        break;

    case (DRAW):
        rc = handle_draw(req.d_data, graph);
        break;

    default:
        rc = UNKNOWN_COMMAND;
        break;
    }

    return rc;
}

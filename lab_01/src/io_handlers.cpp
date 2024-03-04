#include "io_handlers.h"

#include "my_graph_file_io.h"

int handle_load(io_data_t data, graph_t &gr)
{
    graph_t new_graph = nullptr;
    int rc = create_graph_from_file(new_graph, data.filename);

    if (rc)
        return rc;

    if (gr != nullptr)
        destroy_graph(gr);

    gr = new_graph;

    return 0;
}

int handle_save(io_data_t data, const graph_t gr)
{
    return write_graph_to_file(gr, data.filename);
}

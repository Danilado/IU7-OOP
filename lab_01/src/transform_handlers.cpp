#include "transform_handlers.h"

int handle_scale(transform_data_t data, graph_t gr)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (data.origin == nullptr)
        return TRANSFORM_NO_ORIGIN;

    if (data.values == nullptr)
        return TRANSFORM_NO_DATA;

    int rc = graph_apply_scale(gr, data.origin, data.values);

    return rc;
}

int handle_rotate(transform_data_t data, graph_t gr)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (data.origin == nullptr)
        return TRANSFORM_NO_ORIGIN;

    if (data.values == nullptr)
        return TRANSFORM_NO_DATA;

    int rc = graph_apply_rotate(gr, data.origin, data.values);

    return rc;
}

int handle_shift(transform_data_t data, graph_t gr)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (data.values == nullptr)
        return TRANSFORM_NO_DATA;

    int rc = graph_apply_shift(gr, data.values);

    return rc;
}

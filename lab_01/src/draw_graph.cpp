#include "draw_graph.h"
#include "my_graph_converters.h"

int draw_graph(graph_t gr, QPainter *ctx, draw_params_t params)
{
    if (gr == nullptr)
        return DRAW_NO_GRAPH;

    if (ctx == nullptr)
        return DRAW_NO_CONTEXT;

    int rc = 0;

    rc = draw_connections(gr, ctx, params);
    if (!rc)
        rc = draw_points(gr, ctx, params);

    return rc;
}

int draw_connections(graph_t gr, QPainter *ctx, draw_params_t params)
{
    if (gr == nullptr)
        return DRAW_NO_GRAPH;
    if (ctx == nullptr)
        return DRAW_NO_CONTEXT;

    int rc = 0;

    ctx->setPen(params.colors.linecolor);

    size_t len = graph_get_con_len(gr);

    for (size_t i = 0; !rc && i < len; ++i)
    {
        connection_t tmp = graph_get_connection(gr, i);
        if (tmp == nullptr)
            rc = GRAPH_BAD_CONNECTION;

        if (!rc)
        {
            QLineF *tmpline = connection_to_QLineF(tmp, params.offset);
            if (tmpline == nullptr)
                rc = GRAPH_BAD_CONNECTION;

            if (!rc)
            {
                ctx->drawLine(*tmpline);
                delete tmpline;
            }
        }
    }

    return rc;
}

int draw_points(graph_t gr, QPainter *ctx, draw_params_t params)
{
    if (gr == nullptr)
        return DRAW_NO_GRAPH;
    if (ctx == nullptr)
        return DRAW_NO_CONTEXT;

    int rc = 0;

    ctx->setBrush(params.colors.pointcolor);

    size_t len = graph_get_pt_len(gr);
    for (size_t i = 0; !rc && i < len; ++i)
    {
        point_t tmp = graph_get_point(gr, i);
        if (tmp == nullptr)
            rc = GRAPH_BAD_POINT;

        if (!rc)
        {
            QPointF *tmppoint = point_to_QPointF(tmp, params.offset);
            if (tmppoint == nullptr)
                rc = GRAPH_BAD_POINT;

            if (!rc)
            {
                ctx->drawPoint(*tmppoint);
                delete tmppoint;
            }
        }
    }

    return rc;
}

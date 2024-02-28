#include "controller.h"

#include "my_graph.h"
#include "my_graph_funcs.h"

static int handle_load(graph_t* gr_ptr, FILE* f)
{
    if (f == nullptr)
        return BAD_ARGS;

    if (*gr_ptr != nullptr)
        destroy_graph(gr_ptr);

    *gr_ptr = create_graph_from_file(f);

    return *gr_ptr != nullptr;
}

static int handle_save(const graph_t gr, FILE* f)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (f == nullptr)
        return BAD_ARGS;

    write_graph_to_file(gr, f);

    return 0;
}

static int handle_scale(graph_t gr, Ui::MainWindow* ui)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (ui == nullptr)
        return BAD_ARGS;

    point_t origin = create_point(ui->scale_Cx->value(),
                                  ui->scale_Cy->value(),
                                  ui->scale_Cz->value());
    if (origin == nullptr)
        return NO_MEMORY;

    graph_apply_scale(gr,
                      origin,
                      ui->scale_Kx->value(),
                      ui->scale_Ky->value(),
                      ui->scale_Kz->value());

    destroy_point(&origin);

    return 0;
}

static int handle_rotate(graph_t gr, Ui::MainWindow* ui)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (ui == nullptr)
        return BAD_ARGS;

    point_t origin = create_point(ui->rotate_Cx->value(),
                                  ui->rotate_Cy->value(),
                                  ui->rotate_Cz->value());
    if (origin == nullptr)
        return NO_MEMORY;

    graph_apply_rotate(gr,
                       origin,
                       ui->rotate_Ax->value(),
                       ui->rotate_Ay->value(),
                       ui->rotate_Az->value());

    destroy_point(&origin);

    return 0;
}

static int handle_shift(graph_t gr, Ui::MainWindow* ui)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (ui == nullptr)
        return BAD_ARGS;

    graph_apply_shift(gr, ui->shift_Dx->value(), ui->shift_Dy->value(), ui->shift_Dz->value());

    return 0;
}

static int handle_draw(const graph_t gr, Ui::MainWindow* ui, QGraphicsScene* scene)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (ui == nullptr)
        return BAD_ARGS;

    if (scene == nullptr)
        return BAD_ARGS;

    QImage img = QImage(ui->canvas->width(), ui->canvas->height(), QImage::Format_RGB32);
    QPainter p(&img);

    p.fillRect(0, 0, ui->canvas->width(), ui->canvas->height(), QColor(255, 255, 255));

    draw_graph(gr,
               &p,
               QColor(0, 0, 0),
               QColor(200, 0, 0),
               ui->canvas->width() / 2,
               ui->canvas->height() / 2);

    QPixmap pixmap = QPixmap::fromImage(img);
    scene->clear();
    scene->addPixmap(pixmap);
    ui->canvas->setScene(scene);

    return 0;
}

int handle(request_t req, req_data_t* req_data)
{
    static graph_t gr = nullptr;
    static Ui::MainWindow* ui = nullptr;
    static QGraphicsScene* scene = nullptr;
    int rc = 0;

    switch (req) {
    case (SET_UI): {
        ui = req_data->ui;
    } break;

    case (SET_SCENE): {
        scene = req_data->scene;
    } break;

    case (EXIT): {
        destroy_graph(&gr);
    } break;

    case (LOAD): {
        if (req_data != nullptr)
            rc = handle_load(&gr, req_data->f);
        else
            rc = BAD_ARGS;
    } break;

    case (SAVE): {
        if (req_data != nullptr)
            rc = handle_save(gr, req_data->f);
        else
            rc = BAD_ARGS;
    } break;

    case (SCALE): {
        rc = handle_scale(gr, ui);
    } break;

    case (ROTATE): {
        rc = handle_rotate(gr, ui);
    } break;

    case (SHIFT): {
        rc = handle_shift(gr, ui);
    } break;

    case (DRAW): {
        rc = handle_draw(gr, ui, scene);
    } break;
    }

    return rc;
}

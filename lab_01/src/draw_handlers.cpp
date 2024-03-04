#include "draw_handlers.h"
#include "draw_graph.h"
#include "ui_mainwindow.h"

int handle_draw(draw_data_t data, const graph_t gr)
{
    if (gr == nullptr)
        return NO_GRAPH;

    if (data.ui == nullptr)
        return DRAW_NO_UI;

    if (data.scene == nullptr)
        return DRAW_NO_SCENE;

    QImage img = QImage(data.ui->canvas->width(), data.ui->canvas->height(), QImage::Format_RGB32);
    QPainter p(&img);

    p.fillRect(0, 0, data.ui->canvas->width(), data.ui->canvas->height(), QColor(255, 255, 255));

    int rc = 0;

    draw_params_t params = {(colors_t){QColor(0, 0, 0), QColor(200, 0, 0)},
                            (offset_t){(double) data.ui->canvas->width() / 2,
                                       (double) data.ui->canvas->height() / 2}};

    rc = draw_graph(gr, &p, params);

    if (!rc) {
        QPixmap pixmap = QPixmap::fromImage(img);
        data.scene->clear();
        data.scene->addPixmap(pixmap);
        data.ui->canvas->setScene(data.scene);
    }

    return rc;
}

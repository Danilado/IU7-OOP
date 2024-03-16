#include "draw_handlers.hpp"
#include "draw_model.hpp"
#include "ui_mainwindow.h"

static QImage get_context(Ui::MainWindow *ui) {
  return QImage(ui->canvas->width(), ui->canvas->height(),
                QImage::Format_RGB32);
}

static void wrap_clear_bg(QPainter *painter, Ui::MainWindow *ui) {
  painter->fillRect(0, 0, ui->canvas->width(), ui->canvas->height(),
                    QColor(255, 255, 255));
}

static void clear_bg(canvas_data_t canv_data, Ui::MainWindow *ui) {
  wrap_clear_bg(canv_data.p, ui);
}

static draw_params_t get_params(Ui::MainWindow *ui) {
  return draw_params_t{
      .colors = colors_t{.linecolor = QColor(0, 0, 0),
                         .pointcolor = QColor(200, 0, 0)},
      .offset = offset_t{.offset_x = (double)ui->canvas->width() / 2,
                         .offset_y = (double)ui->canvas->height() / 2},
  };
}

static int draw_image(QImage &img, QGraphicsScene *scene, Ui::MainWindow *ui) {
  if (ui == nullptr)
    return DRAW_NO_UI;

  if (scene == nullptr)
    return DRAW_NO_SCENE;

  QPixmap pixmap = QPixmap::fromImage(img);
  scene->clear();
  scene->addPixmap(pixmap);
  ui->canvas->setScene(scene);

  return ALL_OK;
}

canvas_data_t form_canvas_data(Ui::MainWindow *ui) {
  canvas_data_t res;
  res.img = get_context(ui);
  res.p = new QPainter(&res.img);
  return res;
}

void clear_canvas_data(canvas_data_t canv_data) { delete canv_data.p; }

int handle_draw(const model_t gr, draw_data_t data) {
  if (gr == nullptr)
    return NO_MODEL;

  if (data.ui == nullptr)
    return DRAW_NO_UI;

  if (data.scene == nullptr)
    return DRAW_NO_SCENE;

  canvas_data_t canv_data = form_canvas_data(data.ui);

  clear_bg(canv_data, data.ui);

  int rc = ALL_OK;

  draw_params_t params = get_params(data.ui);

  rc = draw_model(gr, canv_data, params);

  if (!rc)
    rc = draw_image(canv_data.img, data.scene, data.ui);

  clear_canvas_data(canv_data);
  return rc;
}

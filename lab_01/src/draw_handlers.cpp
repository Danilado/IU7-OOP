#include "draw_handlers.hpp"
#include "draw_model.hpp"
#include "ui_mainwindow.h"

static int clearQtBg(QPainter *painter, Ui::MainWindow *ui) {
  if (painter == nullptr)
    return DRAW_NO_UI;
  if (ui == nullptr)
    return DRAW_NO_UI;

  painter->fillRect(0, 0, ui->canvas->width(), ui->canvas->height(),
                    QColor(255, 255, 255));

  return ALL_OK;
}

static int clear_bg(const canvas_data_t &canv_data,
                    const draw_data_t &draw_data) {
  return clearQtBg(canv_data.p, draw_data.ui);
}

static int getQtColors(OUT colors_t &dst) {
  dst.linecolor = QColor(0, 0, 0);
  dst.pointcolor = QColor(200, 0, 0);
  return ALL_OK;
}

static int getQtOffset(OUT offset_t &dst, Ui::MainWindow *ui) {
  if (ui == nullptr)
    return DRAW_NO_UI;

  dst.offset_x = (double)ui->canvas->width() / 2;
  dst.offset_y = (double)ui->canvas->height() / 2;

  return ALL_OK;
}

static int get_params(draw_params_t &dst, const draw_data_t &draw_data) {
  int rc = getQtColors(dst.colors);
  if (!rc)
    rc = getQtOffset(dst.offset, draw_data.ui);
  return rc;
}

static int drawQtImage(const QImage &img, QGraphicsScene *scene,
                       Ui::MainWindow *ui) {
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

static int formQtCanvasData(OUT canvas_data_t &dst, Ui::MainWindow *ui) {
  if (ui == nullptr)
    return DRAW_NO_UI;

  dst.img =
      QImage(ui->canvas->width(), ui->canvas->height(), QImage::Format_RGB32);
  dst.p = new QPainter(&dst.img);

  return ALL_OK;
}

static int form_canvas_data(OUT canvas_data_t &dst,
                            const draw_data_t &draw_data) {
  return formQtCanvasData(dst, draw_data.ui);
}

static void clearQtCanvData(QPainter *&p) { delete p; }

static void clear_canvas_data(canvas_data_t &canv_data) {
  clearQtCanvData(canv_data.p);
}

static int show_image(const canvas_data_t &canv_data,
                      const draw_data_t &draw_data) {
  return drawQtImage(canv_data.img, draw_data.scene, draw_data.ui);
}

typedef struct {
  draw_data_t &d_data;
  canvas_data_t &canv_data;
  draw_params_t &params;
} image_draw_data_t;

static image_draw_data_t pack_image_d_data(draw_data_t &d_data,
                                           canvas_data_t &canv_data,
                                           draw_params_t &params) {
  return image_draw_data_t{
      .d_data = d_data, .canv_data = canv_data, .params = params};
}

static int draw_image_on_screen(const model_t model,
                                const image_draw_data_t &img_d_data) {
  int rc = clear_bg(img_d_data.canv_data, img_d_data.d_data);
  if (!rc) {
    rc = draw_model(model, img_d_data.canv_data, img_d_data.params);
    if (!rc)
      rc = show_image(img_d_data.canv_data, img_d_data.d_data);
  }
  return rc;
}

int handle_draw(const model_t model, draw_data_t &draw_data) {
  if (model == nullptr)
    return NO_MODEL;

  canvas_data_t canv_data;
  int rc = form_canvas_data(canv_data, draw_data);
  if (!rc) {
    draw_params_t params;
    rc = get_params(params, draw_data);
    if (!rc) {
      image_draw_data_t img_d_data =
          pack_image_d_data(draw_data, canv_data, params);

      rc = draw_image_on_screen(model, img_d_data);
    }
    clear_canvas_data(canv_data);
  }
  return rc;
}

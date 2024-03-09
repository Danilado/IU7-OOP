#include "draw_handlers.hpp"
#include "draw_model.hpp"
#include "ui_mainwindow.h"

static QImage get_context(Ui::MainWindow *ui)
{
  return QImage(ui->canvas->width(), ui->canvas->height(),
                QImage::Format_RGB32);
}

static void clear_bg(QPainter &painter, Ui::MainWindow *ui)
{
  painter.fillRect(0, 0, ui->canvas->width(), ui->canvas->height(),
                   QColor(255, 255, 255));
}

static draw_params_t get_params(Ui::MainWindow *ui)
{
  return (draw_params_t){
      .colors = (colors_t){
          .linecolor = QColor(0, 0, 0),
          .pointcolor = QColor(200, 0, 0)},
      .offset = (offset_t){.offset_x = (double)ui->canvas->width() / 2, .offset_y = (double)ui->canvas->height() / 2},
  };
}

static int draw_image(QImage &img, QGraphicsScene *scene, Ui::MainWindow *ui)
{
  if (ui == nullptr)
    return DRAW_NO_UI;

  if (scene == nullptr)
    return DRAW_NO_SCENE;

  QPixmap pixmap = QPixmap::fromImage(img);
  scene->clear();
  scene->addPixmap(pixmap);
  ui->canvas->setScene(scene);

  return 0;
}

int handle_draw(const model_t gr, draw_data_t data)
{
  if (gr == nullptr)
    return NO_MODEL;

  if (data.ui == nullptr)
    return DRAW_NO_UI;

  if (data.scene == nullptr)
    return DRAW_NO_SCENE;

  QImage img = get_context(data.ui);
  QPainter p(&img);

  clear_bg(p, data.ui);

  int rc = 0;

  draw_params_t params = get_params(data.ui);

  rc = draw_model(gr, &p, params);

  if (!rc)
    rc = draw_image(img, data.scene, data.ui);

  return rc;
}

#ifndef BUILDMAP_DIALOG_H
#define BUILDMAP_DIALOG_H

#include <QDialog>
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/tool_manager.h>

namespace Ui {
class Buildmap_Dialog;
}

class Buildmap_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Buildmap_Dialog(QWidget *parent = 0);
  ~Buildmap_Dialog();

public Q_SLOTS:
  void on_back_btn_clicked();

  void on_mapping_btn_clicked();

  void on_forward_btn_clicked();

  void on_leftturn_btn_clicked();

  void on_stop_btn_clicked();

  void on_rightturn_btn_clicked();

  void on_backward_btn_clicked();

private:
  Ui::Buildmap_Dialog *ui;

  rviz::VisualizationManager *manager_;
  rviz::RenderPanel *render_panel_;
  rviz::Display *map_;
  QTimer *m_timer;
};

#endif // BUILDMAP_DIALOG_H

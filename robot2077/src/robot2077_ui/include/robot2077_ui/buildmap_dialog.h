#ifndef BUILDMAP_DIALOG_H
#define BUILDMAP_DIALOG_H

#include <QDialog>
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/tool_manager.h>
#include "CCtrlDashBoard.h"
#include "QProcess"
#include <QStandardItemModel>
#include <QTreeWidgetItem>
#include <QComboBox>
#include <QSpinBox>
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <map>
#include <QKeyEvent>
namespace Ui {
class Buildmap_Dialog;
}

class Buildmap_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Buildmap_Dialog(QWidget *parent = 0);
  ~Buildmap_Dialog();

Q_SIGNALS:

  void movemsg_create(float x, float y, float z);

public Q_SLOTS:
    void on_mapping_btn_clicked();
    void on_back_btn_clicked();

    void movemsg_btn_color(float x, float y, float z);

  private slots:
    void on_left_btn_clicked();

    void on_stop_btn_clicked();

    void on_right_btn_clicked();

    void on_leftturn_btn_clicked();

    void on_forward_btn_clicked();

    void on_rightturn_btn_clicked();

    void on_backward_btn_clicked();

private:
  Ui::Buildmap_Dialog *ui;

  rviz::VisualizationManager *manager_;
  rviz::RenderPanel *render_panel_;
  rviz::Display *map_;
  QTimer *m_timer;
  void keyPressEvent(QKeyEvent *event);
};

#endif // BUILDMAP_DIALOG_H

#ifndef DETECT_GRAB_DIALOG_H
#define DETECT_GRAB_DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/tool_manager.h>
#include <rviz/yaml_config_reader.h>
#include <visualization_msgs/Marker.h>

namespace Ui {
class Detect_Grab_Dialog;
}

class Detect_Grab_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Detect_Grab_Dialog(QWidget *parent = 0);
  ~Detect_Grab_Dialog();

public Q_SLOTS:
  void on_back_btn_clicked();

  void on_detect_btn_clicked();

  void get_detectmsg(int num);

  void getButtonText(bool check);

private:
  Ui::Detect_Grab_Dialog *ui;

  rviz::VisualizationManager *manager_;
  rviz::RenderPanel *render_panel_;
};

#endif // DETECT_GRAB_DIALOG_H

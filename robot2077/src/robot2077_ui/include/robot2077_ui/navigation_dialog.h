#ifndef NAVIGATION_DIALOG_H
#define NAVIGATION_DIALOG_H

#include <QDialog>
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/tool.h>
#include <rviz/tool_manager.h>
#include <waterplus_map_tools/Waypoint.h>
#include "robot2077_ui/loadWayPoint.h"

namespace Ui {
class Navigation_Dialog;
}

class Navigation_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Navigation_Dialog(QWidget *parent = 0);
  ~Navigation_Dialog();

Q_SIGNALS:

  void navigationmsg_create(WayPoint msg);

public Q_SLOTS:
  void on_back_btn_clicked();

  //void on_set_pos_btn_clicked();

  void on_set_goal_btn_clicked();

  void on_mapselect_btn_clicked();

  void on_mapshow_btn_clicked();

  void on_save_goal_btn_clicked();

  void getButtonText(bool check);

private:
  Ui::Navigation_Dialog *ui;

  QString mapfile;

  QString mapname;

  QString xmlfile;
  std::vector<WayPoint> arr;

  rviz::VisualizationManager *manager_;
  rviz::RenderPanel *render_panel_;
  rviz::Display *map_;
  rviz::Tool *current_tool_;
  rviz::ToolManager *tool_manager_;

};

#endif // NAVIGATION_DIALOG_H

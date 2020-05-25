#ifndef NAVIGATION_DIALOG_H
#define NAVIGATION_DIALOG_H

#include <QDialog>
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/tool.h>
#include <rviz/tool_manager.h>

namespace Ui {
class Navigation_Dialog;
}

class Navigation_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Navigation_Dialog(QWidget *parent = 0);
  ~Navigation_Dialog();

public Q_SLOTS:
  void on_back_btn_clicked();

  //void on_set_pos_btn_clicked();

  void on_set_goal_btn_clicked();

private:
  Ui::Navigation_Dialog *ui;

  rviz::VisualizationManager *manager_;
  rviz::RenderPanel *render_panel_;
  rviz::Display *map_;
  rviz::Tool *current_tool_;
  rviz::ToolManager *tool_manager_;

};

#endif // NAVIGATION_DIALOG_H

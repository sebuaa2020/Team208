#include "../include/robot2077_ui/navigation_dialog.h"
#include "ui_navigation_dialog.h"
// add by xq
Navigation_Dialog::Navigation_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Navigation_Dialog)
{
  ui->setupUi(this);
  render_panel_ = new rviz::RenderPanel();
  ui->mapdisplay_layout->addWidget(render_panel_);
  manager_ = new rviz::VisualizationManager(render_panel_);
  tool_manager_ = manager_->getToolManager();
  render_panel_->initialize(manager_->getSceneManager(), manager_);
  manager_->initialize();
  manager_->startUpdate();

  manager_->removeAllDisplays();

  rviz::Display *map_ = manager_->createDisplay("rviz/Map", "adjustable map", true);
  ROS_ASSERT(map_!=NULL);
  map_->subProp("Topic")->setValue("/map");

  rviz::Display *robot_ = manager_->createDisplay("rviz/RobotModel", "adjustable robot", true);
  ROS_ASSERT(robot_!=NULL);
  robot_->subProp("Robot Description")->setValue("robot_description");

  rviz::Display *laser_ = manager_->createDisplay("rviz/LaserScan", "adjustable scan", true);
  ROS_ASSERT(laser_!=NULL);
  laser_->subProp("Topic")->setValue("/robot2077/slam/scan");
  laser_->subProp("Size (m)")->setValue("0.1");
}

Navigation_Dialog::~Navigation_Dialog()
{
  delete ui;
}

void Navigation_Dialog::on_back_btn_clicked()
{
    this->close();
}

/*void Navigation_Dialog::on_set_pos_btn_clicked()
{
  current_tool_ = tool_manager_->addTool("rviz/SetInitialPose");
  tool_manager_->setCurrentTool(current_tool_);
  manager_->startUpdate();
}*/

void Navigation_Dialog::on_set_goal_btn_clicked()
{
  current_tool_ = tool_manager_->addTool("rviz/SetGoal");
  rviz::Property *pro = current_tool_->getPropertyContainer();
  pro->subProp("Topic")->setValue("move_base_simple/goal");
  manager_->setFixedFrame("map");
  tool_manager_->setCurrentTool(current_tool_);

  manager_->startUpdate();
}

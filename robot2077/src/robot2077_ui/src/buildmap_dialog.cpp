#include "../include/robot2077_ui/buildmap_dialog.h"
#include "ui_buildmap_dialog.h"

Buildmap_Dialog::Buildmap_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Buildmap_Dialog)
{
  ui->setupUi(this);
  render_panel_ = new rviz::RenderPanel;
  ui->mapdisplay_layout->addWidget(render_panel_);
  manager_ = new rviz::VisualizationManager(render_panel_);
  render_panel_->initialize(manager_->getSceneManager(), manager_);
  manager_->initialize();
  manager_->startUpdate();
}

Buildmap_Dialog::~Buildmap_Dialog()
{
  delete ui;
}

void Buildmap_Dialog::on_back_btn_clicked()
{
  this->close();
}

void Buildmap_Dialog::on_mapping_btn_clicked()
{
  manager_->removeAllDisplays();

  rviz::Display *map_ = manager_->createDisplay("rviz/Map", "adjustable map", true);
  ROS_ASSERT(map_!=NULL);
  map_->subProp("Topic")->setValue("/map");

  rviz::Display *robot_ = manager_->createDisplay("rviz/RobotModel", "adjustable robot", true);
  ROS_ASSERT(robot_!=NULL);
  robot_->subProp("Robot Description")->setValue("robot_description");

  rviz::Display *laser_ = manager_->createDisplay("rviz/LaserScan", "adjustable scan", true);
  ROS_ASSERT(laser_!=NULL);
  laser_->subProp("Topic")->setValue("/scan");
  laser_->subProp("Size (m)")->setValue("0.1");
}

void Buildmap_Dialog::on_forward_btn_clicked()
{

}

void Buildmap_Dialog::on_leftturn_btn_clicked()
{

}

void Buildmap_Dialog::on_stop_btn_clicked()
{

}

void Buildmap_Dialog::on_rightturn_btn_clicked()
{

}

void Buildmap_Dialog::on_backward_btn_clicked()
{

}

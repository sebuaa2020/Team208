#include "../include/robot2077_ui/navigation_dialog.h"
#include "ui_navigation_dialog.h"
#include "QMessageBox"
#include "QFileDialog"
// add by xq
Navigation_Dialog::Navigation_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Navigation_Dialog)
{
  ui->setupUi(this);

  mapfile = "";

  render_panel_ = new rviz::RenderPanel();
  ui->mapdisplay_layout->addWidget(render_panel_);
  manager_ = new rviz::VisualizationManager(render_panel_);
  tool_manager_ = manager_->getToolManager();
  render_panel_->initialize(manager_->getSceneManager(), manager_);
  manager_->initialize();
  manager_->startUpdate();

  /*rviz::Display *laser_ = manager_->createDisplay("rviz/LaserScan", "adjustable scan", true);
  ROS_ASSERT(laser_!=NULL);
  laser_->subProp("Topic")->setValue("/robot2077/slam/scan");
  laser_->subProp("Size (m)")->setValue("0.1");*/
}

Navigation_Dialog::~Navigation_Dialog()
{
  delete ui;
}

void Navigation_Dialog::on_back_btn_clicked()
{
    QString str = "gnome-terminal -x bash -c 'source ~/GIT/Team208/robot2077/devel/setup.bash; rosnode kill /navi_move_trans '&";
    system(str.toLatin1().data());
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

void Navigation_Dialog::on_mapselect_btn_clicked()
{
    /*QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("选择地图"));
    fileDialog->setDirectory("~/GIT/Team208/robot2077/src/robot2077_slam/maps/");
    fileDialog->setNameFilter(tr("Map file(*.yaml)"));
    mapfile = fileDialog->getOpenFileName();*/
    mapfile = QFileDialog::getOpenFileName(this, tr("选择地图"), "..", "", 0);
}

void Navigation_Dialog::on_mapshow_btn_clicked()
{
    if (mapfile == "")
    {
        QMessageBox::information(this, tr("ERROR"), tr("请先选择地图"));
    }
    else
    {
        manager_->setFixedFrame("/map");
        manager_->removeAllDisplays();

        rviz::Display *map_ = manager_->createDisplay("rviz/Map", "adjustable map", true);
        ROS_ASSERT(map_!=NULL);
        map_->subProp("Topic")->setValue("/map");

        rviz::Display *robot_ = manager_->createDisplay("rviz/RobotModel", "adjustable robot", true);
        ROS_ASSERT(robot_!=NULL);
        robot_->subProp("Robot Description")->setValue("robot_description");
        QString str = "gnome-terminal -x bash -c 'source ~/GIT/Team208/robot2077/devel/setup.bash; roslaunch robot2077_ui navigation.launch map_file:=" + mapfile + "'&";
        system(str.toLatin1().data());
    }
}

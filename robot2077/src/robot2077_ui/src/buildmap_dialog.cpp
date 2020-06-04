#include "../include/robot2077_ui/buildmap_dialog.h"
#include "ui_buildmap_dialog.h"
#include "QMessageBox"
// add by xq
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

  ui->map_name->setPlaceholderText("请输入地图名称");

  // add to move control
  setFocusPolicy(Qt::StrongFocus);
  connect(this, SIGNAL(movemsg_create(float,float,float)), this, SLOT(movemsg_btn_color(float,float,float)));
}

Buildmap_Dialog::~Buildmap_Dialog()
{
  delete ui;
}

// func call when click bace
void Buildmap_Dialog::on_back_btn_clicked()
{
  QString str = "gnome-terminal -x bash -c 'source ~/Team208/robot2077/devel/setup.bash; rosnode kill /slam_gmapping '&";
  system(str.toLatin1().data());
  this->close();
}

// func call when click mapping
void Buildmap_Dialog::on_mapping_btn_clicked()
{
  QString str = "gnome-terminal -x bash -c 'source ~/Team208/robot2077/devel/setup.bash; roslaunch robot2077_ui slam.launch '&";
  system(str.toLatin1().data());

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


// func blow to listen control and show
void Buildmap_Dialog::movemsg_btn_color(float x, float y, float z)
{
  ui->forward_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->backward_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->left_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->right_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->leftturn_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->rightturn_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->stop_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  if (x > 0.2)
    ui->forward_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  else if (x < -0.2)
    ui->backward_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  if (y > 0.2)
    ui->left_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  else if (y < -0.2)
    ui->right_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  if (z > 0.2)
    ui->leftturn_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  else if (z < -0.2)
    ui->rightturn_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  if (x == 0 && y == 0 && z == 0)
    ui->stop_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
}

void Buildmap_Dialog::on_left_btn_clicked()
{
  float x = 0;
  float y = 1;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void Buildmap_Dialog::on_stop_btn_clicked()
{
  float x = 0;
  float y = 0;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void Buildmap_Dialog::on_right_btn_clicked()
{
  float x = 0;
  float y = -1;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void Buildmap_Dialog::on_leftturn_btn_clicked()
{
  float x = 0;
  float y = 0;
  float z = 1;
  Q_EMIT movemsg_create(x, y, z);
}

void Buildmap_Dialog::on_forward_btn_clicked()
{
  float x = 1;
  float y = 0;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void Buildmap_Dialog::on_rightturn_btn_clicked()
{
  float x = 0;
  float y = 0;
  float z = -1;
  Q_EMIT movemsg_create(x, y, z);
}

void Buildmap_Dialog::on_backward_btn_clicked()
{
  float x = -1;
  float y = 0;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void Buildmap_Dialog::keyPressEvent(QKeyEvent *event)
{
  float x = 0;
  float y = 0;
  float z = 0;
  switch(event->key()) {
  case Qt::Key_W:
    x = 1;
    y = 0;
    z = 0;
    break;
  case Qt::Key_Q:
    x = 1;
    y = 0;
    z = 1;
    break;
  case Qt::Key_E:
    x = 1;
    y = 0;
    z = -1;
    break;
  case Qt::Key_A:
    x = 0;
    y = 0;
    z = 1;
    break;
  case Qt::Key_S:
    x = 0;
    y = 0;
    z = 0;
    break;
  case Qt::Key_D:
    x = 0;
    y = 0;
    z = -1;
    break;
  case Qt::Key_Z:
    x = -1;
    y = 0;
    z = 1;
    break;
  case Qt::Key_X:
    x = -1;
    y = 0;
    z = 0;
    break;
  case Qt::Key_C:
    x = -1;
    y = 0;
    z = -1;
    break;
  default:
    x = 0;
    y = 0;
    z = 0;
    break;
  }

  Q_EMIT movemsg_create(x, y, z);
}

// func to save map
void Buildmap_Dialog::on_map_save_clicked()
{
   std::string map_name = ui->map_name->text().toStdString();
   if (map_name == "")
   {
       QMessageBox::information(this, tr("ERROR"), tr("地图名不能为空"));
   }
   else
   {
       std::string s1="rosrun map_server map_saver -f ~/Team208/robot2077/src/robot2077_slam/maps/" + map_name;
       std::stringstream ss;
       ss<<"gnome-terminal -x bash -c 'source ~/Team208/robot2077/devel/setup.bash;"<< s1 << "'";
       system(ss.str().c_str());
       QMessageBox::information(this, tr("提示"), tr("保存成功"));
   }
}

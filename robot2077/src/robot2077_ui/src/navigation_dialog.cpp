#include "../include/robot2077_ui/navigation_dialog.h"
#include "../include/robot2077_ui/loadWayPoint.h"
#include "ui_navigation_dialog.h"
#include "QMessageBox"
#include "QFileDialog"
#include "QCheckBox"
// add by xq
Navigation_Dialog::Navigation_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Navigation_Dialog)
{
  ui->setupUi(this);

  mapfile = "";
  mapname = "";
  xmlfile = "";

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
  /*current_tool_ = tool_manager_->addTool("rviz/SetGoal");
  rviz::Property *pro = current_tool_->getPropertyContainer();
  pro->subProp("Topic")->setValue("move_base_simple/goal");
  manager_->setFixedFrame("map");
  tool_manager_->setCurrentTool(current_tool_);*/

  current_tool_ = tool_manager_->addTool("rviz/AddWaypoint");
  rviz::Property *pro = current_tool_->getPropertyContainer();
  pro->subProp("Topic")->setValue("/waterplus/add_waypoint");
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
    QString mapname = "所选地图:" + mapfile.right(mapfile.length() - mapfile.lastIndexOf("/") - 1);
    ui->map_name->setText(mapname);
}

void Navigation_Dialog::on_mapshow_btn_clicked()
{
    if (mapfile == "")
    {
        QMessageBox::information(this, tr("ERROR"), tr("请先选择地图"));
    }
    else if (mapfile.right(mapfile.length() - mapfile.lastIndexOf(".") - 1) != "yaml")
    {
        QMessageBox::information(this, tr("ERROR"), tr("地图文件后缀名应为yaml"));
    }
    else
    {
        mapname = mapfile.mid(mapfile.lastIndexOf("/") + 1, mapfile.lastIndexOf(".") - mapfile.lastIndexOf("/") - 1);

        xmlfile = mapfile.left(mapfile.indexOf("/robot2077_slam")) + "/robot2077_navigation/waypoints/" + mapname + ".xml";
        //QMessageBox::information(this, tr("ERROR"), xmlfile);
        arr = LoadWaypointsFromFile(xmlfile.toStdString());
        /*for (int i = 0;i< arr.size();i++)
            QMessageBox::information(this, tr("ERROR"), QString::fromStdString(arr[i].name));*/

        ui->target_list_widget->clear();
        for (int i=0;i<arr.size();i++)
        {
            QListWidgetItem *item = new QListWidgetItem();
            QString description = QString::fromStdString(arr[i].name);
            QCheckBox *box = new QCheckBox(description);
            box->setCheckable(true);
            connect(box, SIGNAL(clicked(bool)), this, SLOT(getButtonText(bool)));
            ui->target_list_widget->addItem(item);
            ui->target_list_widget->setItemWidget(item, box);
        }

        manager_->setFixedFrame("/map");
        manager_->removeAllDisplays();

        rviz::Display *map_ = manager_->createDisplay("rviz/Map", "adjustable map", true);
        ROS_ASSERT(map_!=NULL);
        map_->subProp("Topic")->setValue("/map");

        rviz::Display *robot_ = manager_->createDisplay("rviz/RobotModel", "adjustable robot", true);
        ROS_ASSERT(robot_!=NULL);
        robot_->subProp("Robot Description")->setValue("robot_description");

        rviz::Display *mark_ = manager_->createDisplay("rviz/Marker", "adjustable mark", true);
        if (mark_!=NULL)
        {
          ROS_ASSERT(mark_!=NULL);
          mark_->subProp("Marker Topic")->setValue("/waypoints_marker");
        }

        /*rviz::Display *path_ = manager_->createDisplay("rviz/Path", "adjustable path", true);
        if (path_!=NULL)
        {
          ROS_ASSERT(path_!=NULL);
          path_->subProp("Topic")->setValue("/move_base/NavfnROS/plan");
        }*/

        QString str = "gnome-terminal -x bash -c 'source ~/GIT/Team208/robot2077/devel/setup.bash; roslaunch robot2077_ui navigation.launch map_file:=" + mapfile + " waypoint_name:="+ mapname + "'&";
        system(str.toLatin1().data());
    }
}

void Navigation_Dialog::on_save_goal_btn_clicked()
{
    if (mapfile == "")
    {
        QMessageBox::information(this, tr("ERROR"), tr("请先选择地图"));
    }
    else
    {
        QString str = "gnome-terminal -x bash -c 'source ~/GIT/Team208/robot2077/devel/setup.bash; roslaunch robot2077_ui pointsave.launch map_name:="+ mapname + "'&";
        system(str.toLatin1().data());
        QMessageBox::information(this, tr("提示"), tr("保存成功"));
    }
}

void Navigation_Dialog::getButtonText(bool check)
{
    if (check == true)
    {
        QCheckBox *box = (QCheckBox *)(sender());
        box->setChecked(false);
            for (int i =0;i<arr.size();i++)
            {
                if (arr[i].name == box->text().toStdString())
                    Q_EMIT navigationmsg_create(arr[i]);
            }
        QString str = "移动到目标" + box->text();
        QMessageBox::information(this, tr("提示"), str);
    }
}

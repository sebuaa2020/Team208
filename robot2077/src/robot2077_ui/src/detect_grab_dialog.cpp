#include "../include/robot2077_ui/detect_grab_dialog.h"
#include "ui_detect_grab_dialog.h"
// add by xq
Detect_Grab_Dialog::Detect_Grab_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Detect_Grab_Dialog)
{
  ui->setupUi(this);

  std::string filename;
  ros::param::get("rvizconfig_detect", filename);
  rviz::YamlConfigReader reader;
  rviz::Config config;
  reader.readFile(config, QString::fromStdString(filename));

  render_panel_ = new rviz::RenderPanel;
  ui->detect_layout->addWidget(render_panel_);
  manager_ = new rviz::VisualizationManager(render_panel_);

  render_panel_->initialize(manager_->getSceneManager(), manager_);
  manager_->initialize();
  //manager_->load(config);
  manager_->startUpdate();
  manager_->setFixedFrame("/base_footprint");
}

Detect_Grab_Dialog::~Detect_Grab_Dialog()
{
  delete ui;
}

void Detect_Grab_Dialog::on_back_btn_clicked()
{
    this->close();
}

void Detect_Grab_Dialog::on_detect_btn_clicked()
{
  manager_->removeAllDisplays();

  rviz::Display *grid_ = manager_->createDisplay( "rviz/Grid", "adjustable grid", true);
  ROS_ASSERT(grid_!=NULL);
  grid_->subProp( "Line Style" )->setValue("Billboards");

  /*rviz::Display *map_ = manager_->createDisplay("rviz/Map", "adjustable map", true);
    ROS_ASSERT(map_!=NULL);
    map_->subProp("Topic")->setValue("/map");*/


  //机器人模型
    rviz::Display *robot_ = manager_->createDisplay("rviz/RobotModel", "adjustable robot", true);
    ROS_ASSERT(robot_!=NULL);
    robot_->subProp("Robot Description")->setValue("robot_description");

    /*rviz::Display *laser_ = manager_->createDisplay("rviz/LaserScan", "adjustable scan", true);
    ROS_ASSERT(laser_!=NULL);
    laser_->subProp("Topic")->setValue("/scan");
    laser_->subProp("Size (m)")->setValue("0.1");*/

    //相机
  rviz::Display *camera_ = manager_->createDisplay("rviz/PointCloud2", "adjustable camera", true);
  ROS_ASSERT(camera_!=NULL);
  camera_->subProp("Topic")->setValue("/kinect2/sd/points");
  camera_->subProp("Size (m)")->setValue("0.01");
  camera_->subProp("Alpha")->setValue("1");
/*
  rviz::Display *camera_RGB_ = manager_->createDisplay("rviz/Kinect2_RGB", "adjustable camera_RGB", true);
  ROS_ASSERT(camera_RGB_!=NULL);
  camera_RGB_->subProp("Image Topic")->setValue("/kinect2/hd/image_color_rect");*/


  //目标检测信息
  /*rviz::Display *pc_pub_ = manager_->createDisplay("rviz/PointCloud2", "adjustable pc", true);
  ROS_ASSERT(pc_pub_!=NULL);
  pc_pub_->subProp("Topic")->setValue("/robot2077/obj_detect/obj_pc");*/

  rviz::Display *mark_pub_ = manager_->createDisplay("rviz/Marker", "adjustable mark", true);
  if (mark_pub_!=NULL)
  {
    ROS_ASSERT(mark_pub_!=NULL);
    mark_pub_->subProp("Marker Topic")->setValue("/robot2077/obj_detect/obj_mark");
  }
  //mark_pub_->setTopic("/robot2077/obj_detect/obj_mark", "visualization_msgs::Marker");
  //mark_pub_->subProp("Queue Size")->setValue("100");

  /*rviz::Display *seg_objs_ = manager_->createDisplay("rviz/PointCloud2", "adjustable objs", true);
  ROS_ASSERT(seg_objs_!=NULL);
  seg_objs_->subProp("Topic")->setValue("/robot2077/obj_detect/segment_objs");

  rviz::Display *seg_planes_ = manager_->createDisplay("rviz/PointCloud2", "adjustable planes", true);
  ROS_ASSERT(seg_planes_!=NULL);
  seg_planes_->subProp("Topic")->setValue("/robot2077/obj_detect/segment_planes");*/
}

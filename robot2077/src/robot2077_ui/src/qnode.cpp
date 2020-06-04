/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/
// add by xq
/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/robot2077_ui/qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace robot2077_ui {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"robot2077_ui");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
  movemsg_subscriber = n.subscribe("/cmd_vel", 10, &QNode::movemsg_sub_callback, this);
  movemsg_publisher = n.advertise<robot2077_basic::Movemsg>("/robot2077/robot_move/vel", 10);
  navigation_publisher = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 10);
  joy_subscriber = n.subscribe("/joy", 10, &QNode::joy_sub_callback, this);
  detectmsg_subscriber = n.subscribe("/robot2077/obj_detect/obj_count", 10, &QNode::detect_sub_callback, this);
	start();
	return true;
}

/*bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"robot2077_ui");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
	start();
	return true;
}*/

void QNode::run() {


  ros::spin();
  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
  Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QNode::movemsg_sub_callback(const geometry_msgs::TwistConstPtr &msg) {
  /*robot2077_basic::Movemsg msg_n;
  msg_n.x = msg->x;
  msg_n.y = msg->y;
  msg_n.z = msg->z;*/
  float x = msg->linear.x;
  float y = msg->linear.y;
  float z = msg->angular.z;
//ROS_INFO_STREAM("listened!");
  Q_EMIT QNode::movemsg_updated(x, y, z);
}

void QNode::movemsg_send(float x, float y, float z) {
  robot2077_basic::Movemsg vel;
  vel.x = x;
  vel.y = y;
  vel.z = z;
  movemsg_publisher.publish(vel);
  //ROS_INFO_STREAM("send!");
}

void QNode::navigationmsg_send(WayPoint msg) {
    ros::Rate loop_rate(50);
    int count = 5;
    while(ros::ok()) {
        geometry_msgs::PoseStamped goal;
        goal.header.stamp = ros::Time::now();
        goal.header.frame_id = "map";
        goal.pose.position.x = msg.pos_x;
        goal.pose.position.y = msg.pos_y;
        goal.pose.position.z = msg.pos_z;
        goal.pose.orientation.x = msg.ori_x;
        goal.pose.orientation.y = msg.ori_y;
        goal.pose.orientation.z = msg.ori_z;
        goal.pose.orientation.w = msg.ori_w;
        navigation_publisher.publish(goal);

        ros::spinOnce();
        loop_rate.sleep();
        if (!count--) break;
    }
}

void QNode::joy_sub_callback(const sensor_msgs::JoyConstPtr &msg)
{
  std::cout << "------------------------------" << std::endl;
  ROS_INFO("LEFT STICK %.6f, %.6f", msg->axes[0], msg->axes[1]);
  ROS_INFO("RIGHT STICK %.6f, %.6f", msg->axes[3], msg->axes[4]);
  ROS_INFO("LT %.6f, LB %d", msg->axes[2], msg->buttons[4]);
  ROS_INFO("RT %.6f, RB %d", msg->axes[5], msg->buttons[5]);
  ROS_INFO("A %d", msg->buttons[0]);

  robot2077_basic::Movemsg vel;
  if (msg->buttons[0]) {
      vel.x = 0;
      vel.y = 0;
      vel.z = 0;
  } else {
      vel.x = fabs(msg->axes[1]) >= 0.2 ? msg->axes[1] : 0;
      vel.y = fabs(msg->axes[0]) >= 0.2 ? msg->axes[0] : 0;
      vel.z = fabs(msg->axes[3]) >= 0.2 ? msg->axes[3] : 0;
  }
  movemsg_publisher.publish(vel);
  Q_EMIT QNode::joymsg(vel.x, vel.y, vel.z);
}

void QNode::detect_sub_callback(const std_msgs::UInt16ConstPtr &msg)
{
    int num = msg->data;
    Q_EMIT QNode::detectmsg(num);
}

}  // namespace robot2077_ui

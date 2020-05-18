/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

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
  ros::Rate loop_rate(1);
	int count = 0;
  while ( ros::ok() ) {

    /*std_msgs::String msg;
		std::stringstream ss;
		ss << "hello world " << count;
		msg.data = ss.str();
    chatter_publisher.publish(msg);*/
		ros::spinOnce();
		loop_rate.sleep();
    ++count;
  }
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
ROS_INFO_STREAM("listened!");
  Q_EMIT QNode::movemsg_updated(x, y, z);
}

void QNode::movemsg_send(float x, float y, float z) {
  robot2077_basic::Movemsg vel;
  vel.x = x;
  vel.y = y;
  vel.z = z;
  movemsg_publisher.publish(vel);
  ROS_INFO_STREAM("send!");
}

}  // namespace robot2077_ui

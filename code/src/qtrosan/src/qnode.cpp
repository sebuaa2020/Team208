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
#include "../include/qtrosan/qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtrosan {

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
	ros::init(init_argc,init_argv,"qtrosan");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
  chatter_publisher = n.advertise<robot2077_basic::Movemsg>("/robot2077_basic/robot_move/vel", 10);
  chatter_subscriber = n.subscribe("/robot2077_basic/robot_move/vel", 10, &QNode::subscribe_callback, this);
	start();
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"qtrosan");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
  chatter_publisher = n.advertise<robot2077_basic::Movemsg>("/robot2077_basic/robot_move/vel", 10);
  chatter_subscriber = n.subscribe("/robot2077_basic/robot_move/vel", 10, &QNode::subscribe_callback, this);
	start();
	return true;
}

void QNode::run() {
	ros::Rate loop_rate(1);
  vel.x = 1;
  vel.y = 0;
  vel.z = 0;
	while ( ros::ok() ) {

    /*std_msgs::String msg;
		std::stringstream ss;
		ss << "hello world " << count;
    msg.data = ss.str();*/
    chatter_publisher.publish(vel);
    //log(Info,std::string("I sent: ")+msg.data);
		ros::spinOnce();
		loop_rate.sleep();
    //++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

void QNode::subscribe(const robot2077_basic::Movemsg &msg)
{
  subscribe_model.insertRows(subscribe_model.rowCount(), 1);
  QVariant new_row(QString("x = %6").arg(msg.x)+QString(" y = %6").arg(msg.y) + QString(" z = %6").arg(msg.z));
  subscribe_model.setData(subscribe_model.index(subscribe_model.rowCount() - 1), new_row);
  Q_EMIT subscribeUpdated();
}

void QNode::subscribe_callback(const robot2077_basic::Movemsg::ConstPtr &msg)
{
  robot2077_basic::Movemsg msg_n;
  msg_n.x = msg->x;
  msg_n.y = msg->y;
  msg_n.z = msg->z;
  QNode::subscribe(msg_n);
}
void QNode::forward()
{
  vel.x = 1;
  vel.y = 0;
  vel.z = 0;
}

void QNode::stop()
{
  vel.x = 0;
  vel.y = 0;
  vel.z = 0;
}

void QNode::left()
{
  vel.x = 0;
  vel.y = 0;
  vel.z = 1;
}

void QNode::right()
{
  vel.x = 0;
  vel.y = 0;
  vel.z = -1;
}

}  // namespace qtrosan

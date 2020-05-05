#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include "robot2077_basic/Movemsg.h"
#include <iostream>

ros::Publisher vel_pub;

void joyListen(const sensor_msgs::Joy::ConstPtr& msg) {
    std::cout << "------------------------------" << std::endl;
    ROS_INFO("LEFT STICK %.6f, %.6f", msg->axes[0], msg->axes[1]);
    ROS_INFO("RIGHT STICK %.6f, %.6f", msg->axes[3], msg->axes[4]);
    ROS_INFO("LT %.6f, LB %d", msg->axes[2], msg->buttons[4]);
    ROS_INFO("RT %.6f, RB %d", msg->axes[5], msg->buttons[5]);
    
    robot2077_basic::Movemsg vel;
    vel.x = msg->axes[0];
    vel.y = msg->axes[1];
    vel.z = msg->axes[3];
    vel_pub.publish(vel);
    
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "user_listen");
    ros::NodeHandle n;
    
    vel_pub = n.advertise<robot2077_basic::Movemsg>("/robot2077/robot_move/vel", 1000);

    ros::Subscriber sub = n.subscribe("joy", 1000, joyListen);
    ros::spin();
    return 0;
}
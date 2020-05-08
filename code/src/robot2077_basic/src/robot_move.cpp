#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "robot2077_basic/Movemsg.h"
#include <iostream>

ros::Publisher vel_pub;
geometry_msgs::Twist vel;
geometry_msgs::Twist vel_zero;
bool avoidence_flag = false;

void move_listen(const robot2077_basic::Movemsg::ConstPtr& msg) {
    ROS_INFO("x: %.6f, y: %.6f, z: %.6f", msg->x, msg->y, msg->z);
    vel.linear.x = msg->x;
    vel.linear.y = msg->y;
    vel.linear.z = 0;
    vel.angular.x = 0;
    vel.angular.y = 0;
    vel.angular.z = msg->z;
    if (!avoidence_flag) vel_pub.publish(vel);
    else vel_pub.publish(vel_zero);
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "robot_move");
    ros::NodeHandle n;
    vel_zero.linear.x = 0;
    vel_zero.linear.y = 0;
    vel_zero.linear.z = 0;
    vel_zero.angular.x = 0;
    vel_zero.angular.y = 0;
    vel_zero.angular.z = 0;
    
    vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::Subscriber sub = n.subscribe("/robot2077/robot_move/vel", 10, move_listen);
    ros::spin();
    return 0;
}
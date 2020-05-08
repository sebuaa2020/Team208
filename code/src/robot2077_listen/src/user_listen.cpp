#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/String.h"
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
    vel.x = msg->axes[1];
    vel.y = msg->axes[0]; 
    vel.z = msg->axes[3];
    vel_pub.publish(vel);
}

void keyboardListen(const std_msgs::String::ConstPtr &msg) {
    std::cout << "------------------------------" << std::endl;
    ROS_INFO("KEYBOARD %s", msg->data.c_str());
    robot2077_basic::Movemsg vel;
    char key = msg->data[0];
    switch(key) {
    case 'a':
    case 'A':
        vel.x = 0;
        vel.y = 1;
        vel.z = 0;
        break;
    case 'd':
    case 'D':
        vel.x = 0;
        vel.y = -1;
        vel.z = 0;
        break;
    case 'w':
    case 'W':
        vel.x = 1;
        vel.y = 0;
        vel.z = 0;
        break;
    case 's':
    case 'S':
        vel.x = -1;
        vel.y = 0;
        vel.z = 0;
        break;
    case 'q':
    case 'Q':
        vel.x = 0;
        vel.y = 0;
        vel.z = 1;
        break;
    case 'e':
    case 'E':
        vel.x = 0;
        vel.y = 0;
        vel.z = -1;
        break;
    default:
        vel.x = 0;
        vel.y = 0;
        vel.z = 0;
        break;
    }
    vel_pub.publish(vel);

}

int main(int argc, char **argv) {

    ros::init(argc, argv, "user_listen");
    ros::NodeHandle n;
    
    vel_pub = n.advertise<robot2077_basic::Movemsg>("/robot2077/robot_move/vel", 10);

    ros::Subscriber sub_joy = n.subscribe("joy", 10, joyListen);
    ros::Subscriber sub_keyboard = n.subscribe("/robot2077/user_listen/keyboard", 10, keyboardListen);
    ros::spin();
    return 0;
}
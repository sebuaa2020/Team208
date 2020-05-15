#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "xbot_basic/Movemsg.h"
#include "xbot_basic/IsAvoidance.h"
#include <iostream>

double LINEAR_VEL_MAX_X = 0.5;
double LINEAR_VEL_MAX_Y = 0;
double ANGULAR_VEL_MAX = 0.4;

ros::Publisher vel_pub;
geometry_msgs::Twist vel_temp;

ros::ServiceClient checkAvoidance;

void move_listen(const xbot_basic::Movemsg::ConstPtr& msg) {
    ROS_INFO("x: %.6f, y: %.6f, z: %.6f", msg->x, msg->y, msg->z);
    vel_temp.linear.x = msg->x * LINEAR_VEL_MAX_X;
    vel_temp.linear.y = msg->y * LINEAR_VEL_MAX_Y;
    vel_temp.linear.z = 0;
    vel_temp.angular.x = 0;
    vel_temp.angular.y = 0;
    vel_temp.angular.z = msg->z * ANGULAR_VEL_MAX;
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "robot_move");
    ros::NodeHandle n;
    
    vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    checkAvoidance = n.serviceClient<xbot_basic::IsAvoidance>("/xbot/robot_move/is_avoidance");

    ros::Subscriber sub = n.subscribe("/xbot/robot_move/vel", 10, move_listen);
    
    ros::Rate loop_rate(10);
    while(ros::ok()) {
        
        geometry_msgs::Twist vel;
        vel.linear.x = vel_temp.linear.x;
        vel.linear.y = vel_temp.linear.y;
        vel.linear.z = vel_temp.linear.z;
        vel.angular.x = vel_temp.angular.x;
        vel.angular.y = vel_temp.angular.y;
        vel.angular.z = vel_temp.angular.z;

        xbot_basic::IsAvoidance srv;
        srv.request.x = vel.linear.x;
        srv.request.y = vel.linear.y;
        if (!checkAvoidance.call(srv)) vel_pub.publish(vel);
        else {
            vel.linear.x *= srv.response.k;
            vel.linear.y *= srv.response.k;
            vel_pub.publish(vel);
        }
        
        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
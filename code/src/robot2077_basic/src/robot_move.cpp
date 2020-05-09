#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "robot2077_basic/Movemsg.h"
#include "robot2077_basic/IsAvoidance.h"
#include <iostream>

double LINEAR_VEL_MAX = 0.5;
double ANGULAR_VEL_MAX = 0.4;

ros::Publisher vel_pub;


ros::ServiceClient checkAvoidance;



void move_listen(const robot2077_basic::Movemsg::ConstPtr& msg) {
    ROS_INFO("x: %.6f, y: %.6f, z: %.6f", msg->x, msg->y, msg->z);
    geometry_msgs::Twist vel;
    vel.linear.x = msg->x * LINEAR_VEL_MAX;
    vel.linear.y = msg->y * LINEAR_VEL_MAX;
    vel.linear.z = 0;
    vel.angular.x = 0;
    vel.angular.y = 0;
    vel.angular.z = msg->z * ANGULAR_VEL_MAX;

    robot2077_basic::IsAvoidance srv;
    srv.request.x = vel.linear.x;
    srv.request.y = vel.linear.y;
    if (!checkAvoidance.call(srv) || !srv.response.isavoidance) vel_pub.publish(vel);
    else {
        vel.linear.x = 0;
        vel.linear.y = 0;
        vel_pub.publish(vel);
    }
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "robot_move");
    ros::NodeHandle n;
    
    vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    checkAvoidance = n.serviceClient<robot2077_basic::IsAvoidance>("/robot2077/robot_move/is_avoidance");

    ros::Subscriber sub = n.subscribe("/robot2077/robot_move/vel", 10, move_listen);
    ros::spin();
    return 0;
}
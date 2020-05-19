#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "robot2077_basic/Movemsg.h"
#include "robot2077_basic/IsAvoidance.h"
#include <iostream>
// add by yzx
// 该节点控制机器人的运动行为
float LINEAR_VEL_MAX = 0.8;
float ANGULAR_VEL_MAX = 0.7;

ros::Publisher vel_pub;
geometry_msgs::Twist vel_temp;

ros::ServiceClient checkAvoidance;

float check_vel(float vel, float vel_max) {
	vel_max = fabs(vel_max);
	if (vel < -vel_max) vel = -vel_max;
	if (vel > vel_max) vel = vel_max;
	return vel;
}

void move_listen(const robot2077_basic::Movemsg::ConstPtr& msg) {
    ROS_INFO("x: %.6f, y: %.6f, z: %.6f", msg->x, msg->y, msg->z);
    vel_temp.linear.x = check_vel(msg->x, LINEAR_VEL_MAX);
    vel_temp.linear.y = check_vel(msg->y, LINEAR_VEL_MAX);
    vel_temp.linear.z = 0;
    vel_temp.angular.x = 0;
    vel_temp.angular.y = 0;
    vel_temp.angular.z = check_vel(msg->z, ANGULAR_VEL_MAX);
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "robot_move");
    ros::NodeHandle n;
    
    n.getParam("linear_vel_max", LINEAR_VEL_MAX);
    n.getParam("angular_vel_max", ANGULAR_VEL_MAX);
    ROS_INFO("Loading params, linear_vel_max: %.2f, angular_vel_max: %.2f", LINEAR_VEL_MAX, ANGULAR_VEL_MAX);

    vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    checkAvoidance = n.serviceClient<robot2077_basic::IsAvoidance>("/robot2077/robot_move/is_avoidance");

    ros::Subscriber sub = n.subscribe("/robot2077/robot_move/vel", 10, move_listen);
    
    ros::Rate loop_rate(10);
    while(ros::ok()) {
        
        geometry_msgs::Twist vel;
        vel.linear.x = vel_temp.linear.x;
        vel.linear.y = vel_temp.linear.y;
        vel.linear.z = vel_temp.linear.z;
        vel.angular.x = vel_temp.angular.x;
        vel.angular.y = vel_temp.angular.y;
        vel.angular.z = vel_temp.angular.z;

        robot2077_basic::IsAvoidance srv;
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

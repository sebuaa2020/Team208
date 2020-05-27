#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

float LINEAR_VEL_MAX = 0.8;
float ANGULAR_VEL_MAX = 0.7;

void check_cmd_vel(const geometry_msgs::Twist::ConstPtr& msg) {
    if (fabs(msg->linear.x) <= LINEAR_VEL_MAX &&
        fabs(msg->linear.y) <= LINEAR_VEL_MAX &&
        msg->linear.z == 0 &&
        msg->angular.x == 0 &&
        msg->angular.y == 0 &&
        fabs(msg->angular.z) == 0)
    {
    }
    else {
        
        ROS_ERROR("error msg in /cmd_vel: %.3f, %.3f, %.3f, %.3f, %.3f, %.3f",
            msg->linear.x,
            msg->linear.y,
            msg->linear.z,
            msg->angular.x,
            msg->angular.y,
            msg->angular.z
        );
        
    }
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_move");
    ros::NodeHandle n;

    n.getParam("linear_vel_max", LINEAR_VEL_MAX);
    n.getParam("angular_vel_max", ANGULAR_VEL_MAX);

    ros::Subscriber sub = n.subscribe("/cmd_vel", 10, check_cmd_vel);
    ros::spin();
    return 0;
}
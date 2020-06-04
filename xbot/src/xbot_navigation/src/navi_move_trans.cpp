#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "xbot_basic/Movemsg.h"
/*该节点的作用：
1. 接受navigation layer的Twist.msg
    Vector3  linear
    Vector3  angular
2. 转化为发送给运动模块的Movemsg.msg
    float32 x
    float32 y
    float32 z
*/
// 只有x,y的水平速度和z方向的转动速度
double LINEAR_VEL_MAX = 0.5;
double ANGULAR_VEL_MAX = 0.4;

xbot_basic::Movemsg movemsg;
ros::Publisher vel_pub;

void trans(const geometry_msgs::Twist::ConstPtr& vel) {
    movemsg.x = vel->linear.x / LINEAR_VEL_MAX;
    movemsg.y = vel->linear.y / LINEAR_VEL_MAX;
    movemsg.z = vel->angular.z / ANGULAR_VEL_MAX;
    vel_pub.publish(movemsg);
}
int main(int argc, char *argv[])
{
    /* code for main function */
    ros::init(argc, argv, "navi_move_trans");
    ros::NodeHandle n;

    vel_pub = n.advertise<xbot_basic::Movemsg>("/xbot/robot_move/vel", 10);
    ros::Subscriber sub_trans = n.subscribe("/xbot/robot_navi/vel", 10, trans);

    ros::spin();

    return 0;
}
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "robot2077_basic/IsAvoidance.h"
#include "robot2077_basic/utils.h"

// add by yzx
// 该节点控制机器人的避障行为
float AVOIDANCE_DIS_MAX = 1.0;
float AVOIDANCE_DIS_MIN = 0.4;

float range_cache[1000];
int range_size;
float range_angle_min, range_angle_max, range_angle_inc;

void laserListen(const sensor_msgs::LaserScan::ConstPtr &scan) {
    range_size = scan->ranges.size();
    range_angle_min = scan->angle_min / M_PI * 180;
    range_angle_max = scan->angle_max / M_PI * 180;
    range_angle_inc = scan->angle_increment / M_PI * 180;
    for (int i = 0; i < range_size; i++) range_cache[i] = scan->ranges[i];
    // ROS_INFO("Update the range_cache: %d, %.3f, %.3f, %.3f", range_size, range_angle_min, range_angle_max, range_angle_inc);
}


int getIndex(float theta) {
    theta = getTheta(theta);
    int ret =  (int)((theta - range_angle_min) / range_angle_inc);
    // printf("%.3f, %d, %.3f, %.3f\n", theta, ret, range_angle_min, range_angle_inc);
    if (ret < 0) ret = 0;
    if (ret >= range_size) ret = range_size - 1;
    return ret;
}

float getK(float dis) {
    if (dis >= AVOIDANCE_DIS_MAX) return 1.0;
    else if (dis <= AVOIDANCE_DIS_MIN) return 0.0;
    else return (dis - AVOIDANCE_DIS_MIN) / (AVOIDANCE_DIS_MAX - AVOIDANCE_DIS_MIN);
}

bool checkAvoidance(robot2077_basic::IsAvoidance::Request &req, robot2077_basic::IsAvoidance::Response &res) {
    if (range_size <= 0) {
        res.k = 0;
        return true;
    }
    float front = getTheta(req.x, req.y);
    float leftFront = front + 45; 
    float rightFront = front - 45; 

    
    float ret_k = 1.0, count = 0.0;
    float step = (leftFront - rightFront) / 10;
    for (float i = rightFront; i <= leftFront; i += step) {
        ret_k *= getK(range_cache[getIndex(i)]);
        count += 1;
    }
    ret_k = pow(ret_k, 1/count);
    ROS_INFO("%.3f, %.3f, %.3f, %.3f", front, getTheta(leftFront), getTheta(rightFront), ret_k);
    res.k = ret_k;
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_avoidance");
    ros::NodeHandle n;
    n.getParam("avoidance_dis_max", AVOIDANCE_DIS_MAX);
    n.getParam("avoidance_dis_min", AVOIDANCE_DIS_MIN);
    ROS_INFO("Loading param: avoidance_dis_max: %.2f, avoidance_dis_min: %.2f", AVOIDANCE_DIS_MAX, AVOIDANCE_DIS_MIN);

    ros::ServiceServer avoidanceServer = n.advertiseService("/robot2077/robot_move/is_avoidance", checkAvoidance);
    ROS_INFO("Robot Avoidance Server Start!");
    ros::Subscriber laserSub = n.subscribe("/scan", 10, &laserListen);
    ros::spin();
    return 0;
}

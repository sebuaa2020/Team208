#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "xbot_basic/IsAvoidance.h"
#include "cmath"

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
    // ROS_INFO("Update the range_cache: %d, front dis: %.3f", range_size, range_cache[range_size/2]);
}

int getTheta(float x, float y) {
    float eps = 1e-8;
    if(fabs(x) < eps) {
        if (fabs(y) < eps) return 0;
        if(y < 0) return -90;
        else return 90;
    }
    float theta = fabs(atan(y / x));
    theta = theta / M_PI * 180;
    if (x > 0 && y >= 0) {
        theta = 0 + theta;
    } else if (x > 0 && y <= 0) {
        theta = 0 - theta;
    } else if (x < 0 && y >= 0) {
        theta = 180 - theta;
    } else if (x < 0 && y <= 0) {
        theta = -180 + theta;
    }
    return theta;
}

int getIndex(float theta) {
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

bool checkAvoidance(xbot_basic::IsAvoidance::Request &req, xbot_basic::IsAvoidance::Response &res) {
    if (range_size <= 0) {
        res.k = 0;
        return true;
    }
    float front = getTheta(req.x, req.y);
    if (front < -90 || front > 90) {
        res.k = 0;
        return true;
    }
    float leftFront = front + 45; 
    float rightFront = front - 45; 

    
    float ret_k = 1.0, count = 0.0;
    for (int i = getIndex(rightFront); i <= getIndex(leftFront); i += 27) {
        ret_k *= getK(range_cache[i]);
        count += 1;
    }
    ROS_INFO("%.3f, %.3f", ret_k, 1/count);
    ret_k = pow(ret_k, 1/count);
    ROS_INFO("%.3f", ret_k);
    res.k = ret_k;
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_avoidance");
    ros::NodeHandle n;

    ros::ServiceServer avoidanceServer = n.advertiseService("/xbot/robot_move/is_avoidance", checkAvoidance);
    ROS_INFO("Robot Avoidance Server Start!");
    ros::Subscriber laserSub = n.subscribe("/scan", 10, &laserListen);
    ros::spin();
    return 0;
}

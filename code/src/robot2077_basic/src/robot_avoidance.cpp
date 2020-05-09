#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "robot2077_basic/IsAvoidance.h"

float AVOIDANCE_DIS = 1.5;
float range_cache[400];

void laserListen(const sensor_msgs::LaserScan::ConstPtr &scan) {
    int size = scan->ranges.size();
    for (int i = 0; i < size; i++) range_cache[i] = scan->ranges[i];
    ROS_INFO("Update the range_cache: %d", size);
}

int getTheta(float x, float y) {
    float eps = 1e-8;
    printf("%f\n", eps);
    if(fabs(x) < eps) {
        if(y < 0) return 270;
        else return 90;
    }
    float theta = fabs(atan(y / x));
    theta = theta / M_PI * 180;
    if (x > 0 && y >= 0) {
        theta = 180 - theta;
    } else if (x > 0 && y <= 0) {
        theta = 180 + theta;
    } else if (x < 0 && y >= 0) {
        theta = 0 + theta;
    } else if (x < 0 && y <= 0) {
        theta = 360 - theta;
    }
    return (int)theta;
}

bool checkAvoidance(robot2077_basic::IsAvoidance::Request &req, robot2077_basic::IsAvoidance::Response &res) {
    int front = getTheta(req.x, req.y);
    int leftFront = front - 45; if(leftFront < 0) leftFront += 360;
    int left = front - 90; if(left < 0) left += 360;
    int rightFront = front + 45; if(rightFront >= 360) rightFront -= 360;
    int right = front + 90; if(right >= 360) right -= 360;
    ROS_INFO("Left: %.3f, LeftFront: %.3f, Front: %.3f, RightFront: %.3f, Rigth: %.3f", 
        range_cache[left], range_cache[leftFront], range_cache[front], range_cache[rightFront], range_cache[right]);
    if (range_cache[front] > AVOIDANCE_DIS &&
        range_cache[leftFront] > AVOIDANCE_DIS &&
        range_cache[left] > AVOIDANCE_DIS &&
        range_cache[rightFront] > AVOIDANCE_DIS &&
        range_cache[right] > AVOIDANCE_DIS
    ) res.isavoidance = false;
    else res.isavoidance = true;
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_avoidance");
    ros::NodeHandle n;

    ros::ServiceServer avoidanceServer = n.advertiseService("/robot2077/robot_move/is_avoidance", checkAvoidance);
    ROS_INFO("Robot Avoidance Server Start!");
    ros::Subscriber laserSub = n.subscribe("/scan", 10, &laserListen);
    ros::spin();
    return 0;
}
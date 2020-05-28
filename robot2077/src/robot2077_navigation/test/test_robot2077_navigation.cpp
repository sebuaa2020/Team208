#include <gtest/gtest.h>
#include "geometry_msgs/Twist.h"
#include "robot2077_basic/Movemsg.h"
#include <ros/ros.h>

double LINEAR_VEL_MAX = 0.8;
double ANGULAR_VEL_MAX = 0.7;
robot2077_basic::Movemsg movemsg;

void trans(geometry_msgs::Twist vel) {
    movemsg.x = vel.linear.x / LINEAR_VEL_MAX;
    movemsg.y = vel.linear.y / LINEAR_VEL_MAX;
    movemsg.z = vel.angular.z / ANGULAR_VEL_MAX;
}


TEST(trans_test, test1) {
    geometry_msgs::Twist vel;
    vel.linear.x = 0;
    vel.linear.y = 0;
    vel.angular.z = 0;
    trans(vel);
    EXPECT_EQ(movemsg.x, 0);
    EXPECT_EQ(movemsg.y, 0);
    EXPECT_EQ(movemsg.z, 0);
}

TEST(trans_test, test2) {
    geometry_msgs::Twist vel;
    vel.linear.x = 0.8;
    vel.linear.y = 0.8;
    vel.angular.z = 0.7;
    trans(vel);
    EXPECT_EQ(movemsg.x, 1);
    EXPECT_EQ(movemsg.y, 1);
    EXPECT_EQ(movemsg.z, 1);
}

int main(int argc, char **argv) {
    srand(time(0));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
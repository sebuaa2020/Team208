#include <robot2077_basic/utils.h>
#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>

TEST(getTheta_test, test1) {
    float x = 0, y = 0;
    float theta = getTheta(x, y);
    EXPECT_LE(theta, 180);
    EXPECT_GT(theta, -180);
    EXPECT_EQ(theta, 0);
}

TEST(getTheta_test, test2) {
    float x = 0, y = 1;
    float theta = getTheta(x, y);
    EXPECT_LE(theta, 180);
    EXPECT_GT(theta, -180);
    EXPECT_EQ(theta, 90);
}

TEST(getTheta_test, test3) {
    float x = 0, y = -1;
    float theta = getTheta(x, y);
    EXPECT_LE(theta, 180);
    EXPECT_GT(theta, -180);
    EXPECT_EQ(theta, -90);
}

TEST(getTheta_test, test4) {
    float x = -1, y = 0;
    float theta = getTheta(x, y);
    EXPECT_LE(theta, 180);
    EXPECT_GT(theta, -180);
    EXPECT_EQ(theta, 180);
}

TEST(getTheta_test, test5) {
    float x = 1, y = 1;
    float theta = getTheta(x, y);
    EXPECT_LE(theta, 180);
    EXPECT_GT(theta, -180);
    EXPECT_EQ(theta, 45);
}

TEST(getTheta_test, test6) {
    float x = -1, y = 1;
    float theta = getTheta(x, y);
    EXPECT_LE(theta, 180);
    EXPECT_GT(theta, -180);
    EXPECT_EQ(theta, 135);
}

TEST(getTheta_test, test7) {
    float x = 1, y = -1;
    float theta = getTheta(x, y);
    EXPECT_LE(theta, 180);
    EXPECT_GT(theta, -180);
    EXPECT_EQ(theta, -45);
}

TEST(getTheta_test, test8) {
    float x = -1, y = -1;
    float theta = getTheta(x, y);
    EXPECT_LE(theta, 180);
    EXPECT_GT(theta, -180);
    EXPECT_EQ(theta, -135);
}

TEST(getTheta_test, test9) {
    float x = 0, y = 0;
    for (int i = 0; i < 1000; i++) {
        x = (float)(rand() % 100 - 50) / 100;
        y = (float)(rand() % 100 - 50) / 100;
        float theta = getTheta(x, y);
        EXPECT_LE(theta, 180);
        EXPECT_GT(theta, -180);   
    }
}

TEST(getTheta_test, test10) {
    float theta = 0;
    for (int i = 0; i < 1000; i++) {
        theta = rand() % 10000 - 5000;
        theta = getTheta(theta);
        EXPECT_LE(theta, 180);
        EXPECT_GE(theta, -180);   
    }
}

TEST(check_vel_test, test1) {
    float vel, vel_max, r_vel;
    for (int i = 0; i < 1000; i++) {
        vel = (rand() % 10000 - 5000) / 10000.0;
        vel_max = (rand() % 5000) / 10000.0;
        r_vel = check_vel(vel, vel_max);
        EXPECT_GE(r_vel, -vel_max);
        EXPECT_LE(r_vel, vel_max);
        if (vel > vel_max) EXPECT_EQ(r_vel, vel_max);
        else if (vel < -vel_max) EXPECT_EQ(r_vel, -vel_max);
        else EXPECT_EQ(r_vel, vel);
    }
}

int main(int argc, char **argv) {
    srand(time(0));
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
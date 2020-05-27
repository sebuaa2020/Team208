#include <robot2077_basic/get_theta.h>
#include <gtest/gtest.h>

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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
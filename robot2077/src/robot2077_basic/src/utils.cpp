#include "robot2077_basic/utils.h"

float getTheta(float x, float y) {
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

float getTheta(float theta) {
    while(theta < -180) theta += 360;
    while(theta > 180) theta -= 360;
    return theta;
}

float check_vel(float vel, float vel_max) {
	vel_max = fabs(vel_max);
	if (vel < -vel_max) vel = -vel_max;
	if (vel > vel_max) vel = vel_max;
	return vel;
}
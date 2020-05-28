#ifndef TEST_H
#define TEST_H

#include <QTime>
#include <geometry_msgs/Twist.h>

class test
{
public:
  test();

  geometry_msgs::Twist gettestvalue();
};

#endif // TEST_H

#include "test.h"

test::test()
{

}

geometry_msgs::Twist gettestvalue()    //生成各向随机速度值
{
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
  geometry_msgs::Twist vel;
  vel.linear.x = float((qrand() % 10000)/5000 - 1);
  vel.linear.y = float((qrand() % 10000)/5000 - 1);
  vel.angular.z = float((qrand() % 10000)/5000 - 1);
  return vel;
}

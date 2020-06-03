/**
 * @file /include/robot2077_ui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef robot2077_ui_QNODE_HPP_
#define robot2077_ui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/UInt16.h"
#include "robot2077_basic/Movemsg.h"


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace robot2077_ui {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
  //bool init(const std::string &master_url, const std::string &host_url);
  void run();
  void movemsg_sub_callback(const geometry_msgs::TwistConstPtr& msg);

	/*********************
	** Logging
  **********************/

Q_SIGNALS:
    void rosShutdown();

    void movemsg_updated(float x, float y, float z);
    void joymsg(float x, float y, float z);
    void detectmsg(int num);

public Q_SLOTS:

    void movemsg_send(float x, float y, float z);

private:
	int init_argc;
	char** init_argv;
  ros::Publisher movemsg_publisher;
  ros::Subscriber movemsg_subscriber;
  ros::Subscriber joy_subscriber;
  ros::Subscriber detectmsg_subscriber;

  void joy_sub_callback(const sensor_msgs::JoyConstPtr& msg);
  void detect_sub_callback(const std_msgs::UInt16ConstPtr& msg);
};

}  // namespace robot2077_ui

#endif /* robot2077_ui_QNODE_HPP_ */

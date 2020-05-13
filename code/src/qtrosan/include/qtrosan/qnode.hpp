/**
 * @file /include/qtrosan/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qtrosan_QNODE_HPP_
#define qtrosan_QNODE_HPP_

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
#include "robot2077_basic/Movemsg.h"


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtrosan {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
  QStringListModel* subscribeModel() { return &subscribe_model; }
	void log( const LogLevel &level, const std::string &msg);
  void subscribe( const robot2077_basic::Movemsg &msg);
  void subscribe_callback(const robot2077_basic::Movemsg::ConstPtr& msg);

  void forward();
  void stop();
  void left();
  void right();

Q_SIGNALS:
	void loggingUpdated();
  void subscribeUpdated();
    void rosShutdown();

private:
	int init_argc;
	char** init_argv;
	ros::Publisher chatter_publisher;
  ros::Subscriber chatter_subscriber;
    QStringListModel logging_model;
    QStringListModel subscribe_model;
    robot2077_basic::Movemsg vel;
};

}  // namespace qtrosan

#endif /* qtrosan_QNODE_HPP_ */

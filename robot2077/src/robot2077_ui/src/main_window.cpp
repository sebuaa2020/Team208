/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/
// add by xq
#include <QtGui>
#include <QMessageBox>
#include <QLabel>
#include <QFileDialog>
#include <QMetaType>
#include <iostream>
#include "../include/robot2077_ui/main_window.hpp"
#include "../include/robot2077_ui/usercontrol_dialog.h"
#include "../include/robot2077_ui/myviz.h"
#include "../include/robot2077_ui/loadWayPoint.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace robot2077_ui {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

    qRegisterMetaType<WayPoint>("WayPoint");

    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

    ReadSettings();
	setWindowIcon(QIcon(":/images/icon.png"));
  //ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    QObject::connect(ui.usercontrol_btn, SIGNAL(clicked()), this, SLOT(usercontrol_change()));

    qnode.init();

    std::string logo;
    ros::param::get("logo", logo);
    QImage *image= new QImage;
    image->load(QString::fromStdString(logo));
    ui.theme->setPixmap(QPixmap::fromImage(*image));
    ui.theme->setScaledContents(true);
    ui.theme->resize(ui.theme->width(), ui.theme->height());

	/*********************
	** Logging
  **********************/

    /*********************
    ** Auto Start
    **********************/
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "robot2077_ui");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://192.168.1.2:11311/")).toString();
    QString host_url = settings.value("host_url", QString("192.168.1.3")).toString();
    //QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    //ui.line_edit_master->setText(master_url);
    //ui.line_edit_host->setText(host_url);
    //ui.line_edit_topic->setText(topic_name);
    //bool remember = settings.value("remember_settings", false).toBool();
    //ui.checkbox_remember_settings->setChecked(remember);
    //bool checked = settings.value("use_environment_variables", false).toBool();
    //ui.checkbox_use_environment->setChecked(checked);
    //if ( checked ) {
    //	ui.line_edit_master->setEnabled(false);
    //	ui.line_edit_host->setEnabled(false);
    	//ui.line_edit_topic->setEnabled(false);
    //}
}

void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "robot2077_ui");
    //settings.setValue("master_url",ui.line_edit_master->text());
    //settings.setValue("host_url",ui.line_edit_host->text());
    //settings.setValue("topic_name",ui.line_edit_topic->text());
    //settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    //settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));

}

void MainWindow::on_usercontrol_btn_clicked()
{
  UserControl_Dialog* dlg = new UserControl_Dialog();
  connect(&qnode, SIGNAL(movemsg_updated(float, float, float)), dlg, SLOT(movemsg_get(float, float, float)));
  connect(dlg, SIGNAL(movemsg_create(float,float,float)), &qnode, SLOT(movemsg_send(float,float,float)));
  connect(&qnode, SIGNAL(joymsg(float,float,float)), dlg, SLOT(movemsg_btn_color(float,float,float)));
  dlg->exec();
}

void MainWindow::usercontrol_change() {

}

void MainWindow::on_buildmap_btn_clicked()
{
  //system("gnome-terminal -x bash -c 'source ~/catkin_ws/devel/setup.bash; roslaunch robot2077_slam gmapping.launch'&");
  Buildmap_Dialog* dlg = new Buildmap_Dialog();
  //connect(&qnode, SIGNAL(movemsg_updated(float, float, float)), dlg, SLOT(movemsg_get(float, float, float)));
  connect(dlg, SIGNAL(movemsg_create(float,float,float)), &qnode, SLOT(movemsg_send(float,float,float)));
  connect(&qnode, SIGNAL(joymsg(float,float,float)), dlg, SLOT(movemsg_btn_color(float,float,float)));
  dlg->exec();
}

void MainWindow::on_navigation_btn_clicked()
{
  Navigation_Dialog* dlg = new Navigation_Dialog();
  connect(dlg, SIGNAL(navigationmsg_create(WayPoint)), &qnode, SLOT(navigationmsg_send(WayPoint)));
  dlg->exec();
}

void MainWindow::on_detect_grab_btn_clicked()
{
  //system("gnome-terminal -x bash -c 'source ~/catkin_ws/devel/setup.bash; roslaunch wpb_sim wpb_rviz.launch'&");
  Detect_Grab_Dialog* dlg = new Detect_Grab_Dialog();
  connect(&qnode, SIGNAL(detectmsg(int)), dlg, SLOT(get_detectmsg(int)));
  dlg->exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	WriteSettings();
	QMainWindow::closeEvent(event);
}

}  // namespace robot2077_ui


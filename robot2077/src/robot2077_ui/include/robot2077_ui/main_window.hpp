/**
 * @file /include/robot2077_ui/main_window.hpp
 *
 * @brief Qt based gui for robot2077_ui.
 *
 * @date November 2010
 **/
#ifndef robot2077_ui_MAIN_WINDOW_H
#define robot2077_ui_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtWidgets/QMainWindow>
#include <QMetaType>
#include <rviz/visualization_manager.h>

#include "ui_main_window.h"
#include "qnode.hpp"
#include "usercontrol_dialog.h"
#include "buildmap_dialog.h"
#include "detect_grab_dialog.h"
#include "navigation_dialog.h"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace robot2077_ui {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void on_actionAbout_triggered();
  void on_button_connect_clicked(bool check );

  void on_usercontrol_btn_clicked();
  void usercontrol_change();

  void on_buildmap_btn_clicked();

  void on_navigation_btn_clicked();

  void on_detect_grab_btn_clicked();

    /******************************************
    ** Manual connections
    *******************************************/

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace robot2077_ui

#endif // robot2077_ui_MAIN_WINDOW_H

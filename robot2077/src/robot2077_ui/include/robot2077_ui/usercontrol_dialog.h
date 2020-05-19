#ifndef USERCONTROL_DIALOG_H
#define USERCONTROL_DIALOG_H

#include <QDialog>
#include "robot2077_basic/Movemsg.h"

#include "CCtrlDashBoard.h"
#include "QProcess"
#include <QStandardItemModel>
#include <QTreeWidgetItem>
#include <QComboBox>
#include <QSpinBox>
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <map>
#include <QKeyEvent>

namespace Ui {
class UserControl_Dialog;
}

class UserControl_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit UserControl_Dialog(QWidget *parent = 0);
  ~UserControl_Dialog();

Q_SIGNALS:

  void movemsg_create(float x, float y, float z);


public Q_SLOTS:
  void on_back_btn_clicked();

  void movemsg_get(float x, float y, float z);

  void movemsg_btn_color(float x, float y, float z);

private slots:
  void on_left_btn_clicked();

  void on_stop_btn_clicked();

  void on_right_btn_clicked();

  void on_leftturn_btn_clicked();

  void on_forward_btn_clicked();

  void on_rightturn_btn_clicked();

  void on_backword_btn_clicked();

private:
  Ui::UserControl_Dialog *ui;
  void keyPressEvent(QKeyEvent *event);

  CCtrlDashBoard *DashBoard_x;
  CCtrlDashBoard *DashBoard_y;
  CCtrlDashBoard *DashBoard_z;
};

#endif // USERCONTROL_DIALOG_H

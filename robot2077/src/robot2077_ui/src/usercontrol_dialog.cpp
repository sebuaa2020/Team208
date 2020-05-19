#include "../include/robot2077_ui/usercontrol_dialog.h"
#include "ui_usercontrol_dialog.h"
// add by xq
UserControl_Dialog::UserControl_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::UserControl_Dialog)
{

  ui->setupUi(this);

  DashBoard_x = new CCtrlDashBoard(ui->speed_x_widget);
  DashBoard_x->setGeometry(ui->speed_x_widget->rect());
  DashBoard_x->setValue(0);
  DashBoard_x->setUnit(0);
  DashBoard_y = new CCtrlDashBoard(ui->speed_y_widget);
  DashBoard_y->setGeometry(ui->speed_y_widget->rect());
  DashBoard_y->setValue(0);
  DashBoard_y->setUnit(0);
  DashBoard_z = new CCtrlDashBoard(ui->speed_z_widget);
  DashBoard_z->setGeometry(ui->speed_z_widget->rect());
  DashBoard_z->setValue(0);
  DashBoard_z->setUnit(1);

}

UserControl_Dialog::~UserControl_Dialog()
{
  delete ui;
}

void UserControl_Dialog::on_back_btn_clicked()
{
  this->close();
}

void UserControl_Dialog::movemsg_get(const float x, const float y, const float z) {
  ui->forward_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->backword_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->left_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->right_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->leftturn_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->rightturn_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->stop_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  if (x > 0)
    ui->forward_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  else if (x < 0)
    ui->backword_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  if (y > 0)
    ui->left_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  else if (y < 0)
    ui->right_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  if (z > 0)
    ui->leftturn_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  else if (z < 0)
    ui->rightturn_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  if (x == 0 && y == 0 && z == 0)
    ui->stop_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  DashBoard_x->setValue(x * 50);
  DashBoard_y->setValue(y * 50);
  DashBoard_z->setValue(z * 50);
}

void UserControl_Dialog::on_left_btn_clicked()
{
  float x = 0;
  float y = 1;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void UserControl_Dialog::on_stop_btn_clicked()
{
  float x = 0;
  float y = 0;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void UserControl_Dialog::on_right_btn_clicked()
{
  float x = 0;
  float y = -1;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void UserControl_Dialog::on_leftturn_btn_clicked()
{
  float x = 0;
  float y = 0;
  float z = 1;
  Q_EMIT movemsg_create(x, y, z);
}

void UserControl_Dialog::on_forward_btn_clicked()
{
  float x = 1;
  float y = 0;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void UserControl_Dialog::on_rightturn_btn_clicked()
{
  float x = 0;
  float y = 0;
  float z = -1;
  Q_EMIT movemsg_create(x, y, z);
}

void UserControl_Dialog::on_backword_btn_clicked()
{
  float x = -1;
  float y = 0;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

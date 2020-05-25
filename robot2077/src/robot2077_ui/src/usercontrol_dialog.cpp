#include "../include/robot2077_ui/usercontrol_dialog.h"
#include "ui_usercontrol_dialog.h"
#include <iostream>
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


  setFocusPolicy(Qt::StrongFocus);

  connect(this, SIGNAL(movemsg_create(float,float,float)), this, SLOT(movemsg_btn_color(float,float,float)));
}

UserControl_Dialog::~UserControl_Dialog()
{
  delete ui;
}

void UserControl_Dialog::on_back_btn_clicked()
{
  this->close();
}

void UserControl_Dialog::movemsg_btn_color(float x, float y, float z)
{
  ui->forward_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->backward_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->left_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->right_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->leftturn_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->rightturn_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  ui->stop_btn->setStyleSheet("background-color: rgb(255, 255, 255)");
  if (x > 0.2)
    ui->forward_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  else if (x < -0.2)
    ui->backward_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  if (y > 0.2)
    ui->left_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  else if (y < -0.2)
    ui->right_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  if (z > 0.2)
    ui->leftturn_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  else if (z < -0.2)
    ui->rightturn_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
  if (x == 0 && y == 0 && z == 0)
    ui->stop_btn->setStyleSheet("background-color: rgb(255, 0, 0)");
}

void UserControl_Dialog::movemsg_get(const float x, const float y, const float z) {
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

void UserControl_Dialog::on_backward_btn_clicked()
{
  float x = -1;
  float y = 0;
  float z = 0;
  Q_EMIT movemsg_create(x, y, z);
}

void UserControl_Dialog::keyPressEvent(QKeyEvent *event)
{
  float x = 0;
  float y = 0;
  float z = 0;
  switch(event->key()) {
  case Qt::Key_W:
    x = 1;
    y = 0;
    z = 0;
    break;
  case Qt::Key_Q:
    x = 1;
    y = 0;
    z = 1;
    break;
  case Qt::Key_E:
    x = 1;
    y = 0;
    z = -1;
    break;
  case Qt::Key_A:
    x = 0;
    y = 0;
    z = 1;
    break;
  case Qt::Key_S:
    x = 0;
    y = 0;
    z = 0;
    break;
  case Qt::Key_D:
    x = 0;
    y = 0;
    z = -1;
    break;
  case Qt::Key_Z:
    x = -1;
    y = 0;
    z = 1;
    break;
  case Qt::Key_X:
    x = -1;
    y = 0;
    z = 0;
    break;
  case Qt::Key_C:
    x = -1;
    y = 0;
    z = -1;
    break;
  default:
    x = 0;
    y = 0;
    z = 0;
    break;
  }

  Q_EMIT movemsg_create(x, y, z);
}

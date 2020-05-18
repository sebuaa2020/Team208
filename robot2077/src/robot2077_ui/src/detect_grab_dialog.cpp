#include "../include/robot2077_ui/detect_grab_dialog.h"
#include "ui_detect_grab_dialog.h"

Detect_Grab_Dialog::Detect_Grab_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Detect_Grab_Dialog)
{
  ui->setupUi(this);
}

Detect_Grab_Dialog::~Detect_Grab_Dialog()
{
  delete ui;
}

void Detect_Grab_Dialog::on_back_btn_clicked()
{
    this->close();
}

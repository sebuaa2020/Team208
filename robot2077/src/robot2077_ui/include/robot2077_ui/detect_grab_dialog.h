#ifndef DETECT_GRAB_DIALOG_H
#define DETECT_GRAB_DIALOG_H

#include <QDialog>

namespace Ui {
class Detect_Grab_Dialog;
}

class Detect_Grab_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Detect_Grab_Dialog(QWidget *parent = 0);
  ~Detect_Grab_Dialog();

public Q_SLOTS:
  void on_back_btn_clicked();

private:
  Ui::Detect_Grab_Dialog *ui;
};

#endif // DETECT_GRAB_DIALOG_H

#include "pushbutton_ok_back.h"



PushButton_OK_BACK::PushButton_OK_BACK(QString name, QWidget *parent):
    QPushButton(parent)
{
    this->setText(name);
    this->setMaximumSize(300,70);
    this->setMinimumSize(300,70);
    this->setStyleSheet("border: 3px solid black; border-radius: 25px; background: gray;color: red;");
}

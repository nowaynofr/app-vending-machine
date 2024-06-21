#ifndef MY_QSPINBOX_H
#define MY_QSPINBOX_H

#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <my_qlabel.h>
class my_qspinbox : public QSpinBox
{
public:
    explicit my_qspinbox(QString,int, QWidget *parent = 0);
    int GetQSpinBoxValue();
    QString getRGBhexColor(const QColor);
    bool IsValueChanged();
    int ValueChanged();
private slots:
    void onSpinBoxValueChanged();
private:
    QSpinBox *spinBox;
    int spb_value;
};

#endif // MY_QSPINBOX_H

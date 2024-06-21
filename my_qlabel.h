#ifndef MY_QLABEL_H
#define MY_QLABEL_H

#include <QWidget>
#include <QMouseEvent>
#include "QLabel"
#include "QPushButton"
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include "QComboBox"
#include "QSpinBox"
#include "QDateEdit"

#include "QPainter"
#include "QScrollArea"
#include "QDebug"
#include "Transaction/log.h"
#include "Machine/machine.h"
class my_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit my_qlabel(QString,QWidget *parent = 0);
    my_qlabel(QString goodId, QImage, QString goodName);
    my_qlabel(quint32,quint8);
    void mousePressEvent(QMouseEvent *ev);
    quint32 Price;
    quint8 Index;
    QString text_label;
signals:

    void home_network(QString);
    void price(quint32,quint8);
protected:
    void  paintEvent(QPaintEvent *event);
private:
    QString Key_MenuGood;
    QImage goodImage;
    QString good_Name;
    bool Check_HomeNetwork;
    bool Check_Price;
    bool Check_Machine;
};

#endif // MY_QLABEL_H

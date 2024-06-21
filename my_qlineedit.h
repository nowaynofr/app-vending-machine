#ifndef MY_QLINEEDIT_H
#define MY_QLINEEDIT_H

#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDateEdit>
#include <QComboBox>
#include <QDebug>

class my_qlineedit : public QLineEdit
{
    Q_OBJECT
public:
    explicit my_qlineedit(QString, QString, QWidget *parent = 0);
    QString GetLineEditContent();
private:
    QLineEdit *lineEdit;
};

#endif // MY_QLINEEDIT_H

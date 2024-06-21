/********************************************************************************
** Form generated from reading UI file 'motor_insurance.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTOR_INSURANCE_H
#define UI_MOTOR_INSURANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_motor_insurance
{
public:

    void setupUi(QWidget *motor_insurance)
    {
        if (motor_insurance->objectName().isEmpty())
            motor_insurance->setObjectName(QString::fromUtf8("motor_insurance"));
        motor_insurance->resize(1080, 1920);

        retranslateUi(motor_insurance);

        QMetaObject::connectSlotsByName(motor_insurance);
    } // setupUi

    void retranslateUi(QWidget *motor_insurance)
    {
        motor_insurance->setWindowTitle(QCoreApplication::translate("motor_insurance", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class motor_insurance: public Ui_motor_insurance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTOR_INSURANCE_H

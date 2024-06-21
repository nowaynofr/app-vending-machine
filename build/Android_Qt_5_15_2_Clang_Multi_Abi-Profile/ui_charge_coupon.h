/********************************************************************************
** Form generated from reading UI file 'charge_coupon.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGE_COUPON_H
#define UI_CHARGE_COUPON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_charge_coupon
{
public:

    void setupUi(QWidget *charge_coupon)
    {
        if (charge_coupon->objectName().isEmpty())
            charge_coupon->setObjectName(QString::fromUtf8("charge_coupon"));
        charge_coupon->resize(1080, 1920);

        retranslateUi(charge_coupon);

        QMetaObject::connectSlotsByName(charge_coupon);
    } // setupUi

    void retranslateUi(QWidget *charge_coupon)
    {
        charge_coupon->setWindowTitle(QCoreApplication::translate("charge_coupon", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class charge_coupon: public Ui_charge_coupon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGE_COUPON_H

/********************************************************************************
** Form generated from reading UI file 'charged_coupon.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGED_COUPON_H
#define UI_CHARGED_COUPON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_charged_coupon
{
public:

    void setupUi(QWidget *charged_coupon)
    {
        if (charged_coupon->objectName().isEmpty())
            charged_coupon->setObjectName(QString::fromUtf8("charged_coupon"));
        charged_coupon->resize(1080, 1920);

        retranslateUi(charged_coupon);

        QMetaObject::connectSlotsByName(charged_coupon);
    } // setupUi

    void retranslateUi(QWidget *charged_coupon)
    {
        charged_coupon->setWindowTitle(QCoreApplication::translate("charged_coupon", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class charged_coupon: public Ui_charged_coupon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGED_COUPON_H

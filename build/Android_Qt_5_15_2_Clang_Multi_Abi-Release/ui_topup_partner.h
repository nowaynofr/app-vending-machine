/********************************************************************************
** Form generated from reading UI file 'topup_partner.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPUP_PARTNER_H
#define UI_TOPUP_PARTNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_topup_partner
{
public:

    void setupUi(QWidget *topup_partner)
    {
        if (topup_partner->objectName().isEmpty())
            topup_partner->setObjectName(QString::fromUtf8("topup_partner"));
        topup_partner->resize(1080, 1920);

        retranslateUi(topup_partner);

        QMetaObject::connectSlotsByName(topup_partner);
    } // setupUi

    void retranslateUi(QWidget *topup_partner)
    {
        topup_partner->setWindowTitle(QCoreApplication::translate("topup_partner", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class topup_partner: public Ui_topup_partner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPUP_PARTNER_H

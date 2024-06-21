/********************************************************************************
** Form generated from reading UI file 'topup_telco.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPUP_TELCO_H
#define UI_TOPUP_TELCO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_topup_telco
{
public:

    void setupUi(QWidget *topup_telco)
    {
        if (topup_telco->objectName().isEmpty())
            topup_telco->setObjectName(QString::fromUtf8("topup_telco"));
        topup_telco->resize(1080, 1920);

        retranslateUi(topup_telco);

        QMetaObject::connectSlotsByName(topup_telco);
    } // setupUi

    void retranslateUi(QWidget *topup_telco)
    {
        topup_telco->setWindowTitle(QCoreApplication::translate("topup_telco", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class topup_telco: public Ui_topup_telco {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPUP_TELCO_H

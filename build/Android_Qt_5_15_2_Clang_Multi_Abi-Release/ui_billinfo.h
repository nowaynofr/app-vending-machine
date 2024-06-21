/********************************************************************************
** Form generated from reading UI file 'billinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BILLINFO_H
#define UI_BILLINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BillInfo
{
public:

    void setupUi(QWidget *BillInfo)
    {
        if (BillInfo->objectName().isEmpty())
            BillInfo->setObjectName(QString::fromUtf8("BillInfo"));
        BillInfo->resize(1080, 1920);

        retranslateUi(BillInfo);

        QMetaObject::connectSlotsByName(BillInfo);
    } // setupUi

    void retranslateUi(QWidget *BillInfo)
    {
        BillInfo->setWindowTitle(QCoreApplication::translate("BillInfo", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BillInfo: public Ui_BillInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BILLINFO_H

/********************************************************************************
** Form generated from reading UI file 'select_charge_type.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_CHARGE_TYPE_H
#define UI_SELECT_CHARGE_TYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_select_charge_type
{
public:

    void setupUi(QWidget *select_charge_type)
    {
        if (select_charge_type->objectName().isEmpty())
            select_charge_type->setObjectName(QString::fromUtf8("select_charge_type"));
        select_charge_type->resize(1080, 1920);

        retranslateUi(select_charge_type);

        QMetaObject::connectSlotsByName(select_charge_type);
    } // setupUi

    void retranslateUi(QWidget *select_charge_type)
    {
        select_charge_type->setWindowTitle(QCoreApplication::translate("select_charge_type", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class select_charge_type: public Ui_select_charge_type {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_CHARGE_TYPE_H

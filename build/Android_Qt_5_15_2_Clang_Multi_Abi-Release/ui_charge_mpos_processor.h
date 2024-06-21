/********************************************************************************
** Form generated from reading UI file 'charge_mpos_processor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGE_MPOS_PROCESSOR_H
#define UI_CHARGE_MPOS_PROCESSOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_charge_mpos_processor
{
public:

    void setupUi(QWidget *charge_mpos_processor)
    {
        if (charge_mpos_processor->objectName().isEmpty())
            charge_mpos_processor->setObjectName(QString::fromUtf8("charge_mpos_processor"));
        charge_mpos_processor->resize(1080, 1920);

        retranslateUi(charge_mpos_processor);

        QMetaObject::connectSlotsByName(charge_mpos_processor);
    } // setupUi

    void retranslateUi(QWidget *charge_mpos_processor)
    {
        charge_mpos_processor->setWindowTitle(QCoreApplication::translate("charge_mpos_processor", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class charge_mpos_processor: public Ui_charge_mpos_processor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGE_MPOS_PROCESSOR_H

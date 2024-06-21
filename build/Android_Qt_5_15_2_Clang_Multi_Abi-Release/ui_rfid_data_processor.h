/********************************************************************************
** Form generated from reading UI file 'rfid_data_processor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RFID_DATA_PROCESSOR_H
#define UI_RFID_DATA_PROCESSOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rfid_data_processor
{
public:

    void setupUi(QWidget *rfid_data_processor)
    {
        if (rfid_data_processor->objectName().isEmpty())
            rfid_data_processor->setObjectName(QString::fromUtf8("rfid_data_processor"));
        rfid_data_processor->resize(1080, 1920);

        retranslateUi(rfid_data_processor);

        QMetaObject::connectSlotsByName(rfid_data_processor);
    } // setupUi

    void retranslateUi(QWidget *rfid_data_processor)
    {
        rfid_data_processor->setWindowTitle(QCoreApplication::translate("rfid_data_processor", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class rfid_data_processor: public Ui_rfid_data_processor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RFID_DATA_PROCESSOR_H

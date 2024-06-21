/********************************************************************************
** Form generated from reading UI file 'process_admin_funtion.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESS_ADMIN_FUNTION_H
#define UI_PROCESS_ADMIN_FUNTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_process_admin_funtion
{
public:

    void setupUi(QWidget *process_admin_funtion)
    {
        if (process_admin_funtion->objectName().isEmpty())
            process_admin_funtion->setObjectName(QString::fromUtf8("process_admin_funtion"));
        process_admin_funtion->resize(1080, 1920);

        retranslateUi(process_admin_funtion);

        QMetaObject::connectSlotsByName(process_admin_funtion);
    } // setupUi

    void retranslateUi(QWidget *process_admin_funtion)
    {
        process_admin_funtion->setWindowTitle(QCoreApplication::translate("process_admin_funtion", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class process_admin_funtion: public Ui_process_admin_funtion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESS_ADMIN_FUNTION_H

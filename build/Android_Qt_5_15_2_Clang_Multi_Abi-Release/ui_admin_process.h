/********************************************************************************
** Form generated from reading UI file 'admin_process.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_PROCESS_H
#define UI_ADMIN_PROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_admin_process
{
public:

    void setupUi(QWidget *admin_process)
    {
        if (admin_process->objectName().isEmpty())
            admin_process->setObjectName(QString::fromUtf8("admin_process"));
        admin_process->resize(1080, 1920);

        retranslateUi(admin_process);

        QMetaObject::connectSlotsByName(admin_process);
    } // setupUi

    void retranslateUi(QWidget *admin_process)
    {
        admin_process->setWindowTitle(QCoreApplication::translate("admin_process", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class admin_process: public Ui_admin_process {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_PROCESS_H

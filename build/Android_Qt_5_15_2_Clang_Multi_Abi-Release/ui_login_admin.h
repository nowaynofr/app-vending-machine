/********************************************************************************
** Form generated from reading UI file 'login_admin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_ADMIN_H
#define UI_LOGIN_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login_admin
{
public:

    void setupUi(QWidget *login_admin)
    {
        if (login_admin->objectName().isEmpty())
            login_admin->setObjectName(QString::fromUtf8("login_admin"));
        login_admin->resize(1080, 1920);

        retranslateUi(login_admin);

        QMetaObject::connectSlotsByName(login_admin);
    } // setupUi

    void retranslateUi(QWidget *login_admin)
    {
        login_admin->setWindowTitle(QCoreApplication::translate("login_admin", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login_admin: public Ui_login_admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_ADMIN_H

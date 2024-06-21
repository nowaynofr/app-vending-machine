/********************************************************************************
** Form generated from reading UI file 'select_service.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_SERVICE_H
#define UI_SELECT_SERVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_select_service
{
public:

    void setupUi(QWidget *select_service)
    {
        if (select_service->objectName().isEmpty())
            select_service->setObjectName(QString::fromUtf8("select_service"));
        select_service->resize(1080, 1920);

        retranslateUi(select_service);

        QMetaObject::connectSlotsByName(select_service);
    } // setupUi

    void retranslateUi(QWidget *select_service)
    {
        select_service->setWindowTitle(QCoreApplication::translate("select_service", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class select_service: public Ui_select_service {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_SERVICE_H

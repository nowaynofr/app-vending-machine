/********************************************************************************
** Form generated from reading UI file 'postpaid.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTPAID_H
#define UI_POSTPAID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Postpaid
{
public:

    void setupUi(QWidget *Postpaid)
    {
        if (Postpaid->objectName().isEmpty())
            Postpaid->setObjectName(QString::fromUtf8("Postpaid"));
        Postpaid->resize(1080, 1920);

        retranslateUi(Postpaid);

        QMetaObject::connectSlotsByName(Postpaid);
    } // setupUi

    void retranslateUi(QWidget *Postpaid)
    {
        Postpaid->setWindowTitle(QCoreApplication::translate("Postpaid", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Postpaid: public Ui_Postpaid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTPAID_H

/********************************************************************************
** Form generated from reading UI file 'menu_good_general.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_GOOD_GENERAL_H
#define UI_MENU_GOOD_GENERAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu_good_general
{
public:

    void setupUi(QWidget *menu_good_general)
    {
        if (menu_good_general->objectName().isEmpty())
            menu_good_general->setObjectName(QString::fromUtf8("menu_good_general"));
        menu_good_general->resize(1080, 1920);

        retranslateUi(menu_good_general);

        QMetaObject::connectSlotsByName(menu_good_general);
    } // setupUi

    void retranslateUi(QWidget *menu_good_general)
    {
        menu_good_general->setWindowTitle(QCoreApplication::translate("menu_good_general", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menu_good_general: public Ui_menu_good_general {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_GOOD_GENERAL_H

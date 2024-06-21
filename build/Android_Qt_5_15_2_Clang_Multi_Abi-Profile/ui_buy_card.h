/********************************************************************************
** Form generated from reading UI file 'buy_card.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUY_CARD_H
#define UI_BUY_CARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_buy_card
{
public:

    void setupUi(QWidget *buy_card)
    {
        if (buy_card->objectName().isEmpty())
            buy_card->setObjectName(QString::fromUtf8("buy_card"));
        buy_card->resize(1080, 1920);

        retranslateUi(buy_card);

        QMetaObject::connectSlotsByName(buy_card);
    } // setupUi

    void retranslateUi(QWidget *buy_card)
    {
        buy_card->setWindowTitle(QCoreApplication::translate("buy_card", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class buy_card: public Ui_buy_card {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUY_CARD_H

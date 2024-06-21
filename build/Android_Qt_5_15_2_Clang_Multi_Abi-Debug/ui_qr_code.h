/********************************************************************************
** Form generated from reading UI file 'qr_code.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QR_CODE_H
#define UI_QR_CODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QR_code
{
public:

    void setupUi(QWidget *QR_code)
    {
        if (QR_code->objectName().isEmpty())
            QR_code->setObjectName(QString::fromUtf8("QR_code"));
        QR_code->resize(1080, 1920);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QR_code->sizePolicy().hasHeightForWidth());
        QR_code->setSizePolicy(sizePolicy);
        QR_code->setMaximumSize(QSize(16777215, 16777215));
        QR_code->setSizeIncrement(QSize(0, 0));

        retranslateUi(QR_code);

        QMetaObject::connectSlotsByName(QR_code);
    } // setupUi

    void retranslateUi(QWidget *QR_code)
    {
        QR_code->setWindowTitle(QCoreApplication::translate("QR_code", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QR_code: public Ui_QR_code {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QR_CODE_H

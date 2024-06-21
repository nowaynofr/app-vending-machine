/********************************************************************************
** Form generated from reading UI file 'testform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTFORM_H
#define UI_TESTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testform
{
public:

    void setupUi(QWidget *testform)
    {
        if (testform->objectName().isEmpty())
            testform->setObjectName(QString::fromUtf8("testform"));
        testform->resize(1080, 1920);

        retranslateUi(testform);

        QMetaObject::connectSlotsByName(testform);
    } // setupUi

    void retranslateUi(QWidget *testform)
    {
        testform->setWindowTitle(QCoreApplication::translate("testform", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testform: public Ui_testform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTFORM_H

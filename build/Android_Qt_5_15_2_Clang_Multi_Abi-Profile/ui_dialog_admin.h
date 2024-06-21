/********************************************************************************
** Form generated from reading UI file 'dialog_admin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ADMIN_H
#define UI_DIALOG_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_Admin
{
public:
    QPushButton *pushButton;
    QLabel *label_Status;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *Dialog_Admin)
    {
        if (Dialog_Admin->objectName().isEmpty())
            Dialog_Admin->setObjectName(QString::fromUtf8("Dialog_Admin"));
        Dialog_Admin->resize(400, 300);
        pushButton = new QPushButton(Dialog_Admin);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(154, 130, 91, 41));
        label_Status = new QLabel(Dialog_Admin);
        label_Status->setObjectName(QString::fromUtf8("label_Status"));
        label_Status->setGeometry(QRect(10, 210, 371, 51));
        widget = new QWidget(Dialog_Admin);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(50, 30, 301, 71));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        retranslateUi(Dialog_Admin);

        QMetaObject::connectSlotsByName(Dialog_Admin);
    } // setupUi

    void retranslateUi(QDialog *Dialog_Admin)
    {
        Dialog_Admin->setWindowTitle(QCoreApplication::translate("Dialog_Admin", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog_Admin", "OK", nullptr));
        label_Status->setText(QString());
        label->setText(QCoreApplication::translate("Dialog_Admin", "Nh\341\272\255p m\341\272\255t kh\341\272\251u", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_Admin: public Ui_Dialog_Admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ADMIN_H

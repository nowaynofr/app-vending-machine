#include "dialog_admin.h"
#include "ui_dialog_admin.h"

Dialog_Admin::Dialog_Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Admin)
{
    ui->setupUi(this);
    PassAdmin = "";
    ui->lineEdit->setFocus();
}

Dialog_Admin::~Dialog_Admin()
{
    delete ui;
}

void Dialog_Admin::ResetNewDialog()
{
    ui->lineEdit->clear();
    ui->label_Status->setText("");
}

void Dialog_Admin::on_pushButton_clicked()
{
    QString password = ui->lineEdit->text();
    qDebug()<<password;
    if(password == PassAdmin){
        emit AdminProcess();
    }else{
        ui->lineEdit->clear();
        ui->label_Status->setText("Mật khẩu không chính xác!");
    }
}

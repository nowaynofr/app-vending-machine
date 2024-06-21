#ifndef LOGIN_ADMIN_H
#define LOGIN_ADMIN_H

#include <QWidget>
#include "Machine/machine.h"
#include "my_qlabel.h"
namespace Ui {
class login_admin;
}

class login_admin : public QWidget
{
    Q_OBJECT

public:
    explicit login_admin(QWidget *parent = nullptr);
    login_admin(QString);
    ~login_admin();
    void SetIsCheckWaitResponseVMSToFail();
    void LoginAdminFail(QString);
signals:
    void Signal_Admin_Login(QString, QString);
private slots:
    void on_Btn_Ok_login_clicked();
    void on_Btn_Back_login_clicked();
private:
    Ui::login_admin *ui;
    bool IsCheckWaitResponseVMS;
  //  QString AdminPass;
    QLineEdit *lineEdit_User;
    QLineEdit *lineEdit_Pass;
    QLabel *Message;
    QLabel *lb_Promotion;
    QPushButton *Ok_login;
    QPushButton *Back;
};

#endif // LOGIN_ADMIN_H

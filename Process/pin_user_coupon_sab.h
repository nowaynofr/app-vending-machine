#ifndef PIN_USER_COUPON_SAB_H
#define PIN_USER_COUPON_SAB_H

#include <QWidget>
#include "my_qlabel.h"
#include "Machine/machine.h"
#include "Transaction/transaction.h"
#include "Transaction/machine_state.h"
namespace Ui {
class pin_user_coupon_sab;
}

class pin_user_coupon_sab : public QWidget
{
    Q_OBJECT

public:
    explicit pin_user_coupon_sab(QWidget *parent = nullptr);
    pin_user_coupon_sab(Machine*);
    ~pin_user_coupon_sab();
    void setPinUserCoupon(Machine*);
    void updatePinUserCoupon(Machine*);
    //bool Check_GetPriceServer;
    QString getPinUserCoupon();
   // void showKeyboard();
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_PinUserCoupon_clicked();

    void on_Btn_Back_PinUserCoupon_clicked();
signals:
    void Signal_PinUserCoupon(MACHINE_STATE);
private:
    Ui::pin_user_coupon_sab *ui;
   // quint8 ServiceType_PinUserCoupon;
    QLabel *Lbl_PinUserCoupon;
    QLineEdit *lineEdit_PinUserCoupon;
    QLabel *Message;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // PIN_USER_COUPON_SAB_H

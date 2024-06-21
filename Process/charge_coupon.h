#ifndef CHARGE_COUPON_H
#define CHARGE_COUPON_H

#include <QWidget>
#include "my_qlabel.h"
#include "Machine/machine.h"
#include "Transaction/transaction.h"
#include "Transaction/machine_state.h"
#include "QTextEdit"
namespace Ui {
class charge_coupon;
}

class charge_coupon : public QWidget
{
    Q_OBJECT

public:
    explicit charge_coupon(QWidget *parent = nullptr);
    charge_coupon(Machine* , quint8);
    ~charge_coupon();
    void setChargeCoupon(Machine*);
    void updateChargeCoupon(Machine*);
    void updateChargeCouponFail(Machine*);
    //bool Check_GetPriceServer;
    QString getOrderInformation();
    //void showKeyboard();
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_ChargeCoupon_clicked();

    void on_Btn_Back_ChargeCoupon_clicked();
signals:
    void Signal_ChargeCoupon(MACHINE_STATE);
private:
    Ui::charge_coupon *ui;
    Machine *s_machine;
    bool CheckPushButtonOKPressed;
    //QString OrderInformation;
    quint8 ServiceType_ChargeCoupon;
    QLabel *Lbl_ChargeCoupon;
    QLineEdit *lineEdit_Coupon;
    QLabel *Message;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // CHARGE_COUPON_H

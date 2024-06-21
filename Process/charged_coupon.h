#ifndef CHARGED_COUPON_H
#define CHARGED_COUPON_H

#include <QWidget>
#include "my_qlabel.h"
#include "Machine/machine.h"
#include "Transaction/transaction.h"
#include "Transaction/machine_state.h"
namespace Ui {
class charged_coupon;
}

class charged_coupon : public QWidget
{
    Q_OBJECT

public:
    explicit charged_coupon(QWidget *parent = nullptr);
    charged_coupon(Machine* , quint8);
    ~charged_coupon();
    void setChargedCoupon(Machine*);
    void updateChargedCoupon(Machine*);
    bool Check_GetPriceServer;
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_ChargedCoupon_clicked();

    void on_Btn_Back_ChargedCoupon_clicked();
signals:
    void Signal_ChargedCoupon(MACHINE_STATE);
private:
    Ui::charged_coupon *ui;
    quint8 ServiceType_ChargedCoupon;
    QLabel *Lbl_ChargedCoupon;
    QLabel *Message;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // CHARGED_COUPON_H

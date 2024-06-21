#ifndef RFID_DATA_PAYMENT_WAITTING_H
#define RFID_DATA_PAYMENT_WAITTING_H

#include <QWidget>
#include <QWidget>
#include "my_qlabel.h"
#include "Machine/machine.h"
#include "Transaction/transaction.h"
#include "Transaction/machine_state.h"
#include "QTextEdit"
namespace Ui {
class rfid_data_payment_waitting;
}

class rfid_data_payment_waitting : public QWidget
{
    Q_OBJECT

public:
    explicit rfid_data_payment_waitting(QWidget *parent = nullptr);
    ~rfid_data_payment_waitting();
    rfid_data_payment_waitting(Machine*);
    void setRfidDataPaymentWaittng(Machine*);
    void updateRfidDataPaymentWaittng(Machine*);
    bool Check_GetPriceServer;
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_RfidDataPaymentWaittng_clicked();

    void on_Btn_Back_RfidDataPaymentWaittng_clicked();
signals:
    void Signal_RfidDataPaymentWaittng(MACHINE_STATE);
private:
    Ui::rfid_data_payment_waitting *ui;
    Machine *s_machine;
    //quint8 ServiceType_ChargedCoupon;
    QLabel *Lbl_ChargedCoupon;
    QLabel *Message;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // RFID_DATA_PAYMENT_WAITTING_H

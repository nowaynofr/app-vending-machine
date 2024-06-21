#ifndef RFID_DATA_PROCESSOR_H
#define RFID_DATA_PROCESSOR_H

#include <QWidget>
#include "my_qlabel.h"
#include "Machine/machine.h"
#include "Transaction/transaction.h"
#include "Transaction/machine_state.h"
#include "QTextEdit"
namespace Ui {
class rfid_data_processor;
}

class rfid_data_processor : public QWidget
{
    Q_OBJECT

public:
    explicit rfid_data_processor(QWidget *parent = nullptr);
    rfid_data_processor(Machine*);
    ~rfid_data_processor();
    void setRfidData(Machine*);
    void updateRfidData(Machine*);
    void updateReceiveRfidData(QString);
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_RfidData_clicked();

    void on_Btn_Back_RfidData_clicked();
signals:
    void Signal_RfidData(MACHINE_STATE);
    void Signal_RfidData1(QString);
private:
    Ui::rfid_data_processor *ui;
    Machine *s_machine;
  //  bool CheckPushButtonOKPressed;
    //QString OrderInformation;
   // quint8 ServiceType_ChargeCoupon;
    QLabel *Lbl_ChargeCoupon;
   // QLineEdit *lineEdit_Coupon;
    QLabel *Message;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;

    //QString show;

};

#endif // RFID_DATA_PROCESSOR_H

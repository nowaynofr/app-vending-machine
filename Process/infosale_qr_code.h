#ifndef INFOSALE_QR_CODE_H
#define INFOSALE_QR_CODE_H

#include <QWidget>
#include "Transaction/transaction.h"
#include "Transaction/machine_state.h"
#include "my_qlabel.h"
#include "Machine/machine.h"

namespace Ui {
class infoSale_qr_code;
}

class infoSale_qr_code : public QWidget
{
    Q_OBJECT

public:
    explicit infoSale_qr_code(QWidget *parent = nullptr);
    infoSale_qr_code(Machine*,quint8);
    ~infoSale_qr_code();
    void setInfoSaleQR(Machine*);
    void updateInfoSaleQR(Machine*);
   // bool Check_GetPriceServer;
    bool Check_GetQRCodeFalse;
private slots:
    void Back_Home(QString);
   // void on_Btn_Ok_infoSale_QRcode_clicked();

    void on_Btn_Back_infoSale_QRcode_clicked();
signals:
    void Signal_infoSale_QRcode(MACHINE_STATE);
private:
    Ui::infoSale_qr_code *ui;
    Machine *s_machine;
    quint8 ServiceType_QR;
    QLabel *Lbl_InfoQR;
    QLabel *Message;
  //  QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // INFOSALE_QR_CODE_H

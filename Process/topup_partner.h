#ifndef TOPUP_PARTNER_H
#define TOPUP_PARTNER_H

#include <QWidget>
#include "Transaction/machine_state.h"
#include "Machine/machine.h"
#include "my_qlabel.h"
#include "Transaction/stringutils.h"
namespace Ui {
class topup_partner;
}

class topup_partner : public QWidget
{
    Q_OBJECT

public:
    explicit topup_partner(QWidget *parent = nullptr);
    topup_partner(Machine*);
    ~topup_partner();
    QString Partner_TopupPartner();
   // quint32 Price_TopupPartner();
    QString customerID_TopupPartner();
    void UpdateGetBillInfoFail(Machine*);
    void UpdateRePartner();
public slots:
    void select_Partner(QString);
   // void select_price(quint32,quint8);
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_TopupPartner_clicked();

    void on_Btn_Back_TopupPartner_clicked();
   // void LineEdit_Price_VND();
signals:
    void Signal_TopupPartner(MACHINE_STATE);
private:
    bool CheckPushButtonOKPressed;
    Db m_db;
    QString Industry_Partner;
    QString Partner;
    Ui::topup_partner *ui;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
    QLineEdit *lineEdit_Number_Phone;
  //  QLineEdit *lineEdit_Price;
    QGridLayout *grid;
   // QLabel *Lbl_TopupPartner;
    QLabel *Message;
    QLabel* partner[8];
    QLabel* price[15];
};

#endif // TOPUP_PARTNER_H

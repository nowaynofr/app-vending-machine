#ifndef SELECT_CHARGE_TYPE_H
#define SELECT_CHARGE_TYPE_H

#include <QWidget>
#include "my_qlabel.h"
#include "Transaction/machine_state.h"
#include "Machine/machine.h"
namespace Ui {
class select_charge_type;
}

class select_charge_type : public QWidget
{
    Q_OBJECT

public:
    explicit select_charge_type(QWidget *parent = nullptr);
    select_charge_type(Machine*, QStringList);
    ~select_charge_type();

    QStringList ListChargeType;
 //   quint8 ChargeType_Select();
    void UpdateBillAmount();
private slots:
  //  void on_Btn_Ok_Topuptelco_clicked();
    void Back_Home(QString);
    void on_Btn_Back_SelectChargeType_clicked();
    void select_charge_type_clicked(QString);
signals:
    void Signal_Select_Charge_Type(MACHINE_STATE);
private:
    Ui::select_charge_type *ui;
    QString TextBillAvailable;
    Machine *s_machine;
    MACHINE_STATE last_state;
   // quint8 TransactionType;
    quint8 ServiceType;
    QList<QString> ListChargeTypeQR;
  //  QPushButton *btn_Ok;
    QPushButton *btn_Back;
    QLabel *Message;
    QLabel* charge_type[15];
};

#endif // SELECT_CHARGE_TYPE_H

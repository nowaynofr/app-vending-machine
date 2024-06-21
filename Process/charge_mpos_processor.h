#ifndef CHARGE_MPOS_PROCESSOR_H
#define CHARGE_MPOS_PROCESSOR_H

#include <QWidget>
#include "my_qlabel.h"
#include "Machine/machine.h"
#include "Transaction/transaction.h"
#include "Transaction/machine_state.h"
namespace Ui {
class charge_mpos_processor;
}

class charge_mpos_processor : public QWidget
{
    Q_OBJECT

public:
    explicit charge_mpos_processor(QWidget *parent = nullptr);
    charge_mpos_processor(Machine*);
    ~charge_mpos_processor();
    void setChargeMpos(Machine*);
    void updateChargeMpos(Machine*);
  //  void updateReceiveRfidData(QString);
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_ChargeMpos_clicked();

    void on_Btn_Back_ChargeMpos_clicked();
signals:
    void Signal_ChargeMpos(MACHINE_STATE);

private:
    Ui::charge_mpos_processor *ui;
    bool CheckPushButtonOKPressed;
    Machine *s_machine;
    QLabel *Lbl_ChargeMpos;
    QLabel *Message;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // CHARGE_MPOS_PROCESSOR_H

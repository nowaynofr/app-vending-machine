#ifndef PROCESS_SETTING_QUANTITY_FUNTION_H
#define PROCESS_SETTING_QUANTITY_FUNTION_H

#include <QWidget>
#include "Machine/machine.h"
#include "my_qlabel.h"
#include "Transaction/machine_state.h"
#include "my_qspinbox.h"

namespace Ui {
class process_setting_quantity_funtion;
}

class process_setting_quantity_funtion : public QWidget
{
    Q_OBJECT

public:
    explicit process_setting_quantity_funtion(QWidget *parent = nullptr);
    process_setting_quantity_funtion(Machine*);
    ~process_setting_quantity_funtion();
    QString getRGBhexColor(const QColor);
    void ReSendTransactionStatus(QString);
signals:
    void Signal_Admin_Setting_Quantity_Funtion_Process(MACHINE_STATE, QString, QString);
private slots:
    void on_Btn_Ok_Admin_Setting_Quantity_Funtion_Process_clicked();
    void on_Btn_Back_Admin_Setting_Quantity_Funtion_Process_clicked();
    void onSpinBoxValueChanged();
//protected:
//    void keyPressEvent(QKeyEvent *ev);
private:
    Ui::process_setting_quantity_funtion *ui;
    Machine* s_machine;

    QSpinBox *spb_general_quantity;
    QLabel *lb_general_quantity;
    my_qspinbox *spb_quantity[100];
    QGridLayout *grid;

//    my_qspinbox *spb_start_transactionId;
//    my_qspinbox *spb_end_transactionId;
//    QLabel *tx_info;
    QDateEdit *StartTime;
    QDateEdit *EndTime;
    QLabel *Status;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // PROCESS_SETTING_QUANTITY_FUNTION_H

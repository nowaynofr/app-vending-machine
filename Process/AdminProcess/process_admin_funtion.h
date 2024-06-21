#ifndef PROCESS_ADMIN_FUNTION_H
#define PROCESS_ADMIN_FUNTION_H

#include <QWidget>
#include "Machine/machine.h"
#include "my_qlabel.h"
#include "Transaction/machine_state.h"
namespace Ui {
class process_admin_funtion;
}

class process_admin_funtion : public QWidget
{
    Q_OBJECT

public:
    explicit process_admin_funtion(QWidget *parent = nullptr);
    process_admin_funtion(Machine*);
    ~process_admin_funtion();

    void SyncInfo(QString);
    void SaleInfo(QString);
    void ReSendSaleStatus(QString);
    void UpdateStatus();
signals:
    void Signal_Admin_Funtion_Process(MACHINE_STATE);
private slots:
    void ProcessSelect(QString);
    void on_Btn_Ok_Admin_Funtion_Process_clicked();
    void on_Btn_Back_Admin_Funtion_Process_clicked();
    void Update_LineEdit_Sale();
private:
    Ui::process_admin_funtion *ui;
    bool IsCheckWaitResponseVMS;
    Machine *s_machine;
    QLineEdit *lineEdit_Sale;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
    QLabel *Message;
    QLabel *Status;
    QLabel* Select[3];
};

#endif // PROCESS_ADMIN_FUNTION_H

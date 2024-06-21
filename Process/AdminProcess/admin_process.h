#ifndef ADMIN_PROCESS_H
#define ADMIN_PROCESS_H

#include <QWidget>
#include "QObject"
#include "QApplication"
#include "Machine/machine.h"
#include "my_qlabel.h"
#include "Transaction/machine_state.h"
#include <QAndroidJniObject>
#include <QtAndroidExtras>

namespace Ui {
class admin_process;
}

class admin_process : public QWidget
{
    Q_OBJECT

public:
    explicit admin_process(QWidget *parent = nullptr);
    admin_process(Machine*,QString);
    ~admin_process();
    void ProcessAdminSuccess();
    void ProcessAdminFail();
    void GetSaleInfo(QString);
    QString GetSelected();
signals:
    void Signal_Admin_Process(MACHINE_STATE);
private slots:
    void ProcessSelect(QString);
    void on_Btn_Ok_Admin_Process_clicked();
    void on_Btn_Back_Admin_Process_clicked();
private:
    Ui::admin_process *ui;
    Machine *s_machine;
    QList<QString> ListSelect;
   // QString Selected;
 
    QPushButton *KillApp;

   // QPushButton *btn_Ok;
    QPushButton *btn_Back;
    //QLabel *Message;
    QLabel* Select[3];
};

#endif // ADMIN_PROCESS_H

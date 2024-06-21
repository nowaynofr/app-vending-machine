#ifndef BILLINFO_H
#define BILLINFO_H

#include <QWidget>
#include "QObject"
#include "QApplication"
#include "Machine/machine.h"
#include "my_qlabel.h"

namespace Ui {
class BillInfo;
}

class BillInfo : public QWidget
{
    Q_OBJECT

public:
    explicit BillInfo(QWidget *parent = nullptr);
    BillInfo(Machine*, QString);
    ~BillInfo();
    int SelectBillIndex();
signals:
    void Signal_Bill_Info(MACHINE_STATE);
private slots:
    void Back_Home(QString);
    void SelectBill_Info(quint32,quint8);
    void on_Btn_Ok_Bill_Info_clicked();
    void on_Btn_Back_Bill_Info_clicked();
private:
    Ui::BillInfo *ui;
    quint8 BillQuatity;
    int _SelectBillIndex;
    QString MesBillInfo;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
    QLabel *Message;
    QLabel* billInfo[12];
};

#endif // BILLINFO_H

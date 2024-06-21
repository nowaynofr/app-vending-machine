#ifndef GOOD_DIGITAL_PROCESS_H
#define GOOD_DIGITAL_PROCESS_H

#include <QWidget>
#include "my_qlabel.h"
namespace Ui {
class good_digital_process;
}

class good_digital_process : public QWidget
{
    Q_OBJECT

public:
    explicit good_digital_process(QWidget *parent = nullptr);
    good_digital_process(Machine*);
    ~good_digital_process();

    void setGetPriceGoodDigitalProcess(Machine*);
    void updateGetPriceGoodDigitalProcess(Machine*);
    void setGoodDigitalProcess(Machine*);
    void updateGoodDigitalProcess(Machine*);
    void updateBillAmount();
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_GoodDigital_clicked();

    void on_Btn_Back_GoodDigital_clicked();
signals:
    void Signal_GoodDigital_Process(MACHINE_STATE);
private:
    Ui::good_digital_process *ui;
    Machine *s_machine;
  //  bool CheckIsWorkingWithVTC;
   // quint8 ServiceType_GoodDigital;
    QLabel *Lbl_InfoGoodDigital;
    QLabel *Message;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // GOOD_DIGITAL_PROCESS_H

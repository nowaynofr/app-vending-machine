#ifndef GET_GOOD_DIGITAL_H
#define GET_GOOD_DIGITAL_H

#include <QWidget>
#include "my_qlabel.h"
namespace Ui {
class get_good_digital;
}

class get_good_digital : public QWidget
{
    Q_OBJECT

public:
    explicit get_good_digital(QWidget *parent = nullptr);
    get_good_digital(Machine*, quint8);
    ~get_good_digital();
    void setGetGoodDigital(Machine*);
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_GetGoodDigital_clicked();

    void on_Btn_Back_GetGoodDigital_clicked();
signals:
    void Signal_GetGoodDigital_Process(MACHINE_STATE);
private:
    Ui::get_good_digital *ui;
    quint8 ServiceTypeGetGoodDigital;
    QLabel *Lbl_InfoGetGoodDigital;
    QLabel *Message;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // GET_GOOD_DIGITAL_H


#ifndef POSTPAID_H
#define POSTPAID_H

#include <QWidget>
#include "Transaction/machine_state.h"
#include "Machine/machine.h"
#include "my_qlabel.h"
#include "Transaction/stringutils.h"
namespace Ui {
class Postpaid;
}

class Postpaid : public QWidget
{
    Q_OBJECT

public:
    explicit Postpaid(QWidget *parent = nullptr);
    Postpaid(Machine*);
    ~Postpaid();
    QString Partner_Postpaid();
    quint32 Price_Postpaid();
    QString NumberPhone_Postpaid();
public slots:
    void select_Partner(QString);
   // void select_price(quint32,quint8);
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_Postpaid_clicked();

    void on_Btn_Back_Postpaid_clicked();
    void LineEdit_Price_VND();
signals:
    void Signal_Postpaid(MACHINE_STATE);
private:
    Db m_db;
    QString Industry_Postpaid;
    QString post_paid;
    Ui::Postpaid *ui;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
    QComboBox *comboBox_Postpaid;
    QComboBox *comboBox_Price;
    QLineEdit *lineEdit_Number_Phone;
    QLineEdit *lineEdit_Price;
    QGridLayout *grid;
    QLabel *Message;
    QLabel* postpaid[8];
    QLabel* price[15];
};

#endif // POSTPAID_H

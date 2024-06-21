#ifndef TOPUP_TELCO_H
#define TOPUP_TELCO_H

#include <QWidget>
#include "Transaction/machine_state.h"
#include "Machine/machine.h"
#include "my_qlabel.h"

namespace Ui {
class topup_telco;
}

class topup_telco : public QWidget
{
    Q_OBJECT

public:
    explicit topup_telco(QWidget *parent = nullptr);
    topup_telco(Machine*);
    ~topup_telco();
    QString HomeNetwork_TopupTelco();
    quint32 Price_TopupTelco();
    QString NumberPhone_TopupTelco();
public slots:
    void select_home_network(QString);
    void select_price(quint32,quint8);
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_Topuptelco_clicked();

    void on_Btn_Back_Topuptelco_clicked();
signals:
    void Signal_ToupupTelco(MACHINE_STATE);
private:
    Db m_db;
    QString HomeNetwork;
    quint32 Price;
    Ui::topup_telco *ui;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
    QComboBox *comboBox_HomeNetwork_Topuptelco;
    QComboBox *comboBox_Price_TopupTelco;
    QLineEdit *lineEdit_Number_Phone;
    QGridLayout *grid;
    QLabel *Message;
    QLabel* home_network[8];
    QLabel* price[15];
};

#endif // TOPUP_TELCO_H

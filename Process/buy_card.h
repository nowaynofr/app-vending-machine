#ifndef BUY_CARD_H
#define BUY_CARD_H

#include <QWidget>
#include "Transaction/machine_state.h"
#include "Machine/machine.h"
#include "my_qlabel.h"
namespace Ui {
class buy_card;
}

class buy_card : public QWidget
{
    Q_OBJECT

public:
    explicit buy_card(QWidget *parent = nullptr);
    buy_card(Machine*);
    ~buy_card();
    QString HomeNetwork_BuyCard();
    quint32 Price_BuyCard();
    QString NumberPhone_BuyCard();
public slots:
    void select_home_network(QString);
    void select_price(quint32,quint8);
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_BuyCard_clicked();

    void on_Btn_Back_BuyCard_clicked();
signals:
    void Signal_BuyCard(MACHINE_STATE);
private:
    Db m_db;
    QString Industry_BuyCard;
    QString HomeNetwork;
    quint32 Price;
    Ui::buy_card *ui;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
    QComboBox *comboBox_HomeNetwork_Topuptelco;
    QComboBox *comboBox_Price_TopupTelco;
    QGridLayout *grid;
    QGridLayout *GridGameCard;
    //QLineEdit *lineEdit_Number_Phone;
    QLabel *Message;
    QLabel* home_network[15];
    QLabel* price[15];
};

#endif // BUY_CARD_H

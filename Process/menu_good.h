#ifndef MENU_GOOD_H
#define MENU_GOOD_H

#include <QWidget>
#include "Transaction/machine_state.h"
#include "Machine/machine.h"
#include "my_qlabel.h"
#include "QTimer"
namespace Ui {
class Menu_Good;
}

class Menu_Good : public QWidget
{
    Q_OBJECT

public:
    explicit Menu_Good(QWidget *parent = nullptr);
    Menu_Good(Machine*, quint8, QString);
    ~Menu_Good();
    void UpdateQuatityImage(quint8);
    void StartTimer();
    void UpdateBillAmount();
//    void UpdateBill(QString BillResponse);
//    void UpdateStatus(QString);
signals:
    void Signal_Menu_Good(QString);
private slots:
    void select_menugood(QString);
    void display_image();
private:

    Ui::Menu_Good *ui;
    Machine *s_machine;
    QString TextBillAvailable;
    quint8 index_image;
    quint8 quatity_image;
    QTimer m_timer;
    QLabel* lb_SaverCreen;
    QString DatabaseDataStoragePath;
    QLabel* lb_Promotion;
//    QLabel* lb_RFID;
//    QLabel* lb_BillAmount;
//    QLabel* lb_BillResponse;
//    QLabel* lb_Status;
};

#endif // MENU_GOOD_H

#ifndef MENU_GOOD_GENERAL_H
#define MENU_GOOD_GENERAL_H

#include <QWidget>
#include "Transaction/machine_state.h"
#include "Machine/machine.h"
#include "QScrollBar"
#include "qgridlayout.h"
#include "qgroupbox.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qscrollarea.h"
namespace Ui {
class menu_good_general;
}

class menu_good_general : public QWidget
{
    Q_OBJECT

public:
    explicit menu_good_general(QWidget *parent = nullptr);
    menu_good_general(Machine*, QString);
    ~menu_good_general();
    QString GetSelectGood();
private slots:
    void on_Btn_Ok_Menu_General_clicked();

    void on_Btn_Back_Menu_General_clicked();

    void on_Btn_increase_quantity_Menu_General_clicked();
    void on_Btn_next_click();

    void on_Btn_decrease_quantity_Menu_General_clicked();

    void Back_Home(QString);
    void select_good_clicked(QString);
signals:
    void Signal_Menu_Good_General(MACHINE_STATE);
    void Signal_Next_Form(MACHINE_STATE);
private:
    Ui::menu_good_general *ui;
    Machine* s_machine;
    QList<int> ListPriority;
    QList<QString> ListGoodIdPriority;
    QString DatabaseDataStoragePath;
   // QString Select_Good;
    Db m_db;
    QGridLayout *grid;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
    QLabel *Message;
    QPushButton *btn_next;
    QPushButton *btn_increase_quantity;
    QPushButton *btn_decrease_quantity;
    QLineEdit *lineEdit_Quantity;

    QGroupBox* GroupIndustry[10];
    QScrollArea* ScrollAreaMenu;
    QLabel* menu[30];
};

#endif // MENU_GOOD_GENERAL_H

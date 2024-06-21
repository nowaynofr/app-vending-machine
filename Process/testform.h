#ifndef TESTFORM_H
#define TESTFORM_H

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
class testform;
}

class testform : public QWidget
{
    Q_OBJECT

public:
    explicit testform(QWidget *parent = nullptr);
    testform(Machine*, QString);
    ~testform();
    QString GetSelectGood();
signals:
    void Signal_Test_Form_Back(MACHINE_STATE);
private slots:
    void on_Btn_Back_login_clicked();
    void on_pushButton_clicked();

private:
    Ui::testform *ui;
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

    QGroupBox* GroupIndustry[10];
    QScrollArea* ScrollAreaMenu;
    QLabel* menu[30];

};

#endif // TESTFORM_H

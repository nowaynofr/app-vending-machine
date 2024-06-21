#ifndef GET_GOOD_GENERAL_H
#define GET_GOOD_GENERAL_H

#include <QWidget>
#include "my_qlabel.h"
namespace Ui {
class Get_Good_General;
}

class Get_Good_General : public QWidget
{
    Q_OBJECT

public:
    explicit Get_Good_General(QWidget *parent = nullptr);
    Get_Good_General(Machine*);
    ~Get_Good_General();
    void OutOfGood();
    void ReturnGoodFail();
    void ReturnGoodSuccess();
    void ShowResponse(QString);
private slots:
    void Back_Home(QString);
    void setInfoSale(Machine*);

    void on_Btn_Back_GetGoodGeneral_clicked();
signals:
    void Signal_GetGoodGeneral_Process(MACHINE_STATE);
private:
    Ui::Get_Good_General *ui;
    QString show;
    QLabel *Lbl_Info;
    QLabel *Message;
    QPushButton *btn_Ok;
    QPushButton *btn_Back;
};

#endif // GET_GOOD_GENERAL_H

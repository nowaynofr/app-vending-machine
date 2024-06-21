#ifndef SELECT_SERVICE_H
#define SELECT_SERVICE_H

#include <QWidget>
#include "QObject"
#include "QApplication"
#include "Machine/machine.h"
#include "my_qlabel.h"

#include "QDebug"
namespace Ui {
class select_service;
}

class select_service : public QWidget
{
    Q_OBJECT

public:
    explicit select_service(QWidget *parent = nullptr);
    select_service(QList<QString>);
    ~select_service();
signals:
    void Signal_Select_Service(QString);
private slots:
    void Back_Home(QString);
    void SelectService(QString);
    void on_Btn_Back_SelectService_clicked();
private:
   // QLabel* service[];

    Ui::select_service *ui;
    QPushButton *btn_Back;
    QLabel* service[12];
   // QPushButton *buttons[10];
};

#endif // SELECT_SERVICE_H

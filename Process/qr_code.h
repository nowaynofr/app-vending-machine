#ifndef QR_CODE_H
#define QR_CODE_H

#include <QWidget>
#include "Transaction/transaction.h"
#include "Transaction/machine_state.h"
#include "Machine/machine.h"
#include "my_qlabel.h"
namespace Ui {
class QR_code;
}

class QR_code : public QWidget
{
    Q_OBJECT

public:
    explicit QR_code(QWidget *parent = nullptr);
    QR_code(QString,quint8);
    ~QR_code();
    void SetImage();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void aaa();
private slots:
    void Back_Home(QString);
    void on_Btn_Ok_QRcode_clicked();

    void on_Btn_Back_QRcode_clicked();

signals:
    void Signal_QR_Code(MACHINE_STATE);
private:
    Db m_db;
    QString ImageQR_Name;
    QString QRCode;
    Ui::QR_code *ui;
    QPushButton *btn_Back;
};

#endif // QR_CODE_H

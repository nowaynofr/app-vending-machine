//#ifdef BILLVALIDATOR_H
//#define BILLVALIDATOR_H


#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QTextCodec>

#include <common/configurationmanager.h>
#include "common/deviceconfig.h"


#define BILL_COMMAND_INIT "3001300033013300000031013100000036013600000037010200390000003301330000003401FF00FF00FF00FF003000"
#define BILL_RESPONSE_ACK "0001"
#define BILL_COMMAND_STATUS "330133000000"
#define BILL_STATUS_BUSY "03000301"
#define BILL_STATUS_REJECTED "0b000b01"
#define BILL_COMMAND_STACKED "350101003600"
#define BILL_RESPONSE_STACKED "0001"

class BillValidator : public QObject
{
    Q_OBJECT
    enum BILL_MODE{
        INIT = 0,
        QUERY
    } ;
public:
    BillValidator(QObject *parent = 0);
    ~BillValidator();

    ConfigurationManager config;

    void setup(const QString portName, int baudrate);
    double amount;
    QString preStatus;
    QString currentStatus;
    bool CheckIdentifiedAmount;
    bool CheckSendResponse;
    QString ResponseBill;


public slots:
    void run();
    void start();
    void stop();

signals:
    void bill_accepted(const double &data);
    void bill_identified(const double &data);
    void bill_unAccepted(const double &data);
    //V1.2 Bắt đầu
    void bill_error(const QString &s);
    void bill_status(QString);
    void bill_response(QString);
    //V1.2 Kết thúc

    void error(const QString &s);
    void timeout(const QString &s);

protected:
    bool check_open();
    QByteArray send_wait(QByteArray data, bool & ok);


//    bool send_init();
//    bool send_status();
//    bool send_stack();
    void do_init();
    void do_query();
    int waitTimeout;
    int m_bill_type;
private:
    double get_bill_amount();

    QThread m_thread;
    QSerialPort m_serial;
    BILL_MODE m_mode;
    int m_retry;
    bool stopThread;
};
//#endif // BILLVALIDATOR_H

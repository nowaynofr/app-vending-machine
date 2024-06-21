//#ifdef RS485CONTROLLER_H

#include <QLinkedList>
#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <Transaction/machinestatus.h>
#include <Transaction/transaction.h>
#define SENSOR_CONTROL 42

#define SENSOR_COMMAND_START 0xAA
// ip slave - 1 byte
// command - byte
#define SENSOR_COMMAND_QUERY 0x30
#define SENSOR_COMMAND_RETURN_GOODS 0x31
#define RFID_SLAVE 0x08
// length - byte
#define SENSOR_COMMAND_QUERY_LENGTH 0x00
#define SENSOR_COMMAND_RETURN_GOODS_LENGTH 0x02
// data
#define SENSOR_COMMAND_STOP 0x01

class RS485Controller : public QObject
{
    Q_OBJECT
    enum CONTROLER_MODE{
        SCAN = 0,
        QUERY,
        RETURN_GOODS,
        RFID_MODE
    } ;
public:
    RS485Controller(QObject *parent = 0);
    ~RS485Controller();

    void setup(const QString portName, const quint32 baudrate);

    quint8 testReturnGoods(quint32 slotId, quint8 count);
    void ConvertRFIDMode();
    void ConvertQueryMode();
    //bool ReturnGoodAndroid(quint32 slotId, quint8 count);

    quint8 returnGoods(quint32 slotId, quint8 count);
    quint8 returnGoodsForTransaction(Transaction *transaction);
    void returnGoodsForTransactionAndroid(QList<quint16>, QList<quint8>);
    void safeClose();
public slots:
    void run();
    void start();
    void stop();

private slots:
    //void handleError(QSerialPort::SerialPortError error);
signals:
    void statusChange(QVariantMap);
    void RFID_Data(QString);
    void status(QString);
protected:
    bool check_open();
    QByteArray send_wait(QByteArray data, bool & ok);
private:
    QList<int> m_nodes;
    QThread m_thread;
    QSerialPort m_serial;
    bool stopThread;
    uchar m_khay_hang;
    int waitTimeout;
    CONTROLER_MODE m_mode;
    quint32 m_slotId;
    quint8 m_count;
    MachineStatus m_status;

    bool CheckScan;
    bool CheckReturnGood;
    QList<quint16> slot_id_list;
    QList<quint8> quantity_list;

};
//#endif // TRAYCONTROLLER_H

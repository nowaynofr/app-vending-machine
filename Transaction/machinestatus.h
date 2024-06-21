#ifndef MACHINESTATUS_H
#define MACHINESTATUS_H

#include <QObject>
#include <QVariantMap>
#include <QTextCodec>
class MachineStatus: public QObject
{
    Q_OBJECT
public:
    explicit MachineStatus(QObject *parent = 0);
    ~MachineStatus();

    bool updateMachineStatus(QString);
    bool updateRFID_Data(QByteArray);
    QString Temp = "0";
    QString Door;
    QString Vibration;

    QVariantMap Json;
    QString JsonString;

    QString Json_RFID_Data;

};

#endif // MACHINESTATUS_H

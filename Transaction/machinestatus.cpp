#include "machinestatus.h"
#include "Transaction/log.h"

#include <QJsonDocument>
#include <QJsonObject>

MachineStatus::MachineStatus(QObject *parent) :QObject(parent)
{
}

MachineStatus::~MachineStatus()
{

}


bool MachineStatus::updateMachineStatus(QString status)
{
// T=+22;V=000;D=0;
    bool needUpdate = false;
    QStringList tokens = status.split(";");
    foreach (QString token , tokens) {
        //LOG << token;
        QStringList subtokens = token.split("=");
        if (subtokens.length() == 2 && subtokens[0] == "T" && Temp != subtokens[1])
        {
            Temp = subtokens[1];
            //LOG << "TEMP" << subtokens[1];
            needUpdate = true;
        }
        else if (subtokens.length() == 2 && subtokens[0] == "V" && Vibration != subtokens[1])
        {
            Vibration = subtokens[1];
           // LOG << "Vibration" << subtokens[1];
            needUpdate = true;
        }
        else if (subtokens.length() == 2 && subtokens[0] == "D" && Door != subtokens[1])
        {
            Door = subtokens[1];
           // LOG << "Door" << subtokens[1];
            needUpdate = true;
        }

    }
    if (needUpdate)
    {
        Json.clear();
	
        Json.insert("Temp", Temp);
        Json.insert("Vibra", Vibration);
        Json.insert("Door", Door);
        Json.insert("Time",QDateTime::currentMSecsSinceEpoch()/1000);
        JsonString = QJsonDocument(QJsonObject::fromVariantMap(Json)).toJson();
        LOG << JsonString;
    }
    return true;
}

bool MachineStatus::updateRFID_Data(QByteArray data)
{
    Json_RFID_Data = "";
    Json_RFID_Data = data.toHex();
    return true;
}

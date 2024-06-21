
// V1.2
// Ngày sửa: 27/11/2018
// Người sửa: Namnd
/* Mục đích:
-Tạo mới 1 Class để làm việc với Bill.
*/



//V1.2 Bắt đầu
#include "billamount.h"
#include <QJsonDocument>
#include <QJsonObject>
//#include "common/stringutils.h"
//#include "common/log.h"
#include <QFile>
BillInputAmount::BillInputAmount(QObject *parent) :
    QObject(parent)
  ,Id("")
  ,BillId("")
  ,StartTime(QDateTime::currentDateTime())
  ,sale_session_id(1)
  ,BillAmount(0)
  ,TotalBill(0)
  //,stt(0)
{
}
BillInputAmount::~BillInputAmount()
{

}

void BillInputAmount::initBill()
{
    BillAvailable = 0;
}
QString BillInputAmount::toBillResponse() const
{
    QVariantMap objectinfo;
    objectinfo.insert("Title", "response");
    objectinfo.insert("id", Id);
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("startTime", StartTime.toMSecsSinceEpoch()/1000);
    objectinfo.insert("BillResponse",BillResponse);
    objectinfo.insert("saleSessionId",sale_session_id);
    objectinfo.insert("BillStatus",BillStatus);

    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();

}

QString BillInputAmount::toBillAmount() const
{
    QVariantMap objectinfo;
    objectinfo.insert("Title", "amount");
    objectinfo.insert("id", Id);
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("startTime", StartTime.toMSecsSinceEpoch()/1000);
    objectinfo.insert("saleSessionId",sale_session_id);
    objectinfo.insert("BillAmount",BillAmount);



    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();

}

//V1.2 Kết thúc

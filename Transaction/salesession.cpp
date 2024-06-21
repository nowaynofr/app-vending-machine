#include "salesession.h"

SaleSession::SaleSession(QObject *parent) : QObject(parent)
  ,SessionId("")
  ,StartTime(QDateTime::currentDateTime())
  ,TotalAmount(0)
  ,TotalBill(0)
  ,StaffCode("Admin")
  ,IsSyncing(false)
  ,CheckSaleMonth(false)
  ,CheckInitPeriodTable(false)
  ,PeriodTotalAmount(0)
  ,TotalAmountShare(0)
  ,PeriodTotalAmountShare(0)
  ,Type("day")
  ,PrePeriod("")
  ,LastPeriod("")
  ,PeriodSale("")
  ,VersionApp("")
{

}
SaleSession::~SaleSession()
{

}

QString SaleSession::toAPIString() const
{
    QVariantMap objectinfo;
    objectinfo.insert("id", SessionId);
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("startTime", StartTime.toMSecsSinceEpoch()/1000);
    objectinfo.insert("actionTime", EndTime.toMSecsSinceEpoch()/1000);
    objectinfo.insert("money",StringUtils::formatNumberVND(TotalBill));
    objectinfo.insert("moneyCalculate",StringUtils::formatNumberVND(TotalAmount));
    objectinfo.insert("staffCode",StaffCode);
    objectinfo.insert("VersionApp",VersionApp);
    objectinfo.insert("period",PrePeriod);
    objectinfo.insert("periodTotalAmount",PeriodTotalAmount);
    objectinfo.insert("shareSale",TotalAmountShare);
    objectinfo.insert("sharePeriodSale",PeriodTotalAmountShare);
    objectinfo.insert("type",Type);



    //LOG << objectinfo;
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}

QVariantMap SaleSession::toMap() const
{
    QVariantMap objectinfo;
    objectinfo.insert("SessionId", SessionId);
    objectinfo.insert("StartDate", StartTime.toString("yyyy-MM-dd hh:mm:ss"));
    objectinfo.insert("EndDate", EndTime.toString("yyyy-MM-dd hh:mm:ss"));
    objectinfo.insert("TotalAmount",StringUtils::formatNumberVND(TotalAmountShare));
    objectinfo.insert("TotalBill",StringUtils::formatNumberVND(TotalBill));
    objectinfo.insert("staffCode",StaffCode);
    objectinfo.insert("VersionApp",VersionApp);
    //objectinfo.insert("Preperiod",PrePeriod);
    objectinfo.insert("PeriodTotalAmonut",StringUtils::formatNumberVND(PeriodTotalAmountShare));
    objectinfo.insert("TotalAmountShared",StringUtils::formatNumberVND(TotalAmountShare));
    objectinfo.insert("PeriodTotalAmonutShared",StringUtils::formatNumberVND(PeriodTotalAmountShare));

    return objectinfo;
}

QVariantMap SaleSession::toMapView() const
{
    QVariantMap objectinfo;
    objectinfo.insert("SessionId", SessionId);
    objectinfo.insert("StartDate", StartTime.toString("yyyy-MM-dd hh:mm:ss"));
    objectinfo.insert("EndDate", EndTime.toString("yyyy-MM-dd hh:mm:ss"));
    objectinfo.insert("TotalAmount",StringUtils::formatNumberVND(TotalAmount));
    objectinfo.insert("TotalBill",StringUtils::formatNumberVND(TotalBill));
    objectinfo.insert("staffCode",StaffCode);
    objectinfo.insert("VersionApp",VersionApp);
    //objectinfo.insert("Preperiod",PrePeriod);
    objectinfo.insert("PeriodTotalAmonut",StringUtils::formatNumberVND(PeriodTotalAmount));
    objectinfo.insert("TotalAmountShared",StringUtils::formatNumberVND(TotalAmountShare));
    objectinfo.insert("PeriodTotalAmonutShared",StringUtils::formatNumberVND(PeriodTotalAmountShare));

    return objectinfo;
}

SaleSession::operator QString()
{

    return QJsonDocument(QJsonObject::fromVariantMap(toMap())).toJson();
}

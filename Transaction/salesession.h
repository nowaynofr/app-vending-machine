#ifndef SALESESSION_H
#define SALESESSION_H

#include <QObject>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include "stringutils.h"
class SaleSession : public QObject
{
    Q_OBJECT
public:
    explicit SaleSession(QObject *parent = nullptr);
    ~SaleSession();
    QString SessionId;
    QString MachineId;
    QDateTime StartTime;
    QDateTime EndTime;
    quint32 TotalBill;
    quint32 TotalAmount;
    QString StaffCode;

    bool CheckSaleMonth;
    quint32 PeriodTotalAmount;
    QString PrePeriod;
    QString LastPeriod;
    QString PeriodSale;
    QString VersionApp;
    bool CheckInitPeriodTable;
    quint32 TotalAmountShare;
    quint32 PeriodTotalAmountShare;
    QString Type;
    bool IsSyncing;

    bool IsUpdateDB;



    operator QString();
    QVariantMap toMap() const;
    QVariantMap toMapView() const;
    QString toAPIString() const;

signals:

};

#endif // SALESESSION_H

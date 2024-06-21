//V1.2 Bắt đầu
#ifndef BILLAMOUNT_H
#define BILLAMOUNT_H

#include <QDateTime>
#include <QObject>
#include <QVariantMap>

class BillInputAmount : public QObject
{
    Q_OBJECT
public:
    explicit BillInputAmount(QObject *parent = 0);
    ~BillInputAmount();
    QString Id;
    QString MachineId;
    QDateTime StartTime;
    QDateTime EndTime;
    quint32 TotalBill;
    quint32 BillAmount;
    QString BillResponse;
    QString BillStatus;
    int sale_session_id;

    QString BillId;
    quint32 BillAvailable;
    QDateTime BillTime;


signals:

public slots:
    void initBill();
   // operator QString();
  //  QVariantMap toMap() const;
    QString toBillResponse() const;
    QString toBillAmount() const;
};

#endif // BILLAMOUNT_H
//V1.2 Kết thúc

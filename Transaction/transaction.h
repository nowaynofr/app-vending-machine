#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include <QDateTime>
//#include <Db/db.h>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "stringutils.h"
#include "machine_state.h"
#include "salesession.h"
#include "log.h"
#include <QUuid>
class Transaction : public QObject
{
    Q_OBJECT
public:
    explicit Transaction(QObject *parent = nullptr);
    ~Transaction();
    QString TransferId;
    QString SaleSessionId;
    QString TransactionId;// bao gồm các chữ cái và số, tối đa 50 ký tự
    QString MachineId;// bao gồm các chữ cái và số, tối đa 50 ký tự
    QString KioskId;
    QString SlotId;
    QString GoodId;
    QString GoodName;
    quint32 GoodPrice;
    quint32 moneyCalculate;
    quint32 GoodPriceGeneral;
    QDateTime TransactionTime;// định dạng theo DD/MM/YYYY HH:MI:SS
    quint32 AvailableAmount;
    quint32 PricePostpaid;
   // QString TextPromotion;
    QString NumberPhonePromotion;
    //QString UrlImagePromotion;
    quint32 IdentifiedAmount;

    quint32 InputAmount;
    quint8 Quantity;
    quint8 TransactionType;
    quint8 TransactionStatus;
    quint8 TransactionSync;
    QString OrderInformation;

    QList<quint16> SlotIdList;
    QList<quint8> QuantityList;
    //QString Checksum;

    //quint8 state;

   // quint8 ChargeTypeLast;
    quint8 ChargeTypeQuatity;

   // bool CheckChargedCoupon;

    QString NumberPhone;
   // quint8 total_page_menu_good;
   // quint8 total_page_type_good;
  //  quint8 current_page_menu_good;
   // quint8 current_page_type_good;

    QString Industry;
    QString goodType;
  //  QList<QString> ListMenuGood;
   // QList<QString> ListTypeGood;
  //  QList<int> ListPriceGood;
    QString BuyType;
    QString MessageRechargeMobile;


    quint8 serviceCode;
    QString nameServer;
    QString CardCode;

   // bool IsCheckCardCode;
    QString idSale;
    quint32 reducedValue;

   // bool CheckServerPostpaid;
    bool CheckPriceServe;
    bool IsCheckingWorkWithVTC;
    QString period;
   // bool CheckFlagSmsGoodDigital;
    bool CheckInputGetGood;
    quint32 InputGetGood;

    quint32 UseValueCash;
   // int moneyLackCoupon;
    quint32 TimeDelayCoupon;
    QString PinUserRechargeCoupon;
    quint8 PriorityCharge;

    QString customerID;
    int CategoryId;
    QString Invoice;
    QString productID;
    QString bill_number;
    quint32 amount_and_fee;

    QString Motor_Insurance_Info;
    bool CheckSaleSharePermission;

    QString RfidData;

    operator QString();
    QVariantMap toMap() const;
    void init(QString);
    void reset();
    qint32 ChargeAmount();
    QString toAPIString() const;
    QString GetPriceSever() const;
    QString GetInvoiceTopupPartner() const;
    QString toRechargeInvoiceTopupPartner() const;
    QString toRechargeMotorInsurance() const;
    QString CheckServerRechargeMobile() const;
    QString toSendSMS() const;
   // QString toDisplayImagePromotion() const;
  //  QString toFinishDisplayImagePromotion() const;
  //  QString toSwitchScreenSaver() const;
  //  qint32 ChargeAmountMobile();
    QString toRechargeCardMobile() const;
    QString toReturnGoodKiosk() const;
    QString toCheckAdminLogin(QString ,QString) const;

signals:
private:



};

#endif // TRANSACTION_H

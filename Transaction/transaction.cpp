#include "transaction.h"

Transaction::Transaction(QObject *parent) : QObject(parent)
{
    TransferId = SaleSessionId = TransactionId = MachineId = SlotId = GoodId = GoodName = OrderInformation = "";
    NumberPhone = idSale = period = nameServer = PinUserRechargeCoupon = bill_number = "";
    Industry = customerID = Invoice = productID = KioskId = "";
    GoodPrice = GoodPriceGeneral = AvailableAmount = IdentifiedAmount = InputAmount = Quantity = InputGetGood = 0;
    TransactionType = TransactionStatus = TransactionSync = moneyCalculate = 0;
    serviceCode = reducedValue = PricePostpaid = UseValueCash = TimeDelayCoupon = 0;
    CategoryId = amount_and_fee = 0;
    CheckInputGetGood= false;
    CheckSaleSharePermission = true;
    RfidData = "";
    SlotIdList.clear();
    QuantityList.clear();
}
Transaction::~Transaction()
{

}
QVariantMap Transaction::toMap() const
{
    QVariantMap objectinfo;
    objectinfo.insert("transactionId", TransactionId);
    objectinfo.insert("transferId", TransferId);
    objectinfo.insert("saleSessionId", SaleSessionId);
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("slotId", SlotId);
    objectinfo.insert("goodId", GoodId);
    objectinfo.insert("goodName", GoodName);
    objectinfo.insert("goodPrice", GoodPrice);
    objectinfo.insert("moneyPostpaid", PricePostpaid);
    objectinfo.insert("time", TransactionTime.toMSecsSinceEpoch()/1000);
    if(TransactionType == KioskTransactionType::COUPON || TransactionType == KioskTransactionType::CASHandCOUPON || TransactionType == KioskTransactionType::RFID)
        objectinfo.insert("pinCoupon", PinUserRechargeCoupon);
    if(serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER)
        objectinfo.insert("moneyCalculate",amount_and_fee);
    else{
        if(moneyCalculate == 0){
            objectinfo.insert("moneyCalculate",GoodPrice * Quantity);
        }else{
            objectinfo.insert("moneyCalculate",moneyCalculate);
        }
    }
    objectinfo.insert("moneyInput",InputAmount);
    objectinfo.insert("moneyAvailable",AvailableAmount);
    objectinfo.insert("quantity",Quantity);
    objectinfo.insert("typePay",TransactionType);
    objectinfo.insert("status",TransactionStatus);
    objectinfo.insert("coupon", OrderInformation);
    objectinfo.insert("qr", OrderInformation);
    objectinfo.insert("period",period);

    objectinfo.insert("idSale",idSale);
    objectinfo.insert("reducedValue",reducedValue);
    if(TransactionType == KioskTransactionType::CASHandCOUPON){
        objectinfo.insert("priorityCharge",PriorityCharge);
    }
    return objectinfo;
}

QString Transaction::toAPIString() const
{
    QVariantMap objectinfo;
    objectinfo.insert("transferId", TransferId);
    objectinfo.insert("saleSessionId", SaleSessionId);
    objectinfo.insert("transactionId", TransactionId);
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("slotId", SlotId);
    objectinfo.insert("goodId", GoodId);
    objectinfo.insert("goodName", GoodName);
    objectinfo.insert("moneyPostpaid", PricePostpaid);

    objectinfo.insert("typePay",TransactionType);
    objectinfo.insert("time",TransactionTime.toMSecsSinceEpoch()/1000);
    objectinfo.insert("coupon", OrderInformation);
    objectinfo.insert("qr", OrderInformation);
    if(TransactionType == KioskTransactionType::COUPON || TransactionType == KioskTransactionType::CASHandCOUPON || TransactionType == KioskTransactionType::RFID)
        objectinfo.insert("pinCoupon", PinUserRechargeCoupon);
    if(serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER)
        objectinfo.insert("moneyCalculate",amount_and_fee);
    else{
        if(moneyCalculate == 0){
            objectinfo.insert("moneyCalculate",GoodPrice * Quantity);
        }else{
            objectinfo.insert("moneyCalculate",moneyCalculate);
        }
    }
    objectinfo.insert("quantity",Quantity);
    objectinfo.insert("moneyInput",InputAmount);

    objectinfo.insert("idSale",idSale);
    objectinfo.insert("reducedValue",reducedValue);
    if(TransactionType == KioskTransactionType::CASHandCOUPON){
        objectinfo.insert("priorityCharge",PriorityCharge);
    }
//    if (TransactionType == KioskTransactionType::CASHandMOMO||TransactionType == KioskTransactionType::CASHandQRPAY||TransactionType == KioskTransactionType::CASHandVINID||TransactionType == KioskTransactionType::CASHandCOUPON||TransactionType == KioskTransactionType::CASHandGRABPAY||TransactionType == KioskTransactionType::CASHandZALOPAY){
//        objectinfo.insert("moneyCalculateMix ",GoodPrice * Quantity - AvailableAmount);
//        objectinfo.insert("moneyAvailableMix",AvailableAmount);
//    }


    objectinfo.insert("moneyAvailable",AvailableAmount);
    objectinfo.insert("goodPrice", GoodPrice);
    objectinfo.insert("status",TransactionStatus);

    objectinfo.insert("period",period);

    LOG << objectinfo;
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}

QString Transaction::toRechargeCardMobile() const
{
    LOG;
    QVariantMap objectinfo;
    objectinfo.insert("Title", GoodId);
    objectinfo.insert("transferId", TransferId);
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("transactionId", TransactionId);
    objectinfo.insert("saleSessionId", SaleSessionId);
    objectinfo.insert("numberPhone", NumberPhone);
    objectinfo.insert("moneyAvailable", AvailableAmount);
    if(serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER)
        objectinfo.insert("moneyCalculate",amount_and_fee);
    else{
        if(moneyCalculate == 0){
            objectinfo.insert("moneyCalculate",GoodPrice * Quantity);
        }else{
            objectinfo.insert("moneyCalculate",moneyCalculate);
        }
    }
    objectinfo.insert("goodPrice", GoodPrice);
    objectinfo.insert("moneyPostpaid", PricePostpaid);
    objectinfo.insert("typePay",TransactionType);
    objectinfo.insert("idSale",idSale);
    objectinfo.insert("moneyInput",InputAmount);
    objectinfo.insert("reducedValue",reducedValue);
    objectinfo.insert("time",TransactionTime.toMSecsSinceEpoch()/1000);
    objectinfo.insert("status",TransactionStatus);
    objectinfo.insert("slotId", SlotId);
    objectinfo.insert("goodId", GoodId);
    objectinfo.insert("goodName", GoodName);
    objectinfo.insert("quantity",Quantity);
    objectinfo.insert("period",period);
    objectinfo.insert("time",QDateTime::currentMSecsSinceEpoch()/1000);
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
    
}

QString Transaction::toReturnGoodKiosk() const
{
    LOG;
    QVariantMap objectinfo;
    objectinfo.insert("Title", "ReturnGood");
    objectinfo.insert("transferId", TransferId);
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("transactionId", TransactionId);
    objectinfo.insert("saleSessionId", SaleSessionId);
    objectinfo.insert("numberPhone", NumberPhone);
    objectinfo.insert("moneyAvailable", AvailableAmount);
    if(serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER)
        objectinfo.insert("moneyCalculate",amount_and_fee);
    else{
        if(moneyCalculate == 0){
            objectinfo.insert("moneyCalculate",GoodPrice * Quantity);
        }else{
            objectinfo.insert("moneyCalculate",moneyCalculate);
        }
    }
    objectinfo.insert("goodPrice", GoodPrice);
    objectinfo.insert("moneyPostpaid", PricePostpaid);
    objectinfo.insert("typePay",TransactionType);
    objectinfo.insert("idSale",idSale);
    objectinfo.insert("moneyInput",InputAmount);
    objectinfo.insert("reducedValue",reducedValue);
    objectinfo.insert("time",TransactionTime.toMSecsSinceEpoch()/1000);
    objectinfo.insert("status",TransactionStatus);
    objectinfo.insert("slotId", SlotId);
    objectinfo.insert("goodId", GoodId);
    objectinfo.insert("goodName", GoodName);
    objectinfo.insert("quantity",Quantity);
    objectinfo.insert("period",period);
   // objectinfo.insert("time",QDateTime::currentMSecsSinceEpoch()/1000);
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}

QString Transaction::toCheckAdminLogin(QString user, QString pass) const
{
    QVariantMap objectinfo;
    objectinfo.insert("Title", "LoginAdmin");
    objectinfo.insert("transferId", TransferId);
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("coupon", user);
    objectinfo.insert("pinCoupon", pass);
    objectinfo.insert("time",QDateTime::currentMSecsSinceEpoch()/1000);
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}
QString Transaction::GetPriceSever() const
{
    LOG;
    QVariantMap objectinfo;
    objectinfo.insert("transferId", "");
    objectinfo.insert("saleSessionId", SaleSessionId);
    objectinfo.insert("transactionId", TransactionId);
    objectinfo.insert("machineId", MachineId);//11111
    objectinfo.insert("slotId", SlotId);
    objectinfo.insert("goodId", GoodId);//1111
    objectinfo.insert("goodName", GoodName);
    objectinfo.insert("numberPhone", NumberPhone);
    objectinfo.insert("typePay",TransactionType);//11111111
    objectinfo.insert("time",QDateTime::currentMSecsSinceEpoch()/1000);//TransactionTime.toTime_t());//.toMSecsSinceEpoch());
    objectinfo.insert("coupon", "");
    objectinfo.insert("moneyCalculate","");
    objectinfo.insert("quantity",Quantity);
    objectinfo.insert("moneyInput",InputAmount);
    objectinfo.insert("goodPrice","");
    objectinfo.insert("moneyAvailable",AvailableAmount);
    objectinfo.insert("status",TransactionStatus);
    objectinfo.insert("period",period);
    LOG << objectinfo;
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}

QString Transaction::GetInvoiceTopupPartner() const
{
    LOG;
    QVariantMap objectinfo;
    objectinfo.insert("Title", "checkBillInfo");
    objectinfo.insert("transferId", TransferId);
  //  objectinfo.insert("transferId", "");
  //  objectinfo.insert("saleSessionId", SaleSessionId);
  //  objectinfo.insert("transactionId", TransactionId);
    objectinfo.insert("machineId", MachineId);//11111
  //  objectinfo.insert("slotId", SlotId);
    objectinfo.insert("goodId", GoodId);//1111
    objectinfo.insert("goodName", GoodName);
 //   objectinfo.insert("numberPhone", NumberPhone);
  //  objectinfo.insert("typePay",TransactionType);//11111111
    objectinfo.insert("time",QDateTime::currentMSecsSinceEpoch()/1000);//TransactionTime.toTime_t());//.toMSecsSinceEpoch());
  //  objectinfo.insert("coupon", "");
    objectinfo.insert("moneyCalculate","");
    objectinfo.insert("quantity",Quantity);
    objectinfo.insert("moneyInput",InputAmount);
    objectinfo.insert("moneyAvailable",AvailableAmount);
    objectinfo.insert("status",TransactionStatus);
    objectinfo.insert("customerID",customerID);
    objectinfo.insert("categoryID",CategoryId);
    objectinfo.insert("productID",0);
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}

QString Transaction::toRechargeInvoiceTopupPartner() const
{
    LOG;
    QVariantMap objectinfo;
    objectinfo.insert("Title", "payBill");
    objectinfo.insert("transferId", TransferId);
    objectinfo.insert("machineId", MachineId);//11111
    objectinfo.insert("goodId", GoodId);//1111
    objectinfo.insert("goodName", GoodName);
    objectinfo.insert("time",QDateTime::currentMSecsSinceEpoch()/1000);//TransactionTime.toTime_t());//.toMSecsSinceEpoch());
    if(moneyCalculate == 0){
        objectinfo.insert("moneyCalculate",GoodPrice * Quantity);
    }else{
        objectinfo.insert("moneyCalculate",moneyCalculate);
    }
    objectinfo.insert("quantity",Quantity);
    objectinfo.insert("moneyInput",InputAmount);
    objectinfo.insert("moneyAvailable",AvailableAmount);
    objectinfo.insert("status",TransactionStatus);
    objectinfo.insert("customerID",customerID);
    objectinfo.insert("categoryID",CategoryId);
    objectinfo.insert("productID",productID);
    objectinfo.insert("productAmount",GoodPrice);
    objectinfo.insert("data",bill_number);
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}

QString Transaction::toRechargeMotorInsurance() const
{
    LOG;
    QVariantMap objectinfo;
    objectinfo.insert("Title", "motorInsurance");
    objectinfo.insert("transferId", TransferId);
    objectinfo.insert("machineId", MachineId);//11111
    objectinfo.insert("goodId", GoodId);//1111
    objectinfo.insert("goodName", GoodName);
    objectinfo.insert("time",QDateTime::currentMSecsSinceEpoch()/1000);//TransactionTime.toTime_t());//.toMSecsSinceEpoch());
    if(moneyCalculate == 0){
        objectinfo.insert("moneyCalculate",GoodPrice * Quantity);
    }else{
        objectinfo.insert("moneyCalculate",moneyCalculate);
    }
    objectinfo.insert("quantity",Quantity);
    objectinfo.insert("moneyInput",InputAmount);
    objectinfo.insert("moneyAvailable",AvailableAmount);
    objectinfo.insert("status",TransactionStatus);
    objectinfo.insert("period",period);
    objectinfo.insert("goodPrice", GoodPrice);
    objectinfo.insert("ownerInfo",Motor_Insurance_Info);
    LOG << QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}

QString Transaction::CheckServerRechargeMobile() const
{
    QVariantMap objectinfo;
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("Title", "CheckServiceAvailable");
    objectinfo.insert("goodId", GoodId);
    objectinfo.insert("time",QDateTime::currentDateTime().toMSecsSinceEpoch()/1000);
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}

QString Transaction::toSendSMS() const
{
    QVariantMap objectinfo;
    objectinfo.insert("machineId", MachineId);
    objectinfo.insert("transactionId", TransactionId);
    objectinfo.insert("goodId", GoodId);
    objectinfo.insert("time",QDateTime::currentDateTime().toMSecsSinceEpoch()/1000);
    objectinfo.insert("phoneNumber", NumberPhonePromotion);
   // LOG << objectinfo;
    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
}

void Transaction::init(QString sessionId)
{
    GoodId = "";
    SlotId = "";
    GoodName = "";
    GoodPrice = PricePostpaid = ChargeTypeQuatity = moneyCalculate = 0;
    Quantity = 1 ;
    TransactionType = KioskTransactionType::UNSET;
    TransferId = "";

    //TextPromotion = UrlImagePromotion = "";

    SaleSessionId = sessionId;
    TransactionId = "";
    GoodPriceGeneral = 0;
    //    LOG << machineId << sessionId;
    //MachineId = machineId;
    //    LOG << machineId << sessionId;
    //    TransactionTime.setTimeSpec(Qt::UTC);
    //    TransactionTime = QDateTime::currentMSecsSinceEpoch();
    TransactionStatus = KioskTransactionStatus::INIT;
    TransactionSync = 0;
    OrderInformation = "";

    if(CheckInputGetGood){
        InputAmount = InputGetGood;
    }else{
        InputAmount = 0;
    }

    idSale = "";
    reducedValue = 0;

    nameServer = "";
    serviceCode = CategoryId = amount_and_fee = 0;
    NumberPhone = NumberPhonePromotion = "";
    CardCode = "";
    CheckInputGetGood = CheckPriceServe = false;
    InputGetGood = 0;
    Industry = "";
    goodType = "";
    //ListMenuGood.clear();
    //ListPriceGood.clear();
    //ListTypeGood.clear();
    BuyType = PinUserRechargeCoupon = "";
    customerID = Invoice = productID = bill_number = "";

    Motor_Insurance_Info = "";
    CheckSaleSharePermission = true;
    RfidData = "";
    SlotIdList.clear();
    QuantityList.clear();
    //    LOG << machineId << sessionId;
}

void Transaction::reset()
{
    GoodId = "";
    SlotId = "";
    GoodName = "";
    GoodPrice = 0;
    GoodPriceGeneral = 0;
    Quantity = 1 ;
    TransactionType = KioskTransactionType::UNSET;
    TransferId = "";
    idSale = "";
    reducedValue = 0;
    CardCode = "";
    TransactionStatus = KioskTransactionStatus::INIT;
}

qint32 Transaction::ChargeAmount()
{
    if(serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
        return AvailableAmount - amount_and_fee;
    }else{
        if(moneyCalculate == 0){
            return AvailableAmount - GoodPrice * Quantity;
        }else{
            return AvailableAmount - moneyCalculate;
        }
    }

}

//qint32 Transaction::ChargeAmountMobile()
//{
//    return AvailableAmount - GoodPrice;
//}

Transaction::operator QString()
{

    return QJsonDocument(QJsonObject::fromVariantMap(toMap())).toJson();
}


//QString Transaction::toDisplayImagePromotion() const
//{
//    QVariantMap objectinfo;
//    objectinfo.insert("DisplayImagePromotion", 1);
//    //if(TextPromotion.length() )
//    objectinfo.insert("TextPromotion", TextPromotion);
//    objectinfo.insert("UrlImagePromotion", UrlImagePromotion);
//    objectinfo.insert("machineId", MachineId);
//    objectinfo.insert("time",QDateTime::currentDateTime().toMSecsSinceEpoch()/1000);
//    objectinfo.insert("goodId", GoodId);
//    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
//}

//QString Transaction::toFinishDisplayImagePromotion() const
//{
//    QVariantMap objectinfo;
//    objectinfo.insert("toFinishDisplayImagePromotion", 1);
//    objectinfo.insert("phoneNumber", NumberPhonePromotion);
//    //if(TextPromotion.length() )
//   // objectinfo.insert("TextPromotion", TextPromotion);
//   // objectinfo.insert("UrlImagePromotion", UrlImagePromotion);
//    objectinfo.insert("machineId", MachineId);
//    objectinfo.insert("time",QDateTime::currentDateTime().toMSecsSinceEpoch()/1000);
//    objectinfo.insert("goodId", GoodId);
//    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
//}

//QString Transaction::toSwitchScreenSaver() const
//{
//    QVariantMap objectinfo;
//    objectinfo.insert("toSwitchScreenSaver", 1);
//    //if(TextPromotion.length() )
//   // objectinfo.insert("TextPromotion", TextPromotion);
//   // objectinfo.insert("UrlImagePromotion", UrlImagePromotion);
//    objectinfo.insert("machineId", MachineId);
//    objectinfo.insert("time",QDateTime::currentDateTime().toMSecsSinceEpoch()/1000);
//    objectinfo.insert("goodId", GoodId);
//    return QJsonDocument(QJsonObject::fromVariantMap(objectinfo)).toJson();
//}

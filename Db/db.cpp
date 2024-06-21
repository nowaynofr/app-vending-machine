#include "db.h"

Db::Db()
{

}
Db::~Db(){
    closeDb();
}
bool Db::openDb()
{
    QFile DbFile;
    QString DatabaseDataStoragePath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
    LOG<<DatabaseDataStoragePath<<"đường dẫn db";
    DbFile.setFileName("assets:/database");
    DbFile.copy(DatabaseDataStoragePath + "/database");
    QFile::setPermissions(DatabaseDataStoragePath + "/database", QFile::WriteOwner | QFile::ReadOwner);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database");
    if (!db.open()) {
        qDebug() << "Cannot open database";
        return false;
    }
    if(!db.tables().contains(QLatin1String("kiosk_menu_good_general"))){
        CreatGoodMenuGeneralTable();
    }
//    if(!db.tables().contains(QLatin1String("kiosk_admin"))){
//        CreatKioskAdminTable();
//        InsertAutoKioskAdmin();
//    }
    UpdateSignalCount("a000a001",0);
    UpdateSignalCount("a100a101",0);
    UpdateSignalCount("a200a201",0);
    UpdateSignalCount("a300a301",0);
    UpdateSignalCount("a400a401",0);
    UpdateSignalCount("a500a501",0);
    UpdateSignalCount("a600a601",0);
    UpdateSignalCount("a700a701",0);
    UpdateSignalCount("0b000b001601",0);
    UpdateSignalCount("09000901",0);
    UpdateSignalCount("050009000e01",0);
    UpdateSignalCount("05000501",0);
//    UpdateSignalCount("error_bill",0);
//    QSqlQuery q(db);
//    q.exec("PRAGMA table_info(kiosk_menu_good)");
//    if(q.next()){
//        if(!q.value(9).toString().contains("imageUrl")){
//            q.exec("ALTER TABLE kiosk_menu_good ADD COLUMN imageUrl TEXT");
//           // q.exec("ALTER TABLE kiosk_sale_session ADD COLUMN period_total_amount integer");
//        }else{
//            LOG<<"Column period exist!!!";
//        }
//    }
   // cleanMenuGoodTable();
   // InsertAutoMenuGoodTable();


    return true;
}

void Db::closeDb()
{
    db.close();
}
QSqlDatabase& Db::getDb()
{
    return db;
}

bool Db::InitDatabase()
{
    return true;
}

void Db::CreatGoodMenuTable()
{
    QSqlQuery q(db);
    if(q.exec(CREATE_MENU_TABLE)){
        LOG<<"creat MenuTable ok!";
    }

}

void Db::CreatGoodMenuGeneralTable()
{
    QSqlQuery q(db);
    if(q.exec(CREATE_MENU_GENERAL_TABLE)){
        LOG<<"creat MenuGeneralTable ok!";
    }
}

void Db::CreatKioskAdminTable()
{
    QSqlQuery q(db);
    if(q.exec(CREATE_KIOSK_ADMIN_TABLE)){
        LOG<<"creat KioskAdminTable ok!";
    }
}

void Db::InsertAutoKioskAdmin()
{
    QVariantList category;
    QVariantList part;
    QVariantList value;

    for(int i = 1; i <= 4; i++){
        category<<"ChargeTypeListDefault";
    }
    part<<"ListBankType"<<"ListChargeType"<<"ListOtherType"<<"ListWalletType";
    value<<"4,5"<<"4,3,6,8,9,14"<<"12"<<"6,8,9,14";

    for(int i = 1; i <= 4; i++){
        category<<"ChargeTypeListSetting";
    }
    part<<"ListBankType"<<"ListChargeType"<<"ListOtherType"<<"ListWalletType";
    value<<"4,5"<<"4,3,6,8,9,14"<<"12"<<"6,8,9,14";

    for(int i = 1; i <= 13; i++){
        category<<"ChargeTypeCodeName";
    }

    part<<"1"<<"12"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"14"<<"97"<<"98"<<"99";
    value<<"Tiền mặt"<<"Card (master,visa..)"<<"Coupon"<<"QR Pay (Bank)"<<"MB Bank"<<"MoMo"<<"ZaloPay"<<"Grab by Moca"<<"VinID"<<"SmartPay"<<"Bank"<<"Ví điện tử"<<"Khác";

    for(int i = 1; i <= 6; i++){
        category<<"ChargeTypeImageName";
    }
    part<<"4"<<"6"<<"7"<<"8"<<"9"<<"14";
    value<<"background_qr.jpg"<<"background_momo.jpg"<<"background_zalopay.jpg"<<"background_grabpay.jpg"<<"background_vinid.jpg"<<"background_smartpay.jpg";

    category<<"UrlPromotionImage";
    part<<"UrlPromotionImageList";
    value<<"";

    category<<"Administrator";
    part<<"PasswordEncode";
    value<<"218bd5788150aba9397432c6a4ec63f6";

    if(insertKioskAdminTable(category, part, value)){
        LOG<<"update errorKioskTable success";
    }
}

QString Db::getValueKioskAdmin(QString category, QString part) const
{
    QString value = "";
    QSqlQuery q(db);

    q.prepare("SELECT value from kiosk_admin where category = :category and part = :part limit 1");// get query
    q.bindValue(":category", category);// bind parameter
    q.bindValue(":part", part);// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("value").isNull()) {
            value = q.value("value").toString();
        }
      //  LOG << "complete!" << value;
    } else
        LOG << "not complete!" << q.lastError();
    return value;
}

void Db::UpdateValueKioskAdmin(QString category, QString part, QString value)
{
    QSqlQuery q(db);
    q.prepare("UPDATE kiosk_admin set value = :value where category = :category and part = :part");
    q.bindValue(":value", value);
    q.bindValue(":category", category);
    q.bindValue(":part", part);
    if(q.exec()){
        LOG<<"Update SignalCount Suscess";
    }
}

QList<QString> Db::GetListPartKioskAdmin(QString category)
{
    QList<QString> list;
    list.clear();
    QString s = "'" + category + "'";
    QSqlQuery q(db);
    q.prepare(QString("SELECT part FROM kiosk_admin WHERE category LIKE " + s));
    if(q.exec()){
        LOG;
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
           // LOG;
            bool Check = false;
            for(int y=0; y < list.size(); y++){
                if(q.value(0).toString() == list.at(y)){
                    Check = false;
                    break;
                }else{
                    Check = true;
                }
            }
            if(Check){
                list.append(q.value(0).toString());
            }
    }
    return list;
}

QList<QString> Db::GetListChargeTypeName(QString category)
{
    QList<QString> list;
    QString s = "'" + category + "'";
    QSqlQuery q(db);
    q.prepare("SELECT part FROM kiosk_admin WHERE category LIKE " + s);
    if(q.exec()){
        LOG;
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
           // LOG;
            bool Check = false;
            for(int y=0; y < list.size(); y++){
                if(q.value(0).toString() == list.at(y)){
                    Check = false;
                    break;
                }else{
                    Check = true;
                }
            }
            if(Check){
                list.append(q.value(0).toString());
            }
    }
    return list;
}

bool Db::CreatKioskAdmin(QString category, QString part, QString value)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare("INSERT INTO kiosk_admin ( category, part,value) VALUES (:category, :part,:value)");// get query
    q.bindValue(":category", category);
    q.bindValue(":part",part);// bind parameter
    q.bindValue(":value", value);// bind parameter

    if(q.exec()) {
        r = true;
        return r;
    }
    LOG << "complete!" << r << q.lastError();

    return r;
}

bool Db::insertKioskAdminTable(QVariantList category, QVariantList part, QVariantList value)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(INSERT_KIOSK_ADMIN_TABLE);// get query
    q.bindValue(":category", category);// bind parameter
    q.bindValue(":part", part);
    q.bindValue(":value", value);
    LOG;
    if (q.execBatch() )
    {
        r = true;
        LOG << "insert complete!";
    } else
        LOG << "query not complete!" << q.lastError();

    return r;
}

QList<QString> Db::GetListErrorCode()
{
    LOG;
    QList<QString> list;
    QSqlQuery q(db);
    q.prepare("SELECT error_code FROM kiosk_error WHERE id > 0 AND error_code NOT NULL");
    if(q.exec()){
        LOG;
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
          //  LOG;
            bool Check = false;
            for(int y=0; y < list.size(); y++){
                if(q.value(0).toString() == list.at(y)){
                    Check = false;
                    break;
                }else{
                    Check = true;
                }
            }
            if(Check){
                list.append(q.value(0).toString());
            }
    }
    return list;
}

QList<QString> Db::GetListErrorCodeSortedByCountMax(QString s)
{
    LOG;
    QList<QString> list;
    QSqlQuery q(db);
    q.prepare("SELECT error_code FROM kiosk_error WHERE id > 0 AND signal_count_max " + s + " 0");
    if(q.exec()){
        LOG;
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
          //  LOG;
            bool Check = false;
            for(int y=0; y < list.size(); y++){
                if(q.value(0).toString() == list.at(y)){
                    Check = false;
                    break;
                }else{
                    Check = true;
                }
            }
            if(Check){
                list.append(q.value(0).toString());
            }
    }
    return list;
}

void Db::UpdateSignalCount(QString a, int s)
{
    QSqlQuery q(db);
    q.prepare(UPDATE_SIGNAL_COUNT);
    q.bindValue(":signal_count", s);
    q.bindValue(":error_code", a);
    if(q.exec()){
        LOG<<"Update SignalCount Suscess";
    }
}

void Db::UpdateSignalCountMax(QString a, int s)
{
    QSqlQuery q(db);
    q.prepare(UPDATE_SIGNAL_COUNT_MAX);
    q.bindValue(":signal_count_max", s);
    q.bindValue(":error_code", a);
    if(q.exec()){
        LOG<<"Update SignalCountMax Suscess";
    }
}

void Db::UpdateResetSignalCounr()
{
    QSqlQuery q(db);
    q.prepare(UPDATE_RESET_SIGNAL_COUNT);
    if(q.exec()){
        LOG<<"Update ResetSignalCount Suscess";
    }
}

int Db::GetSignalCount(QString error_code)
{
    int SignalCount = 0;
    QString error = "'"+ error_code + "'";
    QSqlQuery q(db);
    q.prepare("select signal_count from kiosk_error where error_code LIKE " + error);
    if(!q.exec()){
        LOG<<"failed to run query";
        return SignalCount;
    }
    if(q.next()){
        if(q.value(0).isNull()){
            SignalCount = 0;
        }else{
            SignalCount = q.value(0).toInt();
        }
        //LOG<<SignalCount<<"yyyyy";
    }
    return SignalCount;
}

int Db::GetSignalCountMax(QString error_code)
{
    int SignalCount = 0;
    QString error = "'"+ error_code + "'";
    QSqlQuery q(db);
    q.prepare("select signal_count_max from kiosk_error where error_code LIKE " + error);
    if(!q.exec()){
        LOG<<"failed to run query";
        return SignalCount;
    }
    if(q.next()){
        if(q.value(0).isNull()){
            SignalCount = 0;
        }else{
            SignalCount = q.value(0).toInt();
        }
        //LOG<<SignalCount<<"yyyyy";
    }
    return SignalCount;
}

bool Db::CreateErrorKiosk(QString error_code, QString error_code_description, QString error_group, QString error_level, int signal_count, int signal_count_max)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(CREATE_ERROR_KIOSK);// get query  error_code, error_code_description, error_group, error_level, signal_count,signal_count_max
    q.bindValue(":error_code", error_code);
    q.bindValue(":error_code_description", error_code_description);// bind parameter
    q.bindValue(":error_group", error_group);// bind parameter
    q.bindValue(":error_level", error_level);// bind parameter
    q.bindValue(":signal_count", signal_count);// bind parameter
    q.bindValue(":signal_count_max", signal_count_max);// bind parameter
    if(q.exec()) {
        r = true;
        return r;
    }
    LOG << "complete!" << r << q.lastError();
    return r;
}

QList<QString> Db::GetErrorKioskListSortBy()
{
    QList<QString> list;
    list.clear();
    QSqlQuery q(db);
    q.prepare("select * from kiosk_error where error_code NOT NULL order by signal_count_max desc, signal_count desc");
    if(q.exec()){

    }else{
        return list;
    }
    while (q.next()){
        LOG;
        const QSqlRecord record = q.record();
        list.append(record.value(1).toString());
        list.append(record.value(5).toString());
        list.append(record.value(6).toString());
    }
    return list;
}

void Db::CleanErrorNull(QString error_code)
{
    QString error = "'"+ error_code + "'";
    QSqlQuery q(db);
    q.prepare("DELETE FROM kiosk_error where error_code LIKE NULL");
    if(q.exec()){
        LOG;
    }

}

void Db::DeleteErrorKiosk()
{
    QSqlQuery q(db);
    q.prepare(DELETE_ERROR_KIOSK);
    if(q.exec()){
        LOG<<"delete errorKiosk suscess";
    }
}

bool Db::CheckDb()
{
    return true;
}

bool Db::CreateTransaction(Transaction *transaction)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(CREATE_TRANSACTION);// get query
    q.bindValue(":slot_id", transaction->SlotId);
    q.bindValue(":good_id", transaction->GoodId);// bind parameter
    q.bindValue(":good_name", transaction->GoodName);// bind parameter
    q.bindValue(":good_price", transaction->GoodPrice);// bind parameter
    q.bindValue(":quantity", transaction->Quantity);// bind parameter
    q.bindValue(":transaction_type", transaction->TransactionType);// bind parameter
    q.bindValue(":input_amount", transaction->AvailableAmount);// bind parameter
    q.bindValue(":order_info", QJsonDocument(QJsonObject::fromVariantMap(transaction->toMap())).toJson());// bind parameter
    q.bindValue(":transaction_status", transaction->TransactionStatus);// bind parameter
    q.bindValue(":sync_status", 0);

    if(q.exec()) {

        transaction->TransactionId = q.lastInsertId().toString();
        r = true;
        return r;
    }
    LOG << "complete!" << r << q.lastError();

    return r;
}

bool Db::UpdateTransaction(Transaction *transaction)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(UPDATE_TRANSACTION);// get query
    q.bindValue(":transaction_id", transaction->TransactionId);// bind parameter
    q.bindValue(":slot_id", transaction->SlotId);
    q.bindValue(":good_id", transaction->GoodId);// bind parameter
    q.bindValue(":good_name", transaction->GoodName);// bind parameter
    q.bindValue(":good_price", transaction->GoodPrice);// bind parameter
    q.bindValue(":quantity", transaction->Quantity);// bind parameter
    q.bindValue(":transaction_type", transaction->TransactionType);// bind parameter
    q.bindValue(":input_amount", transaction->AvailableAmount);// bind parameter
    q.bindValue(":order_info", QJsonDocument(QJsonObject::fromVariantMap(transaction->toMap())).toJson());// bind parameter
    q.bindValue(":transaction_status", transaction->TransactionStatus);// bind parameter
    q.bindValue(":sync_status", transaction->TransactionSync);
    r = q.exec();
    LOG << "complete!" << r << q.lastError() << q.executedQuery();

    return r;
}

bool Db::CreateSaleSession(SaleSession *sale)
{
    bool r=false;
    LOG;
    QSqlQuery q(db);
    q.prepare(CREATE_SALE_SESSION);// get query
    q.bindValue(":start_time", sale->StartTime.toString("yyyy-MM-dd hh:mm:ss"));// bind parameter
    q.bindValue(":end_time", sale->EndTime.toString("yyyy-MM-dd hh:mm:ss"));// bind parameter
    q.bindValue(":total_amount", sale->TotalAmount);// bind parameter
    q.bindValue(":staff_code", sale->StaffCode);
    q.bindValue(":period", sale->PrePeriod);
    q.bindValue(":period_total_amount", sale->PeriodTotalAmount);
    q.bindValue(":share_total_amount", sale->TotalAmountShare);
    q.bindValue(":share_period_total_amount", sale->PeriodTotalAmountShare);
    q.bindValue(":type", sale->Type);
    LOG;
    if(q.exec()) {
        sale->SessionId = q.lastInsertId().toString();
        r = true;
        LOG << "complete!";
        return r;
    }
    LOG << "complete!" << r << q.lastError();

    return r;
}

bool Db::GetCurrentSaleSession(SaleSession *sale)
{
    bool r=false;
    QSqlQuery q(db);
    r = q.exec(QString(READ_ACTIVE_SALE_SESSION));

    if (r && q.first() )
    {

        if (!q.value("session_id").isNull()) {
            sale->SessionId = QString::number(q.value("session_id").toFloat());
        }

        if (!q.value("start_time").isNull() && q.value("start_time").isValid())
            sale->StartTime = q.value("start_time").toDateTime();

        if (!q.value("total_amount").isNull() )
            sale->TotalAmount = q.value("total_amount").toDouble(&r);
        if (!q.value("total_bill").isNull() )
            sale->TotalBill = q.value("total_bill").toDouble(&r);

        if (!q.value("staff_code").isNull() )
            sale->StaffCode = q.value("staff_code").toString();

        if (!q.value("period").isNull() )
            sale->PrePeriod = q.value("period").toString();
        else
            sale->PrePeriod = QDate::currentDate().toString("yyyyMM");
        if (!q.value("period_total_amount").isNull() )
            sale->PeriodTotalAmount = q.value("period_total_amount").toDouble();
        else
            sale->PeriodTotalAmount = 0;
        if (!q.value("share_total_amount").isNull() ){
            if(q.value("share_total_amount").toDouble() == 0){
                sale->TotalAmountShare = sale->TotalAmount;
            }else
                sale->TotalAmountShare = q.value("share_total_amount").toDouble();
        }
        else
            sale->TotalAmountShare = sale->TotalAmount;

        if (!q.value("type").isNull() ){
            if(q.value("type").toString() == ""){
                sale->Type = "day";
            }else
                sale->Type = q.value("type").toString();
        }
        else
            sale->Type = "day";
        if (!q.value("share_period_total_amount").isNull() ){
            if(q.value("share_period_total_amount").toDouble() == 0){
                sale->PeriodTotalAmountShare = sale->PeriodTotalAmount;
            }else{
                sale->PeriodTotalAmountShare = q.value("share_period_total_amount").toDouble();
            }
        }
        else
            sale->PeriodTotalAmountShare = sale->PeriodTotalAmount;

        return r;
    }
    LOG << "not complete!" << r << q.lastError();
    return false;
}

bool Db::UpdateSaleSession(SaleSession *sale)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(UPDATE_SALE_SESSION);// get query
    q.bindValue(":start_time",sale->StartTime.toString("yyyy-MM-dd hh:mm:ss"));// bind parameter
    q.bindValue(":end_time", sale->EndTime.toString("yyyy-MM-dd hh:mm:ss"));//QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));// bind parameter
    q.bindValue(":total_amount", sale->TotalAmount);// bind parameter
    q.bindValue(":total_bill", sale->TotalBill);// bind parameter
    q.bindValue(":staff_code", sale->StaffCode);// bind parameter
    q.bindValue(":session_id", sale->SessionId);// bind parameter
    q.bindValue(":period", sale->PrePeriod);
    q.bindValue(":period_total_amount", sale->PeriodTotalAmount);

    q.bindValue(":share_total_amount", sale->TotalAmountShare);
    q.bindValue(":type", sale->Type);
    q.bindValue(":share_period_total_amount", sale->PeriodTotalAmountShare);

    r = q.exec();
    LOG << "complete!" << r << q.lastError() << q.executedQuery();
    return r;
}

bool Db::CreateBillAmount(BillInputAmount *billvalidator)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(CREATE_BILL_AMOUNT);// get query
    q.bindValue(":start_time", billvalidator->StartTime.toString("yyyy-MM-dd hh:mm:ss"));// bind parameter
    q.bindValue(":sale_session_id", billvalidator->sale_session_id);
    q.bindValue(":bill_amount", billvalidator->BillAmount);// bind parameter
    if(q.exec()) {
        billvalidator->Id = q.lastInsertId().toString();
        r = true;
        LOG << "complete!";
        return r;
    }
    LOG << "complete!" << r << q.lastError();

    return r;
}

bool Db::UpdateBillAmount(BillInputAmount* billvalidator)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(UPDATE_BILL_AMOUNT);// get query
    q.bindValue(":start_time", billvalidator->StartTime.toString("yyyy-MM-dd hh:mm:ss"));// bind parameter
    q.bindValue(":session_id", billvalidator->Id);
    q.bindValue(":bill_amount", billvalidator->BillAmount);// bind parameter
    r = q.exec();
    return r;
}


bool Db::CreateBillStatus(BillInputAmount *billvalidator)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(CREATE_BILL_STATUS);// get query
    q.bindValue(":start_time", billvalidator->StartTime.toString("yyyy-MM-dd hh:mm:ss"));// bind parameter
    q.bindValue(":sale_session_id", billvalidator->sale_session_id);
    q.bindValue(":bill_response", billvalidator->BillResponse);// bind parameter
    q.bindValue(":bill_status", billvalidator->BillStatus);
    if(q.exec()) {
        billvalidator->Id = q.lastInsertId().toString();
        r = true;
        return r;
    }
    LOG << "complete!" << r << q.lastError();

    return r;
}

bool Db::CreateBillDescriptionStatus(QString response, QString description)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(CREATE_DESCRIPTION_STATUS);// get query
    q.bindValue(":bill_response", response);// bind parameter
    q.bindValue(":status_description", description);
    if(q.exec()){
        r = true;
        return r;
    }
    return r;

}

QString Db::GetBillAmount(QString SessionId)
{
    QString s = "'" + SessionId + "'";
    QSqlQuery q(db);
    q.prepare("SELECT * FROM kiosk_bill_amount WHERE sale_session_id LIKE " +  s);
    if(q.exec()){
    }
    QJsonDocument  json;
    QJsonArray     recordsArray;
    while(q.next())
      {
         QJsonObject recordObject;
            for(int x=0; x < q.record().count(); x++)
            {
            recordObject.insert( q.record().fieldName(x),QJsonValue::fromVariant(q.value(x)) );
            }
         recordsArray.push_back(recordObject);
      }
      json.setArray(recordsArray);
      return json.toJson();
}
QString Db::GetDescriptionStatus(QString BillResponse)
{
    QString Description = "";
    QString s = "'" + BillResponse + "'";
    QSqlQuery q(db);
    q.prepare("SELECT status_description FROM kiosk_Bill_StatusDescription WHERE bill_response LIKE " + s );
    if(q.exec()){
    //    LOG;
    }
    if(q.next()){
    Description = q.value(0).toString();
    }

    return Description;
}

QString Db::GetBillStatus(QString SessionId)
{
    QString s = "'" + SessionId + "'";
    QSqlQuery q(db);
    q.prepare("SELECT * FROM kiosk_bill_status WHERE sale_session_id LIKE " +  s);
    if(q.exec()){
    }
    QJsonDocument  json;
    QJsonArray     recordsArray;
    while(q.next())
      {
         QJsonObject recordObject;
            for(int x=0; x < q.record().count(); x++)
            {
            recordObject.insert( q.record().fieldName(x),QJsonValue::fromVariant(q.value(x)) );
            }
         recordsArray.push_back(recordObject);
      }
      json.setArray(recordsArray);
      return json.toJson();
}

QString Db::GetErrorSale(QString SessionId)
{
    QString SessionID= "";
    QString s = "'" + SessionId + "'";
    QSqlQuery q(db);
    q.prepare("SELECT * FROM kiosk_sale_session WHERE session_id LIKE " +  s);
    if(!q.exec()){
        LOG<<"failed to run query";
    }
    QJsonDocument  json;
    if(q.next())
      {
        QJsonObject recordObject;
        for(int x=0; x < q.record().count(); x++)
        {
        recordObject.insert( q.record().fieldName(x),QJsonValue::fromVariant(q.value(x)) );
        }
        SessionID = QJsonDocument(recordObject).toJson();
      }

    return SessionID;
}

QString Db::GetSessionIdMax()
{
    QString SessionID= "";
    QSqlQuery q(db);
    q.prepare("select session_id from kiosk_sale_session ORDER BY session_id DESC LIMIT 1");
    if(!q.exec()){
        LOG<<"failed to run query";
    }
    if(q.next()){
    SessionID = q.value(0).toString();
    LOG<<SessionID<<"yyyyyyyyyyyyyyyyyy";
    }
    return SessionID;
}

QString Db::GetReTransaction(QString TransactionId)
{
    QString Transaction= "";
    QString s = "'" + TransactionId + "'";
    QSqlQuery q(db);
    q.prepare("SELECT order_info FROM kiosk_transaction WHERE id LIKE " +  s);
    if(!q.exec()){
        LOG<<"failed to run query";
    }
    if(q.next()){
        Transaction = q.value(0).toString();
        LOG<<Transaction<<"yyyyyyyyyyyyyyyyyy";
    }
    return Transaction;
}

int Db::GetIdReTransactionMax()
{
    int id = 0;
    QSqlQuery q(db);
    q.prepare("select id from kiosk_transaction ORDER BY id DESC LIMIT 1");
    if(!q.exec()){
        LOG<<"failed to run query";
    }
    if(q.next()){
        id = q.value(0).toInt();
        LOG<<id<<"yyyyyyyyyyyyyyyyyy";
    }
    return id;
}



bool Db::CreatBillAvailable(BillInputAmount *billvalidator)
{
    {
        bool r=false;
        QSqlQuery q(db);
        q.prepare(CREATE_BILL_AVAILABLE);// get query
        q.bindValue(":start_time", billvalidator->BillTime.toString("yyyy-MM-dd hh:mm:ss"));// bind parameter
        q.bindValue(":sale_session_id", billvalidator->sale_session_id);
        q.bindValue(":bill_available", billvalidator->BillAvailable);// bind parameter
        if(q.exec()) {
            billvalidator->BillId = q.lastInsertId().toString();
            r = true;
            LOG << "complete!";
            return r;
        }
        LOG << "complete!" << r << q.lastError();

        return r;
    }
}

bool Db::UpdateBillAvailable(BillInputAmount *billvalidator)
{

    bool r=false;
    QSqlQuery q(db);
    q.prepare(UPDATE_BILL_AVAILABLE);// get query
    q.bindValue(":id", billvalidator -> BillId);
    q.bindValue(":start_time", billvalidator->BillTime.toString("yyyy-MM-dd hh:mm:ss"));// bind parameter
    q.bindValue(":sale_session_id", billvalidator->sale_session_id);
    q.bindValue(":bill_available", billvalidator->BillAvailable);// bind parameter
    r = q.exec();

    return r;

}

int Db::GetBillAvailable()
{

    int GetBillAvailable = 0;
    QSqlQuery query(db);
    query.prepare("select * from kiosk_bill_available ORDER BY id DESC LIMIT 1");
    if (!query.exec()){
        LOG<<("failed to run query");
        return 0;
    }
    if(query.next()){
        const QSqlRecord record = query.record();
        GetBillAvailable = record.value(2).toInt();
    }
    return GetBillAvailable;
}

quint8 Db::GetGoodQuatity(QString goodId)
{
    quint8 quatity = 0;
    QSqlQuery q(db);
    q.prepare("select good_quatity from kiosk_menu_good_general where good_id = :good_id");
    q.bindValue(":good_id", goodId);
    if(!q.exec()){
        LOG<<"failed to run query";
        return quatity;
    }
    if(q.next()){
        quatity = q.value(0).toInt();
        LOG<<quatity<<"yyyyyyyyyyyyyyyyyy";
    }
    return quatity;
}

bool Db::UpdateGoodQuatity(QString goodId, quint8 quatity)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare("UPDATE kiosk_menu_good_general set good_quatity = :good_quatity where good_id = :good_id");// get query
    q.bindValue(":good_id", goodId);
    q.bindValue(":good_quatity", quatity);// bind parameter

    r = q.exec();
    if(r)
        LOG<<"cập nhật số lượng thành công, số lượng: "<< quatity;
    return r;
}


bool Db::insertInventoryBatch(QVariantList name_service, QVariantList tray_id, QVariantList slot_id, QVariantList good_id, QVariantList good_name, QVariantList good_price, QVariantList good_count, QVariantList max_count)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(INSERT_INVENTORY);// get query
    q.bindValue(":name_service", name_service);// bind parameter
    q.bindValue(":tray_id", tray_id);
    q.bindValue(":slot_id", slot_id);
    q.bindValue(":good_id", good_id);// bind parameter
    q.bindValue(":good_name", good_name);// bind parameter
    q.bindValue(":good_price", good_price);// bind parameter
    q.bindValue(":good_count", good_count);// bind parameter
    q.bindValue(":max_count", max_count);// bind parameter
    LOG;
    if (q.execBatch() )
    {
        r = true;
        LOG << "insert complete!";
    } else
        LOG << "query not complete!" << q.lastError();

    return r;
}

bool Db::insertMenuGoodTable(QVariantList Industry, QVariantList goodType, QVariantList serviceType, QVariantList good_id, QVariantList good_name, QVariantList good_price, QVariantList permission,QVariantList chargetype_quatity,QVariantList list_charge_type, QVariantList share_sale_permission )
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(INSERT_MENUGOOD_TABLE);// get query
    q.bindValue(":Industry", Industry);// bind parameter
    q.bindValue(":goodType", goodType);
    q.bindValue(":serviceType", serviceType);
    q.bindValue(":good_id", good_id);// bind parameter
    q.bindValue(":good_name", good_name);// bind parameter
    q.bindValue(":good_price", good_price);// bind parameter
    q.bindValue(":permission", permission);
    q.bindValue(":charge_type_quatity", chargetype_quatity);
    q.bindValue(":list_charge_type", list_charge_type);
    q.bindValue(":share_sale_permission", share_sale_permission);// bind parameter
    LOG;
    if (q.execBatch() )
    {
        r = true;
        LOG << "insert menugoodtable complete!";
    } else
        LOG << "query menugoodtable not complete!" << q.lastError();

    return r;
}

bool Db::insertMenuGoodGeneralTable(QVariantList Industry, QVariantList supplier, QVariantList good_name, QVariantList good_id, QVariantList good_price,QVariantList good_quatity, QVariantList image_url, QVariantList charge_type_quatity, QVariantList list_charge_type, QVariantList priority, QVariantList status)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(INSERT_MENUGOOD_GENERAL_TABLE);// get query
    q.bindValue(":Industry", Industry);// bind parameter
    q.bindValue(":supplier", supplier);
    q.bindValue(":good_name", good_name);
    q.bindValue(":good_id", good_id);// bind parameter
    q.bindValue(":good_price", good_price);// bind parameter
    q.bindValue(":good_quatity", good_quatity);// bind parameter
    q.bindValue(":image_url", image_url);// bind parameter
    q.bindValue(":charge_type_quatity", charge_type_quatity);
    q.bindValue(":list_charge_type", list_charge_type);
    q.bindValue(":priority", priority);
    q.bindValue(":status", status);// bind parameter
    LOG;
    if (q.execBatch() )
    {
        r = true;
        LOG << "insert complete!";
    } else
        LOG << "query not complete!" << q.lastError();

    return r;
}

bool Db::insertErrorKioskTable(QVariantList error_code, QVariantList error_code_description, QVariantList error_group, QVariantList error_level, QVariantList signal_count, QVariantList signal_count_max)
{
    bool r=false;
    QSqlQuery q(db);
    q.prepare(INSERT_ERROR_KIOSK_TABLE);// get query
    q.bindValue(":error_code", error_code);// bind parameter
    q.bindValue(":error_code_description", error_code_description);
    q.bindValue(":error_group", error_group);
    q.bindValue(":error_level", error_level);// bind parameter
    q.bindValue(":signal_count", signal_count);// bind parameter
    q.bindValue(":signal_count_max", signal_count_max);// bind parameter
    LOG;
    if (q.execBatch() )
    {
        r = true;
        LOG << "insert complete!";
    } else
        LOG << "query not complete!" << q.lastError();

    return r;
}
bool Db::cleanInventory()
{
    bool r=false;
    QSqlQuery q(db);
    LOG;
    q.prepare(DELETE_INVENTORY);
    r = q.exec();
    if ( r )
    {
        LOG << "complete!" << r;
    } else
        LOG << "not complete!" << r << q.lastError();
    return r;
}

bool Db::cleanMenuGoodTable()
{
    bool r=false;
    QSqlQuery q(db);
    LOG;
    q.prepare(DELETE_MENUGOOD_TABLE);
    r = q.exec();
    if ( r )
    {
        LOG << "complete!" << r;
    } else
        LOG << "not complete!" << r << q.lastError();
    return r;
}

bool Db::cleanMenuGoodGeneralTable()
{
    bool r=false;
    QSqlQuery q(db);
    LOG;
    q.prepare(DELETE_MENUGOOD_GENERAL_TABLE);
    r = q.exec();
    if ( r )
    {
        LOG << "complete!" << r;
    } else
        LOG << "not complete!" << r << q.lastError();
    return r;
}

QList<int> Db::GetListGoodinInventoryTable(QString nameservice)
{
    QList<int> list;
    QString s = "'" + nameservice + "'";
    QSqlQuery q(db);
    q.prepare("SELECT good_price FROM kiosk_inventory WHERE name_service LIKE " +  s);
    if(q.exec()){
    }
    while(q.next())
      {
        for(int x=0; x < q.record().count(); x++)
        {
            list.append(q.value(x).toInt());
        }

      }
    return list;
}

QList<QString> Db::GetListGoodMenu()
{
    QList<QString> list;
    QSqlQuery q(db);
    q.prepare("SELECT Industry FROM kiosk_menu_good WHERE permission LIKE 'show'");
    if(q.exec()){
       // LOG;
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
            //LOG;
            bool Check = false;
            for(int y=0; y < list.size(); y++){
                if(q.value(0).toString() == list.at(y)){
                    Check = false;
                    break;
                }else{
                    Check = true;
                }
            }
            if(Check){
                list.append(q.value(0).toString());
            }
    }
    return list;
}

QList<QString> Db::GetListGoodMenuGeneral()
{
    QList<QString> list;
    QSqlQuery q(db);
    q.prepare("SELECT Industry FROM kiosk_menu_good_general WHERE status LIKE 'sale' and good_quatity > 0");
    if(q.exec()){
       // LOG;
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
            //LOG;
            bool Check = false;
            for(int y=0; y < list.size(); y++){
                if(q.value(0).toString() == list.at(y)){
                    Check = false;
                    break;
                }else{
                    Check = true;
                }
            }
            if(Check){
                list.append(q.value(0).toString());
            }
    }
    return list;
}

QList<int> Db::GetListPriority()
{
    QList<int> list;
    QSqlQuery q(db);
    q.prepare("SELECT priority FROM kiosk_menu_good_general WHERE status LIKE 'sale'");
    if(q.exec()){
       // LOG;
    }
    if(q.next()){
        list.append(q.value(0).toInt());
    }
    while(q.next()){
            //LOG;
            bool Check = false;
            for(int y=0; y < list.size(); y++){
                if(q.value(0).toInt() == list.at(y)){
                    Check = false;
                    break;
                }else{
                    Check = true;
                }
            }
            if(Check){
                list.append(q.value(0).toInt());
            }
    }
    return list;
}

QList<QString> Db::GetListGoodIdPriority(int priority)
{
    QList<QString> list;
    QString s = "'" + QString::number(priority) + "' ";
    QSqlQuery q(db);
    q.prepare("SELECT good_id FROM kiosk_menu_good_general WHERE priority LIKE " + s + "and status LIKE 'sale' AND good_quatity > 0");
    //q.prepare("SELECT good_id FROM kiosk_menu_good_general WHERE status LIKE 'sale' and priority LIKE " + s );
    if(q.exec()){
       // LOG;
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
            //LOG;
            bool Check = false;
            for(int y=0; y < list.size(); y++){
                if(q.value(0).toString() == list.at(y)){
                    Check = false;
                    break;
                }else{
                    Check = true;
                }
            }
            if(Check){
                list.append(q.value(0).toString());
            }
    }
    return list;
}

QList<QString> Db::GetListGoodId()
{
    LOG;
    QList<QString> list;
    QSqlQuery q(db);
    q.prepare("SELECT good_id FROM kiosk_menu_good_general WHERE status LIKE 'sale'");
    if(q.exec()){
        LOG;
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
        //LOG;
        bool Check = false;
        for(int y=0; y < list.size(); y++){
            if(q.value(0).toString() == list.at(y)){
                Check = false;
                break;
            }else{
                Check = true;
            }
        }
        if(Check){
            list.append(q.value(0).toString());
        }
    }
    return list;
}

QList<QString> Db::GetListGoodType(QString GoodType)
{
    QList<QString> list;
    QString s = "'" + GoodType + "'";
    QSqlQuery q(db);
    q.prepare("SELECT goodType FROM kiosk_menu_good WHERE Industry LIKE " +  s +" AND permission LIKE 'show'");
    if(q.exec()){
        //LOG;
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
        bool Check = false;
        for(int y=0; y < list.size(); y++){
            if(q.value(0).toString() == list.at(y)){
                Check = false;
                break;
            }else{
                Check = true;
            }
        }
        if(Check){
            list.append(q.value(0).toString());
        }
    }
    return list;
}

QList<QString> Db::GetListGoodIdMenuGoodGeneral(QString Industry)
{
    QList<QString> list;
    QString s = "'" + Industry + "'";
    QSqlQuery q(db);
    q.prepare("SELECT good_id FROM kiosk_menu_good_general WHERE Industry LIKE " +  s +" AND status LIKE 'sale' AND good_quatity > 0");
    if(q.exec()){
    }
    if(q.next()){
        list.append(q.value(0).toString());
    }
    while(q.next()){
            bool Check = false;
            for(int y=0; y < list.size(); y++){
                if(q.value(0).toString() == list.at(y)){
                    Check = false;
                    break;
                }else{
                    Check = true;
                }
            }
            if(Check){
                list.append(q.value(0).toString());
            }
    }
    return list;
}

QList<int> Db::GetListGoodPrice(QString Industry, QString GoodType)
{
    QList<int> list;
    QSqlQuery q(db);
    q.prepare(SELECT_GOODPRICE_MENU_TABLE);
    q.bindValue(":Industry", Industry);// bind parameter
    q.bindValue(":goodType", GoodType);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if(q.exec()){
    }
    while(q.next())
      {
        list.append(q.value(0).toInt());
      }
    return list;
}

QString Db::getImageUrlMenuGoodGeneral(QString GoodId) const
{
    QString id = "";
    QSqlQuery q(db);

    q.prepare("SELECT image_url from kiosk_menu_good_general where good_id = :good_id limit 1");// get query
    q.bindValue(":good_id", GoodId);// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("image_url").isNull()) {
            id = q.value("image_url").toString();
        }
        LOG << "complete!" << id;
    } else
        LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getGoodIdForSlot(QString nameservice, int price) const
{
    QString id;
    QSqlQuery q(db);

    q.prepare(SELECT_INVENTORY_GOOD_ID);// get query
    q.bindValue(":name_service", nameservice);// bind parameter
    q.bindValue(":good_price", price);// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("good_id").isNull()) {
            id = q.value("good_id").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getGoodNameForSlot(QString goodId) const
{
    QString id;
    QSqlQuery q(db);

    q.prepare(SELECT_INVENTORY_GOOD_NAME);// get query
    q.bindValue(":name_service", goodId);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("good_name").isNull()) {
            id = q.value("good_name").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getGoodIdInMenuTable(QString goodType, int price) const
{
    QString id;
    QSqlQuery q(db);

    q.prepare(SELECT_GOODID_MENU_TABLE);// get query
    q.bindValue(":goodType", goodType);// bind parameter
    q.bindValue(":good_price", price);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("good_id").isNull()) {
            id = q.value("good_id").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getGoodId1InMenuTable(QString a , QString b) const
{
    QString id;
    QSqlQuery q(db);

    q.prepare(SELECT_GOODID1_MENU_TABLE);// get query
    q.bindValue(":Industry", a);// bind parameter
    q.bindValue(":goodType", b);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("good_id").isNull()) {
            id = q.value("good_id").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getGoodNameInMenuTable(QString goodId) const
{
    QString id;
    QSqlQuery q(db);

    q.prepare(SELECT_GOODNAME_MENU_TABLE);// get query
    q.bindValue(":good_id", goodId);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("good_name").isNull()) {
            id = q.value("good_name").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getGoodNameInMenuGeneralTable(QString goodId) const
{
    QString id;
    QSqlQuery q(db);

    q.prepare("SELECT good_name from kiosk_menu_good_general where good_id = :good_id and status = :status limit 1");// get query
    q.bindValue(":good_id", goodId);// bind parameter
    q.bindValue(":status", "sale");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("good_name").isNull()) {
            id = q.value("good_name").toString();
        }
      //  LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getGoodPriceInMenuGeneralTable(QString goodId) const
{
    QString id;
    QSqlQuery q(db);

    q.prepare("SELECT good_price from kiosk_menu_good_general where good_id = :good_id and status = :status limit 1");// get query
    q.bindValue(":good_id", goodId);// bind parameter
    q.bindValue(":status", "sale");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("good_price").isNull()) {
            id = q.value("good_price").toString();
        }
       // LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getShareSalePermissionInMenuTable(QString goodId) const
{
    QString id = "true";
    QSqlQuery q(db);

    q.prepare(SELECT_SHARE_SALE_PERMISSION_MENU_TABLE);// get query
    q.bindValue(":good_id", goodId);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("share_sale_permission").isNull()) {
            id = q.value("share_sale_permission").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getServiceType1InMenuTable(QString a, QString b) const
{
    QString id;
    QSqlQuery q(db);

    q.prepare(SELECT_NAMESERVICE1_MENU_TABLE);// get query
    q.bindValue(":Industry", a);// bind parameter
    q.bindValue(":goodType", b);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("serviceType").isNull()) {
            id = q.value("serviceType").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

int Db::getGoodPriceInMenuTable(QString a)
{
    int id = 0;
    QSqlQuery q(db);

    q.prepare(SELECT_GOODPRICE1_MENU_TABLE);// get query
    q.bindValue(":good_id", a);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("good_price").isNull()) {
            id = q.value("good_price").toInt();
        }
        LOG << "complete!" << id;
    } else
        LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getListChargeTypeInMenuTable(QString goodId) const
{
    QString id = "";
    QSqlQuery q(db);

    q.prepare(SELECT_LISTCHARGETYPE_MENU_TABLE);// get query
    q.bindValue(":good_id", goodId);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("list_charge_type").isNull()) {
            id = q.value("list_charge_type").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getListChargeTypeInMenuGeneralTable(QString goodId) const
{
    QString id = "";
    QSqlQuery q(db);

    q.prepare(SELECT_LISTCHARGETYPE_MENU_GENERAL_TABLE);// get query
    q.bindValue(":good_id", goodId);// bind parameter
    q.bindValue(":status", "sale");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("list_charge_type").isNull()) {
            id = q.value("list_charge_type").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

quint8 Db::getChargeTypeQuatity(QString Goodid) const
{
    quint8 id = 0;
    QSqlQuery q(db);

    q.prepare("SELECT charge_type_quatity from kiosk_menu_good where good_id = :good_id and permission = :permission limit 1");// get query
    q.bindValue(":good_id", Goodid);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("charge_type_quatity").isNull()) {
            id = q.value("charge_type_quatity").toInt();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

quint8 Db::getChargeTypeQuatityMenuGoodGeneral(QString Goodid) const
{
    quint8 id = 0;
    QSqlQuery q(db);

    q.prepare("SELECT charge_type_quatity from kiosk_menu_good_general where good_id = :good_id and status = :status limit 1");// get query
    q.bindValue(":good_id", Goodid);// bind parameter
    q.bindValue(":status", "sale");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("charge_type_quatity").isNull()) {
            id = q.value("charge_type_quatity").toInt();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getShareSalePermissionInMenuGeneralTable(QString goodId) const
{
    QString id = "true";
    QSqlQuery q(db);

    q.prepare(SELECT_SHARE_SALE_PERMISSION_MENU_GENERAL_TABLE);// get query
    q.bindValue(":good_id", goodId);// bind parameter
    q.bindValue(":status", "sale");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("share_sale_permission").isNull()) {
            id = q.value("share_sale_permission").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getServiceTypeInMenuTable(QString goodType, int price) const
{
    QString id;
    QSqlQuery q(db);

    q.prepare(SELECT_NAMESERVICE_MENU_TABLE);// get query
    q.bindValue(":goodType", goodType);// bind parameter
    q.bindValue(":good_price", price);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if (q.exec() && q.first() )
    {
        if (!q.value("serviceType").isNull()) {
            id = q.value("serviceType").toString();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

int Db::getTrayForSlot(QString goodId) const
{
    int id = 0;
    QSqlQuery q(db);
    QString s = "'" + goodId + "'";
    q.prepare("SELECT tray_id from kiosk_inventory WHERE good_id LIKE " +  s +"AND good_count > '0'");// get query
    if (q.exec() && q.first() )
    {
        if (!q.value("tray_id").isNull()) {
            id = q.value("tray_id").toInt();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

int Db::getSlotForSlot(QString goodId) const
{
    int id = 0;
    QSqlQuery q(db);
    QString s = "'" + goodId + "'";
    q.prepare("SELECT slot_id from kiosk_inventory WHERE good_id LIKE " +  s +"AND good_count > '0'");// get query
    if (q.exec() && q.first() )
    {
        if (!q.value("slot_id").isNull()) {
            id = q.value("slot_id").toInt();
        }
        LOG << "complete!" << id;
    } else
    LOG << "not complete!" << q.lastError();
    return id;
}

QString Db::getGoodIdCouponInMenuTable(QString a, QString b) const
{
        QString id;
        QSqlQuery q(db);

        q.prepare(SELECT_GOODID_COUPON_MENU_TABLE);// get query
        q.bindValue(":serviceType", a);// bind parameter
        q.bindValue(":goodType", b);// bind parameter
        q.bindValue(":permission", "show");// bind parameter
        if (q.exec() && q.first() )
        {
            if (!q.value("good_id").isNull()) {
                id = q.value("good_id").toString();
            }
            LOG << "complete!" << id;
        } else
        LOG << "not complete!" << q.lastError();
        return id;

}

QList<QString> Db::GetListTypeCoupon(QString Industry, QString GoodType)
{

    QList<QString> list;
    QSqlQuery q(db);
    q.prepare(SELECT_TYPECOUPON_MENU_TABLE);
    q.bindValue(":Industry", Industry);// bind parameter
    q.bindValue(":goodType", GoodType);// bind parameter
    q.bindValue(":permission", "show");// bind parameter
    if(q.exec()){
    }
    while(q.next())
      {
        list.append(q.value(0).toString());
      }
    return list;
}

bool Db::DeleteTransaction(Transaction *transaction)
{
    bool r=false;
   // LOG << QString(*transaction);
    QSqlQuery q(db);
    q.prepare("DELETE FROM kiosk_transaction WHERE id = '" + transaction->TransactionId + "'");// get query
    r = q.exec();

    return r;
}
//V1.2 Kết thúc
QString Db::escapedCSV(QString unexc)
{
    if (!unexc.contains(QLatin1Char(',')))
        return unexc.toLocal8Bit();
    return '\"' + unexc.replace(QLatin1Char('\"'), QStringLiteral("\"\"")) + '\"';
}

bool Db::queryToCsv(QString path, QString date, QString time)
{
    bool r=false;
    QString dateExport = "'" + date + "'";
    QString timeExport = "'" + time + "'";
    QSqlQuery query(db);
    query.prepare(" select * from kiosk_transaction  where transaction_time between" + dateExport + " and " + timeExport );
    if(query.exec()){
        r = true;
    }else{
        r = false;

        return r;
    }

    QFile csvFile (path);

    if (!csvFile.open(QFile::WriteOnly | QFile::Text | QFile::ReadOnly)){
        LOG<<("failed to open csv file");
        r = false;
        return r;

    }
    QTextStream outStream(&csvFile);
    outStream.setCodec("UTF-8");
    outStream <<"id" <<','<<"transaction_time"<<','<<"slot_id"<<','<<"good_id"<<','<<"good_name"<<','<<"good_price"<<','<<"quantity"<<','<<"transaction_type"<<','<<"input_amount"<<','<<"order_info"<<','<<"transaction_status"<<','<<"sync_status";

    outStream << '\n';
    while (query.next()){

        const QSqlRecord record = query.record();
        for (int i=0, recCount = record.count() ; i<recCount ; ++i){
            if (i>0)
                outStream << ',';

            outStream << escapedCSV(record.value(i).toString());
        }
        outStream << '\n';

    }
    csvFile.close();
    return r;
}
QList<QString> Db::getReTransaction(QString startTime, QString endTime)
{
    QList<QString> list;
    QString start_time = "'" + startTime + "'";
    QString end_time = "'" + endTime + "'";
    QSqlQuery q(db);
    q.prepare(" select order_info from kiosk_transaction  where transaction_time between" + start_time + " and " + end_time );
    if(q.exec()){
    }
    while(q.next())
      {
        for(int x=0; x < q.record().count(); x++)
        {
            list.append(q.value(x).toString());
        }

      }
    return list;

}

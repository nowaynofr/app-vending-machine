#include "machine.h"
#include "Transaction/log.h"
#include "Transaction/param.h"
#include "Transaction/transaction.h"


Machine::Machine(QObject *parent) : QObject(parent), config(CONFIG_PATH),m_db()
{
    m_last_input = m_current_input = "";

    StartTimeSale = EndTimeSale = StaffCodeSale = "";
    TotalAmountSale = TotalBillSale = 0;

    SlotTest = 0;
    CheckSlotTest = Check_GetQRCode = Check_GetPriceServer = false;
    m_state = m_last_state = MACHINE_STATE::INIT;
    AdminType = ADMINFUNTIONLIST::INIT_ADMIN;

    UpdateAdminFile();
    config.load();

    if(m_db.getValueKioskAdmin("AndroidDevice","IsReturnGoodByKiosk") == "true"){
        IsReturnGoodByKiosk = true;
    }else{
        IsReturnGoodByKiosk = false;
    }

    if (m_db.CheckDb()) m_db.openDb();
    m_sale = new SaleSession(this);
    m_transaction = new Transaction(this);
    m_billvalidator = new BillInputAmount(this);
    if(m_db.GetBillAvailable() == 0){
        m_transaction->AvailableAmount = 0;
        balanceBillAccepted_BillIdentified();
        m_billvalidator->BillAvailable = 0;
        m_billvalidator->BillTime = QDateTime::currentDateTime();
        m_db.CreatBillAvailable(m_billvalidator);
    }else{
        m_transaction->AvailableAmount = m_db.GetBillAvailable();
        balanceBillAccepted_BillIdentified();
        m_billvalidator->BillAvailable = m_db.GetBillAvailable();
        m_billvalidator->BillTime = QDateTime::currentDateTime();
        m_db.CreatBillAvailable(m_billvalidator);
    }
    init_sale_session();
    init_transaction();
    SetListGoodIdPriority();
   // m_db.CreateBillDescriptionStatus();
    //m_machinestatus->Temp = "";
}

Machine::~Machine()
{
    delete m_transaction;
    delete m_sale;
}
QJsonDocument Machine::JsonSyncConfig()
{
    QJsonObject kiosk;
    QJsonObject machine;
    QJsonObject AdministratorObject;
    AdministratorObject[QString("DeviceID")] = "kiosk-" + config.getMachineId();
    AdministratorObject[QString("MachineID")] = config.getMachineClienNumber();
    AdministratorObject[QString("NetworkCard")] = "eth0";
   // QByteArray password = getAdminPwd().toUtf8().toBase64(QByteArray::Base64Encoding);
   // QString password = QCryptographicHash::hash(getAdminPwd().toUtf8(),QCryptographicHash::Md5).toHex();
    AdministratorObject[QString("Password")] = config.getAdminPwd();
   // QByteArray passwordEncode = getPasswordEncode().toUtf8().toBase64(QByteArray::Base64Encoding);
 //   QString passwordEncode = QCryptographicHash::hash(getPasswordEncode().toUtf8(),QCryptographicHash::Md5).toHex();
   // AdministratorObject[QString("PasswordEncode")] = config.getPasswordEncode();
    AdministratorObject[QString("PasswordEncode")] = m_db.getValueKioskAdmin("Administrator","PasswordEncode");
    AdministratorObject[QString("Version")] = config.getVersion();
    machine[QString("Administrator")] = AdministratorObject;


    QJsonObject AndroidDeviceObject;
    AndroidDeviceObject[QString("IdDevice")] = config.getIdAndroidDevice();
    machine[QString("AndroidDevice")] = AndroidDeviceObject;


//    QJsonObject BankTypeObject;
//    for(int i = 1; i <= getBankTypeQuatity(); i++){
//        BankTypeObject["BankType" + QString::number(i)] = getBankType(i);
//    }
//    BankTypeObject["BankTypeQuatity"] = getBankTypeQuatity();
//    machine["BankType"] = BankTypeObject;

    QJsonObject BillObject;
    BillObject[QString("Baudrate")] = config.getBillBaudrate();
    if(config.getBillAmountEnabled())
        BillObject[QString("BillAmount")] = "true";
    else
        BillObject[QString("BillAmount")] = "false";
    if(config.getBillResponseEnabled())
        BillObject[QString("BillResponse")] = "true";
    else
        BillObject[QString("BillResponse")] = "false";
    if(config.getBillEnabled())
        BillObject[QString("Enable")] = "true";
    else
        BillObject[QString("Enable")] = "false";
    BillObject[QString("Port")] = config.getBillPort();
    machine[QString("Bill")] = BillObject;

    QJsonObject BillResponseObject;
    for(int i = 1; i <= config.getBillResponseQuatity(); i++){
        BillResponseObject["Response" + QString::number(i)] = config.getResponse(i);
    }
    BillResponseObject[QString("ResponseQuatity")] = config.getBillResponseQuatity();
    machine[QString("BillResponse")] = BillResponseObject;

    QJsonObject ChargeTypeCodeNameObject;
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::CASH)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::CASH));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::MPOS)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::MPOS));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::COUPON)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::COUPON));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::QRPAY)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::QRPAY));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::QRMB)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::QRMB));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::MOMO)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::MOMO));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::ZALOPAY)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::ZALOPAY));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::GRABPAY)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::GRABPAY));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::VINID)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::VINID));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::SMARTPAY)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::SMARTPAY));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::QRBANK)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::QRBANK));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::DIGITAL_WALLET)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::DIGITAL_WALLET));
    ChargeTypeCodeNameObject[QString::number(KioskTransactionType::OTHER)] = m_db.getValueKioskAdmin("ChargeTypeCodeName",QString::number(KioskTransactionType::OTHER));

    machine[QString("ChargeTypeCodeName")] = ChargeTypeCodeNameObject;

    QJsonObject ChargeTypeListDefaultObject;
    ChargeTypeListDefaultObject[QString("ListBankType")] = m_db.getValueKioskAdmin("ChargeTypeListDefault","ListBankType");
    ChargeTypeListDefaultObject[QString("ListChargeType")] = m_db.getValueKioskAdmin("ChargeTypeListDefault","ListChargeType");
    ChargeTypeListDefaultObject[QString("ListOtherType")] = m_db.getValueKioskAdmin("ChargeTypeListDefault","ListOtherType");
    ChargeTypeListDefaultObject[QString("ListWalletType")] = m_db.getValueKioskAdmin("ChargeTypeListDefault","ListWalletType");
    machine[QString("ChargeTypeListDefault")] = ChargeTypeListDefaultObject;

    QJsonObject ChargeTypeListSettingObject;
    ChargeTypeListSettingObject[QString("ListBankType")] = m_db.getValueKioskAdmin("ChargeTypeListSetting","ListBankType");
    ChargeTypeListSettingObject[QString("ListChargeType")] = m_db.getValueKioskAdmin("ChargeTypeListSetting","ListChargeType");
    ChargeTypeListSettingObject[QString("ListOtherType")] = m_db.getValueKioskAdmin("ChargeTypeListSetting","ListOtherType");
    ChargeTypeListSettingObject[QString("ListWalletType")] = m_db.getValueKioskAdmin("ChargeTypeListSetting","ListWalletType");
    machine[QString("ChargeTypeListSetting")] = ChargeTypeListSettingObject;

    QJsonObject ChargeTypeImageNameObject;
    ChargeTypeImageNameObject[QString::number(KioskTransactionType::QRPAY)] = m_db.getValueKioskAdmin("ChargeTypeImageName",QString::number(KioskTransactionType::QRPAY));
    ChargeTypeImageNameObject[QString(QString::number(KioskTransactionType::MOMO))] = m_db.getValueKioskAdmin("ChargeTypeImageName",QString::number(KioskTransactionType::MOMO));
    ChargeTypeImageNameObject[QString(QString::number(KioskTransactionType::ZALOPAY))] = m_db.getValueKioskAdmin("ChargeTypeImageName",QString::number(KioskTransactionType::ZALOPAY));
    ChargeTypeImageNameObject[QString(QString::number(KioskTransactionType::GRABPAY))] = m_db.getValueKioskAdmin("ChargeTypeImageName",QString::number(KioskTransactionType::GRABPAY));
    ChargeTypeImageNameObject[QString(QString::number(KioskTransactionType::VINID))] = m_db.getValueKioskAdmin("ChargeTypeImageName",QString::number(KioskTransactionType::VINID));
    ChargeTypeImageNameObject[QString(QString::number(KioskTransactionType::SMARTPAY))] = m_db.getValueKioskAdmin("ChargeTypeImageName",QString::number(KioskTransactionType::SMARTPAY));
    machine[QString("ChargeTypeImageName")] = ChargeTypeImageNameObject;

    QJsonObject CouponObject;
    CouponObject[QString("MaxPriceCoupon")] = config.getMaxPriceCoupon();
    CouponObject[QString("MinPriceCoupon")] = config.getMinPriceCoupon();
    CouponObject[QString("InputMinimumLimit")] = config.getInputMinimumLimit();
    if(config.getCheckHidePin())
        CouponObject[QString("AllPinHide")] = "true";
    else
        CouponObject[QString("AllPinHide")] = "false";
    machine[QString("Coupon")] = CouponObject;

    QJsonObject HandlingConnectObject;
    HandlingConnectObject[QString("TimeDelayToReConnectMQ")] = config.getTimeDelayToReConnecMQ();
    HandlingConnectObject[QString("TimesToRestartApp")] = config.getTimesToRestartApp();
    machine[QString("HandlingConnect")] = HandlingConnectObject;

    QJsonObject LanguageObject;
    LanguageObject[QString("ChangeLanguageScreenCode")] = config.getCodeChangeLanguageScreen();
    LanguageObject[QString("DefaultLanguage")] = config.getCodeLanguageScreen();
    if(config.getCheckPermissionMultiLanguages())
        LanguageObject[QString("MultiLanguagesPermission")] = "true";
    else
        LanguageObject[QString("MultiLanguagesPermission")] = "false";
    machine[QString("Language")] = LanguageObject;


    QJsonObject RabbitmqObject;
    RabbitmqObject[QString("Exchange")] = config.getQueueExchange();
    RabbitmqObject[QString("Host")] = config.getQueueHost();
   // QString passwordMQ = QCryptographicHash::hash(getQueuePassword().toUtf8(),QCryptographicHash::Md5).toHex();
    //QByteArray passwordMQ = getQueuePassword().toUtf8().toBase64(QByteArray::Base64Encoding);
   // LOG<<QString(password)<<QString(passwordEncode)<<QString(passwordMQ)<<"pw";
    RabbitmqObject[QString("Password")] = config.getQueuePassword();
    RabbitmqObject[QString("Port")] = config.getQueuePort();
    RabbitmqObject[QString("User")] = config.getQueueUser();
    RabbitmqObject[QString("VHost")] = config.getQueueVHost();
    machine[QString("Rabbitmq")] = RabbitmqObject;

    QJsonObject ResponseAmountObject;
    for(int i = 1; i <= config.getBillResponseQuatity(); i++){
        ResponseAmountObject[config.getResponse(i)] = config.getAmountResponse(config.getResponse(i));
    }
    machine[QString("ResponseAmount")] = ResponseAmountObject;

    QJsonObject ScreenTimeoutObject;
    ScreenTimeoutObject[QString("AdminTimeout")] = config.getAdminTimeout();
    if(config.getCheckScreenTimeout())
        ScreenTimeoutObject[QString("CheckScreenTimeout")] = "true";
    else
        ScreenTimeoutObject[QString("CheckScreenTimeout")] = "false";
    ScreenTimeoutObject[QString("GetGoodTimeout")] = config.getGetGoodTimeout();
    ScreenTimeoutObject[QString("QRCodeTimeout")] = config.getQRCodeTimeout();
    ScreenTimeoutObject[QString("SaverScreen")] = config.getSaverScreen();
    ScreenTimeoutObject[QString("ScreenTimeout")] = config.getScreenTimeout();
    machine[QString("ScreenTimeout")] = ScreenTimeoutObject;

    QJsonObject SensorObject;
    SensorObject[QString("Baudrate")] = config.getSensorBaudrate();
    if(config.getSensorEnabled())
        SensorObject[QString("Enable")] = "true";
    else
        SensorObject[QString("Enable")] = "false";
    SensorObject[QString("Port")] = config.getSensorPort();
    machine[QString("Sensor")] = SensorObject;

    QJsonObject SetPriceObject;
    if(config.getCheckGeneralPrice())
        SetPriceObject[QString("CheckGeneralPrice")] = "true";
    else
        SetPriceObject[QString("CheckGeneralPrice")] = "false";
    if(config.getCheckSlotPrice())
        SetPriceObject[QString("CheckSlotPrice")] = "true";
    else
        SetPriceObject[QString("CheckSlotPrice")] = "false";
    if(config.getCheckTrayPrice())
        SetPriceObject[QString("CheckTrayPrice")] = "true";
    else
        SetPriceObject[QString("CheckTrayPrice")] = "false";
    SetPriceObject[QString("Coefficient")] = config.getCoefficient();
    SetPriceObject[QString("PriceGoodsMax")] = config.getPriceGoodsMax();
    SetPriceObject[QString("PriceGoodsMin")] = config.getPriceGoodsMin();
    machine[QString("SetPrice")] = SetPriceObject;

    QJsonObject TestMachineObject;
    if(config.getCheckTestLoxo())
        TestMachineObject[QString("CheckTestLoxo")] = "true";
    else
        TestMachineObject[QString("CheckTestLoxo")] = "false";
    machine[QString("TestMachine")] = TestMachineObject;

    QJsonObject TimeExportDataObject;
    TimeExportDataObject[QString("DayNumberRemove")] = config.getNumberDayRemoveFileExport();
    TimeExportDataObject[QString("DefineTime")] = config.getTimeExportData();
    machine[QString("TimeExportData")] = TimeExportDataObject;

    QJsonObject VTCDigitalObject;
    VTCDigitalObject[QString("MaxPricePostpaid")] = config.getMaxPricePostPaid();
    VTCDigitalObject[QString("Menu")] = config.getMenuDigital();
    VTCDigitalObject[QString("MinPricePostpaid")] = config.getMinPricePostPaid();
    machine[QString("VTCDigital")] = VTCDigitalObject;

    QJsonObject TimeProcessUSBData;
    TimeProcessUSBData[QString("StarTimeProcess")] = config.getTimeProcessUSB();
    machine[QString("TimeProcessUSBData")] = TimeProcessUSBData;

//    QJsonObject StopFlagObject;
//    if(getStopFlagKiosk())
//        StopFlagObject[QString("FlagStop")] = "true";
//    else
//        StopFlagObject[QString("FlagStop")] = "false";
//    machine[QString("KioskStatus")] = StopFlagObject;

    QString signature = QCryptographicHash::hash(QJsonDocument(machine).toJson(QJsonDocument::Compact),QCryptographicHash::Md5).toHex();
    kiosk[QString("Signature")] = signature;
    kiosk[QString("machine")] = machine;
    kiosk[QString("Version")] = "1.0";




    QJsonDocument doc(kiosk);
    LOG<<doc.toJson()<<"---adminfile";
    return doc;
}
Transaction* Machine::transaction()
{
    return m_transaction;
}

SaleSession* Machine::saleSession()
{
    return m_sale;
}
BillInputAmount* Machine::BillAmount()
{
    return m_billvalidator;
}

QList<QString> Machine::GetListPartKioskAdmin(QString category)
{
    return m_db.GetListPartKioskAdmin(category);
}

QString Machine::GetValueKioskAdmin(QString category, QString part)
{
    return m_db.getValueKioskAdmin(category, part);
}

void Machine::UpdateValueKioskAdmin(QString category, QString part, QString value)
{
    m_db.UpdateValueKioskAdmin(category, part, value);
}

bool Machine::CreatKioskAdmin(QString category, QString part, QString value)
{
    return m_db.CreatKioskAdmin(category, part, value);
}
QList<QString> Machine::GetListChargeTypeName(QString s)
{
    return m_db.GetListChargeTypeName(s);
}

void Machine::SetListGoodIdPriority()
{
    ListPriority.clear();
    ListPriority = m_db.GetListPriority();
   // ListPriority<<1<<5<<2<<3<<4;
    std::sort(ListPriority.begin(), ListPriority.end());
//    for(int i = 0; i < ListPriority.size(); i++){
//       LOG<< ListPriority.at(i)<<"llllllllll";
//    }
    ListGoodIdPriority.clear();
    for(int i = 0; i < ListPriority.size(); i++){
        ListGoodIdPriority.append(m_db.GetListGoodIdPriority(ListPriority.at(i)));
    }
   // LOG<<ListGoodIdPriority.size()<<ListPriority.size()<<"kkkkk";
}

QList<QString> Machine::ReturnListGooIdPriority()
{
    return ListGoodIdPriority;
}

void Machine::UpdateAdminFile()
{
//    config.setVersion("1.6.4.3");
//    if(!config.admin()->contains("ScreenTimeout","AdminTimeout")){
//        config.setAdminTimeout(240000);
//    }
//   // if(!config.admin()->contains("ScreenTimeout","GetGoodTimeout")){
//        config.setGetGoodTimeout(20000);
//   // }

//    if(!config.admin()->contains("SetPrice","CheckGeneralPrice")){
//        config.setCheckGeneralPrice(true);
//    }
//    if(!config.admin()->contains("SetPrice","CheckTrayPrice")){
//        config.setCheckTrayPrice(true);
//    }
//    if(!config.admin()->contains("SetPrice","CheckSlotPrice")){
//        config.setCheckSlotPrice(true);
//    }

//    if(!config.admin()->contains("TestMachine","CheckTestLoxo")){
//        config.setCheckTestLoxo(true);
//    }
//    if(!config.admin()->contains("ChargeType","MBBank")){
//        config.setCheckMBBank(true);
//    }
//    //V1.6.0
//    if(!config.admin()->contains("VTCDigital","Menu")){
//        config.setMenuDigital("00");
//    }
//    if(!config.admin()->contains("VTCDigital","MaxPricePostpaid")){
//        config.setMaxPricePostPaid(10000000);
//    }
//    if(!config.admin()->contains("VTCDigital","MinPricePostpaid")){
//        config.setMinPricePostPaid(5000);
//    }

//    if(!config.admin()->contains("Coupon","MaxPriceCoupon")){
//        config.setMaxPriceCoupon(10000000);
//    }
//    if(!config.admin()->contains("Coupon","MinPriceCoupon")){
//        config.setMinPriceCoupon(1000);
//    }

//    if(!config.admin()->contains("AndroidDevice","IdDevice")){
//        config.setIdAndroidDevice("");
//    }

//    if(!config.admin()->contains("Administrator","PasswordEncode")){
//        config.setPasswordEncode("218bd5788150aba9397432c6a4ec63f6");
//    }
//    if(!config.admin()->contains("BillResponse","Response9")){
//        config.setResponse(9, "8700");
//    }
//    if(!config.admin()->contains("ResponseAmount","8700")){
//        config.setAmountResponse("8700", 200000);
//    }
//    config.setBillResponseQuatity(9);

//    if(!config.admin()->contains("TimeProcessUSBData","StarTimeProcess")){
//        QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd 00:00:00");
//        config.setTimeProcessUSB(date);
//    }
//    config.save();

}

void Machine::input(int keycode)
{

}

void Machine::KillApp()
{
    emit killApp();
}

void Machine::KillProcessApp()
{
    emit killProcessApp();
}
void Machine::GetListUsbPort()
{
    emit getListUsbPort();
}

void Machine::MountUsb()
{
    emit mountUsb();
}

void Machine::SyncUsb(QString sync)
{
    emit syncUsb(sync);
}
void Machine::inputBill(double inputAmount)
{
    m_transaction->AvailableAmount += inputAmount;
    balanceBillAccepted_BillIdentified();

    m_transaction->InputAmount += inputAmount;
    m_sale->TotalBill += inputAmount;

    if(m_state == GET_GOOD_DIGITAL || m_state == GET_GOOD_GENERAL){
        m_transaction->CheckInputGetGood = true;
        m_transaction->InputGetGood = inputAmount;
    }

   // m_billvalidator->stt += 1;

    //V1.2 Bắt đầu
    QString session_id = m_sale->SessionId;
    m_billvalidator->sale_session_id = session_id.toInt();
    m_billvalidator->BillTime = QDateTime::currentDateTime();
    m_billvalidator->BillAvailable += inputAmount;
    m_db.UpdateBillAvailable(m_billvalidator);


    m_billvalidator->StartTime = QDateTime::currentDateTime();
    m_billvalidator->BillAmount = inputAmount;
    m_db.CreateBillAmount(m_billvalidator);
    //V1.2 Kết thúc

    m_db.UpdateSaleSession(m_sale);
//    LOG;

}

void Machine::inputBIllIdentified(double inputAmount)
{
    m_transaction->IdentifiedAmount += inputAmount;
}

void Machine::balanceBillAccepted_BillIdentified()
{
    m_transaction->IdentifiedAmount = m_transaction->AvailableAmount;
}

void Machine::BillUnAccepted(double inputamount)
{
    m_transaction->IdentifiedAmount -= inputamount;
}


bool Machine::exportToCsv()
{
    bool r = false;
    QString path = "";
    QString nameCsvExort = "kiosk-";
    QString hostname = m_transaction->MachineId + "-";
    path = "/home/pi/export/"+nameCsvExort+hostname+dateExport+"to"+timeExport+".csv";
    if(m_db.queryToCsv(path, dateExport, timeExport)){
        r = true;
    }
    return r;
}

bool Machine::CheckExistCsv()
{
    bool r = false;
    QDir dir( "/home/pi/export" );
    QStringList listnameCsv = dir.entryList(QStringList() << "*.csv" ,QDir::Files);
    QString datetime = QDate::currentDate().toString("yyyyMMdd");

    foreach(QString nameCsv, listnameCsv){

        if(nameCsv.contains(datetime, Qt::CaseInsensitive))
            r = true;

    }
    return r;
}

void Machine::CreatDB()
{
    m_transaction->TransactionTime = QDateTime::currentDateTime();
    if (m_db.CreateTransaction(m_transaction))
    {
        m_transaction->TransactionTime = QDateTime::currentDateTime();
    }
}

void Machine::UpdateDB()
{
    if (m_db.UpdateTransaction(m_transaction))
    {
        LOG;
    }
}

void Machine::DeleteDB()
{
    if(m_db.DeleteTransaction(m_transaction)){

    }
}

void Machine::CreatAndUpdateDB()
{
    m_transaction->TransactionTime = QDateTime::currentDateTime();
    if (m_db.CreateTransaction(m_transaction))
    {
        m_transaction->TransactionTime = QDateTime::currentDateTime();
        m_db.UpdateTransaction(m_transaction);
    }
}

void Machine::UpdateBillAvailable()
{
    m_db.UpdateBillAvailable(m_billvalidator);
}


void Machine::GetTemp(QVariantMap data)
{
    if(data.isEmpty()){

    }
//    QJsonObject obj = QJsonObject::fromVariantMap(data);
//    if (obj.contains("Temp") && !obj["Temp"].isNull() && obj["Temp"].isString()){
//        m_machinestatus->Temp = obj["Temp"].toString();
//    }
}

//V1.2 Bắt đầu
void Machine::errorBill(QString error)
{
    if(error.isNull()){

    }
//    m_billvalidator->BillResponse = error;
//    QString session_id = m_sale->SessionId;
//    m_billvalidator->sale_session_id = session_id.toInt();
//    m_billvalidator->StartTime = QDateTime::currentDateTime();
//    QString BillStatus = error;

//    m_billvalidator->BillStatus  = m_db.GetDescriptionStatus(BillStatus);
//    m_db.CreateBillStatus(m_billvalidator);
}
QString Machine::GetBillAmount()
{
    QString DBBillAmount = "";
    DBBillAmount = m_db.GetBillAmount(m_sale->SessionId);

    return DBBillAmount;
}

QString Machine::GetBillStatus()
{
    QString DBBillStatus = "";
    DBBillStatus = m_db.GetBillStatus(m_sale->SessionId);

    return DBBillStatus;
}

void Machine::CreatErrorKioskTable(QVariantList error_code,
                                   QVariantList error_code_description,
                                   QVariantList error_group,
                                   QVariantList error_level,
                                   QVariantList signal_count,
                                   QVariantList signal_count_max)
{
    m_db.insertErrorKioskTable(error_code,error_code_description,error_group,error_level,signal_count,signal_count_max);
}

void Machine::DeleteErrorKioskTable()
{
    m_db.DeleteErrorKiosk();
}

int Machine::GetSignalCountErrorKiosk(QString error_code)
{
    return m_db.GetSignalCount(error_code);
}
QList<QString> Machine::GetListErrorCode()
{
    return m_db.GetListErrorCode();
}

QList<QString> Machine::GetListErrorCodeSorted(QString s)
{
    return m_db.GetListErrorCodeSortedByCountMax(s);
}

int Machine::GetSignalCountMaxErrorKiosk(QString error_code)
{
    return m_db.GetSignalCountMax(error_code);
}

void Machine::UpdateSignalCountErrorKiosk(QString s, int a)
{
    m_db.UpdateSignalCount(s, a);
}

void Machine::UpdateIncreaseSignalCountErrorKiosk(QString s , int a)
{
    quint16 count = GetSignalCountErrorKiosk(s);
    m_db.UpdateSignalCount(s, count + a);
}

void Machine::UpdateSignalCountErrorMaxKiosk(QString s , int a)
{
    m_db.UpdateSignalCountMax(s, a);
}

bool Machine::CreateErrorKiosk(QString error_code, QString error_code_description, QString error_group, QString error_level, int signal_count, int signal_count_max)
{
    return m_db.CreateErrorKiosk(error_code, error_code_description, error_group,error_level,signal_count,signal_count_max);
}

QList<QString> Machine::GetErrorKioskListSortBy()
{
    return m_db.GetErrorKioskListSortBy();
}

void Machine::CleanErrorNull(QString)
{
//    if(GetListErrorCode().contains("")){
//        for(int i = 0; i < GetListErrorCode().size(); i++){
//            if()
//        }
//    }
    m_db.CleanErrorNull("");
}

void Machine::UpdateResetSignalCountErrorKiosk()
{
    m_db.UpdateResetSignalCounr();
}


QString Machine::GetErrorSale()
{
    QString DbErrorSale;
    QString DBSale = m_db.GetErrorSale(m_current_input);
    QJsonDocument sale = QJsonDocument::fromJson(DBSale.toUtf8());
    QJsonObject saleObj = sale.object();


    QString StartTime = saleObj["start_time"].toString();
    QString EndTime = saleObj["end_time"].toString();
    QDateTime Start = QDateTime::fromString(StartTime,"yyyy-MM-dd hh:mm:ss");
    QDateTime End = QDateTime::fromString(EndTime,"yyyy-MM-dd hh:mm:ss");
    int StarttoMSecsSinceEpoch =Start.toMSecsSinceEpoch()/1000;
    int EndtoMSecsSinceEpoch =End.toMSecsSinceEpoch()/1000;
    int total_amount = saleObj["total_amount"].toInt();
    int total_bill = saleObj["total_bill"].toInt();
    QString staff_code = saleObj["staff_code"].toString();
    QString period = saleObj["period"].toString();
    int totalPeriod = saleObj["period_total_amount"].toInt();
    int share_total_amount = saleObj["share_total_amount"].toInt();
    int totalPeriodShare = saleObj["share_period_total_amount"].toInt();
    QString type = saleObj["type"].toString();

    QJsonObject ErrorSale;
    ErrorSale["actionTime"] = EndtoMSecsSinceEpoch;
    ErrorSale["id"] = m_current_input;
    ErrorSale["machineId"] = config.getMachineId();
    ErrorSale["money"] = total_bill;
    ErrorSale["moneyCalculate"] = total_amount;
    ErrorSale["staffCode"] = staff_code;
    ErrorSale["startTime"] = StarttoMSecsSinceEpoch;
    ErrorSale["period"] = period;
    ErrorSale["periodTotalAmount"] = totalPeriod;

    ErrorSale["shareSale"] = share_total_amount;
    ErrorSale["sharePeriodSale"] = totalPeriodShare;
    ErrorSale["type"] = type;
    ErrorSale["VersionApp"] = m_sale->VersionApp;
    DbErrorSale = QJsonDocument(ErrorSale).toJson();


    return DbErrorSale;
}

QString Machine::GetSaleMax()
{
    return m_db.GetSessionIdMax();
}

QString Machine::GetSaleStarUsb(QString s)
{
    return s;
   // return m_db.GetSessionIdStarDataUsb(s);
}

void Machine::GetInfoSale()
{
    QString DBSale = m_db.GetErrorSale(m_current_input);
    QJsonDocument sale = QJsonDocument::fromJson(DBSale.toUtf8());
    QJsonObject saleObj = sale.object();


    QString StartTime = saleObj["start_time"].toString();
    QString EndTime = saleObj["end_time"].toString();
    int total_amount = saleObj["total_amount"].toInt();
    int total_bill = saleObj["total_bill"].toInt();
    QString staff_code = saleObj["staff_code"].toString();


    StartTimeSale = StartTime;
    EndTimeSale = EndTime;
    TotalAmountSale = total_amount;
    TotalBillSale = total_bill;
    StaffCodeSale  = staff_code;
}

QString Machine::GetSaleInfo(QString sale)
{
    return m_db.GetErrorSale(sale);
}

//QString Machine::GetReTransaction(QString id)
//{
//    LOG<<"fffff";
//    return m_db.GetReTransaction(id);
//}

int Machine::GetIdReTransactionMax()
{
    return m_db.GetIdReTransactionMax();
}

QString Machine::GetReTransaction(QString startTime, QString endTime)
{
    QString ReTransactionList = "";
    QJsonObject TransactionData;
    QJsonArray TransactionArray;
    QList<QString> list = m_db.getReTransaction(startTime, endTime);
    LOG<<list.size()<<"list ls gd";
    for(int i = 0; i < list.size(); i++){
        QJsonDocument doc = QJsonDocument::fromJson(list.at(i).toUtf8());
        QJsonObject json = doc.object();
        TransactionArray.append(json);
    }
    TransactionData["Transaction"] = TransactionArray;
    QString signatureTransaction = QCryptographicHash::hash(QJsonDocument(TransactionData).toJson(QJsonDocument::Compact),QCryptographicHash::Md5).toHex();
    TransactionData["Signature"] = signatureTransaction;
    TransactionData["Version"] =  "1.0";
    ReTransactionList = QJsonDocument(TransactionData).toJson();
    LOG<< ReTransactionList<<"list giao dịch trong ngày";
    return ReTransactionList;
}


void Machine::input_rollback()
{
    m_current_input = m_last_input;
}

void Machine::input_append(QChar c)
{
    m_current_input.append(c);
}

void Machine::input_del()
{
   // LOG ;
    m_current_input = m_current_input.remove(m_current_input.length()-1,1);
}

void Machine::input_clean()
{
    m_last_input = m_current_input = "";
}

QString Machine::current_input() const
{
    //LOG << m_current_input;
    return m_current_input;
}

void Machine::set_current_input(QString input)
{
   // LOG << input;
    m_current_input = input;
}

void Machine::init_transaction_keep_info()
{
    m_transaction->OrderInformation = "";
    m_transaction->GoodPrice = m_transaction->GoodPriceGeneral;
    m_transaction->TransferId = "";
    m_transaction->TransactionStatus = KioskTransactionStatus::INIT;
    m_transaction->TransactionType = KioskTransactionType::UNSET;
    m_transaction->CheckPriceServe = false;
    m_transaction->idSale = "";
    m_transaction->reducedValue = 0;
    m_transaction->moneyCalculate = 0;
    m_transaction->RfidData = "";

   // m_db.CreateTransaction(m_transaction);
}

void Machine::init_transaction()
{

    m_transaction->init(m_sale->SessionId);

   // m_db.CreateTransaction(m_transaction);
}

void Machine::init_sale_session()
{
    LOG;
    m_sale->VersionApp = "1.0";
    m_sale->EndTime.setDate(QDate());
    m_sale->EndTime.setTime(QTime());

    if(!m_db.GetCurrentSaleSession(m_sale)) {
        m_sale->StartTime = QDateTime::currentDateTime();
        m_sale->TotalAmount = 0;
        m_sale->TotalAmountShare = 0;
        m_sale->Type = "day";
        m_sale->TotalBill = 0;
        m_sale->IsSyncing = false;
        m_sale->IsUpdateDB = false;

        if(m_db.CheckInitPeriodTable){
            m_sale->PrePeriod = QDate::currentDate().toString("yyyyMM");
            m_transaction->period = m_sale->PrePeriod;
            m_sale->PeriodTotalAmount = 0;
            m_sale->PeriodTotalAmountShare = 0;
            m_db.CheckInitPeriodTable = false;
        }
        if(m_sale->CheckSaleMonth){
            m_sale->PrePeriod = m_sale->LastPeriod;
            m_transaction->period = m_sale->PrePeriod;
            m_sale->PeriodTotalAmount = 0;
            m_sale->PeriodTotalAmountShare = 0;
            m_sale->CheckSaleMonth = false;
        }

        m_db.CreateSaleSession(m_sale);
    }else{
        m_transaction->period = m_sale->PrePeriod;
    }
}

void Machine::finish_sale_session()
{
    LOG << m_sale;
    m_sale->EndTime = QDateTime::currentDateTime();
    m_sale->Type = "day";
    if (m_db.UpdateSaleSession(m_sale)) {
        m_sale->IsUpdateDB = true;

    } else
        m_sale->EndTime = QDateTime();
}

void Machine::finish_sale_month_session()
{
    m_sale->CheckSaleMonth = true;
    m_sale->Type = "month";
    m_sale->EndTime = QDateTime::currentDateTime();
    if (m_db.UpdateSaleSession(m_sale)) {
        m_sale->IsUpdateDB = true;

    } else
        m_sale->EndTime = QDateTime();
    LOG;
}

int Machine::input_length()
{
   // LOG << m_current_input.length();
    return m_current_input.length();
}

void Machine::cancel_transaction()
{
    LOG << m_transaction;
    m_transaction->TransactionStatus = KioskTransactionStatus::CANCEL;
    m_transaction->TransactionTime = QDateTime::currentDateTime();
    if(m_transaction->TransactionType != KioskTransactionType::UNSET){
        if (m_db.CreateTransaction(m_transaction))
        {
            m_transaction->TransactionTime = QDateTime::currentDateTime();
            m_db.UpdateTransaction(m_transaction);
        }
    }
//    if (m_db.CreateTransaction(m_transaction))
//    {
//        //        m_transaction->TransferId = "";
//        //        m_transaction->TransactionStatus = 0;
//        //        m_transaction->TransactionType = 0;
//                m_db.UpdateTransaction(m_transaction);
//    }

    //    setState(SELECT_CHARGE_TYPE);
}

void Machine::finish_transaction()
{
    if(m_transaction->TransactionStatus != KioskTransactionStatus::TIMEOUT){
        m_transaction->TransactionStatus = KioskTransactionStatus::SUCCESS;
    }
    LOG << m_transaction;
    if (m_transaction->TransactionType == KioskTransactionType::CASH){
        m_transaction->AvailableAmount = m_transaction->ChargeAmount() > 0 ? m_transaction->ChargeAmount() : 0;
        balanceBillAccepted_BillIdentified();
        m_billvalidator->BillAvailable = (m_billvalidator->BillAvailable - m_transaction->GoodPrice * m_transaction->Quantity) > 0 ? (m_billvalidator->BillAvailable - m_transaction->GoodPrice * m_transaction->Quantity) : 0;
        m_billvalidator->BillTime = QDateTime::currentDateTime();
        QString session_id = m_sale->SessionId;
        m_billvalidator->sale_session_id = session_id.toInt();
        m_db.UpdateBillAvailable(m_billvalidator);
        if(m_billvalidator->BillAvailable == 0){
            m_db.CreatBillAvailable(m_billvalidator);
        }
    }else if(m_transaction->TransactionType == KioskTransactionType::CASHandMOMO || m_transaction->TransactionType == KioskTransactionType::CASHandQRPAY
        || m_transaction->TransactionType == KioskTransactionType::CASHandVINID || m_transaction->TransactionType == KioskTransactionType::CASHandGRABPAY || m_transaction->TransactionType == KioskTransactionType::CASHandZALOPAY){
        m_transaction->AvailableAmount = 0;
        m_billvalidator->BillAvailable = 0;
        balanceBillAccepted_BillIdentified();
        m_billvalidator->BillTime = QDateTime::currentDateTime();
        QString session_id = m_sale->SessionId;
        m_billvalidator->sale_session_id = session_id.toInt();
       // m_db.UpdateBillAvailable(m_billvalidator);
        m_db.CreatBillAvailable(m_billvalidator);

    }else if(m_transaction->TransactionType == KioskTransactionType::CASHandCOUPON){
            m_transaction->AvailableAmount = m_transaction->AvailableAmount - m_transaction->UseValueCash;
            balanceBillAccepted_BillIdentified();
            m_billvalidator->BillAvailable = m_transaction->AvailableAmount;
            m_billvalidator->BillTime = QDateTime::currentDateTime();
            QString session_id = m_sale->SessionId;
            m_billvalidator->sale_session_id = session_id.toInt();
           // m_db.UpdateBillAvailable(m_billvalidator);
            m_db.CreatBillAvailable(m_billvalidator);

    }

    if (m_transaction->TransactionStatus == KioskTransactionStatus::TIMEOUT ){
        m_transaction->IdentifiedAmount = 0;
        m_billvalidator->BillAvailable = 0;
        m_billvalidator->BillTime = QDateTime::currentDateTime();
        QString session_id = m_sale->SessionId;
        m_billvalidator->sale_session_id = session_id.toInt();
        m_db.UpdateBillAvailable(m_billvalidator);
        m_db.CreatBillAvailable(m_billvalidator);

    }
    if(m_transaction->TransactionType == KioskTransactionType::CASH && !m_transaction->GoodId.startsWith("VTC") && m_transaction->serviceCode != RECHARGEMOBILETYPE::COUPONGENERALSAB
        && m_transaction->serviceCode != RECHARGEMOBILETYPE::COUPONPINSAB && m_transaction->serviceCode != RECHARGEMOBILETYPE::COUPONPROMOTIONSAB && m_transaction->serviceCode != RECHARGEMOBILETYPE::COUPONRECHARGESAB && m_transaction->serviceCode != RECHARGEMOBILETYPE::MOTORINSURANCE){
        m_transaction->TransactionTime = QDateTime::currentDateTime();
        if (m_db.CreateTransaction(m_transaction)){
            m_transaction->TransactionTime = QDateTime::currentDateTime();
            if (m_db.UpdateTransaction(m_transaction))
            {
                if(m_transaction->moneyCalculate == 0){
                    m_sale->TotalAmount += m_transaction->Quantity * m_transaction->GoodPrice;
                    m_sale->PeriodTotalAmount += m_transaction->Quantity * m_transaction->GoodPrice;
                    if(m_transaction->CheckSaleSharePermission){
                        m_sale->TotalAmountShare += m_transaction->Quantity * m_transaction->GoodPrice;
                        m_sale->PeriodTotalAmountShare += m_transaction->Quantity * m_transaction->GoodPrice;
                    }
                }else{
                    m_sale->TotalAmount += m_transaction->moneyCalculate;
                    m_sale->PeriodTotalAmount += m_transaction->moneyCalculate;
                    if(m_transaction->CheckSaleSharePermission){
                        m_sale->TotalAmountShare += m_transaction->moneyCalculate;
                        m_sale->PeriodTotalAmountShare += m_transaction->moneyCalculate;
                    }
                }
                m_db.UpdateSaleSession(m_sale);
            }
        }
    }else{
        if (m_db.UpdateTransaction(m_transaction))
        {
            if(m_transaction->moneyCalculate == 0){
                m_sale->TotalAmount += m_transaction->Quantity * m_transaction->GoodPrice;
                m_sale->PeriodTotalAmount += m_transaction->Quantity * m_transaction->GoodPrice;
                if(m_transaction->CheckSaleSharePermission){
                    m_sale->TotalAmountShare += m_transaction->Quantity * m_transaction->GoodPrice;
                    m_sale->PeriodTotalAmountShare += m_transaction->Quantity * m_transaction->GoodPrice;
                }
            }else{
                m_sale->TotalAmount += m_transaction->moneyCalculate;
                m_sale->PeriodTotalAmount += m_transaction->moneyCalculate;
                if(m_transaction->CheckSaleSharePermission){
                    m_sale->TotalAmountShare += m_transaction->moneyCalculate;
                    m_sale->PeriodTotalAmountShare += m_transaction->moneyCalculate;
                }
            }
            m_db.UpdateSaleSession(m_sale);

        }
    }

    if(!m_transaction->GoodId.startsWith("VTC") && m_transaction->serviceCode !=  RECHARGEMOBILETYPE::COUPONGENERALSAB && m_transaction->serviceCode != RECHARGEMOBILETYPE::COUPONPINSAB && m_transaction->serviceCode != RECHARGEMOBILETYPE::COUPONPROMOTIONSAB && m_transaction->serviceCode != RECHARGEMOBILETYPE::COUPONRECHARGESAB && m_transaction->serviceCode != RECHARGEMOBILETYPE::MOTORINSURANCE){
        bool ok = false;
        quint8 khay = 0;
        quint8 slot = 0;
        quint8 good_count = 0;
        quint8 _input = m_transaction->SlotId.toInt(&ok);

        if (ok ) {
            khay = _input / 10;
            slot = _input % 10;
            good_count = config.getGoodCountForSlot(khay,slot);
            config.setGoodCountForSlot(khay, slot, good_count - m_transaction->Quantity);
            config.save();
            UpdateGoodQuatity(m_transaction->GoodId,GetGoodQuatity(m_transaction->GoodId) - m_transaction->Quantity);
            SetListGoodIdPriority();
            LOG<<config.getGoodCountForSlot(khay,slot)<<"số lượng sp";
        }
    }
}

bool Machine::insertInventoryBatch(QVariantList name_service, QVariantList tray_id, QVariantList slot_id, QVariantList good_id, QVariantList good_name, QVariantList good_price, QVariantList good_count, QVariantList max_count)
{
    LOG;
    return m_db.insertInventoryBatch(name_service, tray_id, slot_id,
                                     good_id, good_name, good_price,
                                     good_count, max_count);
}

bool Machine::insertMenuGood(QVariantList a, QVariantList b, QVariantList c, QVariantList d, QVariantList e, QVariantList f, QVariantList g, QVariantList k,QVariantList l,QVariantList h)
{
    LOG;
    return m_db.insertMenuGoodTable(a,b,c,d,e,f,g, k,l,h);
}

bool Machine::insertMenuGoodGeneral(QVariantList a, QVariantList b, QVariantList c, QVariantList d, QVariantList e,QVariantList q, QVariantList f, QVariantList g, QVariantList k,QVariantList l, QVariantList m)
{
    LOG;
    return m_db.insertMenuGoodGeneralTable(a,b,c,d,e,q,f,g, k,l, m);
}

bool Machine::clearInventory()
{
    LOG;
    return m_db.cleanInventory();
}

bool Machine::cleanMenuGoodTable()
{
    LOG;
    return m_db.cleanMenuGoodTable();
}

bool Machine::cleanMenuGoodGeneralTable()
{
    LOG;
    return m_db.cleanMenuGoodGeneralTable();
}

quint8 Machine::GetGoodQuatity(QString goodId)
{
    return m_db.GetGoodQuatity(goodId);
}

bool Machine::UpdateGoodQuatity(QString goodId,quint8 quatity)
{
    return m_db.UpdateGoodQuatity(goodId, quatity);
}

QList<int> Machine::getListGoodInventoryTable(QString s)
{
    LOG;
    return m_db.GetListGoodinInventoryTable(s);
}

QList<QString> Machine::getListGoodMenu()
{
    LOG;
    return m_db.GetListGoodMenu();
}

QList<QString> Machine::getListGoodId()
{
    LOG;
    return m_db.GetListGoodId();
}

QList<QString> Machine::getListGoodType(QString s)
{
    LOG;
    return m_db.GetListGoodType(s);
}

QList<int> Machine::getListGoodPrice(QString a, QString b)
{
    LOG;
    return m_db.GetListGoodPrice(a, b);
}

QList<QString> Machine::getListTypeCoupon(QString a, QString b)
{
    LOG;
    return m_db.GetListTypeCoupon(a, b);
}

QString Machine::getImageUrlMenuGoodGeneral(QString goodId)
{
    LOG;
    return m_db.getImageUrlMenuGoodGeneral(goodId);
}

QString Machine::getGoodIdForSlot(QString nameservice, int price) const
{
    LOG;
    return m_db.getGoodIdForSlot(nameservice, price);
}

QString Machine::getGoodNameForSlot(QString goodId) const
{
    LOG;
    return m_db.getGoodNameForSlot(goodId);
}

quint32 Machine::getTrayForSlot(QString goodId) const
{
    LOG;
    return m_db.getTrayForSlot(goodId);
}

quint32 Machine::getSlotForSlot(QString goodId) const
{
    LOG;
    return m_db.getSlotForSlot(goodId);
}

QString Machine::getGoodIdInMenuTable(QString typeGood, int price)
{
    LOG;
    return m_db.getGoodIdInMenuTable(typeGood, price);
}

QString Machine::getGoodId1InMenuTable(QString a, QString b)
{
    LOG;
    return m_db.getGoodId1InMenuTable(a, b);
}

QString Machine::getGoodIdCouponInMenuTable(QString a, QString b)
{
    return m_db.getGoodIdCouponInMenuTable(a ,b);
}

QString Machine::getGoodNameInMenuTable(QString goodId)
{
    LOG;
    return m_db.getGoodNameInMenuTable(goodId);
}

QString Machine::getListChargeTypeInMenuTable(QString goodId)
{
    LOG;
    return m_db.getListChargeTypeInMenuTable(goodId);
}

QString Machine::getListChargeTypeInMenuGeneralTable(QString goodId)
{
    LOG;
    return m_db.getListChargeTypeInMenuGeneralTable(goodId);
}

quint8 Machine::getChargeTypeQuatityInMenuTable(QString goodId)
{
    LOG;
    return m_db.getChargeTypeQuatity(goodId);
}

quint8 Machine::getChargeTypeQuatityInMenuGeneralTable(QString goodId)
{
    LOG;
    return m_db.getChargeTypeQuatityMenuGoodGeneral(goodId);
}

QString Machine::getGoodNameInMenuGeneralTable(QString goodId)
{
    LOG;
    return m_db.getGoodNameInMenuGeneralTable(goodId);
}

quint32 Machine::getGoodPriceInMenuGeneralTable(QString goodId)
{
    LOG;
    return m_db.getGoodPriceInMenuGeneralTable(goodId).toDouble();
}

MACHINE_STATE Machine::state() const { return m_state; }

MACHINE_STATE Machine::last_state() const
{
    return m_last_state;
}


void Machine::setState(MACHINE_STATE state)
{
    m_last_state = m_state;
    m_state = state;
}

void Machine::setLastState(MACHINE_STATE state)
{
    m_last_state = state;
}

QString Machine::getNameServerInMenuTable(QString typeGood, int price)
{
    LOG;
    return m_db.getServiceTypeInMenuTable(typeGood, price);
}

QString Machine::getNameServer1InMenuTable(QString a, QString b)
{
    LOG;
    return m_db.getServiceType1InMenuTable(a, b);
}

int Machine::getGoodPriceInMenuTable(QString a)
{
    LOG;
    return m_db.getGoodPriceInMenuTable(a);
}

QString Machine::getShareSalePermissionInMenuTable(QString goodId)
{
    LOG;
    return m_db.getShareSalePermissionInMenuTable(goodId);
}

QString Machine::getShareSalePermissionInMenuGeneralTable(QString goodId)
{
    return m_db.getShareSalePermissionInMenuGeneralTable(goodId);
}


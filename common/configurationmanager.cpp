
// V1.1
// Ngày sửa: 25/11/2018
// Người sửa: Namnd
/* Mục đích:
-Bổ sung thêm 2 hàm để lấy thời gian màn hình chờ trong file Admin.ini
*/

/*Chỉnh sửa bởi Hải
    Ngày 25/10/2018
    Chức năng: chỉnh sửa cài đặt giá
    Ver: 1.0
    File chỉnh sửa: - ...\20180704\works\app\data\screen.json
                     - ...\20180704\works\core\processor\administrator\1200000_price\1240000_detail\1241000_select_slot_processor.cpp
    Nội dung chỉnh sửa: đã coment chi tiết  ở trong code, ảnh đính kèm
    Mô tả chỉnh sửa: - ccài đặt giá trên một màn hình
                     - có thể cài đặt giá theo số lương slot của khay trong file setting.ini
                     - cài đặt ngưỡng cài đặt giá (lấy dữ liệu từ file admin.ini).*/





#include "configurationmanager.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkInterface>
#include <QUuid>
#include "Transaction/log.h"

ConfigurationManager::ConfigurationManager(QString filename):m_filename(filename)
{
    current_page_khay = 0;
    current_page_slot = 0;
}

ConfigurationManager::~ConfigurationManager()
{
    delete m_config;
    delete m_admin;
    //    qDeleteAll(m_ds_khay);
}

bool ConfigurationManager::load()
{
    LOG;
    bool ret = false;
    QFile DbFile;
    QString DatabaseDataStoragePath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
    DbFile.setFileName(":/img/admin.ini");
    DbFile.copy(DatabaseDataStoragePath + "/admin.ini");
    QFile::setPermissions(DatabaseDataStoragePath + "/admin.ini", QFile::WriteOwner | QFile::ReadOwner);
    m_admin = new DeviceCfg(DatabaseDataStoragePath + "/admin.ini");
    ret = m_admin->load();

    for(int i = 1; i <= getBillResponseQuatity(); i++){
        listReponseBill.insert(i - 1, getResponse(i));
        listAmountResponseBill.insert(i - 1,QString::number(getAmountResponse(getResponse(i))));
    }
    LOG<<listAmountResponseBill<<listReponseBill<<"listresponbill";

    LOG<<"load file admin success!"<<ret;
    if (!ret) return ret;

    QFile DbFile1;
    QString DatabaseDataStoragePath1 = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
    DbFile1.setFileName(":/img/setting.ini");
    DbFile1.copy(DatabaseDataStoragePath + "/setting.ini");
    QFile::setPermissions(DatabaseDataStoragePath + "/setting.ini", QFile::WriteOwner | QFile::ReadOwner);

    ret = false;
    m_config = new DeviceCfg(DatabaseDataStoragePath + "/" + m_filename );
    ret = m_config->load();
    LOG<<"load file setting success!"<<ret;
    if (!ret) return ret;
//    LOG << "* [Device]";
//    LOG << "* Số lượng khay:" << getTrayCount();
//    LOG << "* Giá mặc định:" << getGeneralPrice();
//    LOG << "* Tên mặc định:" << getGeneralName();
//    if (getTrayCount() > 0)
//    {
//        for (int i = 1; i <= getTrayCount() ; i++)
//        {
//            QString MaKhay = QString("Khay_%1").arg(i);
//            int SlotCount = m_config->getInt(MaKhay,"SlotCount",0);
//            LOG << "* ["<< MaKhay <<"]";
//            LOG << "* Số lượng khay:" << SlotCount;
//            LOG << "* Mã sp mặc định:" << m_config->getString(MaKhay,"GeneralId","");
//            LOG << "* Tên mặc định:" << m_config->getString(MaKhay,"GeneralName","");
//            LOG << "* Giá mặc định:" << m_config->getInt(MaKhay,"GeneralPrice",0);
//            if (SlotCount > 0)
//            {
//                for (int j = 0; j < SlotCount; j++)
//                {
//                    QString MaSLOT = QString("%1_Slot_%2").arg(MaKhay).arg(j);
//                    QString MaSP = m_config->getString(MaSLOT,"GoodId",0);
//                    QString TenSP = m_config->getString(MaSLOT,"GoodName","");
//                    int GiaSP = m_config->getInt(MaSLOT,"GoodPrice",0);
//                    LOG << "*   ["<<MaSLOT<<"]";
//                    LOG << "*     Mã sản phẩm:" << MaSP;
//                    LOG << "*     Tên sản phẩm:" << TenSP;
//                    LOG << "*     Giá sản phẩm:" << GiaSP;
//                }
//            }
//            //            m_ds_khay.append(k);
//        }
//    }
    return ret;
}

bool ConfigurationManager::loadAdminFile()
{
    bool ret = false;
    QString DatabaseDataStoragePath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
    m_admin = new DeviceCfg(DatabaseDataStoragePath + "/" + m_filename);
    ret = m_admin->load();

    for(int i = 1; i <= getBillResponseQuatity(); i++){
        listReponseBill.insert(i - 1, getResponse(i));
        listAmountResponseBill.insert(i - 1,QString::number(getAmountResponse(getResponse(i))));
    }
    return ret;
}


bool ConfigurationManager::save()
{
    bool ret = m_config->save();
    bool voi = m_admin->save();
    if(voi){

    }
  //  LOG << m_config->filename() << ret;
    return ret;
}

bool ConfigurationManager::clear()
{
    m_config->clear();
    return true;
}

void ConfigurationManager::loadListBillAmount()
{
    for(int i = 1; i <= getBillResponseQuatity(); i++){
        listReponseBill.insert(i - 1, getResponse(i));
        listAmountResponseBill.insert(i - 1,QString::number(getAmountResponse(getResponse(i))));
    }
    LOG<<listAmountResponseBill<<listReponseBill<<"listresponbill";
}

void ConfigurationManager::setDefautChargeType()
{
    listChargeType.clear();
    listBankType.clear();
    listWalletType.clear();
    for(int i = 1; i <= getChargeTypeQuatity(); i++){
        listChargeType.insert(i - 1, getChargeType(i));
    }

    for(int i = 1; i <= getBankTypeQuatity(); i++){
        listBankType.insert(i - 1, getBankType(i));
    }
    for(int i = 1; i <= getWalletTypeQuatity(); i++){
        listWalletType.insert(i - 1, getWalletType(i));
    }
 //   LOG<<listChargeType.at(0)<<listChargeType.at(1)<<listChargeType.at(2)<<listChargeType.at(3);
}

QJsonDocument ConfigurationManager::Json(quint8 a) {
    QJsonObject machine;
    int trayCount = getTrayCount();
    machine["GeneralCode"] =  getGeneralID();
    machine["GeneralId"] =  "";
    machine["GeneralName"] =  getGeneralName();
    machine["GeneralPrice"] = (int)getGeneralPrice();
    machine["GoodCount"] =  getGeneralGoodCount();
    machine["GoodMaxCount"] =  getGeneralGoodMaxCount();
    machine["SlotCount"] =  getGeneralSlotCount();
    machine["TrayCount"] =  trayCount;
    machine["name"] =  getMachineId();
    machine["CheckResponse"] =  a;


    QJsonArray khayArray;

    for (int i = 1; i <= trayCount; i++) {
        QJsonObject khayObject;
        int slotCount = getSlotCountForTray(i);;
        //        khayObject["GeneralId"] = "";getGeneralIDForTray(i);// "5a4c7319c11c4231088b4570";
        khayObject["GeneralCode"] = getGeneralIDForTray(i);//getGe"103120301";
        khayObject["GeneralName"] = getGeneralNameForTray(i);//"Milo uống liền 12(4x180ml)";
        khayObject["GeneralPrice"] = (int)getGeneralPriceForTray(i);//10000;
        khayObject["GoodMaxCount"] =  (int)getMaxCountForTray(i);
        khayObject["SlotCount"] = slotCount;

        khayObject["name"] = QString("Khay_%1").arg(i);
        QJsonArray slotArray;
        for (int s = 0; s < slotCount; s++) {
            QJsonObject slotObject;
            // slotObject["GoodId"] = /*getIdForSlot(i,s);*/
            slotObject["GoodCode"] = getIdForSlot(i,s);
            slotObject["GoodName"] = getNameForSlot(i,s);//"Milo uống liền 12(4x180ml)";
            slotObject["GoodPrice"] = (int)getPriceForSlot(i,s);//10000;
            slotObject["GoodCount"] = getGoodCountForSlot(i,s);
            slotObject["GoodMaxCount"] = getGoodMaxCountForSlot(i,s);
            slotObject["name"] = QString("Khay_%1_Slot_%2").arg(i).arg(s);
            slotArray.append(slotObject);
        }
        khayObject["slots"] = slotArray;
        khayArray.append(khayObject);
    }
    machine["khays"] = khayArray;
    QString sign;
    sign = getMachineId() + machine["khays"].toString();
    LOG<<machine["khays"].toString();
    QString signature = QCryptographicHash::hash(sign.toUtf8(),QCryptographicHash::Md5).toHex();
    machine["Signature"] = signature;
    QJsonDocument doc(machine);
    return doc;
}

QJsonDocument ConfigurationManager::JsonSyncConfig()
{
    QJsonObject kiosk;
    QJsonObject machine;
    QJsonObject AdministratorObject;
    AdministratorObject["DeviceID"] = "kiosk-" + getMachineId();
    AdministratorObject["MachineID"] = getMachineClienNumber();
    AdministratorObject["NetworkCard"] = "eth0";
    AdministratorObject["Password"] = getAdminPwd();
    AdministratorObject["PasswordEncode"] = getPasswordEncode();
    AdministratorObject["Version"] = getVersion();
    machine["Administrator"] = AdministratorObject;


    QJsonObject AndroidDeviceObject;
    AndroidDeviceObject["IdDevice"] = "";
    machine["AndroidDevice"] = AndroidDeviceObject;


    QJsonObject BankTypeObject;
    for(int i = 1; i <= getBankTypeQuatity(); i++){
        BankTypeObject["BankType" + QString::number(i)] = getBankType(i);
    }
    BankTypeObject["BankTypeQuatity"] = getBankTypeQuatity();
    machine["BankType"] = BankTypeObject;

    QJsonObject BillObject;
    BillObject["Baudrate"] = getBillBaudrate();
    if(getBillAmountEnabled())
        BillObject["BillAmount"] = "true";
    else
        BillObject["BillAmount"] = "false";
    if(getBillResponseEnabled())
        BillObject["BillResponse"] = "true";
    else
        BillObject["BillResponse"] = "false";
    if(getBillEnabled())
        BillObject["Enable"] = "true";
    else
        BillObject["Enable"] = "false";
    BillObject["Port"] = getBillPort();
    machine["Bill"] = BillObject;

    QJsonObject BillResponseObject;
    for(int i = 1; i <= getBillResponseQuatity(); i++){
        BillResponseObject["Response" + QString::number(i)] = getResponse(i);
    }
    BillResponseObject["ResponseQuatity"] = getBillResponseQuatity();
    machine["BillResponse"] = BillResponseObject;

    QJsonObject ChargeTypeObject;
    for(int i = 1; i <= getChargeTypeQuatity(); i++){
        ChargeTypeObject["ChargeType" + QString::number(i)] = getChargeType(i);
    }
    ChargeTypeObject["ChargeTypeQuatity"] = getChargeTypeQuatity();
    if(getCheckMBBank())
        ChargeTypeObject["MBBank"] = "true";
    else
        ChargeTypeObject["MBBank"] = "false";
    machine["ChargeType"] = ChargeTypeObject;

    QJsonObject CouponObject;
    CouponObject["MaxPriceCoupon"] = getMaxPriceCoupon();
    CouponObject["MinPriceCoupon"] = getMinPriceCoupon();
    machine["Coupon"] = CouponObject;

    QJsonObject RabbitmqObject;
    RabbitmqObject["Exchange"] = getQueueExchange();
    RabbitmqObject["Host"] = getQueueHost();
    RabbitmqObject["Password"] = getQueuePassword();
    RabbitmqObject["Port"] = getQueuePort();
    RabbitmqObject["User"] = getQueueUser();
    RabbitmqObject["VHost"] = getQueueVHost();
    machine["Rabbitmq"] = RabbitmqObject;

    QJsonObject ResponseAmountObject;
    for(int i = 1; i <= getBillResponseQuatity(); i++){
        ResponseAmountObject[getResponse(i)] = getAmountResponse(getResponse(i));
    }
    machine["ResponseAmount"] = ResponseAmountObject;

    QJsonObject ScreenTimeoutObject;
    ScreenTimeoutObject["AdminTimeout"] = getAdminTimeout();
    if(getCheckScreenTimeout())
        ScreenTimeoutObject["CheckScreenTimeout"] = "true";
    else
        ScreenTimeoutObject["CheckScreenTimeout"] = "false";
    ScreenTimeoutObject["GetGoodTimeout"] = getGetGoodTimeout();
    ScreenTimeoutObject["QRCodeTimeout"] = getQRCodeTimeout();
    ScreenTimeoutObject["SaverScreen"] = getSaverScreen();
    ScreenTimeoutObject["ScreenTimeout"] = getScreenTimeout();
    machine["ScreenTimeout"] = ScreenTimeoutObject;

    QJsonObject SensorObject;
    SensorObject["Baudrate"] = getSensorBaudrate();
    if(getSensorEnabled())
        SensorObject["Enable"] = "true";
    else
        SensorObject["Enable"] = "false";
    SensorObject["Port"] = getSensorPort();
    machine["Sensor"] = SensorObject;

    QJsonObject SetPriceObject;
    if(getCheckGeneralPrice())
        SetPriceObject["CheckGeneralPrice"] = "true";
    else
        SetPriceObject["CheckGeneralPrice"] = "false";
    if(getCheckSlotPrice())
        SetPriceObject["CheckSlotPrice"] = "true";
    else
        SetPriceObject["CheckSlotPrice"] = "false";
    if(getCheckTrayPrice())
        SetPriceObject["CheckTrayPrice"] = "true";
    else
        SetPriceObject["CheckTrayPrice"] = "false";
    SetPriceObject["Coefficient"] = getCoefficient();
    SetPriceObject["PriceGoodsMax"] = getPriceGoodsMax();
    SetPriceObject["PriceGoodsMin"] = getPriceGoodsMin();
    machine["SetPrice"] = SetPriceObject;

    QJsonObject TestMachineObject;
    if(getCheckTestLoxo())
        TestMachineObject["CheckTestLoxo"] = "true";
    else
        TestMachineObject["CheckTestLoxo"] = "false";
    machine["TestMachine"] = TestMachineObject;

    QJsonObject VTCDigitalObject;
    VTCDigitalObject["MaxPricePostpaid"] = getMaxPricePostPaid();
    VTCDigitalObject["Menu"] = getMenuDigital();
    VTCDigitalObject["MinPricePostpaid"] = getMinPricePostPaid();
    machine["VTCDigital"] = VTCDigitalObject;

    QJsonObject WalletTypeObject;
    for(int i = 1; i <= getWalletTypeQuatity(); i++){
        WalletTypeObject["WalletType" + QString::number(i)] = getWalletType(i);
    }
    WalletTypeObject["WalletTypeQuatity"] = getWalletTypeQuatity();
    machine["WalletType"] = WalletTypeObject;

    QJsonObject TimeProcessUSBData;
    TimeProcessUSBData["StarTimeProcess"] = getTimeProcessUSB();
    machine["TimeProcessUSBData"] = TimeProcessUSBData;

    QString signature = QCryptographicHash::hash(QJsonDocument(machine).toJson(QJsonDocument::Compact),QCryptographicHash::Md5).toHex();
    kiosk["Signature"] = signature;
    kiosk["machine"] = machine;




    QJsonDocument doc(kiosk);
    LOG<<doc.toJson()<<"---adminfile";
    return doc;

}

DeviceCfg *ConfigurationManager::admin()
{
    return  m_admin;
}

quint8 ConfigurationManager::getTrayCount() const
{
    return m_config->getInt(
                "Device",
                "TrayCount",
                0
                );
}

void ConfigurationManager::setTrayCount(quint8 count)
{
    m_config->setInt(
                "Device",
                "TrayCount",
                count
                );
}

quint8 ConfigurationManager::getGeneralSlotCount() const
{
    return m_config->getInt(
                "Device",
                "SlotCount",
                0
                );
}

void ConfigurationManager::setGeneralSlotCount(quint8 count)
{
    m_config->setInt(
                "Device",
                "SlotCount",
                count
                );
}

quint8 ConfigurationManager::getGeneralGoodCount() const
{
    return m_config->getInt(
                "Device",
                "GoodCount",
                0
                );
}

void ConfigurationManager::setGeneralGoodCount(quint8 count)
{
    m_config->setInt(
                "Device",
                "GoodCount",
                count
                );
}

quint8 ConfigurationManager::getGeneralGoodMaxCount() const
{
    return m_config->getInt(
                "Device",
                "GoodMaxCount",
                0
                );
}

void ConfigurationManager::setGeneralGoodMaxCount(quint8 count)
{
    m_config->setInt(
                "Device",
                "GoodMaxCount",
                count
                );
}

quint32 ConfigurationManager::getGeneralPrice() const
{
    return m_config->getInt(
                "Device",
                "GeneralPrice",
                0
                );
}

void ConfigurationManager::setGeneralPrice(quint32 price)
{
    m_config->setInt(
                "Device",
                "GeneralPrice",
                price);
}

QString ConfigurationManager::getGeneralID() const
{
    return m_config->getString(
                "Device",
                "GeneralId",
                "Unknow"
                );
}

void ConfigurationManager::setGeneralID(QString name)
{
    m_config->setString(
                "Device",
                "GeneralId",
                name);
}


QString ConfigurationManager::getGeneralName() const
{
    return m_config->getString(
                "Device",
                "GeneralName",
                "Unset"
                ).left(200);
}

void ConfigurationManager::setGeneralName(QString name)
{
    m_config->setString(
                "Device",
                "GeneralName",
                name.left(200));
}

quint8 ConfigurationManager::getSlotCountForTray(int tray) const
{
    return m_config->getInt(
                QString("Khay_%1").arg(tray),
                "SlotCount",
                getGeneralSlotCount()
                );
}

void ConfigurationManager::setSlotCountForTray(int tray, quint8 count)
{
    m_config->setInt(
                QString("Khay_%1").arg(tray),
                "SlotCount",
                count
                );
}



quint8 ConfigurationManager::getMaxCountForTray(int tray) const
{
    return m_config->getInt(
                QString("Khay_%1").arg(tray),
                "GoodMaxCount",
                getGeneralSlotCount()
                );
}

void ConfigurationManager::setMaxCountForTray(int tray, quint8 count)
{
    m_config->setInt(
                QString("Khay_%1").arg(tray),
                "GoodMaxCount",
                count
                );
}

quint8 ConfigurationManager::getGoodCountForTray(int tray) const
{
    return m_config->getInt(
                QString("Khay_%1").arg(tray),
                "GoodCount",
                getGeneralGoodCount()
                );
}

void ConfigurationManager::setGoodCountForTray(int tray, quint8 count)
{
    m_config->setInt(
                QString("Khay_%1").arg(tray),
                "GoodCount",
                count
                );
}

quint32 ConfigurationManager::getGeneralPriceForTray(int tray) const
{
    return m_config->getInt(
                QString("Khay_%1").arg(tray),
                "GeneralPrice",
                getGeneralPrice()
                );
}

void ConfigurationManager::setGeneralPriceForTray(int tray, quint32 price)
{
    m_config->setInt(
                QString("Khay_%1").arg(tray),
                "GeneralPrice",
                price);
}

QString ConfigurationManager::getGeneralIDForTray(int tray) const
{
    return getGeneralID() != "Unknow" ?
                getGeneralID() :
                m_config->getString(
                    QString("Khay_%1").arg(tray),
                    "GeneralId",
                    "Unset"
                    );
}

void ConfigurationManager::setGeneralIDForTray(int tray, QString name)
{
    m_config->setString(
                QString("Khay_%1").arg(tray),
                "GeneralId",
                name
                );
}


QString ConfigurationManager::getGeneralNameForTray(int tray) const
{
    return m_config->getString(
                QString("Khay_%1").arg(tray),
                "GeneralName",
                getGeneralName()
                ).left(200);
}

void ConfigurationManager::setGeneralNameForTray(int tray, QString name)
{
    m_config->setString(
                QString("Khay_%1").arg(tray),
                "GeneralName",
                name.left(200)
                );
}

QString ConfigurationManager::getseviceCodeForTray(int tray) const
{
    return m_config->getString(
                QString("Khay_%1").arg(tray),
                "serviceCode",
                ""
                );
}

void ConfigurationManager::setseviceCodeForTray(int tray, QString name)
{
    m_config->setString(
                QString("Khay_%1").arg(tray),
                "serviceCode",
                name
                );
}



int ConfigurationManager::getTypeCardMobileForTray(QString type) const
{
    return m_config->getInt(
                type,
                "Khay",
                0
                );
}

void ConfigurationManager::setTypeCardMobileForTray(QString type, int tray)
{
    m_config->setInt(
                type,
                "Khay",
                tray
                );
}



int ConfigurationManager::getGoodCountForSlot(int tray, int slot) const
{
    return m_config->getInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "GoodCount",
                getGoodCountForTray(tray)
                );
}

void ConfigurationManager::setGoodCountForSlot(int tray, int slot, int count)
{
    LOG << tray << slot << count;
    m_config->setInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "GoodCount",
                count
                );
}

int ConfigurationManager::getGoodMaxCountForSlot(int tray, int slot) const
{
    return m_config->getInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "GoodMaxCount",
                getGoodCountForTray(tray)
                );
}

void ConfigurationManager::setGoodMaxCountForSlot(int tray, int slot, int count)
{
    LOG << tray << slot << count;
    m_config->setInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "GoodMaxCount",
                count
                );
}

int ConfigurationManager::getPriceMask(int tray, int slot) const
{
    return m_config->getInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "PriceMask",
                0
                );
}

void ConfigurationManager::setPriceMask(int tray, int slot, int mask)
{
    m_config->setInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "PriceMask",
                mask
                );
}

quint32 ConfigurationManager::getPriceForSlot(int tray, int slot) const
{
    return m_config->getInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "GoodPrice",
                getGeneralPriceForTray(tray)
                );
}

void ConfigurationManager::setPriceForSlot(int tray, int slot, quint32 price)
{
    LOG << tray << slot << price;
    m_config->setInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "GoodPrice",
                price
                );
}
QString ConfigurationManager::getNameForSlot(int tray, int slot) const
{
    return m_config->getString(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "GoodName",
                getGeneralNameForTray(tray)
                ).left(200);
}

void ConfigurationManager::setNameForSlot(int tray, int slot, QString name)
{
    m_config->setString(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "GoodName",
                name.left(200)
                );
}

QString ConfigurationManager::getIdForSlot(int tray, int slot) const
{
    return getGeneralIDForTray(tray) > 0 ? getGeneralIDForTray(tray)
                                         : m_config->getString(
                                               QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                                               "GoodId",
                                               "Unknow"
                                               );
}

void ConfigurationManager::setIdForSlot(int tray, int slot, QString name)
{
    m_config->setString(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "GoodId",
                name
                );
}
QString ConfigurationManager::getTextPromotionForSlot(int tray, int slot) const
{
    return m_config->getString(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "TextPromotion",
                ""
                );
}

void ConfigurationManager::setTextPromotionForSlot(int tray, int slot, QString text)
{
    m_config->setString(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "TextPromotion",
                text
                );
}

quint8 ConfigurationManager::getChargeTypeQuatityPermission(int tray, int slot) const
{
    return m_config->getInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "ChargeTypeQuatity",
                0
                );
}

void ConfigurationManager::setChargeTypeQuatityPermission(int tray, int slot, quint8 quatity)
{
    m_config->setInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "ChargeTypeQuatity",
                quatity
                );
}

QString ConfigurationManager::getChargeTypePermission(int tray, int slot, quint8 index) const
{
    return m_config->getString(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "ChargeType"+ QString::number(index),
                ""
                );
}

void ConfigurationManager::setChargeTypePermission(int tray, int slot, quint8 index, QString ChargeType)
{
    m_config->setString(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "ChargeType"+ QString::number(index),
                ChargeType
                );
}

quint8 ConfigurationManager::getSaleProductPermission(int tray, int slot) const
{
    return m_config->getInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "SaleProductPermission",
                0
                );
}

void ConfigurationManager::setSaleProductPermission(int tray, int slot, quint8 quatity)
{
    m_config->setInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "SaleProductPermission",
                quatity
                );
}

QString ConfigurationManager::getStopProductContent(int tray, int slot) const
{
    return m_config->getString(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "StopProductContent",
                ""
                );
}

void ConfigurationManager::setStopProductContent(int tray, int slot, QString ChargeType)
{
    m_config->setString(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "StopProductContent",
                ChargeType
                );
}

quint8 ConfigurationManager::getProductNumber(int tray, int slot) const
{
    return m_config->getInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "ProductNumber",
                1
                );
}

void ConfigurationManager::setProductNumber(int tray, int slot, quint8 quatity)
{
    m_config->setInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "ProductNumber",
                quatity
                );
}

quint8 ConfigurationManager::getProductChange(int tray, int slot) const
{
    return m_config->getInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "ProductChange",
                1
                );
}

void ConfigurationManager::setProductChange(int tray, int slot, quint8 quatity)
{
    m_config->setInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "ProductChange",
                quatity
                );
}

quint8 ConfigurationManager::getPriorityCharge(int tray, int slot) const
{
    return m_config->getInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "PriorityCharge",
                0
                );
}

void ConfigurationManager::setPriorityCharge(int tray, int slot, quint8 charge)
{
    m_config->setInt(
                QString("Khay_%1_Slot_%2").arg(tray).arg(slot),
                "PriorityCharge",
                charge
                );
}



QString ConfigurationManager::getAdminPwd() const
{
    return m_admin->getString(
                "Administrator",
                "Password",
                "Unknow"
                );
}

void ConfigurationManager::setAdminPwd(QString pwd)
{
    m_admin->setString(
                "Administrator",
                "Password",
                pwd
                );
}

QString ConfigurationManager::getMachineId() const
{
    QString mId = m_admin->getString(
                "Administrator",
                "DeviceID",
                QUuid::createUuid().toRfc4122()
                );
    if (mId.startsWith("kiosk-"))
        mId = mId.mid(6, mId.length()-6);
    return mId;
}

void ConfigurationManager::setMachineId(QString deviceID)
{
    m_admin->setString(
                "Administrator",
                "DeviceID",
                deviceID
                );
}

QString ConfigurationManager::getKioskId() const
{
    return m_admin->getString(
                "Administrator",
                "KioskId",
                "Unknow"
                );
}

void ConfigurationManager::setKioskId(QString KioskID)
{
    m_admin->setString(
                "Administrator",
                "KioskId",
                KioskID
                );
}

QString ConfigurationManager::getVersion() const
{
    return m_admin->getString(
                "Administrator",
                "Version",
                "Unknow"
                );
}

void ConfigurationManager::setVersion(QString Vs)
{
    m_admin->setString(
                "Administrator",
                "Version",
                Vs
                );
}

QString ConfigurationManager::getPasswordEncode() const
{
    return m_admin->getString(
                "Administrator",
                "PasswordEncode",
                "Unknow"
                );
}

void ConfigurationManager::setPasswordEncode(QString pw)
{
    m_admin->setString(
                "Administrator",
                "PasswordEncode",
                pw
                );
}

QString ConfigurationManager::getMachineClienNumber() const
{
    return m_admin->getString(
                "Administrator",
                "MachineID",
                "Unknow"
                );
}

void ConfigurationManager::setMachineClientNumber(QString id)
{
    m_admin->setString(
                "Administrator",
                "MachineID",
                id
                );
}


quint32 ConfigurationManager::getTrayDigital(QString s) const
{
        return m_config->getInt(
                    s,
                    "Khay",
                    0
                    );
}

void ConfigurationManager::setTrayDigital(QString digital, int tray)
{
    m_config->setInt(
                digital,
                "Khay",
                tray
                );
}

QString ConfigurationManager::getMenuDigital() const
{
    return m_admin->getString("VTCDigital","Menu","00");
}

void ConfigurationManager::setMenuDigital(QString menu)
{
    m_admin->setString("VTCDigital","Menu",menu);
}

int ConfigurationManager::getMaxPricePostPaid() const
{
    return m_admin->getInt("VTCDigital","MaxPricePostpaid",10000000);
}

void ConfigurationManager::setMaxPricePostPaid(int a)
{
    m_admin->setInt("VTCDigital","MaxPricePostpaid", a);
}

int ConfigurationManager::getMinPricePostPaid() const
{
    return m_admin->getInt("VTCDigital","MinPricePostpaid",10000000);
}

void ConfigurationManager::setMinPricePostPaid(int a)
{
    m_admin->setInt("VTCDigital","MinPricePostpaid", a);
}

int ConfigurationManager::getMaxPriceCoupon() const
{
    return m_admin->getInt("Coupon","MaxPriceCoupon",10000000);
}

void ConfigurationManager::setMaxPriceCoupon(int a)
{
    m_admin->setInt("Coupon","MaxPriceCoupon", a);
}

int ConfigurationManager::getMinPriceCoupon() const
{
    return m_admin->getInt("Coupon","MinPriceCoupon",1000);
}

void ConfigurationManager::setMinPriceCoupon(int a)
{
    m_admin->setInt("Coupon","MinPriceCoupon", a);
}

bool ConfigurationManager::getCheckHidePin() const
{
    return m_admin->getBool("Coupon","AllPinHide",true);
}

void ConfigurationManager::setCheckHidePin(bool a)
{
    m_admin->setBool("Coupon","AllPinHide",a);
}

int ConfigurationManager::getInputMinimumLimit() const
{
    return m_admin->getInt("Coupon","InputMinimumLimit",10);
}

void ConfigurationManager::setInputMinimumLimit(int a)
{
    m_admin->setInt("Coupon","InputMinimumLimit", a);
}

bool ConfigurationManager::getBillEnabled() const
{
    return m_admin->getBool("Bill","Enable",false);
}

void ConfigurationManager::setBillEnabled(bool enabled)
{
    return m_admin->setBool("Bill","Enable",enabled);
}

bool ConfigurationManager::getBillAmountEnabled() const
{
    return m_admin->getBool("Bill","BillAmount",false);
}

void ConfigurationManager::setBillAmountEnabled(bool enabled)
{
    return m_admin->setBool("Bill","BillAmount",enabled);
}

bool ConfigurationManager::getBillResponseEnabled() const
{
    return m_admin->getBool("Bill","BillResponse",false);
}

void ConfigurationManager::setBillResponseEnabled(bool enabled)
{
    return m_admin->setBool("Bill","BillResponse",enabled);
}

bool ConfigurationManager::getCheckScreenTimeout() const
{
    return m_admin->getBool("ScreenTimeout","CheckScreenTimeout",false);
}

void ConfigurationManager::setCheckScreenTimeout(bool enabled)
{
    return m_admin->setBool("ScreenTimeout","CheckScreenTimeout",enabled);
}

bool ConfigurationManager::getCheckGeneralPrice() const
{
    return m_admin->getBool("SetPrice","CheckGeneralPrice",true);
}

void ConfigurationManager::setCheckGeneralPrice(bool enabled)
{
    return m_admin->setBool("SetPrice","CheckGeneralPrice",enabled);
}

bool ConfigurationManager::getCheckTrayPrice() const
{
    return m_admin->getBool("SetPrice","CheckTrayPrice",true);
}

void ConfigurationManager::setCheckTrayPrice(bool enabled)
{
    return m_admin->setBool("SetPrice","CheckTrayPrice",enabled);
}

bool ConfigurationManager::getCheckSlotPrice() const
{
    return m_admin->getBool("SetPrice","CheckSlotPrice",true);
}

void ConfigurationManager::setCheckSlotPrice(bool enabled)
{
    return m_admin->setBool("SetPrice","CheckSlotPrice",enabled);
}

bool ConfigurationManager::getCheckTestLoxo() const
{
    return m_admin->getBool("TestMachine","CheckTestLoxo",true);
}

void ConfigurationManager::setCheckTestLoxo(bool a)
{
    return m_admin->setBool("TestMachine","CheckTestLoxo",a);
}


bool ConfigurationManager::getCheckMBBank() const
{
    return m_admin->getBool("ChargeType","MBBank",true);
}

void ConfigurationManager::setCheckMBBank(bool a)
{
    m_admin->setBool("ChargeType","MBBank",a);
}




QString ConfigurationManager::getBillPort() const
{
    return m_admin->getString("Bill","Port","");
}

void ConfigurationManager::setBillPort(QString port)
{
    m_admin->setString("Bill","Port",port);
}

int ConfigurationManager::getBillBaudrate() const
{
    return m_admin->getInt("Bill","Baudrate",115200);
}

void ConfigurationManager::setBillBaudrate(int baudrate)
{
    m_admin->setInt("Bill","Baudrate",baudrate);
}

bool ConfigurationManager::getSensorEnabled() const
{
    return m_admin->getBool("Sensor","Enable",false);
}

void ConfigurationManager::setSensorEnabled(bool enabled)
{
    return m_admin->setBool("Sensor","Enable",enabled);
}

QString ConfigurationManager::getSensorPort() const
{
    return m_admin->getString("Sensor","Port","");
}

void ConfigurationManager::setSensorPort(QString port)
{
    m_admin->setString("Sensor","Port",port);
}

int ConfigurationManager::getSensorBaudrate() const
{
    return m_admin->getInt("Sensor","Baudrate",115200);
}

void ConfigurationManager::setSensorBaudrate(int baudrate)
{
    m_admin->setInt("Sensor","Baudrate",baudrate);
}

QString ConfigurationManager::getQueueHost() const
{
    return m_admin->getString("Rabbitmq","Host","");
}

void ConfigurationManager::setQueueHost(QString host)
{
    m_admin->setString("Rabbitmq","Host",host);
}

int ConfigurationManager::getQueuePort() const
{
    return m_admin->getInt("Rabbitmq","Port",5672);
}

void ConfigurationManager::setQueuePort(int port)
{
    m_admin->setInt("Rabbitmq","Port",port);
}

QString ConfigurationManager::getQueueVHost() const
{
    return m_admin->getString("Rabbitmq","VHost","");
}

void ConfigurationManager::setQueueVHost(QString vhost)
{
    m_admin->setString("Rabbitmq","VHost",vhost);
}

QString ConfigurationManager::getQueueUser() const
{
    return m_admin->getString("Rabbitmq","User","");
}

void ConfigurationManager::setQueueUser(QString user)
{
    m_admin->setString("Rabbitmq","User",user);
}

QString ConfigurationManager::getQueuePassword() const
{
    return m_admin->getString("Rabbitmq","Password","");
}

void ConfigurationManager::setQueuePassword(QString password)
{
    m_admin->setString("Rabbitmq","Password",password);
}

QString ConfigurationManager::getQueueExchange() const
{
    return m_admin->getString("Rabbitmq","Exchange","");
}

void ConfigurationManager::setQueueExchange(QString exchange)
{
    m_admin->setString("Rabbitmq","Exchange",exchange);
}

QString ConfigurationManager::getIpAddress() const
{
    QString networkCard = m_admin->getString(
                "Administrator",
                "NetworkCard",
                ""
                );
    QString currentIp = "127.0.0.1";
    if (networkCard.isEmpty()) return currentIp;
    QNetworkInterface eth1Ip = QNetworkInterface::interfaceFromName(networkCard);
    QList<QNetworkAddressEntry> entries = eth1Ip.addressEntries();
    if (!entries.isEmpty()) {
        //        QNetworkAddressEntry entry = entries.first();
        foreach (QNetworkAddressEntry entry, entries) {
            qDebug() << entry.ip().toString() << "/" << entry.netmask().toString();

            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                currentIp = entry.ip().toString();
                break;
            }
        }
    }
    return currentIp;
}

void ConfigurationManager::setIpAddress(QString s)
{
    m_admin->setString("Administrator","NetworkCard",s);
}


int ConfigurationManager::getScreenTimeout() const
{
    return m_admin->getInt("ScreenTimeout","ScreenTimeout",300000);
}

void ConfigurationManager::setScreenTimeout(int timeout)
{
    m_admin->setInt("ScreenTimeout","ScreenTimeout",timeout);
}


QString ConfigurationManager::getResponse(int i) const
{
    return m_admin->getString("BillResponse","Response" + QString::number(i),"");
}

void ConfigurationManager::setResponse(quint8 i, QString a)
{
    m_admin->setString("BillResponse","Response" + QString::number(i), a);
}

int ConfigurationManager::getAmountResponse(QString s) const
{
    return m_admin->getInt("ResponseAmount",s,0);
}

void ConfigurationManager::setAmountResponse(QString s,int a)
{
    m_admin->setInt("ResponseAmount",s,a);
}
int ConfigurationManager::getBillResponseQuatity() const
{
    return m_admin->getInt("BillResponse","ResponseQuatity",0);
}

void ConfigurationManager::setBillResponseQuatity(int a)
{
    m_admin->setInt("BillResponse","ResponseQuatity",a);
}

QString ConfigurationManager::getAcceptBillResponse(int i) const
{
    return m_admin->getString("BillAcceptResponse","AcceptResponse" + QString::number(i),"");
}

int ConfigurationManager::getAmountAcceptBill(QString s) const
{
    return m_admin->getInt("BillAcceptResponseAmount",s,0);
}

int ConfigurationManager::getAcceptBillQuatity() const
{
    return m_admin->getInt("BillAcceptResponse","BillAcceptQuatity",0);
}

QString ConfigurationManager::getChargeType(int i) const
{
    return m_admin->getString("ChargeType","ChargeType" + QString::number(i),"");
}

void ConfigurationManager::setChargeType(int i, QString s)
{
    m_admin->setString("ChargeType","ChargeType" + QString::number(i),s);
}

int ConfigurationManager::getChargeTypeQuatity() const
{
    return m_admin->getInt("ChargeType","ChargeTypeQuatity",0);
}

void ConfigurationManager::setChargeTypeQuatity(int s)
{
    m_admin->setInt("ChargeType","ChargeTypeQuatity",s);
}

QString ConfigurationManager::getBankType(int i) const
{
    return m_admin->getString("BankType","BankType" + QString::number(i),"");
}

void ConfigurationManager::setBankType(int i, QString s)
{
    m_admin->setString("BankType","BankType" + QString::number(i),s);
}

int ConfigurationManager::getBankTypeQuatity() const
{
    return m_admin->getInt("BankType","BankTypeQuatity",0);
}

void ConfigurationManager::setBankTypeQuatity(int s)
{
    m_admin->setInt("BankType","BankTypeQuatity",s);
}

QString ConfigurationManager::getWalletType(int i) const
{
    return m_admin->getString("WalletType","WalletType" + QString::number(i),"");
}

void ConfigurationManager::setWalletType(int i, QString s)
{
    m_admin->setString("WalletType","WalletType" + QString::number(i),s);
}

int ConfigurationManager::getWalletTypeQuatity() const
{
    return m_admin->getInt("WalletType","WalletTypeQuatity",0);
}

void ConfigurationManager::setWalletTypeQuatity(int s)
{
    m_admin->setInt("WalletType","WalletTypeQuatity",s);
}




//V1.1 Bắt đầu
int ConfigurationManager::getSaverScreen() const
{
    return m_admin->getInt("ScreenTimeout","SaverScreen",20000);
}

void ConfigurationManager::setSaverScreen(int timeout)
{
    m_admin->setInt("ScreenTimeout","SaverScreen",timeout);
}
//V1.1 Kết thúc

int ConfigurationManager::getQRCodeTimeout() const
{
    return m_admin->getInt("ScreenTimeout","QRCodeTimeout",600000);
}

void ConfigurationManager::setQRCodeTimeout(int timeout)
{
    m_admin->setInt("ScreenTimeout","QRCodeTimeout",timeout);
}

int ConfigurationManager::getAdminTimeout() const
{
    return m_admin->getInt("ScreenTimeout","AdminTimeout",600000);
}

void ConfigurationManager::setAdminTimeout(int timeout)
{
    m_admin->setInt("ScreenTimeout","AdminTimeout",timeout);
}

int ConfigurationManager::getGetGoodTimeout() const
{
    return m_admin->getInt("ScreenTimeout","GetGoodTimeout",10000);
}

void ConfigurationManager::setGetGoodTimeout(int timeout)
{
    m_admin->setInt("ScreenTimeout","GetGoodTimeout",timeout);
}

//V1.0 bắt đầu
int ConfigurationManager::getPriceGoodsMax() const
{
    return m_admin->getInt(
                "SetPrice",
                "PriceGoodsMax",
                0
                );
}

void ConfigurationManager::setPriceGoodsMax(int PriceGoodsMax)
{
    m_admin->setInt(
                "SetPrice",
                "PriceGoodsMax",
                PriceGoodsMax
                );
}

int ConfigurationManager::getPriceGoodsMin() const
{
    return m_admin->getInt(
                "SetPrice",
                "PriceGoodsMin",
                0
                );
}

void ConfigurationManager::setPriceGoodsMin(int PriceGoodsMin)
{
    m_admin->setInt(
                "SetPrice",
                "PriceGoodsMin",
                PriceGoodsMin
                );
}

int ConfigurationManager::getCoefficient() const
{
    return m_admin->getInt(
                "SetPrice",
                "Coefficient",
                0
                );
}

void ConfigurationManager::setCoefficient(int Coefficient)
{
    m_admin->setInt(
                "SetPrice",
                "Coefficient",
               Coefficient
                );
}

QString ConfigurationManager::getIdAndroidDevice() const
{
    return m_admin->getString("AndroidDevice","IdDevice","");
}

void ConfigurationManager::setIdAndroidDevice(QString s)
{
    m_admin->setString("AndroidDevice","IdDevice",s);
}

QString ConfigurationManager::getTextAndroidDevice() const
{
    return m_admin->getString("AndroidDevice","TextDevice","");
}

void ConfigurationManager::setTextAndroidDevice(QString s)
{
    m_admin->setString("AndroidDevice","TextDevice",s);
}

QString ConfigurationManager::getTimeProcessUSB() const
{
    return m_admin->getString("TimeProcessUSBData","StarTimeProcess","");
}

void ConfigurationManager::setTimeProcessUSB(QString s)
{
    m_admin->setString("TimeProcessUSBData","StarTimeProcess",s);
}

QString ConfigurationManager::getTimeExportData() const
{
    return m_admin->getString("TimeExportData","DefineTime","");
}

void ConfigurationManager::setTimeExportData(QString s)
{
    m_admin->setString("TimeExportData","DefineTime",s);
}

quint8 ConfigurationManager::getNumberDayRemoveFileExport() const
{
    return m_admin->getInt("TimeExportData","DayNumberRemove",7);
}

void ConfigurationManager::setNumberDayRemoveFileExport(quint8 s)
{
    m_admin->setInt("TimeExportData","DayNumberRemove",s);
}

quint32 ConfigurationManager::getFrequencyExportData() const
{
    return m_admin->getInt("TimeExportData","Frequency",0);
}

void ConfigurationManager::setFrequencyExportData(quint32 s)
{
    m_admin->setInt("TimeExportData","Frequency",s);
}

int ConfigurationManager::getTimeDelayToReConnecMQ() const
{
    return m_admin->getInt("HandlingConnect","TimeDelayToReConnectMQ",30000);
}

void ConfigurationManager::setTimeDelayReConnecMQ(int s)
{
    m_admin->setInt("HandlingConnect","TimeDelayToReConnectMQ",s);
}

quint8 ConfigurationManager::getTimesToRestartApp() const
{
    return m_admin->getInt("HandlingConnect","TimesToRestartApp",1);
}

void ConfigurationManager::setTimesToRestartApp(quint8 s)
{
    m_admin->setInt("HandlingConnect","TimesToRestartApp",s);
}
QString ConfigurationManager::getCodeLanguageScreen() const
{
    return m_admin->getString("Language","DefaultLanguage","Vietnam");
}

void ConfigurationManager::setCodeLanguageScreen(QString s)
{
    m_admin->setString("Language","DefaultLanguage",s);
}

QString ConfigurationManager::getCodeChangeLanguageScreen() const
{
    return m_admin->getString("Language","ChangeLanguageScreenCode","");
}

void ConfigurationManager::setCodeChangeLanguageScreen(QString s)
{
    m_admin->setString("Language","ChangeLanguageScreenCode",s);
}

QString ConfigurationManager::getCodePromotionInfoScreen() const
{
    return m_admin->getString("Promotions","PromotionInfoScreenCode","");
}

void ConfigurationManager::setCodePromotionInfoScreen(QString s)
{
    m_admin->setString("Promotions","PromotionInfoScreenCode",s);
}

QString ConfigurationManager::getDisplayLanguage(QString, QString textcode) const
{
    //return m_language->getString("Message",textcode,"");
}

void ConfigurationManager::setDisplayLanguage(QString textcode, QString text)
{
//    m_language->setString("Message",textcode,text);
}

bool ConfigurationManager::getCheckPermissionMultiLanguages() const
{
    return m_admin->getBool("Language","MultiLanguagesPermission",true);
}

void ConfigurationManager::setCheckPermissionMultiLanguages(bool a)
{
    m_admin->setBool("Language","MultiLanguagesPermission",a);
}

QString ConfigurationManager::getPromotionQr() const
{
    return m_admin->getString("Promotions","PromotionQr","");
}

void ConfigurationManager::setPromotionQr(QString s)
{
    m_admin->setString("Promotions","PromotionQr",s);
}

bool ConfigurationManager::getIsReturnGoodByKiosk() const
{
    return m_admin->getBool("AndroidDevice","IsReturnGoodByKiosk",false);
}

void ConfigurationManager::setIsReturnGoodByKiosk(bool a)
{
    m_admin->setBool("AndroidDevice","IsReturnGoodByKiosk",a);
}

//////////end/////////////////

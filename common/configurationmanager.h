#ifndef CONFIGUTILS_H
#define CONFIGUTILS_H

#include "deviceconfig.h"
#include "QCryptographicHash"
#include "QFile"
#include <QStandardPaths>
class ConfigurationManager
{
public:
ConfigurationManager(QString filename="");
~ConfigurationManager();

bool load();
bool loadAdminFile();
bool save();
bool clear();

void loadListBillAmount();

int current_khay;
int current_slot;
int total_page_khay;
int current_page_khay;
int total_page_slot;
int current_page_slot;

QList<QString> listReponseBill;
QList<QString> listAmountResponseBill;

QList<QString> listAcceptBill;
QList<QString> listAmountAcceptBill;


QList<QString> listChargeType;
QList<QString> listBankType;
QList<QString> listWalletType;

void setDefautChargeType();


quint8 getTrayCount() const;
void setTrayCount(quint8 count);

quint8 getGeneralSlotCount() const;
void setGeneralSlotCount(quint8 count);

quint8 getGeneralGoodCount() const;
void setGeneralGoodCount(quint8 count);

quint8 getGeneralGoodMaxCount() const;
void setGeneralGoodMaxCount(quint8 count);

QString getGeneralID() const;
void setGeneralID(QString name);

quint32 getGeneralPrice() const;
void setGeneralPrice(quint32 price);

QString getGeneralName() const;
void setGeneralName(QString name);

quint8 getSlotCountForTray(int tray) const;
void setSlotCountForTray(int tray, quint8 count);

quint8 getMaxCountForTray(int tray) const;
void setMaxCountForTray(int tray, quint8 count);

quint8 getGoodCountForTray(int tray) const;
void setGoodCountForTray(int tray, quint8 count);

QString getGeneralIDForTray(int tray) const;
void setGeneralIDForTray(int tray, QString name);

quint32 getGeneralPriceForTray(int tray) const;
void setGeneralPriceForTray(int tray, quint32 price);

QString getGeneralNameForTray(int tray) const;
void setGeneralNameForTray(int tray, QString name);

QString getseviceCodeForTray(int tray) const;
void setseviceCodeForTray(int tray, QString name);

int getTypeCardMobileForTray(QString) const;
void setTypeCardMobileForTray(QString, int);





QString getIdForSlot(int tray, int slot) const;
void setIdForSlot(int tray, int slot, QString name);

QString getNameForSlot(int tray, int slot) const;
void setNameForSlot(int tray, int slot, QString name);




quint32 getPriceForSlot(int tray, int slot) const;
void setPriceForSlot(int tray, int slot, quint32 price);

//    quint32 getPriceForSlot(int tray, int slot, int i ) const;
//    void setPriceForSlot(int tray, int slot,int i, quint32 price);

//    QString getDateStartForSlot(int tray, int slot, int i) const;
//    void setDateStartForSlot(int tray, int slot, int i, QString name);
//    QString getDateEndForSlot(int tray, int slot, int i) const;
//    void setDateEndForSlot(int tray, int slot, int i, QString name);




int getGoodCountForSlot(int tray, int slot) const;
void setGoodCountForSlot(int tray, int slot, int count);

int getGoodMaxCountForSlot(int tray, int slot) const;
void setGoodMaxCountForSlot(int tray, int slot, int count);

int getPriceMask(int tray, int slot) const;
void setPriceMask(int tray, int slot, int mask);

QString getTextPromotionForSlot(int tray, int slot) const;
void setTextPromotionForSlot(int tray, int slot, QString text);

quint8 getChargeTypeQuatityPermission( int tray, int slot) const;
void setChargeTypeQuatityPermission(int tray, int slot, quint8 quatity);

QString getChargeTypePermission( int tray, int slot, quint8 index) const;
void setChargeTypePermission(int tray, int slot, quint8 index, QString ChargeType);

quint8 getSaleProductPermission( int tray, int slot) const;
void setSaleProductPermission(int tray, int slot, quint8 quatity);

QString getStopProductContent( int tray, int slot) const;
void setStopProductContent(int tray, int slot, QString ChargeType);



quint8 getProductNumber( int tray, int slot) const;
void setProductNumber(int tray, int slot, quint8 quatity);

quint8 getProductChange( int tray, int slot) const;
void setProductChange(int tray, int slot, quint8 quatity);

quint8 getPriorityCharge( int tray, int slot) const;
void setPriorityCharge(int tray, int slot, quint8 quatity);

QString getAdminPwd() const;
void setAdminPwd(QString);

QString getMachineId() const;
void setMachineId(QString);

QString getKioskId() const;
void setKioskId(QString);

QString getVersion() const;
void setVersion(QString);

QString getPasswordEncode() const;
void setPasswordEncode(QString);

QString getMachineClienNumber() const;
void setMachineClientNumber(QString);


bool getBillEnabled() const;
void setBillEnabled(bool);
bool getBillAmountEnabled() const;
void setBillAmountEnabled(bool);
bool getBillResponseEnabled() const;
void setBillResponseEnabled(bool);

bool getCheckScreenTimeout() const;
void setCheckScreenTimeout(bool);

bool getCheckGeneralPrice() const;
void setCheckGeneralPrice(bool);
bool getCheckTrayPrice() const;
void setCheckTrayPrice(bool);
bool getCheckSlotPrice() const;
void setCheckSlotPrice(bool);

bool getCheckTestLoxo() const;
void setCheckTestLoxo(bool a);

bool getCheckMBBank() const;
void setCheckMBBank(bool a);

QString getBillPort() const;
void setBillPort(QString);

int getBillBaudrate() const;
void setBillBaudrate(int);

bool getSensorEnabled() const;
void setSensorEnabled(bool);

QString getSensorPort() const;
void setSensorPort(QString);

int getSensorBaudrate() const;
void setSensorBaudrate(int);

QString getQueueHost() const;
void setQueueHost(QString);

int getQueuePort() const;
void setQueuePort(int);

QString getQueueVHost() const;
void setQueueVHost(QString);

QString getQueueUser() const;
void setQueueUser(QString);

QString getQueuePassword() const;
void setQueuePassword(QString);

QString getQueueExchange() const;
void setQueueExchange(QString);

QString getIpAddress() const;
void setIpAddress(QString);

int getScreenTimeout() const;
void setScreenTimeout(int);

QString getResponse(int) const;
void setResponse(quint8, QString);

int getAmountResponse(QString) const;
void setAmountResponse(QString,int);

int getBillResponseQuatity() const;
void setBillResponseQuatity(int);

QString getAcceptBillResponse(int) const;
int getAmountAcceptBill(QString) const;
int getAcceptBillQuatity() const;

QString getChargeType(int) const;
void setChargeType(int,QString);
int getChargeTypeQuatity() const;
void setChargeTypeQuatity(int);


QString getBankType(int) const;
void setBankType(int,QString);
int getBankTypeQuatity() const;
void setBankTypeQuatity(int);

QString getWalletType(int) const;
void setWalletType(int,QString);
int getWalletTypeQuatity() const;
void setWalletTypeQuatity(int);





quint32 getTrayDigital(QString) const;
void setTrayDigital(QString, int);
QString getMenuDigital() const;
void setMenuDigital(QString);

int getMaxPricePostPaid() const;
void setMaxPricePostPaid(int);

int getMinPricePostPaid() const;
void setMinPricePostPaid(int);

int getMaxPriceCoupon() const;
void setMaxPriceCoupon(int);

int getMinPriceCoupon() const;
void setMinPriceCoupon(int);

bool getCheckHidePin() const;
void setCheckHidePin(bool a);

int getInputMinimumLimit() const;
void setInputMinimumLimit(int);

//V1.1 Bắt đầu
int getSaverScreen() const;
void setSaverScreen(int);
//V1.1 Kết thúc

int getQRCodeTimeout() const;
void setQRCodeTimeout(int);

int getAdminTimeout() const;
void setAdminTimeout(int);

int getGetGoodTimeout() const;
void setGetGoodTimeout(int);
/* V1.0 Bắt đầu chỉnh sửa
     ___________Khai báo hàm. __________*/


int getPriceGoodsMax() const;
void setPriceGoodsMax(int);

int getPriceGoodsMin() const;
void setPriceGoodsMin(int);

int getCoefficient() const;
void setCoefficient(int);

QString getIdAndroidDevice() const;
void setIdAndroidDevice(QString);
QString getTextAndroidDevice() const;
void setTextAndroidDevice(QString) ;

QString getTimeProcessUSB() const;
void setTimeProcessUSB(QString);

QString getTimeExportData() const;
void setTimeExportData(QString);

quint8 getNumberDayRemoveFileExport() const;
void setNumberDayRemoveFileExport(quint8);

quint32 getFrequencyExportData() const;
void setFrequencyExportData(quint32);

int getTimeDelayToReConnecMQ() const;
void setTimeDelayReConnecMQ(int);

quint8 getTimesToRestartApp() const;
void setTimesToRestartApp(quint8);

QString getCodeLanguageScreen() const;
void setCodeLanguageScreen(QString);

QString getCodeChangeLanguageScreen() const;
void setCodeChangeLanguageScreen(QString);

QString getCodePromotionInfoScreen() const;
void setCodePromotionInfoScreen(QString);

QString getDisplayLanguage(QString, QString) const;
void setDisplayLanguage(QString, QString);

bool getCheckPermissionMultiLanguages() const;
void setCheckPermissionMultiLanguages(bool a);

QString getPromotionQr() const;
void setPromotionQr(QString);

bool getIsReturnGoodByKiosk() const;
void setIsReturnGoodByKiosk(bool a);


////////////// Chỉnh sửa xong ///////////////////
QJsonDocument Json(quint8);
QJsonDocument JsonSyncConfig();
DeviceCfg *admin();

private:
QString m_filename;
QString m_status;
//    QList<Khay*> m_ds_khay;
DeviceCfg *m_config;
DeviceCfg *m_admin;
};

#endif // CONFIGUTILS_H

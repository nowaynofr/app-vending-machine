/*Chỉnh sửa bởi Hải
Ngày 25/10/2018
Chức năng: chỉnh sửa lỗi màn hình
Ver: 1.0
File chỉnh sửa: - .../20180704/works/core/kiosk/machine.cpp
                - .../20180704/works/core/kiosk/machine.h
                - .../20180704/works/core/processor/administrator/1100000_good/1110000_auto/1110000_auto_processor.cpp
                - .../20180704/works/core/processor/administrator/1100000_good/1110000_auto/1111000_auto_loading_processor.cpp
                - .../20180704/works/core/processor/administrator/1100000_good/1110000_auto/1112000_auto_failed_processor.cpp
                - .../20180704/works/core/processor/administrator/1100000_good/1110000_auto/1113000_auto_success_processor.cpp
                - .../20180704/works/core/processor/administrator/1500000_system/1540000_admin_system_config_processor.cpp
Nội dung chỉnh sửa: đã coment chi tiết  ở trong code, ảnh đính kèm
Mô tả chỉnh sửa: chỉnh sửa lỗi màn hình.*/

#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include <QDateTime>
//Bổ sung
#include<QFile>
#include<QTextStream>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QVariantMap>

#include "common/deviceconfig.h"
//#include "common/machine_state.h"
//#include <model/khay.h>
#include "Transaction/transaction.h"
#include "Transaction/machine_state.h"
#include "Transaction/billamount.h"

#include <QDir>

#include <common/configurationmanager.h>

#include <Db/db.h>

#include <Transaction/salesession.h>
#include <pushbutton_ok_back.h>

#define ITEMS_PER_PAGE 10
//extern MACHINE_STATE;

class Machine : public QObject
{
    Q_OBJECT
public:
    explicit Machine(QObject *parent = 0);
    ~Machine();

    bool IsReturnGoodByKiosk;

    QString StartTimeSale;
    QString EndTimeSale;
    int TotalAmountSale;
    int TotalBillSale;
    QString StaffCodeSale;

    int SlotTest;
    bool CheckSlotTest;

    int current_page;
    QString dateExport;
    QString timeExport;
    bool    IsSetDateExport;

    quint8 AdminType;

    QJsonDocument JsonSyncConfig();

    MACHINE_STATE state() const;
    MACHINE_STATE last_state() const;


    Transaction* transaction();
    SaleSession* saleSession();
    BillInputAmount* BillAmount();
    bool Check_GetPriceServer;
    bool Check_GetQRCode;

    QList<QString> GetListPartKioskAdmin(QString);
    QList<QString> GetListChargeTypeName( QString);
    QString GetValueKioskAdmin(QString category, QString part);
    void UpdateValueKioskAdmin(QString category, QString part, QString value);
    bool CreatKioskAdmin(QString category, QString part, QString value);



    //V1.2 Bắt đầu
  //  BillInputAmount* BillAmount();
   // MachineStatus* Machine_Status();
    //V1.2 Kết thúc
    void SetListGoodIdPriority();
    QList<QString> ReturnListGooIdPriority();
    void UpdateAdminFile();

    void input_rollback();
    void input_append(QChar c);
    void input_del();
    void input_clean();
    void inputBill(double inputAmount);

    void inputBIllIdentified(double inputAmount);
    void balanceBillAccepted_BillIdentified();
    void BillUnAccepted(double inputamount);

    bool exportToCsv();
    bool CheckExistCsv();

    void CreatDB();
    void UpdateDB();
    void DeleteDB();
    void CreatAndUpdateDB();
    void UpdateBillAvailable();

    //V1.2 Bắt đầu
    void GetTemp(QVariantMap data);
    void errorBill(QString error);
    QString GetBillAmount();
    QString GetBillStatus();

    void CreatErrorKioskTable(QVariantList, QVariantList,QVariantList,QVariantList,QVariantList,QVariantList);
    void DeleteErrorKioskTable();

    QList<QString> GetListErrorCode();
    QList<QString> GetListErrorCodeSorted(QString);
    int GetSignalCountErrorKiosk(QString);
    int GetSignalCountMaxErrorKiosk(QString);
    void UpdateSignalCountErrorKiosk(QString, int);
    void UpdateIncreaseSignalCountErrorKiosk(QString, int);
    void UpdateSignalCountErrorMaxKiosk(QString, int);
    bool CreateErrorKiosk(QString error_code, QString error_code_description, QString error_group, QString error_level, int signal_count, int signal_count_max);
    QList<QString> GetErrorKioskListSortBy();
    void CleanErrorNull(QString);
    void UpdateResetSignalCountErrorKiosk();
  //  void CreatResponseDescriptionTable(QString, QString);

    QString GetErrorSale();
    QString GetSaleMax();
    QString GetSaleStarUsb(QString);
    void GetInfoSale();
    QString GetSaleInfo(QString);

   // QString GetReTransaction(QString);
    int GetIdReTransactionMax();

    QString GetReTransaction(QString, QString);

    //V1.2 Kết thúc

    int  input_length();
    QString current_input() const;
    void set_current_input(QString input);
    ConfigurationManager config;
    void init_transaction();
    void init_transaction_keep_info();
    void cancel_transaction();
    void finish_transaction();
    void init_sale_session();
    void finish_sale_session();
    void finish_sale_month_session();

    bool insertInventoryBatch(QVariantList name_service, QVariantList tray_id, QVariantList slot_id, QVariantList good_id, QVariantList good_name, QVariantList good_price, QVariantList good_count, QVariantList max_count);
    bool insertMenuGood(QVariantList a, QVariantList b, QVariantList c, QVariantList d, QVariantList e, QVariantList f, QVariantList g, QVariantList k,QVariantList l,QVariantList h);
    bool insertMenuGoodGeneral(QVariantList a, QVariantList b, QVariantList c, QVariantList d, QVariantList e,QVariantList q, QVariantList f, QVariantList g, QVariantList k,QVariantList l,QVariantList m);

    bool clearInventory();
    bool cleanMenuGoodTable();
    bool cleanMenuGoodGeneralTable();

    quint8 GetGoodQuatity(QString);
    bool UpdateGoodQuatity(QString,quint8);

    QList<int> getListGoodInventoryTable(QString);
    QList<QString> getListGoodMenu();
    QList<QString> getListGoodId();
    QList<QString> getListGoodType(QString);
    QList<int> getListGoodPrice(QString,QString);
    QList<QString> getListTypeCoupon(QString, QString);
    QString getImageUrlMenuGoodGeneral(QString);

    QString getGoodIdForSlot(QString nameservice, int price) const;
    QString getGoodNameForSlot(QString) const;
    quint32 getGoodPriceForSlot(QString nameservice, int price) const;
    quint32 getTrayForSlot(QString) const;
    quint32 getSlotForSlot(QString) const;
    QString getGoodIdInMenuTable(QString, int);
    QString getGoodId1InMenuTable(QString, QString);
    QString getGoodIdCouponInMenuTable(QString, QString);


    QString getGoodNameInMenuTable(QString);
    QString getNameServerInMenuTable(QString, int);
    QString getNameServer1InMenuTable(QString, QString);
    int getGoodPriceInMenuTable(QString);

    QString getShareSalePermissionInMenuTable(QString);
    QString getShareSalePermissionInMenuGeneralTable(QString);

    QString getListChargeTypeInMenuTable(QString);
    QString getListChargeTypeInMenuGeneralTable(QString);
    quint8 getChargeTypeQuatityInMenuTable(QString);
    quint8 getChargeTypeQuatityInMenuGeneralTable(QString);

    QString getGoodNameInMenuGeneralTable(QString);

    quint32 getGoodPriceInMenuGeneralTable(QString);

signals:
   // void stateChanged(MACHINE_STATE state);
    void stateChanged(QVariantMap data);
    void killApp();
    void killProcessApp();
    void getListUsbPort();
    void mountUsb();
    void syncUsb(QString);
public slots:
    void setState(MACHINE_STATE state);
    void setLastState(MACHINE_STATE state);
    void input(int keycode);
    void KillApp();
    void KillProcessApp();
    void GetListUsbPort();
    void MountUsb();
    void SyncUsb(QString);
protected:

private:
    MACHINE_STATE m_state;
    MACHINE_STATE m_last_state;
    QList<int> ListPriority;
    QList<QString> ListGoodIdPriority;

    Transaction* m_transaction;
    BillInputAmount* m_billvalidator;
    SaleSession* m_sale;

    QString m_last_input;
    QString m_status;
    QString m_current_input;

   // bool IsReturnGoodByKiosk;

    Db m_db;


};

#endif // MACHINE_H

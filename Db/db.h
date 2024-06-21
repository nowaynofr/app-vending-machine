#ifndef DB_H
#define DB_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QTextStream>
#include <Transaction/log.h>
#include <Transaction/param.h>
#include <Transaction/transaction.h>
#include <Transaction/salesession.h>
#include <Transaction/billamount.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <fstream>
class Db : public QObject
{
    Q_OBJECT
public:
    Db();
    ~Db();
    bool openDb();
    void closeDb();
    bool InitDatabase();

    void CreatGoodMenuTable();
    void CreatGoodMenuGeneralTable();
    void CreatKioskAdminTable();
    void InsertAutoKioskAdmin();
    QString getValueKioskAdmin(QString category, QString part) const;
    void UpdateValueKioskAdmin(QString, QString,QString);
    QList<QString> GetListPartKioskAdmin(QString category);
    QList<QString> GetListChargeTypeName(QString category);
    bool CreatKioskAdmin(QString category, QString part, QString value);
    bool insertKioskAdminTable(QVariantList category,
                              QVariantList part,
                               QVariantList value);

    QList<QString> GetListErrorCode();
    QList<QString> GetListErrorCodeSortedByCountMax(QString);
    void UpdateSignalCount(QString,int);
    void UpdateSignalCountMax(QString,int);
    void UpdateResetSignalCounr();
    int GetSignalCount(QString);
    int GetSignalCountMax(QString);
    bool CreateErrorKiosk(QString error_code, QString error_code_description, QString error_group, QString error_level, int signal_count, int signal_count_max);
    QList<QString> GetErrorKioskListSortBy();
    void CleanErrorNull(QString);
    void DeleteErrorKiosk();

    bool CheckDb();
    bool CreateTransaction(Transaction *transaction);
    bool UpdateTransaction(Transaction *transaction);
    bool CreateSaleSession(SaleSession *sale);
    bool UpdateSaleSession(SaleSession *sale);
    bool GetCurrentSaleSession(SaleSession *sale);

    //V1.1 Bắt đầu
    bool CreateBillAmount(BillInputAmount *billvalidator);
    bool UpdateBillAmount(BillInputAmount *billvalidator);
    bool CreateBillStatus(BillInputAmount *billvalidator);
    bool CreateBillDescriptionStatus(QString, QString);


    QString GetBillAmount(QString);
    QString GetDescriptionStatus(QString);
    QString GetBillStatus(QString);

    QString GetErrorSale(QString);
    QString GetSessionIdMax();

    QString GetReTransaction(QString);
    int GetIdReTransactionMax();

    bool CreatBillAvailable(BillInputAmount *billvalidator);
    bool UpdateBillAvailable(BillInputAmount *billvalidator);
    int  GetBillAvailable();

    quint8 GetGoodQuatity(QString);
    bool UpdateGoodQuatity(QString, quint8 quatity);


    bool CheckInitPeriodTable;


    //V1.1 Kết thúc

    bool insertInventoryBatch(QVariantList name_service,
                              QVariantList tray_id,
                              QVariantList slot_id,
                              QVariantList good_id,
                              QVariantList good_name,
                              QVariantList good_price,
                              QVariantList good_count,
                              QVariantList max_count);
    bool insertMenuGoodTable(QVariantList Industry,
                              QVariantList goodType,
                              QVariantList serviceType,
                              QVariantList good_id,
                              QVariantList good_name,
                              QVariantList good_price,
                              QVariantList permission,
                             QVariantList chargetype_quatity,
                             QVariantList list_charge_type,
                             QVariantList share_sale_permission
                             );

    bool insertMenuGoodGeneralTable(QVariantList Industry,
                              QVariantList supplier,
                              QVariantList good_name,
                              QVariantList good_id,
                              QVariantList good_price,
                              QVariantList good_quatity,
                              QVariantList image_url,
                              QVariantList charge_type_quatity,
                             QVariantList list_charge_type,
                              QVariantList priority,
                             QVariantList status);

    bool insertErrorKioskTable(QVariantList error_code,
                              QVariantList error_code_description,
                              QVariantList error_group,
                              QVariantList error_level,
                              QVariantList signal_count,
                              QVariantList signal_count_max);


    bool cleanInventory();
    bool cleanMenuGoodTable();
    bool cleanMenuGoodGeneralTable();

    QList<int> GetListGoodinInventoryTable(QString);
    QList<QString> GetListGoodMenu();
    QList<QString> GetListGoodMenuGeneral();
    QList<int> GetListPriority();
    QList<QString> GetListGoodIdPriority(int);

    QList<QString> GetListGoodId();
    QList<QString> GetListGoodType(QString);
    QList<QString> GetListGoodIdMenuGoodGeneral(QString);
    QList<int> GetListGoodPrice(QString, QString);

    QString getImageUrlMenuGoodGeneral(QString GoodId) const;

    QString getGoodIdForSlot(QString nameservice, int price) const;
    QString getGoodNameForSlot(QString) const;
    QString getGoodCountForSlot(QString nameservice, int price) const;
    QString getGoodMaxCountForSlot(QString nameservice, int price) const;

    QString getGoodIdInMenuTable(QString, int price) const;
    QString getGoodId1InMenuTable(QString, QString) const;
    QString getGoodNameInMenuTable(QString) const;
    QString getGoodNameInMenuGeneralTable(QString) const;
    QString getGoodPriceInMenuGeneralTable(QString) const;
    QString getShareSalePermissionInMenuTable(QString) const;


    QString getServiceTypeInMenuTable(QString, int price) const;
    QString getServiceType1InMenuTable(QString a, QString b) const;
    int getGoodPriceInMenuTable(QString);

    QString getListChargeTypeInMenuTable(QString) const;
    QString getListChargeTypeInMenuGeneralTable(QString) const;
    quint8 getChargeTypeQuatity(QString) const;
    quint8 getChargeTypeQuatityMenuGoodGeneral(QString) const;
    QString getShareSalePermissionInMenuGeneralTable(QString) const;

    int getTrayForSlot(QString) const;
    int getSlotForSlot(QString) const;

    QString getGoodIdCouponInMenuTable(QString a, QString b) const;
    QList<QString> GetListTypeCoupon(QString Industry, QString GoodType);

    bool DeleteTransaction(Transaction *transaction);


    QString escapedCSV(QString);
    bool queryToCsv(QString, QString,QString);

    QList<QString> getReTransaction(QString, QString);

    QSqlDatabase& getDb();

signals:
private:
    QSqlDatabase db;
};

#endif // DB_H

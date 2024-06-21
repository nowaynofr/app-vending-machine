#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Transaction/machine_state.h>
#include "qamqp\qamqpclient.h"
#include "qamqp/qamqpexchange.h"
#include "qamqp/qamqpqueue.h"
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtAndroid>

#include <QDebug>
#include "Process/topup_telco.h"
#include "Process/buy_card.h"
#include "Process/infosale_qr_code.h"
#include "Process/select_service.h"
#include "Process/select_charge_type.h"
#include "Process/qr_code.h"
#include "Process/good_digital_process.h"
#include "Process/get_good_digital.h"
#include "Process/charge_coupon.h"
#include "Process/charged_coupon.h"
#include "Process/pin_user_coupon_sab.h"
#include "Process/topup_partner.h"
#include "Process/menu_good.h"
#include "Process/postpaid.h"
#include "Process/billinfo.h"
#include "Process/menu_good_general.h"
#include "Process/get_good_general.h"
#include "Process/motor_insurance.h"
#include "Process/rfid_data_payment_waitting.h"
#include "Process/rfid_data_processor.h"
#include "Process/charge_mpos_processor.h"
#include "Process/testform.h"

#include "Process/AdminProcess/admin_process.h"
#include "Process/AdminProcess/login_admin.h"
#include "Process/AdminProcess/process_admin_funtion.h"
#include "Process/AdminProcess/process_setting_quantity_funtion.h"

//#include <QNetworkAccessManager>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Transaction/transaction.h"
#include "Machine/machine.h"
#include "Transaction/machinestatus.h"

//#ifdef BILLVALIDATOR_H
#include <Machine/billvalidator.h>
#define BILL_PORT "/dev/ttyS4"
#define BILL_BAUD 115200
//#endif

//#ifdef RS485CONTROLLER_H
#include <Machine/rs485controller.h>
#define KHAYHANG_PORT "/dev/ttyS3"
#define KHAYHANG_BAUD 2400
//#endif

#include "dialog_admin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum URL_IMAGE{
        MENU_GOOD_GENERAL = 0,
        PROMOTION_IMAGE = 1

    };
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initQueueServer();
    QString getId();
    void process_message_MenuGoodTable(QByteArray data);
    void process_message_MenuGoodGeneralTable(QByteArray data);
    void process_message_SetConfigSync(QByteArray data);
    void process_request_VMSSync(QByteArray);
    void getByteArrayListMenuGoodGeneralImage();
    void getByteArrayListPromotionImage();
;protected:
    void keyPressEvent(QKeyEvent *ev);
public slots:
    void setImage();
    void clientConnected() ;
    void clientDisconnected() ;
    void exchangeDeclared() ;
    void queueDeclared() ;
    void queueBound();
    void message_queue_received();
    //nạp tiền điện thoại
    void process_select_service(QString);
    void process_select_good_general(QString);
    void process_state(MACHINE_STATE);

    void GrantPermission();
signals:
    void update_display();
private slots:
    void UpdateMenuGoodGeneral();
    void UpdateDisplay();
    void requestUrl(QString);
    void downloadFinished(QNetworkReply*);
    void input_delay();
    void select_menu_good(QString);

    void ReSendData();
    void ReSendTransaction(QString,QString);

    void ReConnectMQ();
    void Check_Login_Admin(QString,QString);
    void Admin_Login_Success(QString);
    void process_admin(MACHINE_STATE);
    void process_Admin_Funtion(MACHINE_STATE);
    void process_Admin_Setting_Quantity_Funtion(MACHINE_STATE, QString, QString);
//#ifdef BILLVALIDATOR_H
    void onBillAccepted(double amount);

    void onBillIdentified(double amount);

    void onBillUnAccepted(double amount);

    void onBillError(QString amount);
    void ConvertStatusKey(int);
    void ConvertStatus();
    void onBillResponse(QString);


    void onRFID_Data(QString);
    void onStatus(QString);

    void exitApp();
//#endif
private:
//#ifdef BILLVALIDATOR_H
    BillValidator m_khaytien;
//#endif

//#ifdef RS485CONTROLLER_H
    RS485Controller m_khayhang;

    QTimer m_timer;
   // QTimer m_savertimer;
   // QTimer m_delaycoupontimer;
    QTimer m_timer_ReSendData;
    QTimer m_timer_ReconnectMQ;
   // quint8 CheckTimesReconnectMQ;


    Machine*    m_machine;
    QNetworkAccessManager *NetworkAccessManager;
    //xu li man hinh chon dich vu
    QList<QString> list_service;
    QList<QString> list_goodId;
    QList<QString> list_PromotionImage;
    quint8 UrlImageType;

    select_service* SelectService;
    quint8 index_RequestUrl;
    QString DatabaseDataStoragePath;

    select_charge_type* SelectChargeType;
    topup_telco* ScreenTopupTelco;
    buy_card* BuyCardMobile;
    infoSale_qr_code* InfoSaleQrCode;
    QR_code* QR_Code_Screen;
    good_digital_process* Good_Digital_Process;
    get_good_digital* Get_Good_Digital;
    charge_coupon* Charge_Coupon;
    charged_coupon* Charged_Coupon;
    pin_user_coupon_sab* PinUserCouponSab;
    topup_partner* ScreenTopupPartner;
    BillInfo* ScreenBillInfo;
    Menu_Good* ScreenMenuGood;
    Postpaid* ScreenPostPaid;
    menu_good_general* ScreenMenuGoodGeneral;
    Get_Good_General* GetGoodGeneral;
    login_admin* LoginAdminScreen;
    admin_process* SCreenAdminProcess;
    process_admin_funtion* ProcessAdminFuntionSCreen;
    process_setting_quantity_funtion* ProcessSettingQuantityFuntionScreen;
    testform* ScreenTestForm;


    rfid_data_processor* Rfid_Data;
    rfid_data_payment_waitting* Rfid_Data_Payment_Waitting;
    charge_mpos_processor* Charge_mpos;
    motor_insurance* ScreenMotorInsurance;

    // Rabbit MQ
    QAmqpClient m_client;
    bool m_queue_connected;
    QString m_correlationId;
    QAmqpExchange *topic_logs;
    bool CheckReconnectMQ;

   // Dialog_Admin* Admin;
    //QInputMethod *input ;


    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H

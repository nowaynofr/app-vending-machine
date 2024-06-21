#ifndef MACHINE_STATE_H
#define MACHINE_STATE_H

//namespace MACHINE_STATE {
enum MACHINE_STATE{
    INIT = 100,
    SCREEN_GET_QRCODE = 99,
    MENU = 0,
    SELECT_SERVICE = 1,
    BUY_CARD_MOBILE = 2,
    TOPUPTELCO = 3,
    POST_PAID = 4,
    TOPUPPARTNER = 5,
    BILLINFO = 6,
    SELECT_CHARGE_TYPE = 8,
    SALEINFO_QRCODE = 9,
    SCREEN_QRCODE = 10,
    CHARGE_COUPON = 11,
    CHARGED_COUPON = 12,
    PIN_USER_COUPON_SAB = 13,
    RFID_DATA = 14,
    RFID_DATA_PAYMENT_WAITING = 15,
    CHARGE_MPOS = 16,
    GOOD_DIGITAL_PROCESS = 17,
    GET_GOOD_DIGITAL = 18,
    MENU_GOOD_GENERAL = 19,
    GET_GOOD_GENERAL = 20,
    ADMIN_LOGIN = 21,
    ADMIN_PROCESS = 22,
    ADMIN_PROCESS_FUNTION = 23,
    ADMIN_PROCESS_SETTING_QUANTITY_FUNTION = 24,
    MOTOR_INSURANCE = 7,
    TESTFORM =25


};
//}

namespace KioskTransactionType {
enum {

    UNSET = 0,
    SELECT = 100,
    QRBANK = 97,
    DIGITAL_WALLET = 98,
    OTHER = 99,
    CASH = 1,
    QRPAY = 4,
    COUPON = 3,
    QRMB = 5,
    MOMO = 6,
    ZALOPAY = 7,
    GRABPAY = 8,
    VINID = 9,
    MPOS = 12,
    CASHandCOUPON = 13,
    SMARTPAY = 14,
    RFID = 15,
    CASHandQRPAY = 21,
    CASHandMOMO = 22,
    CASHandZALOPAY = 23,
    CASHandGRABPAY = 24,
    CASHandVINID = 25

};
}

namespace KioskCardMobileType {
enum{
    UNSET = 0,
    VIETTEL = 1,
    VINAPHONE = 2,
    MOBIPHONE = 3,
    VIETNAMMOBILE = 4,
    GMOBILE = 5
};
}

enum RECHARGEMOBILETYPE{
    GOOD_GENERAL = 0,
    TOPUP_TELCO = 1,
    POSTPAID = 2,
    BUYCARDMOBILE = 3,
    CARD3G = 4,
    GAMECARD = 5,
    COUPONGENERALSAB = 6,
    COUPONPINSAB = 7,
    COUPONPROMOTIONSAB = 8,
    COUPONRECHARGESAB = 9,
    TOPUP_PARTNER = 10,
    MOTORINSURANCE = 11

};

enum ADMINFUNTIONLIST{
    SYNC = 0,
    SETTING_QUATITY,
    SALE,
    CHECKING_MACHINE,
    SETTING_SYSTEM,
    SYNC_VMS_TO_APP,
    SYNC_APP_TO_VMS,
    GENERAL_SETTING,
    KHAY_SETTING,
    SLOT_SETTING,
    DAY_SALE,
    MONTH_SALE,
    RESEND_SALE,
    RESEND_TRANSACTION,
    EXIT_APP,
    INIT_ADMIN = 99
};

namespace KioskTransactionStatus {
enum {
    ERROR = 0,
    SUCCESS,
    FAILED,
    PAYMENT_WAITING,
    RETURN_GOOD_WAITING,
    CANCEL,
    TIMEOUT,
    NO_RETURN_GOOD,
    INIT = 99

};



}
#endif // MACHINE_STATE_H
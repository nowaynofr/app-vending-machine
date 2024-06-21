QT += core gui network sql androidextras serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Db/db.cpp \
    Machine/billvalidator.cpp \
    Machine/machine.cpp \
    Machine/rs485controller.cpp \
    Process/AdminProcess/admin_process.cpp \
    Process/AdminProcess/login_admin.cpp \
    Process/AdminProcess/process_admin_funtion.cpp \
    Process/AdminProcess/process_setting_quantity_funtion.cpp \
    Process/billinfo.cpp \
    Process/buy_card.cpp \
    Process/charge_coupon.cpp \
    Process/charge_mpos_processor.cpp \
    Process/charged_coupon.cpp \
    Process/get_good_digital.cpp \
    Process/get_good_general.cpp \
    Process/good_digital_process.cpp \
    Process/infosale_qr_code.cpp \
    Process/menu_good.cpp \
    Process/menu_good_general.cpp \
    Process/motor_insurance.cpp \
    Process/pin_user_coupon_sab.cpp \
    Process/postpaid.cpp \
    Process/qr_code.cpp \
    Process/rfid_data_payment_waitting.cpp \
    Process/rfid_data_processor.cpp \
    Process/select_charge_type.cpp \
    Process/select_service.cpp \
    Process/testform.cpp \
    Process/topup_partner.cpp \
    Process/topup_telco.cpp \
    Transaction/billamount.cpp \
    Transaction/machinestatus.cpp \
    Transaction/salesession.cpp \
    Transaction/stringutils.cpp \
    Transaction/transaction.cpp \
    common/configurationmanager.cpp \
    common/deviceconfig.cpp \
    dialog_admin.cpp \
    main.cpp \
    mainwindow.cpp \
    my_qlabel.cpp \
    my_qlineedit.cpp \
    my_qspinbox.cpp \
    pushbutton_ok_back.cpp \
    qamqp/qamqpauthenticator.cpp \
    qamqp/qamqpchannel.cpp \
    qamqp/qamqpchannelhash.cpp \
    qamqp/qamqpclient.cpp \
    qamqp/qamqpexchange.cpp \
    qamqp/qamqpframe.cpp \
    qamqp/qamqpmessage.cpp \
    qamqp/qamqpqueue.cpp \
    qamqp/qamqptable.cpp \
    qrcode/BitBuffer.cpp \
    qrcode/QrCode.cpp \
    qrcode/QrSegment.cpp

HEADERS += \
    Db/db.h \
    Machine/billvalidator.h \
    Machine/machine.h \
    Machine/rs485controller.h \
    Process/AdminProcess/admin_process.h \
    Process/AdminProcess/login_admin.h \
    Process/AdminProcess/process_admin_funtion.h \
    Process/AdminProcess/process_setting_quantity_funtion.h \
    Process/billinfo.h \
    Process/buy_card.h \
    Process/charge_coupon.h \
    Process/charge_mpos_processor.h \
    Process/charged_coupon.h \
    Process/get_good_digital.h \
    Process/get_good_general.h \
    Process/good_digital_process.h \
    Process/infosale_qr_code.h \
    Process/menu_good.h \
    Process/menu_good_general.h \
    Process/motor_insurance.h \
    Process/pin_user_coupon_sab.h \
    Process/postpaid.h \
    Process/qr_code.h \
    Process/rfid_data_payment_waitting.h \
    Process/rfid_data_processor.h \
    Process/select_charge_type.h \
    Process/select_service.h \
    Process/testform.h \
    Process/topup_partner.h \
    Process/topup_telco.h \
    Transaction/billamount.h \
    Transaction/log.h \
    Transaction/machine_state.h \
    Transaction/machinestatus.h \
    Transaction/param.h \
    Transaction/salesession.h \
    Transaction/stringutils.h \
    Transaction/transaction.h \
    common/configurationmanager.h \
    common/deviceconfig.h \
    dialog_admin.h \
    mainwindow.h \
    my_qlabel.h \
    my_qlineedit.h \
    my_qspinbox.h \
    pushbutton_ok_back.h \
    qamqp/qamqpauthenticator.h \
    qamqp/qamqpchannel.h \
    qamqp/qamqpchannel_p.h \
    qamqp/qamqpchannelhash_p.h \
    qamqp/qamqpclient.h \
    qamqp/qamqpclient_p.h \
    qamqp/qamqpexchange.h \
    qamqp/qamqpexchange_p.h \
    qamqp/qamqpframe_p.h \
    qamqp/qamqpglobal.h \
    qamqp/qamqpmessage.h \
    qamqp/qamqpmessage_p.h \
    qamqp/qamqpqueue.h \
    qamqp/qamqpqueue_p.h \
    qamqp/qamqptable.h \
    qrcode/BitBuffer.h \
    qrcode/QrCode.h \
    qrcode/QrSegment.h

FORMS += \
    Process/AdminProcess/admin_process.ui \
    Process/AdminProcess/login_admin.ui \
    Process/AdminProcess/process_admin_funtion.ui \
    Process/AdminProcess/process_setting_quantity_funtion.ui \
    Process/billinfo.ui \
    Process/buy_card.ui \
    Process/charge_coupon.ui \
    Process/charge_mpos_processor.ui \
    Process/charged_coupon.ui \
    Process/get_good_digital.ui \
    Process/get_good_general.ui \
    Process/good_digital_process.ui \
    Process/infosale_qr_code.ui \
    Process/menu_good.ui \
    Process/menu_good_general.ui \
    Process/motor_insurance.ui \
    Process/pin_user_coupon_sab.ui \
    Process/postpaid.ui \
    Process/qr_code.ui \
    Process/rfid_data_payment_waitting.ui \
    Process/rfid_data_processor.ui \
    Process/select_charge_type.ui \
    Process/select_service.ui \
    Process/testform.ui \
    Process/topup_partner.ui \
    Process/topup_telco.ui \
    dialog_admin.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    admin.ini \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    database

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
android
{
my_files.path = /assets
my_files.files = $$PWD/database
INSTALLS += my_files
QT += androidextras
}


contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
android: include(D:\downloads\android_openssl-master\openssl.pri)

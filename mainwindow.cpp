#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_machine(new Machine(this))
    ,m_queue_connected(false)
    ,CheckReconnectMQ(false)
    ,m_timer(this),

    //V1.1 Bắt đầu
  //  m_savertimer(this),
   // m_delaycoupontimer(this),
    m_timer_ReSendData(this),
    //CheckTimesReconnectMQ(0),
    m_timer_ReconnectMQ(this)
{
    LOG<<"Start Machine";
    ui->setupUi(this);
    index_RequestUrl = UrlImageType = 0;
    list_PromotionImage = m_machine->GetValueKioskAdmin("UrlPromotionImage","UrlPromotionImageList").split(QLatin1Char(','));
    DatabaseDataStoragePath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
    m_machine->transaction()->MachineId = getId();
    m_machine->saleSession()->MachineId = m_machine->transaction()->MachineId;
    m_machine->BillAmount()->MachineId = m_machine->transaction()->MachineId;
    m_machine->config.setMachineId(m_machine->transaction()->MachineId);
    m_machine->transaction()->KioskId = m_machine->config.getKioskId();
    m_machine->config.save();
    LOG<<m_machine->config.getMachineId()<<m_machine->config.getScreenTimeout()<<m_machine->transaction()->KioskId<<"djfdfj";

//#ifdef BILLVALIDATOR_H
    connect(&m_khaytien, SIGNAL(bill_accepted(double)), this, SLOT(ConvertStatus()));

    connect(&m_khaytien, SIGNAL(bill_accepted(double)), this, SLOT(onBillAccepted(double)));

    connect(&m_khaytien, SIGNAL(bill_identified(double)), this, SLOT(onBillIdentified(double)));

    connect (&m_khaytien, SIGNAL(bill_unAccepted(double)),this, SLOT(onBillUnAccepted(double)));
    connect(&m_khaytien, SIGNAL(bill_error(QString)), this, SLOT(onBillError(QString)));
    connect(&m_khaytien, SIGNAL(bill_status(QString)), this, SLOT(onBillResponse(QString)));

    connect(&m_khaytien, SIGNAL(bill_response(QString)), this, SLOT(onBillResponse(QString)));


    m_khaytien.setup(BILL_PORT, BILL_BAUD);

    if (m_machine->config.getBillEnabled())
        m_khaytien.start();


//#endif

//#ifdef RS485CONTROLLER_H
    //connect(&m_khayhang, SIGNAL(statusChange(QVariantMap)), this, SLOT(onMachineStatusChange(QVariantMap)));
    connect(&m_khayhang, SIGNAL(RFID_Data(QString)), this, SLOT(onRFID_Data(QString)));
   // connect(&m_khayhang, SIGNAL(status(QString)), this, SLOT(onStatus(QString)));
    m_khayhang.setup(KHAYHANG_PORT, KHAYHANG_BAUD);
    if (m_machine->config.getSensorEnabled())
        m_khayhang.start();
//#endif
    m_timer.setInterval(m_machine->config.getScreenTimeout());
    m_timer.setSingleShot(true);
    connect (&m_timer, SIGNAL(timeout()), this, SLOT(input_delay()));
    m_timer_ReconnectMQ.setInterval(30000);
    m_timer_ReconnectMQ.setSingleShot(true);
    m_timer_ReconnectMQ.stop();
    connect(&m_timer_ReconnectMQ, SIGNAL(timeout()), this, SLOT(ReConnectMQ()));

    QTime current_time = QTime::fromString(QTime::currentTime().toString("HH:mm:ss"));
    QTime define_time = QTime::fromString(m_machine->config.getTimeExportData(),"HH:mm:ss");
    qint32 time = current_time.msecsTo(define_time);
    if(time < 0){
        time += 86400000;
    }
    LOG<< time <<"thời gian đến thời điểm gửi lại số liệu";

    m_timer_ReSendData.setInterval(time);
    m_timer_ReSendData.start();
    connect(&m_timer_ReSendData, SIGNAL(timeout()), this, SLOT(ReSendData()));

  //  setImage();
    connect(this, SIGNAL(update_display()),this, SLOT(UpdateDisplay()));
    NetworkAccessManager = new QNetworkAccessManager(this);
    connect(NetworkAccessManager, &QNetworkAccessManager::finished, this, &MainWindow::downloadFinished);
    UpdateDisplay();

//    Admin = new Dialog_Admin(this);
//    connect(Admin, SIGNAL(AdminProcess()), this, SLOT(Admin_Process()));
//    Admin->PassAdmin = m_machine->config.getAdminPwd();
//    Admin->hide();
  //  GrantPermission();
    initQueueServer();
}
MainWindow::~MainWindow()
{
    delete ui;
    delete m_machine;
    delete SelectService;
    delete SelectChargeType;
    delete ScreenTopupTelco;
    delete InfoSaleQrCode;
    delete QR_Code_Screen;
    delete Good_Digital_Process;
    delete Get_Good_Digital;
    delete Charge_Coupon;
    delete Charged_Coupon;
    delete ScreenTopupPartner;
    delete ScreenMenuGood;
    delete PinUserCouponSab;
    delete BuyCardMobile;
    delete ScreenPostPaid;
    delete ScreenBillInfo;
    delete ScreenMenuGoodGeneral;
    delete GetGoodGeneral;
    delete ScreenMotorInsurance;
    delete ScreenTestForm;

    delete SCreenAdminProcess;
    delete ProcessAdminFuntionSCreen;
    delete LoginAdminScreen;
    delete ProcessSettingQuantityFuntionScreen;


    delete Rfid_Data;
    delete Rfid_Data_Payment_Waitting;
    delete Charge_mpos;
}

void MainWindow::initQueueServer()
{
   // m_client.setHost("mqsrvtest.sab.com.vn");
  //  m_client.setPassword("ejMUe>X32B^wRbs");

//    m_client.setHost("mqsrv.sab.com.vn");
//    m_client.setPassword("+E!H>=7x]tZ$$2ggR21@M&");

 //   m_client.setHost("210.245.26.34");
 //   m_client.setPassword("P@sslaginhi*2020");
//    m_client.setVirtualHost("/");
//    m_client.setPort(5672);
//    m_client.setUsername("kiosk");
//    m_client.setAutoReconnect(true);
//    m_client.setWriteTimeout(-2);
//    connect(&m_client, SIGNAL(connected()), this, SLOT(clientConnected()), Qt::UniqueConnection);
//    connect(&m_client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()), Qt::UniqueConnection);
//    m_queue_connected = false;
//    m_client.connectToHost();

    m_client.setHost(m_machine->config.getQueueHost());
    m_client.setVirtualHost(m_machine->config.getQueueVHost());
    m_client.setPort(m_machine->config.getQueuePort());
    m_client.setUsername(m_machine->config.getQueueUser());
    QByteArray password = QByteArray::fromBase64(m_machine->config.getQueuePassword().toUtf8());
    m_client.setPassword(QString(password));
    m_client.setAutoReconnect(true);
    m_client.setWriteTimeout(-2);
    connect(&m_client, SIGNAL(connected()), this, SLOT(clientConnected()), Qt::UniqueConnection);
    connect(&m_client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()), Qt::UniqueConnection);
    m_queue_connected = false;
    m_client.connectToHost();
}
QString MainWindow::getId()
{
    QAndroidJniObject stringNumber = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/bindings/SAB",
                                                                               "getSerialNumber",
                                                                               "(I)Ljava/lang/String;",
                                                                               1);
    QString Id = stringNumber.toString();
    qDebug()<<Id<<"Ma May";
    return Id;
}

void MainWindow::process_message_MenuGoodTable(QByteArray data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject docobj = doc.object();
    if (!docobj["MenuGood"].isObject()){
        return;
    }
    if(docobj.contains("MenuGood")){
        QJsonObject obj = docobj["MenuGood"].toObject();
        LOG;
        m_machine->cleanMenuGoodTable();
        QVariantList Industry;
        QVariantList goodType;
        QVariantList serviceType;
        QVariantList good_id;
        QVariantList good_name;
        QVariantList good_price;
        QVariantList permission;
        QVariantList charge_type_quatity;
        QVariantList list_charge_type;
        QVariantList share_sale_permission;

        if (obj.contains("menu") && obj["menu"].isArray()) {
            QJsonArray menuArray = obj["menu"].toArray();
            for (int i = 0; i < menuArray.size(); ++i) {
                QJsonObject menuObject = menuArray[i].toObject();
                if (menuObject.contains("Industry") && menuObject["Industry"].isString()){
                    Industry << menuObject["Industry"].toString();
                } else
                    Industry << "";
                if (menuObject.contains("goodType") && menuObject["goodType"].isString()){
                    goodType << menuObject["goodType"].toString();
                } else
                    goodType << "";
                if (menuObject.contains("serviceType") && menuObject["serviceType"].isString()){
                    serviceType << menuObject["serviceType"].toString();
                } else
                    serviceType << "";
                if (menuObject.contains("good_id") && menuObject["good_id"].isString()){
                    good_id << menuObject["good_id"].toString();
                } else
                    good_id << "";
                if (menuObject.contains("good_name") && menuObject["good_name"].isString()){
                    good_name << menuObject["good_name"].toString();
                } else
                    good_name << "";
                if (menuObject.contains("good_price") && menuObject["good_price"].isDouble()){
                    good_price << menuObject["good_price"].toInt();
                } else
                    good_price << "";
                if (menuObject.contains("share_sale_permission") && menuObject["share_sale_permission"].isString()){
                    share_sale_permission << menuObject["share_sale_permission"].toString();
                } else
                    share_sale_permission << "";
                if (menuObject.contains("permission") && menuObject["permission"].isString()){
                    permission << menuObject["permission"].toString();
                } else
                    permission << "";

                if (menuObject.contains("ChargeTypeQuatity") && menuObject["ChargeTypeQuatity"].isDouble()){
                    quint8 quatity = menuObject["ChargeTypeQuatity"].toDouble();
                    QJsonObject chargeType = menuObject["ChargeType"].toObject();
                    charge_type_quatity << menuObject["ChargeTypeQuatity"].toDouble();
                    if(quatity != 0){
                        QString ListChargeType = "";

                        for(int i=1;i <= quatity;i++){
                            if(ListChargeType == "")
                                ListChargeType.append(QString::number(chargeType["ChargeType"+QString::number(i)].toInt()));
                            else
                                ListChargeType.append("," + QString::number(chargeType["ChargeType"+QString::number(i)].toInt()));
                        }
                        list_charge_type<<ListChargeType;
                    }else{
                        list_charge_type << "";
                    }

                }else{
                    list_charge_type << "";
                    charge_type_quatity << 0;
                }

            }
        }


        if (m_machine->insertMenuGood(Industry, goodType, serviceType,
                                            good_id, good_name, good_price,
                                            permission,charge_type_quatity,list_charge_type,share_sale_permission)) {
            LOG<<"update MenuGoodTable success";
        }
    }
}

void MainWindow::process_message_MenuGoodGeneralTable(QByteArray data)
{
    if(m_timer_ReconnectMQ.isActive())
        m_timer_ReconnectMQ.stop();
   // m_machine->UpdateSignalCountErrorKiosk("kiosk101",0);
   // m_machine->UpdateSignalCountErrorKiosk("kiosk113",0);
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject docobj = doc.object();

    LOG << docobj["machine"].isUndefined() << docobj["machine"].isObject() << docobj["machine"].isString();
    if (!docobj["machine"].isObject()){
//        if (docobj.contains("description") && !docobj["description"].isNull() && docobj["description"].isString()){
//            m_machine->transaction()->MessageRechargeMobile  = docobj["description"].toString();
//            LOG<<m_machine->transaction()->MessageRechargeMobile;
//        }
//        m_machine->input(Qt::Key_L);
        return;
    }
    QJsonObject obj = docobj["machine"].toObject();

    QVariantList Industry;
    QVariantList supplier;
    QVariantList good_name;
    QVariantList good_id;
    QVariantList good_price;
    QVariantList good_quatity;
    QVariantList priority;
    QVariantList image_url;
    QVariantList charge_type_quatity;
    QVariantList list_charge_type;
    QVariantList status;

    m_machine->config.clear();
    list_goodId.clear();
    if (obj.contains("GeneralId") && obj["GeneralId"].isString()){
        LOG<<"fffff";
        m_machine->config.setGeneralID(obj["GeneralId"].toString());
    }
    if (obj.contains("GeneralPrice") && obj["GeneralPrice"].isDouble()){
        m_machine->config.setGeneralPrice(obj["GeneralPrice"].toInt());
    }
    if (obj.contains("SlotCount") && obj["SlotCount"].isDouble()){
        m_machine->config.setGeneralSlotCount(obj["SlotCount"].toInt());
    }
    if (obj.contains("TrayCount") && obj["TrayCount"].isDouble()){
        m_machine->config.setTrayCount(obj["TrayCount"].toInt());
    }
    if (obj.contains("GoodCount") && obj["GoodCount"].isDouble()){
        m_machine->config.setGeneralGoodCount(obj["GoodCount"].toInt());
    }
    if (obj.contains("GoodMaxCound") && obj["GoodMaxCound"].isDouble()){
        m_machine->config.setGeneralGoodMaxCount(obj["GoodMaxCound"].toInt());
    }

    LOG << "Update tray";
    if (obj.contains("khays") && obj["khays"].isArray()) {
        LOG << "Update tray2";
        QJsonArray trayArray = obj["khays"].toArray();
        for (int i = 0; i < trayArray.size(); ++i) {
            QJsonObject trayObject = trayArray[i].toObject();
            if (!trayObject.contains("name") ) continue;
            bool ok = false;
            int tray  = trayObject["name"].toString().mid(5).toInt(&ok);
            if (!ok || tray < 0) continue;
            LOG << "Update tray" << tray;
            if (trayObject.contains("GeneralCode") && trayObject["GeneralCode"].isString()){
                m_machine->config.setGeneralIDForTray(tray,trayObject["GeneralCode"].toString());
            }
            if (trayObject.contains("GeneralName") && trayObject["GeneralName"].isString()){
                m_machine->config.setGeneralNameForTray(tray,trayObject["GeneralName"].toString());
            }
            if (trayObject.contains("GeneralPrice") && trayObject["GeneralPrice"].isDouble()){
                m_machine->config.setGeneralPriceForTray(tray,trayObject["GeneralPrice"].toInt());
            }
            if (trayObject.contains("SlotCount") && trayObject["SlotCount"].isDouble()){
                m_machine->config.setSlotCountForTray(tray,trayObject["SlotCount"].toInt());
            }
            if (trayObject.contains("GoodMaxCound") && trayObject["GoodMaxCound"].isDouble()){
                m_machine->config.setMaxCountForTray(tray,trayObject["GoodMaxCound"].toInt());
            }


            if (trayObject.contains("slots") && trayObject["slots"].isArray()) {
                QJsonArray slotArray = trayObject["slots"].toArray();
                for (int i = 0; i < slotArray.size(); ++i) {
                    QJsonObject slotObject = slotArray[i].toObject();
                    if (!slotObject.contains("name") ) continue;
                    bool ok = false;
                    QString slotStr = slotObject["name"].toString();
                    int slot  = slotStr.mid(slotStr.indexOf("_Slot_")+6).toInt(&ok);
                    if (!ok || slot < 0) continue;
                    LOG << "Update tray " << tray << "slot" << slot;
                    if (slotObject.contains("GoodCode") && slotObject["GoodCode"].isString()){
                        LOG << "Update tray " << slotObject["GoodCode"].toString();
                        m_machine->config.setIdForSlot(tray,slot ,slotObject["GoodCode"].toString());
                    }
                    if (slotObject.contains("GoodName") && slotObject["GoodName"].isString()){
                        m_machine->config.setNameForSlot(tray,slot ,slotObject["GoodName"].toString());
                    }
                    if (slotObject.contains("GoodPrice") && slotObject["GoodPrice"].isDouble()){
                        m_machine->config.setPriceForSlot(tray,slot ,slotObject["GoodPrice"].toInt());
                    }
                    if (slotObject.contains("GoodCount") && slotObject["GoodCount"].isDouble()){
                        m_machine->config.setGoodCountForSlot(tray,slot ,slotObject["GoodCount"].toInt());
                    }
                    if (slotObject.contains("GoodMaxCound") && slotObject["GoodMaxCound"].isDouble()){
                        m_machine->config.setGoodMaxCountForSlot(tray,slot ,slotObject["GoodMaxCound"].toInt());
                    }

                    if (slotObject.contains("priceMask") && slotObject["priceMask"].isDouble()){
                        m_machine->config.setPriceMask(tray,slot ,slotObject["priceMask"].toDouble());
                    }
                    if (slotObject.contains("ChargeTypeQuatity") && slotObject["ChargeTypeQuatity"].isDouble()){
                        quint8 quatity = slotObject["ChargeTypeQuatity"].toDouble();
                        QJsonObject chargeType = slotObject["ChargeType"].toObject();
                        m_machine->config.setChargeTypeQuatityPermission(tray,slot ,slotObject["ChargeTypeQuatity"].toDouble());
                        if(quatity != 0){
                            for(int i=1;i <= quatity;i++){
                                m_machine->config.setChargeTypePermission(tray,slot,i,QString::number(chargeType["ChargeType"+QString::number(i)].toInt()));
                            }
                        }

                    }
                    bool flag = true;
                    if (slotObject.contains("GoodCode") && slotObject["GoodCode"].isString()){
                        if(good_id.contains(slotObject["GoodCode"].toString())){
                            flag = false;
                        }else{
                            good_id << slotObject["GoodCode"].toString();
                        }
                    } else
                        good_id << "";
                    if(flag){
                        if(slotObject.contains("Industry") && slotObject["Industry"].isString()){
                            Industry << slotObject["Industry"].toString();
                        }else
                            Industry << "";
                        if (slotObject.contains("supplier") && slotObject["supplier"].isString()){
                            supplier << slotObject["supplier"].toString();
                        } else
                            supplier << "";
                        if (slotObject.contains("image_url") && slotObject["image_url"].isString()){
                            image_url << slotObject["image_url"].toString();
                            if(slotObject.contains("GoodCode") && slotObject["GoodCode"].isString()){
                                if(slotObject["image_url"].toString() != m_machine->getImageUrlMenuGoodGeneral(slotObject["GoodCode"].toString())){
                                    list_goodId.append(slotObject["GoodCode"].toString());
                                }
                            }
                        } else
                            image_url << "";

                        if (slotObject.contains("GoodName") && slotObject["GoodName"].isString()){
                            good_name << slotObject["GoodName"].toString();
                        } else
                            good_name << "";
                        if (slotObject.contains("GoodPrice") && slotObject["GoodPrice"].isDouble()){
                            good_price << slotObject["GoodPrice"].toInt();
                        } else
                            good_price << "";
                        if (slotObject.contains("GoodCount") && slotObject["GoodCount"].isDouble()){
                            good_quatity << slotObject["GoodCount"].toInt();
                        } else
                            good_quatity << 0;

                        if (slotObject.contains("priority") && slotObject["priority"].isDouble()){
                            priority << slotObject["priority"].toInt();
                        } else
                            priority << 99;

//                        if (slotObject.contains("status") && slotObject["status"].isString()){
//                            status << slotObject["status"].toString();
//                        } else
//                            status << "";
                        status << "sale";
                        if (slotObject.contains("ChargeTypeQuatity") && slotObject["ChargeTypeQuatity"].isDouble()){
                            quint8 quatity = slotObject["ChargeTypeQuatity"].toDouble();
                            QJsonObject chargeType = slotObject["ChargeType"].toObject();
                            charge_type_quatity << slotObject["ChargeTypeQuatity"].toDouble();
                            if(quatity != 0){
                                QString ListChargeType = "";

                                for(int i=1;i <= quatity;i++){
                                    if(ListChargeType == "")
                                        ListChargeType.append(QString::number(chargeType["ChargeType"+QString::number(i)].toInt()));
                                    else
                                        ListChargeType.append("," + QString::number(chargeType["ChargeType"+QString::number(i)].toInt()));
                                }
                                list_charge_type<<ListChargeType;
                            }else{
                                list_charge_type << "";
                            }

                        }else{
                            list_charge_type << "";
                            charge_type_quatity << 0;
                        }
                    }else{
                        int quatity = 0;
                        if(good_id.indexOf(slotObject["GoodCode"].toString()) >= 0)
                            quatity = good_quatity.at(good_id.indexOf(slotObject["GoodCode"].toString())).toInt();
                        if (slotObject.contains("GoodCount") && slotObject["GoodCount"].isDouble()){
                            quatity += slotObject["GoodCount"].toInt();
                            good_quatity.replace(good_id.indexOf(slotObject["GoodCode"].toString()), quatity);
                        } //else
                            //good_quatity << 0;
                    }

                    if (slotObject.contains("productNumber") && slotObject["productNumber"].isDouble()){
                        m_machine->config.setProductNumber(tray,slot ,slotObject["productNumber"].toDouble());
                    }
                    if (slotObject.contains("prodnumChange") && slotObject["prodnumChange"].isDouble()){
                        m_machine->config.setProductChange(tray,slot ,slotObject["prodnumChange"].toDouble());
                    }

                    if (slotObject.contains("StopProductId") && slotObject["StopProductId"].isString()){
                        m_machine->config.setStopProductContent(tray,slot ,slotObject["StopProductId"].toString());
                    }

                    if (slotObject.contains("prioritycharge") && slotObject["prioritycharge"].isDouble()){
                        m_machine->config.setPriorityCharge(tray,slot ,slotObject["prioritycharge"].toDouble());
                    }

//                    if (slotObject.contains("promotion") && slotObject["promotion"].isDouble()){
//                        m_machine->config.setPromotion(tray,slot ,slotObject["promotion"].toDouble());
//                    }

//                    if (slotObject.contains("ShareSale") && slotObject["ShareSale"].isDouble()){
//                        m_machine->config.setShareSalePermission(tray,slot ,slotObject["ShareSale"].toDouble());
//                    }

                }
            }
        }
    }

    if (m_machine->config.save()) {
        LOG<<"cập nhật quy cách thành công";
    }


    m_machine->cleanMenuGoodGeneralTable();
    if (m_machine->insertMenuGoodGeneral(Industry, supplier, good_name,
                                        good_id, good_price,good_quatity, image_url,
                                        charge_type_quatity,list_charge_type,priority,status)) {
//        if(m_machine->state() == MACHINE_STATE::ADMIN_PROCESS){
//            SCreenAdminProcess->ProcessAdminSuccess();
//        }
        m_machine->SetListGoodIdPriority();
        if(list_goodId.size() != 0){
            UrlImageType = URL_IMAGE::MENU_GOOD_GENERAL;
            getByteArrayListMenuGoodGeneralImage();
        }

        LOG<<"update MenuGoodGeneralTable success";
    }
}

void MainWindow::process_message_SetConfigSync(QByteArray data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject docobject = doc.object();

    if (!docobject[QString("admin")].isObject()){
        return;
    }
    QJsonObject docobj = docobject[QString("admin")].toObject();
    if (docobj[QString("Administrator")].isObject()){
        QJsonObject obj = docobj[QString("Administrator")].toObject();
        if(obj[QString("MachineID")].isString() && !obj[QString("MachineID")].isNull())
            m_machine->config.setMachineClientNumber(obj[QString("MachineID")].toString());
        if(obj[QString("NetworkCard")].isString() && !obj[QString("NetworkCard")].isNull())
            m_machine->config.setIpAddress(obj[QString("NetworkCard")].toString());
       // QByteArray password = QByteArray::fromBase64(obj[QString("Password")].toString().toUtf8());
        if(obj[QString("Password")].isString() && !obj[QString("Password")].isNull())
            m_machine->config.setAdminPwd(obj[QString("Password")].toString());
       // QByteArray passwordEncode = QByteArray::fromBase64(obj[QString("PasswordEncode")].toString().toUtf8());
        if(obj[QString("PasswordEncode")].isString() && !obj[QString("PasswordEncode")].isNull())
            m_machine->UpdateValueKioskAdmin("Administrator","PasswordEncode",obj[QString("PasswordEncode")].toString());
           // m_machine->config.setPasswordEncode(obj[QString("PasswordEncode")].toString());
        if(obj[QString("Version")].isString() && !obj[QString("Version")].isNull())
            m_machine->config.setVersion(obj[QString("Version")].toString());
    }

    if (docobj[QString("AndroidDevice")].isObject()){
        QJsonObject obj = docobj[QString("AndroidDevice")].toObject();
        if(obj[QString("IdDevice")].isString() && !obj[QString("IdDevice")].isNull())
            m_machine->config.setIdAndroidDevice(obj[QString("IdDevice")].toString());
    }


    if (docobj[QString("Bill")].isObject()){
        QJsonObject obj = docobj[QString("Bill")].toObject();
        if(obj[QString("Baudrate")].isDouble() && !obj[QString("Baudrate")].isNull())
            m_machine->config.setBillBaudrate(obj[QString("Baudrate")].toString().toInt());
        if(obj[QString("BillAmount")].isString() && !obj[QString("BillAmount")].isNull()){
            if(obj[QString("BillAmount")].toString().contains("true")){
                 m_machine->config.setBillAmountEnabled(true);
            }else if(obj[QString("BillAmount")].toString().contains("false")){
                m_machine->config.setBillAmountEnabled(false);
            }
        }
        if(obj[QString("BillResponse")].isString() && !obj[QString("BillResponse")].isNull()){
            if(obj[QString("BillResponse")].toString().contains("true")){
                m_machine->config.setBillResponseEnabled(true);
            }else if(obj[QString("BillResponse")].toString().contains("false")){
                m_machine->config.setBillResponseEnabled(false);
            }
        }
        if(obj[QString("Enable")].isString() && !obj[QString("Enable")].isNull()){
            if(obj[QString("Enable")].toString().contains("true")){
                m_machine->config.setBillEnabled(true);
            }else if(obj[QString("Enable")].toString().contains("false")){
                m_machine->config.setBillEnabled(false);
            }
        }
        if(obj[QString("Port")].isString() && !obj[QString("Port")].isNull())
            m_machine->config.setBillPort(obj[QString("Port")].toString());
    }

    if (docobj[QString("BillResponse")].isObject()){
        QJsonObject obj = docobj[QString("BillResponse")].toObject();
        for(int i = 1; i <= obj[QString("ResponseQuatity")].toString().toInt(); i++){
            if(obj[QString("Response"+QString::number(i))].isString() && !obj["Response"+QString::number(i)].isNull())
                m_machine->config.setResponse(i, obj["Response"+QString::number(i)].toString());
        }
        if(obj[QString("ResponseQuatity")].isDouble() && !obj[QString("ResponseQuatity")].isNull())
            m_machine->config.setBillResponseQuatity(obj[QString("ResponseQuatity")].toString().toInt());
    }

    if (docobj[QString("ChargeTypeCodeName")].isObject()){
        QJsonObject obj = docobj[QString("ChargeTypeCodeName")].toObject();
        QList<QString> listKey;
        listKey.clear();
        listKey = obj.keys();
        for(int i = 0; i < listKey.size(); i++){
            if(obj[listKey.at(i)].isString() && !obj[listKey.at(i)].isNull()){
                if(m_machine->GetListChargeTypeName("ChargeTypeCodeName").contains(listKey.at(i))){
                    m_machine->UpdateValueKioskAdmin("ChargeTypeCodeName",listKey.at(i),obj[listKey.at(i)].toString());
                }else{
                    m_machine->CreatKioskAdmin("ChargeTypeCodeName", listKey.at(i),obj[listKey.at(i)].toString());
                }
            }
        }
    }

    if (docobj[QString("ChargeTypeImageName")].isObject()){
        QJsonObject obj = docobj[QString("ChargeTypeImageName")].toObject();
        QList<QString> listKey;
        listKey.clear();
        listKey = obj.keys();
        for(int i = 0; i < listKey.size(); i++){
            if(obj[listKey.at(i)].isString() && !obj[listKey.at(i)].isNull()){
                if(m_machine->GetListChargeTypeName("ChargeTypeImageName").contains(listKey.at(i))){
                    m_machine->UpdateValueKioskAdmin("ChargeTypeImageName",listKey.at(i),obj[listKey.at(i)].toString());
                }else{
                    m_machine->CreatKioskAdmin("ChargeTypeImageName", listKey.at(i),obj[listKey.at(i)].toString());
                }
            }
        }
//        for(int i = 0; i < m_machine->GetListChargeTypeName().size(); i++){
//            if(obj.contains(m_machine->GetListChargeTypeName().at(i))){
//                m_machine->UpdateValueKioskAdmin("ChargeTypeImageName",m_machine->GetListChargeTypeName().at(i), obj[m_machine->GetListChargeTypeName().at(i)].toString());
//            }
//        }
    }

    if (docobj[QString("ChargeTypeListDefault")].isObject()){
        QJsonObject obj = docobj[QString("ChargeTypeListDefault")].toObject();
        if(obj[QString("ListBankType")].isString() && !obj[QString("ListBankType")].isNull()){
            m_machine->UpdateValueKioskAdmin("ChargeTypeListDefault","ListBankType", obj[QString("ListBankType")].toString());
        }
        if(obj[QString("ListChargeType")].isString() && !obj[QString("ListChargeType")].isNull()){
            m_machine->UpdateValueKioskAdmin("ChargeTypeListDefault","ListChargeType", obj[QString("ListChargeType")].toString());
        }
        if(obj[QString("ListOtherType")].isString() && !obj[QString("ListOtherType")].isNull()){
            m_machine->UpdateValueKioskAdmin("ChargeTypeListDefault","ListOtherType", obj[QString("ListOtherType")].toString());
        }
        if(obj[QString("ListWalletType")].isString() && !obj[QString("ListWalletType")].isNull()){
            m_machine->UpdateValueKioskAdmin("ChargeTypeListDefault","ListWalletType", obj[QString("ListWalletType")].toString());
        }
    }

    if (docobj[QString("ChargeTypeListSetting")].isObject()){
        QJsonObject obj = docobj[QString("ChargeTypeListSetting")].toObject();
        if(obj[QString("ListBankType")].isString() && !obj[QString("ListBankType")].isNull()){
            m_machine->UpdateValueKioskAdmin("ChargeTypeListSetting","ListBankType", obj[QString("ListBankType")].toString());
        }
        if(obj[QString("ListChargeType")].isString() && !obj[QString("ListChargeType")].isNull()){
            m_machine->UpdateValueKioskAdmin("ChargeTypeListSetting","ListChargeType", obj[QString("ListChargeType")].toString());
        }
        if(obj[QString("ListOtherType")].isString() && !obj[QString("ListOtherType")].isNull()){
            m_machine->UpdateValueKioskAdmin("ChargeTypeListSetting","ListOtherType", obj[QString("ListOtherType")].toString());
        }
        if(obj[QString("ListWalletType")].isString() && !obj[QString("ListWalletType")].isNull()){
            m_machine->UpdateValueKioskAdmin("ChargeTypeListSetting","ListWalletType", obj[QString("ListWalletType")].toString());
        }
    }
    LOG<<"fffff";
    if (docobj[QString("UrlPromotionImage")].isObject()){
        QJsonObject obj = docobj[QString("UrlPromotionImage")].toObject();
        if(obj[QString("UrlPromotionImageList")].isString() && !obj[QString("UrlPromotionImageList")].isNull()){
            if(m_machine->GetListPartKioskAdmin("UrlPromotionImage").size() == 0)
                m_machine->CreatKioskAdmin("UrlPromotionImage","UrlPromotionImageList", obj[QString("UrlPromotionImageList")].toString());
            else
                m_machine->UpdateValueKioskAdmin("UrlPromotionImage","UrlPromotionImageList", obj[QString("UrlPromotionImageList")].toString());
        }
        LOG<<"ddd";
        if(m_machine->GetValueKioskAdmin("UrlPromotionImage","UrlPromotionImageList") != ""){
            list_PromotionImage = m_machine->GetValueKioskAdmin("UrlPromotionImage","UrlPromotionImageList").split(QLatin1Char(','));
            if(list_PromotionImage.size() != 0){
                UrlImageType = URL_IMAGE::PROMOTION_IMAGE;
                getByteArrayListPromotionImage();
            }
        }else{
            LOG<<"list ảnh trống";
        }
    }


   // m_machine->setChargeTypeSetting();

    if (docobj[QString("Coupon")].isObject()){
        QJsonObject obj = docobj[QString("Coupon")].toObject();
        if(obj[QString("MaxPriceCoupon")].isDouble() && !obj[QString("MaxPriceCoupon")].isNull())
            m_machine->config.setMaxPriceCoupon(obj[QString("MaxPriceCoupon")].toString().toInt());
        if(obj[QString("MinPriceCoupon")].isDouble() && !obj[QString("MinPriceCoupon")].isNull())
            m_machine->config.setMinPriceCoupon(obj[QString("MinPriceCoupon")].toString().toInt());
        if(obj[QString("InputMinimumLimit")].isDouble() && !obj[QString("InputMinimumLimit")].isNull())
            m_machine->config.setInputMinimumLimit(obj[QString("InputMinimumLimit")].toString().toInt());

        if(obj[QString("AllPinHide")].isString() && !obj[QString("AllPinHide")].isNull()){
            if(obj[QString("AllPinHide")].toString().contains("true")){
                m_machine->config.setCheckHidePin(true);
            }else if(obj[QString("AllPinHide")].toString().contains("false")){
                m_machine->config.setCheckHidePin(false);
            }
        }
    }

    if (docobj[QString("HandlingConnect")].isObject()){
        QJsonObject obj = docobj[QString("HandlingConnect")].toObject();
        if(obj[QString("TimeDelayToReConnectMQ")].isString() && !obj[QString("TimeDelayToReConnectMQ")].isNull())
            m_machine->config.setTimeDelayReConnecMQ(obj[QString("TimeDelayToReConnectMQ")].toString().toDouble());
        if(obj[QString("TimesToRestartApp")].isDouble() && !obj[QString("TimesToRestartApp")].isNull())
            m_machine->config.setTimesToRestartApp(obj[QString("TimesToRestartApp")].toString().toInt());
    }

    if (docobj[QString("Language")].isObject()){
        QJsonObject obj = docobj[QString("Language")].toObject();
        if(obj[QString("ChangeLanguageScreenCode")].isString() && !obj[QString("ChangeLanguageScreenCode")].isNull())
            m_machine->config.setCodeChangeLanguageScreen(obj[QString("ChangeLanguageScreenCode")].toString());
        if(obj[QString("DefaultLanguage")].isString() && !obj[QString("DefaultLanguage")].isNull())
            m_machine->config.setCodeLanguageScreen(obj[QString("DefaultLanguage")].toString());
        if(obj[QString("PermissionMultiLanguages")].isString() && !obj[QString("PermissionMultiLanguages")].isNull()){
            if(obj[QString("PermissionMultiLanguages")].toString().contains("true")){
                m_machine->config.setCheckPermissionMultiLanguages(true);
            }else if(obj[QString("PermissionMultiLanguages")].toString().contains("false")){
                m_machine->config.setCheckPermissionMultiLanguages(false);
            }
        }
    }

    if (docobj[QString("Rabbitmq")].isObject()){
        QJsonObject obj = docobj[QString("Rabbitmq")].toObject();
        if(obj[QString("Exchange")].isString() && !obj[QString("Exchange")].isNull())
            m_machine->config.setQueueExchange(obj[QString("Exchange")].toString());
        if(obj[QString("Host")].isString() && !obj[QString("Host")].isNull())
            m_machine->config.setQueueHost(obj[QString("Host")].toString());
        //QByteArray passwordMQ = QByteArray::fromBase64(obj[QString("Password")].toString().toUtf8());
        if(obj[QString("Password")].isString() && !obj[QString("Password")].isNull())
            m_machine->config.setQueuePassword(QString(obj[QString("Password")].toString()));
        if(obj[QString("Port")].isString() && !obj[QString("Port")].isNull())
            m_machine->config.setQueuePort(obj[QString("Port")].toString().toInt());
        if(obj[QString("User")].isString() && !obj[QString("User")].isNull())
            m_machine->config.setQueueUser(obj[QString("User")].toString());
        if(obj[QString("VHost")].isString() && !obj[QString("VHost")].isNull())
            m_machine->config.setQueueVHost(obj[QString("VHost")].toString());
    }

    if (docobj[QString("ResponseAmount")].isObject()){
        QJsonObject obj = docobj[QString("ResponseAmount")].toObject();
        QList<QString> listKey;
        listKey.clear();
        listKey = obj.keys();
        for(int i = 1; i < listKey.size(); i++){
            if(obj[listKey.at(i)].isDouble() && !obj[listKey.at(i)].isNull()){
                m_machine->config.setAmountResponse(listKey.at(i), obj[listKey.at(i)].toString().toInt());
            }
        }
    }

    if (docobj[QString("ScreenTimeout")].isObject()){
        QJsonObject obj = docobj[QString("ScreenTimeout")].toObject();
        if(obj[QString("AdminTimeout")].isDouble() && !obj[QString("AdminTimeout")].isNull())
            m_machine->config.setAdminTimeout(obj[QString("AdminTimeout")].toString().toInt());
        if(obj[QString("CheckScreenTimeout")].isString() && !obj[QString("CheckScreenTimeout")].isNull()){
            if(obj[QString("CheckScreenTimeout")].toString().contains("true")){
                m_machine->config.setCheckScreenTimeout(true);
            }else if(obj[QString("CheckScreenTimeout")].toString().contains("false")){
                m_machine->config.setCheckScreenTimeout(false);
            }
        }
        if(obj[QString("GetGoodTimeout")].isDouble() && !obj[QString("GetGoodTimeout")].isNull())
            m_machine->config.setGetGoodTimeout(obj[QString("GetGoodTimeout")].toString().toInt());
        if(obj[QString("QRCodeTimeout")].isDouble() && !obj[QString("QRCodeTimeout")].isNull())
            m_machine->config.setQRCodeTimeout(obj[QString("QRCodeTimeout")].toString().toInt());
        if(obj[QString("SaverScreen")].isDouble() && !obj[QString("SaverScreen")].isNull())
            m_machine->config.setSaverScreen(obj[QString("SaverScreen")].toString().toInt());
        if(obj[QString("ScreenTimeout")].isDouble() && !obj[QString("ScreenTimeout")].isNull())
            m_machine->config.setScreenTimeout(obj[QString("ScreenTimeout")].toString().toInt());
    }
    if (docobj[QString("Sensor")].isObject()){
        QJsonObject obj = docobj[QString("Sensor")].toObject();
        if(obj[QString("Baudrate")].isDouble() && !obj[QString("Baudrate")].isNull())
            m_machine->config.setSensorBaudrate(obj[QString("Baudrate")].toString().toInt());
        if(obj[QString("Enable")].isString() && !obj[QString("Enable")].isNull()){
            if(obj[QString("Enable")].toString().contains("true")){
                m_machine->config.setSensorEnabled(true);
            }else{
                m_machine->config.setSensorEnabled(false);
            }
        }
        //m_machine->config.setSensorPort(obj[QString("Port")].toString());
    }

    if (docobj[QString("SetPrice")].isObject()){
        QJsonObject obj = docobj[QString("SetPrice")].toObject();
        if(obj[QString("CheckGeneralPrice")].isString() && !obj[QString("CheckGeneralPrice")].isNull()){
            if(obj[QString("CheckGeneralPrice")].toString().contains("true")){
                m_machine->config.setCheckGeneralPrice(true);
            }else if(obj[QString("CheckGeneralPrice")].toString().contains("false")){
                m_machine->config.setCheckGeneralPrice(false);
            }
        }
        if(obj[QString("CheckSlotPrice")].isString() && !obj[QString("CheckSlotPrice")].isNull()){
            if(obj[QString("CheckSlotPrice")].toString().contains("true")){
                m_machine->config.setCheckSlotPrice(true);
            }else if(obj[QString("CheckSlotPrice")].toString().contains("false")){
                m_machine->config.setCheckSlotPrice(false);
            }
        }
        if(obj[QString("CheckTrayPrice")].isString() && !obj[QString("CheckTrayPrice")].isNull()){
            if(obj[QString("CheckTrayPrice")].toString().contains("true")){
                m_machine->config.setCheckTrayPrice(true);
            }else if(obj[QString("CheckTrayPrice")].toString().contains("false")){
                m_machine->config.setCheckTrayPrice(false);
            }
        }
        if(obj[QString("Coefficient")].isDouble() && !obj[QString("Coefficient")].isNull())
            m_machine->config.setCoefficient(obj[QString("Coefficient")].toString().toInt());
        if(obj[QString("PriceGoodsMax")].isDouble() && !obj[QString("PriceGoodsMax")].isNull())
            m_machine->config.setPriceGoodsMax(obj[QString("PriceGoodsMax")].toString().toInt());
        if(obj[QString("PriceGoodsMin")].isDouble() && !obj[QString("PriceGoodsMin")].isNull())
            m_machine->config.setPriceGoodsMin(obj[QString("PriceGoodsMin")].toString().toInt());
    }

    if (docobj[QString("TestMachine")].isObject()){
        QJsonObject obj = docobj[QString("TestMachine")].toObject();
        if(obj[QString("CheckTestLoxo")].isString() && !obj[QString("CheckTestLoxo")].isNull()){
            if(obj[QString("CheckTestLoxo")].toString().contains("true")){
                m_machine->config.setCheckTestLoxo(true);
            }else if(obj[QString("CheckTestLoxo")].toString().contains("false")){
                m_machine->config.setCheckTestLoxo(false);
            }
        }
    }

    if (docobj[QString("VTCDigital")].isObject()){
        QJsonObject obj = docobj[QString("VTCDigital")].toObject();
        if(obj[QString("MaxPricePostpaid")].isDouble() && !obj[QString("MaxPricePostpaid")].isNull())
            m_machine->config.setMaxPricePostPaid(obj[QString("MaxPricePostpaid")].toString().toInt());
        if(obj[QString("Menu")].isString() && !obj[QString("Menu")].isNull())
            m_machine->config.setMenuDigital(obj[QString("Menu")].toString());
        if(obj[QString("MinPricePostpaid")].isDouble() && !obj[QString("MinPricePostpaid")].isNull())
            m_machine->config.setMinPricePostPaid(obj[QString("MinPricePostpaid")].toString().toInt());
    }

    if (docobj[QString("TimeProcessUSBData")].isObject()){
        QJsonObject obj = docobj[QString("TimeProcessUSBData")].toObject();
        if(obj[QString("StarTimeProcess")].isString() && !obj[QString("StarTimeProcess")].isNull())
            m_machine->config.setTimeProcessUSB(obj[QString("StarTimeProcess")].toString());
    }

    if (docobj[QString("TimeExportData")].isObject()){
        QJsonObject obj = docobj[QString("TimeExportData")].toObject();
        if(obj[QString("DayNumberRemove")].isDouble() && !obj[QString("DayNumberRemove")].isNull())
            m_machine->config.setNumberDayRemoveFileExport(obj[QString("DayNumberRemove")].toString().toInt());
        if(obj[QString("DefineTime")].isString() && !obj[QString("DefineTime")].isNull())
            m_machine->config.setTimeExportData(obj[QString("DefineTime")].toString());
    }

    if (m_machine->config.save()){
        m_machine->config.loadAdminFile();
        LOG<<"update Config VMS to Kiosk";
    }
}

void MainWindow::process_request_VMSSync(QByteArray data)
{
    LOG;
    LOG;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject docobj = doc.object();
    if (!docobj["machine"].isObject()){
        return;
    }
    QJsonObject obj = docobj["machine"].toObject();
    if (!obj["ListDataType"].isObject()){
        return;
    }
    QJsonObject objListDataType = obj["ListDataType"].toObject();
    LOG<<objListDataType.contains("SendData") << objListDataType["SendData"].isArray()<<"jiji";
    if (objListDataType.contains("SendData") && objListDataType["SendData"].isArray()){

        QJsonArray DataArray = objListDataType["SendData"].toArray();
        LOG<<DataArray.size();
        for (int i = 0; i < DataArray.size(); ++i) {
            LOG;
            QJsonObject DataObject = DataArray[i].toObject();
            if (DataObject.contains("AdminData") && DataObject["AdminData"].isDouble()){
                if(DataObject["AdminData"].toDouble() == 1){
                    if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                        LOG;
                        QAmqpMessage::PropertyHash properties;
                        properties[QAmqpMessage::DeliveryMode] = "1";   // make message persistent
                        m_correlationId = m_machine->config.getMachineId();
                        properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                        properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                        topic_logs->publish( QString(m_machine->config.JsonSyncConfig().toJson())
                                             ,QString("%1.request.setconfigSync").arg(m_machine->config.getMachineId())
                                             ,properties);
                    }else{
                        LOG<<"setconfigSync failed!!!";
                    }
                }
            }
            if (DataObject.contains("MenuData") && DataObject["MenuData"].isDouble()){
                if(DataObject["MenuData"].toDouble() == 1){
                    if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                        LOG;
                        QAmqpMessage::PropertyHash properties;
                        properties[QAmqpMessage::DeliveryMode] = "1";   // make message persistent
                        m_correlationId = m_machine->config.getMachineId();
                        properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                        properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                        topic_logs->publish( QString(m_machine->config.Json(1).toJson())
                                             ,QString("%1.request.setconfig").arg(m_machine->config.getMachineId())
                                             ,properties);
                    }else{
                        LOG<<"menu failed!!!";
                    }
                }
            }
            if (DataObject.contains("ErrorList") && DataObject["ErrorList"].isDouble()){
                LOG;
            }
        }
    }
//    if (objListDataType.contains("ExportData") && objListDataType["ExportData"].isArray()){
//        QJsonArray DataArray = objListDataType["ExportData"].toArray();
//        for (int i = 0; i < DataArray.size(); ++i) {
//            QJsonObject DataObject = DataArray[i].toObject();
//            if (DataObject.contains("AdminData") && DataObject["AdminData"].isDouble()){
//                if(DataObject["AdminData"].toDouble() == 1){
//                    QString StartTimeEp = DataObject["StartTime"].toString();
//                    StartTimeEp.remove(QChar('-'));
//                   // StartTimeEp.replace(QString(":"),QString("."));
//                    QString EndTimeEp = DataObject["EndTime"].toString();
//                    EndTimeEp.remove(QChar('-'));
//                  //  EndTimeEp.replace(QString(":"),QString("."));

//                    QString date_name_file = StartTimeEp + "to" + EndTimeEp;
//                    QString nameKiosk = "kiosk-" + m_machine->config.getMachineId() + "_";
//                    QFile SyncAdminKiosktoVmsFile("/home/pi/export/DataKiosk/" + nameKiosk + "AdminInfo_" + date_name_file + ".json");
//                    if (SyncAdminKiosktoVmsFile.open(QFile::WriteOnly | QFile::Text | QFile::ReadOnly)){
//                        QString SyncAdminKiosktoVms;
//                        SyncAdminKiosktoVms = m_machine->config.JsonSyncConfig().toJson();
//                        SyncAdminKiosktoVmsFile.write(SyncAdminKiosktoVms.toLocal8Bit());
//                        SyncAdminKiosktoVmsFile.close();
//                    }
//                }
//            }
//            if (DataObject.contains("MenuData") && DataObject["MenuData"].isDouble()){
//                LOG;
//                if(DataObject["MenuData"].toDouble() == 1){
//                    QString StartTimeEp = DataObject["StartTime"].toString();
//                    StartTimeEp.remove(QChar('-'));
//                  //  StartTimeEp.replace(QString(":"),QString("."));
//                    QString EndTimeEp = DataObject["EndTime"].toString();
//                    EndTimeEp.remove(QChar('-'));
//                   // EndTimeEp.replace(QString(":"),QString("."));

//                    QString date_name_file = StartTimeEp + "to" + EndTimeEp;
//                    QString nameKiosk = "kiosk-" + m_machine->config.getMachineId() + "_";
//                    QFile SyncKiosktoVmsFile("/home/pi/export/DataKiosk/" + nameKiosk +"MachineInfo_" + date_name_file + ".json");
//                    if (SyncKiosktoVmsFile.open(QFile::WriteOnly | QFile::Text | QFile::ReadOnly)){
//                        QString SyncKiosktoVms;
//                        SyncKiosktoVms = m_machine->config.Json(1).toJson();
//                        SyncKiosktoVmsFile.write(SyncKiosktoVms.toLocal8Bit());
//                        SyncKiosktoVmsFile.close();
//                    }
//                }
//            }
//            if (DataObject.contains("ErrorList") && DataObject["ErrorList"].isDouble()){
//                if(DataObject["ErrorList"].toDouble() == 1){
//                    QString StartTimeEp = DataObject["StartTime"].toString();
//                    StartTimeEp.remove(QChar('-'));
//                   // StartTimeEp.replace(QString(":"),QString("."));
//                    QString EndTimeEp = DataObject["EndTime"].toString();
//                    EndTimeEp.remove(QChar('-'));
//                  //  EndTimeEp.replace(QString(":"),QString("."));

//                    QString date_name_file = StartTimeEp + "to" + EndTimeEp;
//                    QString nameKiosk = "kiosk-" + m_machine->config.getMachineId() + "_";
//                    QFile ErrorKioskUsb("/home/pi/export/DataKiosk/" + nameKiosk + "ErrorList_" + date_name_file + ".json");
//                    QJsonObject ErrorKioskData;
//                    QJsonArray ErrorKioskArray;
//                    for(int i = 1; i <= m_machine->GetListErrorCode().size(); i++){
//                       // m_machine->set_current_input(QString::number(i));
//                        QJsonDocument doc = QJsonDocument::fromJson(m_machine->GetErrorKioskUsb(m_machine->GetListErrorCode().at(i - 1)).toUtf8());
//                        QJsonObject json = doc.object();
//                        ErrorKioskArray.append(json);
//                    }
//                    ErrorKioskData["machine"] = ErrorKioskArray;
//                    QString signatureErrorKiosk = QCryptographicHash::hash(QJsonDocument(ErrorKioskData).toJson(QJsonDocument::Compact),QCryptographicHash::Md5).toHex();
//                    ErrorKioskData["Signature"] = signatureErrorKiosk;

//                    int StarttoMSecsSinceEpoch =QDateTime::currentDateTime().toMSecsSinceEpoch()/1000;
//                    ErrorKioskData["TimeExport"] = StarttoMSecsSinceEpoch;
//                    if (ErrorKioskUsb.open(QFile::WriteOnly | QFile::Text | QFile::ReadOnly)){
//                        ErrorKioskUsb.write(QJsonDocument(ErrorKioskData).toJson());
//                        ErrorKioskUsb.close();
//                    }
//                }
//            }
//            if (DataObject.contains("BillAmountData") && DataObject["BillAmountData"].isDouble()){
//                if(DataObject["BillAmountData"].toDouble() == 1){
//                    if(DataObject["StartTime"].isString() && !DataObject["StartTime"].isNull()){
//                        QString StartTimeEp = DataObject["StartTime"].toString();
//                        StartTimeEp.remove(QChar('-'));
//                      //  StartTimeEp.replace(QString(":"),QString("."));
//                        QString EndTimeEp = DataObject["EndTime"].toString();
//                        EndTimeEp.remove(QChar('-'));
//                      //  EndTimeEp.replace(QString(":"),QString("."));

//                        QString date_name_file = StartTimeEp + "to" + EndTimeEp;
//                        QString nameKiosk = "kiosk-" + m_machine->config.getMachineId() + "_";
//                        QFile BillAmountUsb("/home/pi/export/DataKiosk/" + nameKiosk  + "BillAmount_"+ date_name_file + ".json");

//                        if (BillAmountUsb.open(QFile::WriteOnly | QFile::Text | QFile::ReadOnly)){
//                            BillAmountUsb.write(m_machine->GetBillAmountDatetoDate(DataObject["StartTime"].toString() + " 00:00:00",DataObject["EndTime"].toString()+ " 00:00:00").toLocal8Bit());
//                            BillAmountUsb.close();
//                        }
//                    }
//                }
//            }
//            if (DataObject.contains("BillResponseData") && DataObject["BillResponseData"].isDouble()){
//                if(DataObject["BillResponseData"].toDouble() == 1){
//                    if(DataObject["StartTime"].isString() && !DataObject["StartTime"].isNull()){
//                        QString StartTimeEp = DataObject["StartTime"].toString();
//                        StartTimeEp.remove(QChar('-'));
//                      //  StartTimeEp.replace(QString(":"),QString("."));
//                        QString EndTimeEp = DataObject["EndTime"].toString();
//                        EndTimeEp.remove(QChar('-'));
//                       // EndTimeEp.replace(QString(":"),QString("."));

//                        QString date_name_file = StartTimeEp + "to" + EndTimeEp;
//                        QString nameKiosk = "kiosk-" + m_machine->config.getMachineId() + "_";
//                        QFile BillResponseUsb("/home/pi/export/DataKiosk/" + nameKiosk + "BillResponse_"+ date_name_file + ".json");
//                        if (BillResponseUsb.open(QFile::WriteOnly | QFile::Text | QFile::ReadOnly)){
//                            BillResponseUsb.write(m_machine->GetBillResponseDatetoDate(DataObject["StartTime"].toString()+ " 00:00:00",DataObject["EndTime"].toString()+ " 00:00:00").toLocal8Bit());
//                            BillResponseUsb.close();
//                        }
//                    }
//                }
//            }
//            if (DataObject.contains("SaleData") && DataObject["SaleData"].isDouble()){
//                if(DataObject["SaleData"].toDouble() == 1){
//                    if(DataObject["StartTime"].isString() && !DataObject["StartTime"].isNull()){
//                        QString StartTimeEp = DataObject["StartTime"].toString();
//                        StartTimeEp.remove(QChar('-'));
//                        StartTimeEp.replace(QString(":"),QString("."));
//                        QString EndTimeEp = DataObject["EndTime"].toString();
//                        EndTimeEp.remove(QChar('-'));
//                        EndTimeEp.replace(QString(":"),QString("."));

//                        QString date_name_file = StartTimeEp + "to" + EndTimeEp;
//                        QString nameKiosk = "kiosk-" + m_machine->config.getMachineId() + "_";
//                        QFile SaleUsb("/home/pi/export/DataKiosk/" + nameKiosk  +"SaleInfo_" + date_name_file + ".json");
//                        if (SaleUsb.open(QFile::WriteOnly | QFile::Text | QFile::ReadOnly)){
//                            SaleUsb.write(m_machine->GetSaleInfoDatetoDate(DataObject["StartTime"].toString()+ " 00:00:00",DataObject["EndTime"].toString()+ " 00:00:00").toLocal8Bit());
//                            SaleUsb.close();
//                        }
//                    }
//                }
//            }
//            if (DataObject.contains("TransactionData") && DataObject["TransactionData"].isDouble()){
//                if(DataObject["TransactionData"].toDouble() == 1){
//                    if(DataObject["StartTime"].isString() && !DataObject["StartTime"].isNull()){
//                        m_machine->dateExport = DataObject["StartTime"].toString() + " 00:00:00";
//                        m_machine->timeExport = DataObject["EndTime"].toString() + " 00:00:00";
//                        if(m_machine->exportToCsv()){
//                            LOG<<"export file csv success";
//                        }else{
//                            LOG<<"export file csv fail";
//                        }
//                    }
//                }
//            }
//        }
//    }
//    if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
//        LOG;
//        QAmqpMessage::PropertyHash properties;
//        properties[QAmqpMessage::DeliveryMode] = "1";   // make message persistent
//        m_correlationId = m_machine->config.getMachineId();
//        properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
//        properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
//        topic_logs->publish( QString(m_machine->JsonSyncConfig().toJson())
//                             ,QString("%1.request.setconfigSync").arg(m_machine->config.getMachineId())
//                             ,properties);
//    }else{
//        LOG<<"setconfigSync failed!!!";
//    }
}

void MainWindow::getByteArrayListMenuGoodGeneralImage()
{
  // list_goodId.clear();
   //list_goodId = m_machine->getListGoodId();
   //list_image_service_url<<"http://sab.com.vn/0-1.png"<<"http://sab.com.vn/1-1.png"<<"http://sab.com.vn/SAB-1.png";
   index_RequestUrl = 0;
   if(list_goodId.size() > 0){
     //  LOG<<list_goodId.at(0);
       requestUrl(m_machine->getImageUrlMenuGoodGeneral(list_goodId.at(0)));
   }
}

void MainWindow::getByteArrayListPromotionImage()
{
    index_RequestUrl = 0;
    requestUrl(list_PromotionImage.at(0));
}
void MainWindow::clientConnected()
{
    topic_logs = m_client.createExchange("transferAPI");
    connect(topic_logs, SIGNAL(declared()), this, SLOT(exchangeDeclared()), Qt::UniqueConnection);
    topic_logs->declare(QAmqpExchange::Topic);
}

void MainWindow::clientDisconnected()
{
    LOG<<"internet disconnect";
    m_queue_connected = false;
}
void MainWindow::exchangeDeclared()
{
    QAmqpExchange *exchange = qobject_cast<QAmqpExchange*>(sender());
    if (!exchange)
        return;
    QAmqpQueue *temporaryQueue = m_client.createQueue(m_machine->transaction()->MachineId);
    connect(temporaryQueue, SIGNAL(declared()), this, SLOT(queueDeclared()), Qt::UniqueConnection);
    connect(temporaryQueue, SIGNAL(bound()), this, SLOT(queueBound()), Qt::UniqueConnection);
    connect(temporaryQueue, SIGNAL(messageReceived()), this, SLOT(message_queue_received()), Qt::UniqueConnection);
    temporaryQueue->declare(QAmqpQueue::Durable);
}
void MainWindow::queueDeclared()
{
    QAmqpQueue *temporaryQueue = qobject_cast<QAmqpQueue*>(sender());
    if (!temporaryQueue)
        return;
    //        foreach (QString bindingKey, /*m_bindingKeys*/)
    temporaryQueue->bind("transferAPI",QString("%1.command.*").arg( m_machine->transaction()->MachineId));

}

void MainWindow::queueBound()
{
    LOG<<"internet online";
    QAmqpQueue *temporaryQueue = qobject_cast<QAmqpQueue*>(sender());
    if (!temporaryQueue)
        return;
    m_queue_connected = true;
    temporaryQueue->consume();
    if(m_machine->state() == CHARGE_COUPON || m_machine->state() == SALEINFO_QRCODE || m_machine->state() == RFID_DATA || m_machine->state() == CHARGE_MPOS){
        LOG;
        QAmqpMessage::PropertyHash properties;
        properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
        m_correlationId = m_machine->transaction()->MachineId;
        properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
        properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
        topic_logs->publish(m_machine->transaction()->GetPriceSever()
                            ,QString("%1.request.getPriceSever").arg(m_machine->transaction()->MachineId)
                            ,properties);
    }else if(m_machine->state() == TOPUPPARTNER){
        LOG;
        QAmqpMessage::PropertyHash properties;
        properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
        m_correlationId = m_machine->transaction()->MachineId;
        properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
        properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
        topic_logs->publish(m_machine->transaction()->GetInvoiceTopupPartner()
                            ,QString("%1.request.goodsdigital").arg(m_machine->transaction()->MachineId)
                            ,properties);
    }

}

void MainWindow::message_queue_received()
{
    QAmqpQueue *queue = qobject_cast<QAmqpQueue*>(sender());
    if (!queue)
        return;
    QAmqpMessage message = queue->dequeue();
    LOG << message.routingKey() << message.deliveryTag();
    LOG << message.payload();
    if(m_timer_ReconnectMQ.isActive()){
        m_timer_ReconnectMQ.stop();
        m_timer_ReconnectMQ.setInterval(30000);
    }
    if(message.routingKey().endsWith("command.menugood")){
        LOG<<"hhs";
        process_message_MenuGoodTable(message.payload());
    }else if(message.routingKey().endsWith("command.setconfig") ){
        process_message_MenuGoodGeneralTable(message.payload());
    }
    else if(message.routingKey().endsWith("command.menugoodgeneral")){
        LOG<<"hh vật lí";
        process_message_MenuGoodGeneralTable(message.payload());
    }else if(message.routingKey().endsWith("command.setKioskId")){
       // QJsonDocument doc = QJsonDocument::fromJson(message.payload());
       // QJsonObject obj = doc.object();
        m_machine->config.setKioskId(QString::fromStdString(message.payload().toStdString()));
        if(m_machine->config.save()){
            LOG<<"lưu mã máy Kiosk thành công!";
        }
        m_machine->transaction()->KioskId = m_machine->config.getKioskId();

        LOG<<m_machine->transaction()->KioskId<<"mã máy kiosk";
        QAmqpMessage::PropertyHash properties;
        properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
        m_correlationId = m_machine->transaction()->MachineId;
        properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
        properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
        topic_logs->publish("Connect_OK"
                            ,QString("%1.command.comfirmConnect").arg(m_machine->transaction()->KioskId)
                            ,properties);

    }else if(message.routingKey().endsWith("command.comfirmReturnGoodFail") && m_machine->state() == MACHINE_STATE::GET_GOOD_GENERAL){
        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::FAILED;
        m_machine->UpdateDB();
        GetGoodGeneral->OutOfGood();
        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
            LOG;
            QAmqpMessage::PropertyHash properties;
            properties[QAmqpMessage::DeliveryMode] = "2";
            topic_logs->publish(m_machine->transaction()->toAPIString()
                                ,QString("%1.transactions").arg(m_machine->transaction()->MachineId)
                                ,properties);
        }
    }else if(message.routingKey().endsWith("command.comfirmReturnGoodSuccess") && m_machine->state() == MACHINE_STATE::GET_GOOD_GENERAL){
        m_machine->transaction()->SlotId = message.payload();
        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::SUCCESS;
        m_machine->UpdateDB();

        m_machine->UpdateGoodQuatity(m_machine->transaction()->GoodId,m_machine->GetGoodQuatity(m_machine->transaction()->GoodId) - 1);
        GetGoodGeneral->ReturnGoodSuccess();
        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
            LOG;
            QAmqpMessage::PropertyHash properties;
            properties[QAmqpMessage::DeliveryMode] = "2";
            topic_logs->publish(m_machine->transaction()->toAPIString()
                                ,QString("%1.transactions").arg(m_machine->transaction()->MachineId)
                                ,properties);
        }
    }
    else if(message.routingKey().endsWith("command.setconfigSync")){
        process_message_SetConfigSync(message.payload());
    }else if(message.routingKey().endsWith("command.getconfigSync")){
        process_request_VMSSync(message.payload());
    }else if(message.routingKey().endsWith("command.exitApp")){
        LOG<<"thoát App";
    }else if(m_machine->state() == MACHINE_STATE::ADMIN_PROCESS_FUNTION){
        if(m_machine->AdminType == ADMINFUNTIONLIST::SYNC_VMS_TO_APP){
            process_message_MenuGoodGeneralTable(message.payload());
            ProcessAdminFuntionSCreen->SyncInfo("success");
        }else if(m_machine->AdminType == ADMINFUNTIONLIST::SYNC_APP_TO_VMS){
            QJsonDocument doc = QJsonDocument::fromJson(message.payload());
            QJsonObject obj = doc.object();
            if (obj.contains("description") && !obj["description"].isNull() && obj["description"].isString()){
                m_machine->transaction()->MessageRechargeMobile  = obj["description"].toString();
                LOG<<m_machine->transaction()->MessageRechargeMobile;
            }
            if (obj.contains("code") && !obj["code"].isNull() && obj["code"].isDouble()){
                int code = obj["code"].toInt();
                if (code == 0)
                    ProcessAdminFuntionSCreen->SyncInfo("success");
                else
                {
                    ProcessAdminFuntionSCreen->SyncInfo(m_machine->transaction()->MessageRechargeMobile);
                }
            }else{
                ProcessAdminFuntionSCreen->SyncInfo("error");
            }
        }else if(m_machine->AdminType == ADMINFUNTIONLIST::RESEND_SALE){
            ProcessAdminFuntionSCreen->ReSendSaleStatus("success");
        }
    }
    else if(m_machine->state() == MACHINE_STATE::SALEINFO_QRCODE){
        if (message.property(QAmqpMessage::CorrelationId).toString() != m_correlationId) {
            // requeue message, it wasn't meant for us
            LOG << message.property(QAmqpMessage::CorrelationId).toString() << m_correlationId;
            queue->reject(message, true);
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
        if(obj["codeProduct"].toString() == m_machine->transaction()->GoodId){
            if (obj.contains("priceSale") && !obj["priceSale"].isNull() && obj["priceSale"].isDouble()){
                quint32 price = obj["priceSale"].toInt();
                m_machine->transaction()->GoodPrice = obj["goodPrice"].toDouble();
                if(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity != price)
                    m_machine->transaction()->moneyCalculate = price;
                else{
                    m_machine->transaction()->moneyCalculate = 0;
                    LOG<<"đơn hàng bình thường";
                }
                m_machine->transaction()->CheckPriceServe = true;
                InfoSaleQrCode->updateInfoSaleQR(m_machine);
                LOG<<"lấy giá sp";
            }else{
                m_machine->transaction()->CheckPriceServe = false;
                InfoSaleQrCode->Check_GetQRCodeFalse = true;
            }

            if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
                m_machine->transaction()->reducedValue = obj["reducedValue"].toInt();
            }
            if (obj.contains("idSale")){
                m_machine->transaction()->idSale = obj["idSale"].toString();
            }
        }
    }else if(m_machine->state() == MACHINE_STATE::CHARGE_COUPON){
        if (message.property(QAmqpMessage::CorrelationId).toString() != m_correlationId) {
            // requeue message, it wasn't meant for us
            LOG << message.property(QAmqpMessage::CorrelationId).toString() << m_correlationId;
            queue->reject(message, true);
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
        if(obj["codeProduct"].toString() == m_machine->transaction()->GoodId){
            if (obj.contains("priceSale") && !obj["priceSale"].isNull() && obj["priceSale"].isDouble()){
                quint32 price = obj["priceSale"].toInt();
                m_machine->transaction()->GoodPrice = obj["goodPrice"].toDouble();
                if(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity != price)
                    m_machine->transaction()->moneyCalculate = price;
                else{
                    m_machine->transaction()->moneyCalculate = 0;
                    LOG<<"đơn hàng bình thường";
                }
                m_machine->transaction()->CheckPriceServe = true;
                Charge_Coupon->updateChargeCoupon(m_machine);
               // Charge_Coupon->showKeyboard();

            }else{
                m_machine->transaction()->CheckPriceServe = false;
            }

            if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
                m_machine->transaction()->reducedValue = obj["reducedValue"].toInt();
            }
            if (obj.contains("idSale")){
                m_machine->transaction()->idSale = obj["idSale"].toString();
            }
        }
    }else if(m_machine->state() == MACHINE_STATE::RFID_DATA){
        if (message.property(QAmqpMessage::CorrelationId).toString() != m_correlationId) {
            // requeue message, it wasn't meant for us
            LOG << message.property(QAmqpMessage::CorrelationId).toString() << m_correlationId;
            queue->reject(message, true);
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
        if(obj["codeProduct"].toString() == m_machine->transaction()->GoodId){
            if (obj.contains("priceSale") && !obj["priceSale"].isNull() && obj["priceSale"].isDouble()){
                quint32 price = obj["priceSale"].toInt();
                m_machine->transaction()->GoodPrice = obj["goodPrice"].toDouble();
                if(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity != price)
                    m_machine->transaction()->moneyCalculate = price;
                else{
                    m_machine->transaction()->moneyCalculate = 0;
                    LOG<<"đơn hàng bình thường";
                }
                m_machine->transaction()->CheckPriceServe = true;
                Rfid_Data->updateRfidData(m_machine);
               // Charge_Coupon->showKeyboard();

            }else{
                m_machine->transaction()->CheckPriceServe = false;
            }

            if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
                m_machine->transaction()->reducedValue = obj["reducedValue"].toInt();
            }
            if (obj.contains("idSale")){
                m_machine->transaction()->idSale = obj["idSale"].toString();
            }
        }

    }
    else if(m_machine->state() == MACHINE_STATE::CHARGE_MPOS && m_machine->transaction()->TransactionStatus == KioskTransactionStatus::INIT){
            if (message.property(QAmqpMessage::CorrelationId).toString() != m_correlationId) {
                // requeue message, it wasn't meant for us
                LOG << message.property(QAmqpMessage::CorrelationId).toString() << m_correlationId;
                queue->reject(message, true);
                return;
            }

            QJsonDocument doc = QJsonDocument::fromJson(message.payload());
            QJsonObject obj = doc.object();
            if(obj["codeProduct"].toString() == m_machine->transaction()->GoodId){
                if (obj.contains("priceSale") && !obj["priceSale"].isNull() && obj["priceSale"].isDouble()){
                    quint32 price = obj["priceSale"].toInt();
                    m_machine->transaction()->GoodPrice = obj["goodPrice"].toDouble();
                    if(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity != price)
                        m_machine->transaction()->moneyCalculate = price;
                    else{
                        m_machine->transaction()->moneyCalculate = 0;
                        LOG<<"đơn hàng bình thường";
                    }
                    m_machine->transaction()->CheckPriceServe = true;
                    Charge_mpos->updateChargeMpos(m_machine);
                   // Charge_Coupon->showKeyboard();

                }else{
                    m_machine->transaction()->CheckPriceServe = false;
                }

                if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
                    m_machine->transaction()->reducedValue = obj["reducedValue"].toInt();
                }
                if (obj.contains("idSale")){
                    m_machine->transaction()->idSale = obj["idSale"].toString();
                }
            }

    }else if(m_machine->state() == MACHINE_STATE::SCREEN_GET_QRCODE){
        if (message.property(QAmqpMessage::CorrelationId).toString() != m_correlationId) {
            // requeue message, it wasn't meant for us
            LOG << message.property(QAmqpMessage::CorrelationId).toString() << m_correlationId;
            queue->reject(message, true);
            return;
        }
        LOG << message.payload();
        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
        LOG <<  obj["qrcode"].toString().length() << obj["qrcode"].isString();
        if (obj.contains("TransferId") && !obj["TransferId"].isNull() && obj["TransferId"].isString()){
            m_machine->transaction()->TransferId  = obj["TransferId"].toString();

        }
        if (obj.contains("qrcode") && !obj["qrcode"].isNull() && obj["qrcode"].isString()){
            LOG << obj["qrcode"].toString();
            if(obj["qrcode"].toString() != ""){
                m_machine->transaction()->OrderInformation  = obj["qrcode"].toString();
            }else{

            }

        } else {

        }
        process_state(SCREEN_QRCODE);

    }else if(m_machine->state() == MACHINE_STATE::SCREEN_QRCODE && m_machine->transaction()->TransactionStatus != KioskTransactionStatus::CANCEL){
        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
       // QByteArray hash = QCryptographicHash::hash(s.toUtf8(),QCryptographicHash::Md5);
        if(obj.contains("statusPay") ){
           // int statusPay = obj["statusPay"].toInt();
            QString signature;
            if(m_machine->transaction()->serviceCode != RECHARGEMOBILETYPE::TOPUP_PARTNER){
                if(m_machine->transaction()->moneyCalculate == 0){
                    signature =m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                }else{
                    signature =m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->moneyCalculate) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                }
            }else
                signature =m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->amount_and_fee) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
            QString sign = QCryptographicHash::hash(signature.toUtf8(),QCryptographicHash::Md5).toHex();
            if(obj["statusPay"].toInt() == 0 && obj["transactionId"].toString() == m_machine->transaction()->TransactionId && obj["signature"].toString() == sign){
                if(m_machine->transaction()->BuyType == "MenuBuy"){
                    m_machine->transaction()->IsCheckingWorkWithVTC = true;
                    m_machine->transaction()->TransactionStatus = KioskTransactionStatus::RETURN_GOOD_WAITING;
                    process_state(GOOD_DIGITAL_PROCESS);
                }else{
                    m_machine->transaction()->TransactionStatus = KioskTransactionStatus::RETURN_GOOD_WAITING;
                    process_state(GET_GOOD_GENERAL);
                }
            }else{
                LOG<<signature<<sign;
            }
        }else{
            LOG;
        }

    }else if ( m_machine->state() == GOOD_DIGITAL_PROCESS && m_machine->transaction()->TransactionStatus == KioskTransactionStatus::PAYMENT_WAITING ) {
            LOG;
            if (message.property(QAmqpMessage::CorrelationId).toString() != m_correlationId) {
                // requeue message, it wasn't meant for us
                LOG << message.property(QAmqpMessage::CorrelationId).toString() << m_correlationId;
                queue->reject(message, true);
                return;
            }
            QJsonDocument doc = QJsonDocument::fromJson(message.payload());
            QJsonObject obj = doc.object();
            LOG<<obj["codeProduct"].toString()<<m_machine->transaction()->GoodId<<"kokoik";
            if(obj["codeProduct"].toString() == m_machine->transaction()->GoodId){
                if (obj.contains("priceSale") && !obj["priceSale"].isNull() && obj["priceSale"].isDouble()){
                    int price = obj["priceSale"].toInt();
                    m_machine->transaction()->GoodPrice = price ;
                    m_machine->transaction()->moneyCalculate = 0;
                    m_machine->transaction()->CheckPriceServe = true;
                    Good_Digital_Process->updateGetPriceGoodDigitalProcess(m_machine);
                    LOG<<"eeeee";
                }else{
                    m_machine->transaction()->CheckPriceServe = false;
                }

                if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
                    int price = obj["reducedValue"].toInt();
                    m_machine->transaction()->reducedValue = price;
                }
                if (obj.contains("idSale")){
                    m_machine->transaction()->idSale = obj["idSale"].toString();
                }
                //m_machine->input(Qt::Key_L);
            }


    }else if(m_machine->state() == MACHINE_STATE::GOOD_DIGITAL_PROCESS && m_machine->transaction()->TransactionStatus == KioskTransactionStatus::RETURN_GOOD_WAITING){

        LOG;
        if (message.property(QAmqpMessage::CorrelationId).toString() != m_correlationId) {
            // requeue message, it wasn't meant for us
            LOG << message.property(QAmqpMessage::CorrelationId).toString() << m_correlationId;
            queue->reject(message, true);
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();

        if(!obj.contains("priceSale") && !obj.contains("vtcService")){
            m_machine->transaction()->IsCheckingWorkWithVTC = false;
            if (obj.contains("TransferId") && !obj["TransferId"].isNull() && obj["TransferId"].isString()){
                m_machine->transaction()->TransferId  = obj["TransferId"].toString();
            }
            if (obj.contains("description") && !obj["description"].isNull() && obj["description"].isString()){
                m_machine->transaction()->MessageRechargeMobile  = obj["description"].toString();
                LOG<<m_machine->transaction()->MessageRechargeMobile;
            }
            if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO ||
                    m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID ||
                    m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE||
                    m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER
                    ){
                if (obj.contains("code")){
                    int code;
                    if(obj["code"].isDouble()){
                        code = obj["code"].toInt();
                    }else if(obj["code"].isString()){
                        code = obj["code"].toString().toInt();
                    }
                    if(obj["code"].isNull()){
                        code = 0;
                    }
                  //  if (obj["Title"].toString() == m_machine->transaction()->GoodId){
                        if (code == 1){
                            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::SUCCESS;
                            m_machine->UpdateDB();
                            if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER)
                                LOG<<"nạp tiền điện thoại thành công";
                            else if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
                                if (obj.contains("card") && obj["card"].isArray()) {
                                    QJsonArray trayArray = obj["card"].toArray();
                                    for (int i = 0; i < trayArray.size(); ++i) {
                                        m_machine->transaction()->CardCode += trayArray[i].toString();
                                    }
                                    LOG<<m_machine->transaction()->CardCode;
                                }

                            }
                            if(m_machine->transaction()->TransactionType == KioskTransactionType::CASH){
                                m_machine->transaction()->AvailableAmount += m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity;
                                m_machine->BillAmount()->BillAvailable += m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity;
                            }
                            m_machine->finish_transaction();
                            process_state(GET_GOOD_DIGITAL);
                        }else if(code == 0 || code == -1 || code == -99){
                            //TH các lỗi không xác định, ko hoàn tiền.

                            if(m_machine->transaction()->TransactionType == KioskTransactionType::CASHandCOUPON){
                                if(m_machine->transaction()->serviceCode != RECHARGEMOBILETYPE::BUYCARDMOBILE)
                                    m_machine->transaction()->AvailableAmount = m_machine->transaction()->AvailableAmount - m_machine->transaction()->UseValueCash;
                                m_machine->BillAmount()->BillAvailable = m_machine->transaction()->AvailableAmount;
                                m_machine->balanceBillAccepted_BillIdentified();
                                m_machine->UpdateBillAvailable();
                            }
                           // CheckStatus = false;
                            if(m_machine->transaction()->serviceCode != RECHARGEMOBILETYPE::BUYCARDMOBILE){
                                m_machine->transaction()->TransactionStatus = KioskTransactionStatus::ERROR;
                            }else{
                                m_machine->transaction()->TransactionStatus = KioskTransactionStatus::FAILED;
                                if(m_machine->transaction()->TransactionType == KioskTransactionType::CASH){
                                    m_machine->transaction()->AvailableAmount += m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity;
                                    m_machine->BillAmount()->BillAvailable += m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity;
                                    m_machine->balanceBillAccepted_BillIdentified();
                                    m_machine->UpdateBillAvailable();
                                }
                            }
                            m_machine->UpdateDB();
                            process_state(GOOD_DIGITAL_PROCESS);

                          //  Good_Digital_Process->updateGoodDigitalProcess(m_machine);
                        }else{
                            if(m_machine->transaction()->TransactionType == KioskTransactionType::CASH){
                                m_machine->transaction()->AvailableAmount += m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity;
                                m_machine->BillAmount()->BillAvailable += m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity;
                                m_machine->balanceBillAccepted_BillIdentified();
                                m_machine->UpdateBillAvailable();
                            }
                            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::FAILED;
                            m_machine->UpdateDB();
                            process_state(GOOD_DIGITAL_PROCESS);
                            LOG;
                        }
                   // }
                }else if(!obj.contains("priceSale")){
                    if(m_machine->transaction()->TransactionType == KioskTransactionType::CASHandCOUPON){
                        if(m_machine->transaction()->serviceCode != RECHARGEMOBILETYPE::BUYCARDMOBILE)
                            m_machine->transaction()->AvailableAmount = m_machine->transaction()->AvailableAmount - m_machine->transaction()->UseValueCash;
                        m_machine->BillAmount()->BillAvailable = m_machine->transaction()->AvailableAmount;
                        m_machine->balanceBillAccepted_BillIdentified();
                        m_machine->UpdateBillAvailable();
                    }
                   // CheckStatus = false;
                    if(m_machine->transaction()->serviceCode != RECHARGEMOBILETYPE::BUYCARDMOBILE){
                        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::ERROR;
                    }else{
                        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::FAILED;
                        if(m_machine->transaction()->TransactionType == KioskTransactionType::CASH){
                            LOG<<m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity<<"hoàn tienefnnnnnnnnnnnnnnnn";
                            m_machine->transaction()->AvailableAmount += m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity;
                            m_machine->BillAmount()->BillAvailable += m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity;
                            m_machine->balanceBillAccepted_BillIdentified();
                            m_machine->UpdateBillAvailable();
                        }
                    }
                    m_machine->UpdateDB();
                    process_state(GOOD_DIGITAL_PROCESS);
                    //m_machine->input(Qt::Key_E);
                    LOG;
                }

            }else if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
                if (obj.contains("code") && !obj["code"].isNull() && obj["code"].isDouble()){
                    int code = obj["code"].toInt();
                    if(code == 1){
                        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::SUCCESS;
                        m_machine->UpdateDB();
                        if(m_machine->transaction()->TransactionType == KioskTransactionType::CASH){
                            m_machine->transaction()->AvailableAmount += m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity;
                            m_machine->BillAmount()->BillAvailable += m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity;
                        }
                        m_machine->finish_transaction();
                        process_state(GET_GOOD_DIGITAL);
                    }
                    else{
                        if(m_machine->transaction()->TransactionType == KioskTransactionType::CASH){
                            m_machine->transaction()->AvailableAmount += m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity;
                            m_machine->BillAmount()->BillAvailable += m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity;
                            m_machine->balanceBillAccepted_BillIdentified();
                            m_machine->UpdateBillAvailable();
                        }
                        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::FAILED;
                        m_machine->UpdateDB();
                        process_state(GOOD_DIGITAL_PROCESS);
                    }
                }
            }
        }

    }
    else if(m_machine->state() == MACHINE_STATE::CHARGED_COUPON && m_machine->transaction()->TransactionStatus != KioskTransactionStatus::CANCEL){
        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
        if (obj.contains("TransferId") && !obj["TransferId"].isNull() && obj["TransferId"].isString()){
            m_machine->transaction()->TransferId  = obj["TransferId"].toString();

        }
        if (obj.contains("description") && !obj["description"].isNull() && obj["description"].isString()){
            m_machine->transaction()->MessageRechargeMobile  = obj["description"].toString();
            LOG<<m_machine->transaction()->MessageRechargeMobile;
        }
        if (obj.contains("code") && !obj["code"].isNull() && obj["code"].isDouble()){
            int code = obj["code"].toInt();
            if (code == 0){
                if (obj.contains("useValueCash") && !obj["useValueCash"].isNull() && obj["useValueCash"].isDouble())
                    m_machine->transaction()->UseValueCash = obj["useValueCash"].toDouble();
                else{
                    if(m_machine->transaction()->AvailableAmount <= m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity){
                        m_machine->transaction()->UseValueCash = m_machine->transaction()->AvailableAmount;
                    }else{
                        m_machine->transaction()->UseValueCash = m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity;
                    }
                }
                QString signature;
                if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER)
                    signature = m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->amount_and_fee) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                else{
                    if(m_machine->transaction()->moneyCalculate == 0){
                        signature = m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                    }else{
                        signature = m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->moneyCalculate) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                    }
                }
                QString sign = QCryptographicHash::hash(signature.toUtf8(),QCryptographicHash::Md5).toHex();
                if(obj["signature"].toString() == sign){
                    if(m_machine->transaction()->BuyType == "MenuBuy"){
                        m_machine->transaction()->IsCheckingWorkWithVTC = true;
                        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::RETURN_GOOD_WAITING;
                        process_state(MACHINE_STATE::GOOD_DIGITAL_PROCESS);

                    }else{
                        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::RETURN_GOOD_WAITING;
                        process_state(GET_GOOD_GENERAL);
                    }
                }else{
                    m_machine->transaction()->MessageRechargeMobile = "Sai chữ kí số";
                    process_state(MACHINE_STATE::CHARGE_COUPON);
                    LOG<<signature<<sign<<"chữ kí ko hợp lệ";
                }
            }/*else{
                LOG<<code<<"mua coupon thất bại";
                Charge_Coupon->updateChargeCoupon(m_machine);
            }*/
            else if(code == 2){
                LOG<<"code = 2";
                process_state(MACHINE_STATE::PIN_USER_COUPON_SAB);
               // m_machine->input(Qt::Key_L);
            }/*else if(code == 13){
                LOG<<"code = 13";
               // if (obj.contains("moneyLack")){
                    //m_machine->transaction()->moneyLackCoupon = obj["moneyLack"].toDouble();
               // }
               // m_machine->input(Qt::Key_D);
            }else if(code == 17){
                // bắt đổi mã PIN
                LOG<<"code = 17";
               // m_machine->input(Qt::Key_J);
            }*/else if(code == 21){
                // mã phổ thông có km
                if (obj.contains("priceSale") && !obj["priceSale"].isNull() && obj["priceSale"].isDouble()){
                    quint32 price = obj["priceSale"].toDouble();
                   // m_machine->transaction()->GoodPrice = obj["goodPrice"].toDouble();
                    if(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity != price)
                        m_machine->transaction()->moneyCalculate = price;
                    else{
                        m_machine->transaction()->moneyCalculate = 0;
                        LOG<<"đơn hàng bình thường";
                    }

                }
                if (obj.contains("idSale")){
                    m_machine->transaction()->idSale = obj["idSale"].toString();
                }
                if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
                    int price = obj["reducedValue"].toInt();
                    m_machine->transaction()->reducedValue = price;
                }
                Charge_Coupon->updateChargeCoupon(m_machine);
                m_machine->setState(MACHINE_STATE::CHARGE_COUPON);
                ui->stackedWidget->setCurrentIndex(m_machine->state());
               // process_state(MACHINE_STATE::CHARGE_COUPON);
               // m_machine->input(Qt::Key_F);
            }else if(code == 22){
                // mã gắn kết có km
                if (obj.contains("priceSale") && !obj["priceSale"].isNull() && obj["priceSale"].isDouble()){
                    quint32 price = obj["priceSale"].toDouble();
                   // m_machine->transaction()->GoodPrice = obj["goodPrice"].toDouble();
                    if(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity != price)
                        m_machine->transaction()->moneyCalculate = price;
                    else{
                        m_machine->transaction()->moneyCalculate = 0;
                        LOG<<"đơn hàng bình thường";
                    }

                }
                if (obj.contains("idSale")){
                    m_machine->transaction()->idSale = obj["idSale"].toString();
                }
                if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
                    int price = obj["reducedValue"].toInt();
                    m_machine->transaction()->reducedValue = price;
                }
                process_state(MACHINE_STATE::PIN_USER_COUPON_SAB);
                //m_machine->input(Qt::Key_L);
            }
            else{
                LOG<<code<< "code = #";
                process_state(MACHINE_STATE::CHARGE_COUPON);
//                if (obj.contains("TimeDelayCoupon") && !obj["TimeDelayCoupon"].isNull() && obj["TimeDelayCoupon"].isDouble()){
//                    m_machine->transaction()->TimeDelayCoupon = obj["TimeDelayCoupon"].toDouble();
//                    LOG<<m_machine->transaction()->TimeDelayCoupon<<"timedelayCoupon";
//                    m_machine->input(Qt::Key_S);
//                }else{
//                    m_machine->input(Qt::Key_G);
//                }
            }
        }

    }
    else if(m_machine->state() == MACHINE_STATE::RFID_DATA_PAYMENT_WAITING && m_machine->transaction()->TransactionStatus != KioskTransactionStatus::CANCEL){
        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
        if (obj.contains("TransferId") && !obj["TransferId"].isNull() && obj["TransferId"].isString()){
            m_machine->transaction()->TransferId  = obj["TransferId"].toString();

        }
        if (obj.contains("description") && !obj["description"].isNull() && obj["description"].isString()){
            m_machine->transaction()->MessageRechargeMobile  = obj["description"].toString();
            LOG<<m_machine->transaction()->MessageRechargeMobile;
        }
        if (obj.contains("code") && !obj["code"].isNull() && obj["code"].isDouble()){
            int code = obj["code"].toInt();
            if (code == 0){
                if (obj.contains("useValueCash") && !obj["useValueCash"].isNull() && obj["useValueCash"].isDouble())
                    m_machine->transaction()->UseValueCash = obj["useValueCash"].toDouble();
                else{
                    if(m_machine->transaction()->AvailableAmount <= m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity){
                        m_machine->transaction()->UseValueCash = m_machine->transaction()->AvailableAmount;
                    }else{
                        m_machine->transaction()->UseValueCash = m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity;
                    }
                }
                QString signature;
                if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER)
                    signature = m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->amount_and_fee) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                else{
                    if(m_machine->transaction()->moneyCalculate == 0){
                        signature = m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                    }else{
                        signature = m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->moneyCalculate) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                    }
                }
                QString sign = QCryptographicHash::hash(signature.toUtf8(),QCryptographicHash::Md5).toHex();
                if(obj["signature"].toString() == sign){
                    if(m_machine->transaction()->BuyType == "MenuBuy"){
                        m_machine->transaction()->IsCheckingWorkWithVTC = true;
                        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::RETURN_GOOD_WAITING;
                        process_state(MACHINE_STATE::GOOD_DIGITAL_PROCESS);

                    }else{
                        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::RETURN_GOOD_WAITING;
                        process_state(GET_GOOD_GENERAL);
                    }
                }else{
                    LOG<<signature<<sign<<"chữ kí ko hợp lệ";
                }
            }/*else{
                LOG<<code<<"mua coupon thất bại";
                Charge_Coupon->updateChargeCoupon(m_machine);
            }*/
            else if(code == 2){
                LOG<<"code = 2";
                process_state(MACHINE_STATE::PIN_USER_COUPON_SAB);
               // m_machine->input(Qt::Key_L);
            }/*else if(code == 13){
                LOG<<"code = 13";
               // if (obj.contains("moneyLack")){
                    //m_machine->transaction()->moneyLackCoupon = obj["moneyLack"].toDouble();
               // }
               // m_machine->input(Qt::Key_D);
            }else if(code == 17){
                // bắt đổi mã PIN
                LOG<<"code = 17";
               // m_machine->input(Qt::Key_J);
            }*/else if(code == 21){
                // mã phổ thông có km
                if (obj.contains("priceSale") && !obj["priceSale"].isNull() && obj["priceSale"].isDouble()){
                    quint32 price = obj["priceSale"].toDouble();
                   // m_machine->transaction()->GoodPrice = obj["goodPrice"].toDouble();
                    if(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity != price)
                        m_machine->transaction()->moneyCalculate = price;
                    else{
                        m_machine->transaction()->moneyCalculate = 0;
                        LOG<<"đơn hàng bình thường";
                    }

                }
                if (obj.contains("idSale")){
                    m_machine->transaction()->idSale = obj["idSale"].toString();
                }
                if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
                    int price = obj["reducedValue"].toInt();
                    m_machine->transaction()->reducedValue = price;
                }
                Rfid_Data->updateRfidData(m_machine);
                m_machine->setState(MACHINE_STATE::RFID_DATA);
                ui->stackedWidget->setCurrentIndex(m_machine->state());
               // process_state(MACHINE_STATE::CHARGE_COUPON);
               // m_machine->input(Qt::Key_F);
            }else if(code == 22){
                // mã gắn kết có km
                if (obj.contains("priceSale") && !obj["priceSale"].isNull() && obj["priceSale"].isDouble()){
                    quint32 price = obj["priceSale"].toDouble();
                   // m_machine->transaction()->GoodPrice = obj["goodPrice"].toDouble();
                    if(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity != price)
                        m_machine->transaction()->moneyCalculate = price;
                    else{
                        m_machine->transaction()->moneyCalculate = 0;
                        LOG<<"đơn hàng bình thường";
                    }

                }
                if (obj.contains("idSale")){
                    m_machine->transaction()->idSale = obj["idSale"].toString();
                }
                if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
                    int price = obj["reducedValue"].toInt();
                    m_machine->transaction()->reducedValue = price;
                }
                process_state(MACHINE_STATE::PIN_USER_COUPON_SAB);
                //m_machine->input(Qt::Key_L);
            }
            else{
                LOG<<code<< "code = #";
                process_state(MACHINE_STATE::RFID_DATA);
//                if (obj.contains("TimeDelayCoupon") && !obj["TimeDelayCoupon"].isNull() && obj["TimeDelayCoupon"].isDouble()){
//                    m_machine->transaction()->TimeDelayCoupon = obj["TimeDelayCoupon"].toDouble();
//                    LOG<<m_machine->transaction()->TimeDelayCoupon<<"timedelayCoupon";
//                    m_machine->input(Qt::Key_S);
//                }else{
//                    m_machine->input(Qt::Key_G);
//                }
            }
        }

    }
    else if(m_machine->state() == MACHINE_STATE::CHARGE_MPOS && m_machine->transaction()->TransactionStatus == KioskTransactionStatus::PAYMENT_WAITING){
        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
       // QByteArray hash = QCryptographicHash::hash(s.toUtf8(),QCryptographicHash::Md5);
        if(obj.contains("statusPay") ){
           // int statusPay = obj["statusPay"].toInt();
            QString signature;
            if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER)
                signature = m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->amount_and_fee) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
            else{
                if(m_machine->transaction()->moneyCalculate == 0){
                    signature = m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                }else{
                    signature = m_machine->transaction()->MachineId + m_machine->transaction()->TransactionId +QString::number(m_machine->transaction()->moneyCalculate) + m_machine->GetValueKioskAdmin("Administrator","PasswordEncode");
                }
            }
            QString sign = QCryptographicHash::hash(signature.toUtf8(),QCryptographicHash::Md5).toHex();
            if(obj["statusPay"].toInt() == 0 && obj["transactionId"].toString() == m_machine->transaction()->TransactionId && obj["signature"].toString() == sign){
                if(m_machine->transaction()->BuyType == "MenuBuy"){
                    m_machine->transaction()->IsCheckingWorkWithVTC = true;
                    m_machine->transaction()->TransactionStatus = KioskTransactionStatus::RETURN_GOOD_WAITING;
                    process_state(MACHINE_STATE::GOOD_DIGITAL_PROCESS);

                }else{
                    m_machine->transaction()->TransactionStatus = KioskTransactionStatus::RETURN_GOOD_WAITING;
                    process_state(GET_GOOD_GENERAL);
                }
            }else{
                LOG<<signature<<sign;
            }
        }else{
            if (obj.contains("TransferId") && !obj["TransferId"].isNull() && obj["TransferId"].isString()){
                m_machine->transaction()->TransferId  = obj["TransferId"].toString();

            }
            LOG;
        }

    }
    else if(m_machine->state() == MACHINE_STATE::TOPUPPARTNER){
        m_machine->transaction()->Invoice = QString(message.payload());
        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
        if (obj.contains("description") && !obj["description"].isNull() && obj["description"].isString()){
            m_machine->transaction()->MessageRechargeMobile  = obj["description"].toString();
            LOG<<m_machine->transaction()->MessageRechargeMobile;
        }
        if (obj.contains("bills") && obj["bills"].isArray()){
//            QJsonArray trayArray = obj["bills"].toArray();

//            if (!docobj["machine"].isObject()) return;
//            QJsonObject obj = docobj["machine"].toObject();

            process_state(MACHINE_STATE::BILLINFO);
        }else{
            ScreenTopupPartner->UpdateGetBillInfoFail(m_machine);
        }

        if (obj.contains("reducedValue") && !obj["reducedValue"].isNull() && obj["reducedValue"].isDouble()){
            m_machine->transaction()->reducedValue = obj["reducedValue"].toInt();
        }
        if (obj.contains("idSale")){
            m_machine->transaction()->idSale = obj["idSale"].toString();
        }

    }else if(m_machine->state() == MACHINE_STATE::ADMIN_LOGIN){
        QJsonDocument doc = QJsonDocument::fromJson(message.payload());
        QJsonObject obj = doc.object();
        if (obj.contains("description") && !obj["description"].isNull() && obj["description"].isString()){
            m_machine->transaction()->MessageRechargeMobile  = obj["description"].toString();
            LOG<<m_machine->transaction()->MessageRechargeMobile;
        }
        if (obj.contains("code") && !obj["code"].isNull() && obj["code"].isDouble()){
            int code = obj["code"].toInt();
            if(code == 0){
                if(obj["listAdminFuntion"].toString().isNull() || obj["listAdminFuntion"].toString().isEmpty()){
                    Admin_Login_Success("all");
                }else{
                    Admin_Login_Success(obj["listAdminFuntion"].toString());
                }
            }else{
                Admin_Login_Success("fail");
            }
        }

    }
    else if(m_machine->state() == MACHINE_STATE::ADMIN_PROCESS){
//        if(SCreenAdminProcess->GetSelected() == "Cập nhật quy cách từ VMS"){
//            LOG<<"hh vật lí";
//            process_message_MenuGoodGeneralTable(message.payload());
//        }else if(SCreenAdminProcess->GetSelected() == "Chốt doanh thu"){

//        }
    }
    queue->ack(message);
    if(message.routingKey().endsWith("command.exitApp")){
        QTimer *timer = new QTimer;
        timer->start(3000);
        connect(timer, SIGNAL(timeout()), this, SLOT(exitApp()));

    }

}

void MainWindow::downloadFinished(QNetworkReply *reply)
{
    if(UrlImageType == URL_IMAGE::MENU_GOOD_GENERAL){
        if(index_RequestUrl < list_goodId.size()){
            QByteArray image = reply->readAll();
            if(!image.isNull()){
                QFile DbFile(DatabaseDataStoragePath + "/" + list_goodId.at(index_RequestUrl) + ".png");
              //  if(!DbFile.exists())
                if(DbFile.open(QIODevice::ReadWrite)){
                    if(!image.isEmpty()){
                        DbFile.write(image);
                    }
                    else
                        LOG<<"lấy ảnh thất bại";
                }
                DbFile.close();
            }else{
                LOG<<"không lấy đc data ảnh";
            }
            index_RequestUrl++;
            if(index_RequestUrl < list_goodId.size()){
                requestUrl(m_machine->getImageUrlMenuGoodGeneral(list_goodId.at(index_RequestUrl)));
            }else{
                index_RequestUrl = 0;
                LOG<<list_goodId.at(index_RequestUrl)<<index_RequestUrl<<"kết thúc lấy ảnh từ url";
            }

        }
    }else if(UrlImageType == URL_IMAGE::PROMOTION_IMAGE){
        if(index_RequestUrl < list_PromotionImage.size()){
            QByteArray image = reply->readAll();
            QFile DbFile(DatabaseDataStoragePath + "/" + "promotion" + QString::number(index_RequestUrl) + ".png");

            if(DbFile.open(QIODevice::ReadWrite)){
                if(!image.isEmpty()){
                    DbFile.write(image);
                  //  LOG<<index_RequestUrl<<"lưu ảnh thành công";
                }
                else
                    LOG<<"lấy ảnh thất bại";
            }
            DbFile.close();
            index_RequestUrl++;
            if(index_RequestUrl < list_PromotionImage.size()){
                requestUrl(list_PromotionImage.at(index_RequestUrl));
            }else{
                index_RequestUrl = 0;
              //  LOG<<list_goodId.at(index_RequestUrl)<<index_RequestUrl<<"kết thúc lấy ảnh từ url";
            }
        }
    }

}

void MainWindow::requestUrl(QString Url)
{
   // LOG<<Url<<"gửi yêu cầu lấy ảnh";
    const QUrl url = QUrl(Url);
    QNetworkRequest request(url);
    NetworkAccessManager->get(request);
}

void MainWindow::process_select_service(QString service)
{
    LOG<<service<<"tên dịch vụ";
    if(m_timer.isActive()){
        m_timer.stop();
        m_timer.setInterval(m_machine->config.getScreenTimeout());
    }
    m_machine->transaction()->BuyType = "MenuBuy";
    if(service == "back_select_service"){

        if (m_machine->transaction()->AvailableAmount > 0) {
            m_timer.start();
        }
        m_khayhang.ConvertQueryMode();
        ScreenMenuGood->UpdateBillAmount();

        m_machine->transaction()->init(m_machine->saleSession()->SessionId);
        ScreenMenuGood->StartTimer();
        m_machine->setState(MACHINE_STATE::MENU);
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(service.contains("Nạp tiền điện thoại trả trước",Qt::CaseInsensitive)){
        m_machine->transaction()->serviceCode = RECHARGEMOBILETYPE::TOPUP_TELCO;
        m_machine->transaction()->Industry = "Nạp tiền điện thoại trả trước";
        m_machine->setState(MACHINE_STATE::TOPUPTELCO);
        ScreenTopupTelco = new topup_telco(m_machine);
        ui->stackedWidget->insertWidget(MACHINE_STATE::TOPUPTELCO, ScreenTopupTelco);
        connect(ScreenTopupTelco, SIGNAL(Signal_ToupupTelco(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        ui->stackedWidget->setCurrentIndex(MACHINE_STATE::TOPUPTELCO);
        QInputMethod *input = QApplication::inputMethod();
        input->show();
        m_timer.start();
    }else if(service.contains("Nạp tiền điện thoại trả sau",Qt::CaseInsensitive)){
        m_machine->transaction()->serviceCode = RECHARGEMOBILETYPE::POSTPAID;
        m_machine->transaction()->Industry = "Nạp tiền điện thoại trả sau";
        m_machine->setState(MACHINE_STATE::POST_PAID);
        ScreenPostPaid = new Postpaid(m_machine);
        ui->stackedWidget->insertWidget(MACHINE_STATE::POST_PAID, ScreenPostPaid);
        connect(ScreenPostPaid, SIGNAL(Signal_Postpaid(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        ui->stackedWidget->setCurrentIndex(MACHINE_STATE::POST_PAID);
        QInputMethod *input = QApplication::inputMethod();
        input->show();
        m_timer.start();

    }else if(service.contains("Mua thẻ điện thoại",Qt::CaseInsensitive) || service.contains("Mua thẻ Data 3G",Qt::CaseInsensitive) || service.contains("Mua thẻ Game",Qt::CaseInsensitive)){
        m_machine->setState(MACHINE_STATE::BUY_CARD_MOBILE);
        m_machine->transaction()->serviceCode = RECHARGEMOBILETYPE::BUYCARDMOBILE;
        m_machine->transaction()->Industry = service;
        BuyCardMobile = new buy_card(m_machine);
        ui->stackedWidget->insertWidget(MACHINE_STATE::BUY_CARD_MOBILE, BuyCardMobile);
        connect(BuyCardMobile, SIGNAL(Signal_BuyCard(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        ui->stackedWidget->setCurrentIndex(MACHINE_STATE::BUY_CARD_MOBILE);
        m_timer.start();
    }else if(service.contains("tiền điện",Qt::CaseInsensitive) || service.contains("tiền nước",Qt::CaseInsensitive)){
        m_machine->setState(MACHINE_STATE::TOPUPPARTNER);
        m_machine->transaction()->serviceCode = RECHARGEMOBILETYPE::TOPUP_PARTNER;
        m_machine->transaction()->Industry = service;
        m_machine->transaction()->customerID = "";
        m_machine->transaction()->CategoryId = 0;
        ScreenTopupPartner = new topup_partner(m_machine);
        ui->stackedWidget->insertWidget(MACHINE_STATE::TOPUPPARTNER, ScreenTopupPartner);
        connect(ScreenTopupPartner, SIGNAL(Signal_TopupPartner(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        ui->stackedWidget->setCurrentIndex(MACHINE_STATE::TOPUPPARTNER);
        QInputMethod *input = QApplication::inputMethod();
        input->show();
        m_timer.start();
    }else if(service.contains("Bảo hiểm",Qt::CaseInsensitive)){
        m_machine->setState(MACHINE_STATE::MOTOR_INSURANCE);
        m_machine->transaction()->serviceCode = RECHARGEMOBILETYPE::MOTORINSURANCE  ;
        m_machine->transaction()->Industry = service;
        ScreenMotorInsurance = new motor_insurance(m_machine);
        ui->stackedWidget->insertWidget(MACHINE_STATE::MOTOR_INSURANCE, ScreenMotorInsurance);
        connect(ScreenMotorInsurance, SIGNAL(Signal_MotorInsurance(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        ui->stackedWidget->setCurrentIndex(MACHINE_STATE::MOTOR_INSURANCE);

        LOG<<ui->stackedWidget->currentIndex()<<ui->stackedWidget->currentWidget()<<"chỉ số hiện tạiiiiiiiiiiii";
        m_timer.start();
    }
    else{
            m_timer.start();
    }
}

void MainWindow::process_select_good_general(QString)
{

}

void MainWindow::process_state(MACHINE_STATE state)
{
    LOG<<state<<m_machine->state()<<m_machine->last_state()<<"màn hình hiển thị";
    if(m_timer.isActive()){
        m_timer.stop();
        m_timer.setInterval(m_machine->config.getScreenTimeout());
    }
    if(m_timer_ReconnectMQ.isActive()){
        m_timer_ReconnectMQ.stop();
        m_timer_ReconnectMQ.setInterval(30000);
    }

    m_machine->setState(state);
    if(m_machine->state() == MACHINE_STATE::SELECT_CHARGE_TYPE){
        m_machine->transaction()->moneyCalculate = 0;
        if(m_machine->last_state() == MACHINE_STATE::TOPUPTELCO || m_machine->last_state() == MACHINE_STATE::BUY_CARD_MOBILE
                || m_machine->last_state() == MACHINE_STATE::POST_PAID || m_machine->last_state() == MACHINE_STATE::BILLINFO || m_machine->last_state() == MACHINE_STATE::MOTOR_INSURANCE){

            //m_machine->transaction()->ListTypeGood = m_machine->getListGoodType("Nạp tiền điện thoại trả trước");
             //m_machine->transaction()->ListPriceGood = m_machine->getListGoodPrice("Nạp tiền điện thoại trả trước", m_machine->transaction()->goodType);
            if(m_machine->last_state() == MACHINE_STATE::TOPUPTELCO){
                m_machine->transaction()->goodType = ScreenTopupTelco->HomeNetwork_TopupTelco();
                m_machine->transaction()->GoodPrice = ScreenTopupTelco->Price_TopupTelco();
                m_machine->transaction()->NumberPhone = ScreenTopupTelco->NumberPhone_TopupTelco();
            }else if(m_machine->last_state() == MACHINE_STATE::BUY_CARD_MOBILE){
                m_machine->transaction()->goodType = BuyCardMobile->HomeNetwork_BuyCard();
                m_machine->transaction()->GoodPrice = BuyCardMobile->Price_BuyCard();
            }else if(m_machine->last_state() == MACHINE_STATE::POST_PAID){
                if(m_machine->transaction()->Industry == "Nạp tiền điện thoại trả sau"){
                    m_machine->transaction()->goodType = ScreenPostPaid->Partner_Postpaid();
                    m_machine->transaction()->GoodPrice = ScreenPostPaid->Price_Postpaid();
                    LOG<<m_machine->transaction()->GoodPrice<<"giá trả sau";
                    m_machine->transaction()->NumberPhone = ScreenPostPaid->NumberPhone_Postpaid();
                    m_machine->transaction()->GoodId = m_machine->getGoodId1InMenuTable(m_machine->transaction()->Industry, m_machine->transaction()->goodType);
                }
            }else if(m_machine->last_state() == MACHINE_STATE::BILLINFO){
                QJsonDocument doc = QJsonDocument::fromJson(m_machine->transaction()->Invoice.toUtf8());
                QJsonObject obj = doc.object();
                QJsonObject customer = obj["customer"].toObject();
                QJsonArray BillArray = obj["bills"].toArray();
                quint8 index = ScreenBillInfo->SelectBillIndex();
                QJsonObject BillObject = BillArray[index].toObject();
                m_machine->transaction()->GoodPrice = BillObject["amount"].toString().toInt();
                m_machine->transaction()->productID = obj["productID"].toString();
                m_machine->transaction()->amount_and_fee = BillObject["amount_and_fee"].toString().toInt();
                m_machine->transaction()->bill_number = BillObject["bill_number"].toString();
                LOG<<index<<m_machine->transaction()->GoodPrice<<"giá hóa đơn";

            }else if(m_machine->last_state() == MACHINE_STATE::MOTOR_INSURANCE){
                m_machine->transaction()->Motor_Insurance_Info = ScreenMotorInsurance->GetOwnerOfMotorInfo();
                m_machine->transaction()->GoodId = m_machine->getGoodId1InMenuTable(m_machine->transaction()->Industry,ScreenMotorInsurance->getDurationOfInsurance());
                m_machine->transaction()->GoodPrice = m_machine->getGoodPriceInMenuTable(m_machine->transaction()->GoodId);
                LOG<<m_machine->transaction()->GoodId<<m_machine->transaction()->GoodPrice<<"bảo hiểm xe máy";
            }
            m_machine->transaction()->nameServer = m_machine->getNameServerInMenuTable(m_machine->transaction()->goodType,m_machine->transaction()->GoodPrice);
            if(m_machine->last_state() != MACHINE_STATE::POST_PAID && m_machine->last_state() != MACHINE_STATE::BILLINFO && m_machine->last_state() != MACHINE_STATE::MOTOR_INSURANCE)
                m_machine->transaction()->GoodId  = m_machine->getGoodIdInMenuTable(m_machine->transaction()->goodType,m_machine->transaction()->GoodPrice);
            m_machine->transaction()->SlotId  =  "0";
            m_machine->transaction()->GoodName  = m_machine->getGoodNameInMenuTable(m_machine->transaction()->GoodId);
            m_machine->transaction()->GoodPriceGeneral = m_machine->transaction()->GoodPrice;
            m_machine->transaction()->Quantity  = 1;
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::INIT;
            m_machine->transaction()->CheckPriceServe = false;
            m_machine->transaction()->OrderInformation = "";
          //  m_machine->transaction()->IsCheckingWorkWithVTC = false;
            if(m_machine->getShareSalePermissionInMenuTable(m_machine->transaction()->GoodId) == "true"){
                m_machine->transaction()->CheckSaleSharePermission = true;
            }else{
                m_machine->transaction()->CheckSaleSharePermission = false;
            }
            if(m_machine->getChargeTypeQuatityInMenuTable(m_machine->transaction()->GoodId) == 0){
                SelectChargeType = new select_charge_type(m_machine,m_machine->GetValueKioskAdmin("ChargeTypeListDefault","ListChargeType").split(QLatin1Char(',')));
            }else{
                SelectChargeType = new select_charge_type(m_machine,m_machine->getListChargeTypeInMenuTable(m_machine->transaction()->GoodId).split(QLatin1Char(',')));
            }
            ui->stackedWidget->insertWidget(MACHINE_STATE::SELECT_CHARGE_TYPE, SelectChargeType);
            connect(SelectChargeType, SIGNAL(Signal_Select_Charge_Type(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        }else if(m_machine->last_state() == MACHINE_STATE::SCREEN_QRCODE || m_machine->last_state() == MACHINE_STATE::CHARGED_COUPON || m_machine->last_state() == MACHINE_STATE::PIN_USER_COUPON_SAB || m_machine->last_state() == MACHINE_STATE::RFID_DATA_PAYMENT_WAITING){
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::CANCEL;
            m_machine->UpdateDB();
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                topic_logs->publish(m_machine->transaction()->toAPIString()
                                    ,QString("%1.transactions").arg(m_machine->transaction()->MachineId)
                                    ,properties);
            }
            m_machine->init_transaction_keep_info();
        }else if(m_machine->last_state() == MACHINE_STATE::CHARGE_COUPON || m_machine->last_state() == MACHINE_STATE::RFID_DATA){
            m_machine->init_transaction_keep_info();
            m_khayhang.ConvertQueryMode();
        }
        else if(m_machine->last_state() == MACHINE_STATE::CHARGE_MPOS && m_machine->transaction()->TransactionStatus == KioskTransactionStatus::PAYMENT_WAITING){
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::CANCEL;
            m_machine->UpdateDB();
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                topic_logs->publish(m_machine->transaction()->toAPIString()
                                    ,QString("%1.transactions").arg(m_machine->transaction()->MachineId)
                                    ,properties);
            }
            m_machine->init_transaction_keep_info();
        }else if(m_machine->last_state() == MACHINE_STATE::CHARGE_MPOS && m_machine->transaction()->TransactionStatus == KioskTransactionStatus::INIT){
            m_machine->init_transaction_keep_info();
            m_khayhang.ConvertQueryMode();
        }
        else if(m_machine->last_state() == MACHINE_STATE::GOOD_DIGITAL_PROCESS){
            if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE
            || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID
            || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONGENERALSAB
            || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPINSAB
            || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONRECHARGESAB){
                m_machine->init_transaction_keep_info();
            }
        }else if(m_machine->last_state() == MACHINE_STATE::MENU_GOOD_GENERAL){
           // m_machine->transaction()->GoodId = ScreenMenuGoodGeneral->GetSelectGood();
//            for (int i = 1; i <= m_machine->config.getTrayCount() ; i++)
//            {
//               // LOG<<"aaaaaa";
//                bool flag = true;
//                int SlotCount = m_machine->config.getSlotCountForTray(i);
//                if (SlotCount > 0)
//                {
//                    for (int j = 0; j < SlotCount; j++)
//                    {
//                      //  LOG<<"fdfdf";
//                        if(m_machine->config.getIdForSlot(i, j) == m_machine->transaction()->GoodId){
//                            if(m_machine->config.getGoodCountForSlot(i, j) > 0){
//                                m_machine->transaction()->SlotId = QString::number(i) + QString::number(j);
//                                flag = false;
//                                break;
//                            }
//                        }
//                    }
//                }
//                if(!flag)
//                    break;
//                //            m_ds_khay.append(k);
//            }
            LOG<<m_machine->transaction()->SlotId<<m_machine->transaction()->Quantity<<m_machine->GetGoodQuatity(m_machine->transaction()->GoodId)<<m_machine->transaction()->GoodId<<"slot hh";
            m_machine->transaction()->GoodName  = m_machine->getGoodNameInMenuGeneralTable(m_machine->transaction()->GoodId);
            m_machine->transaction()->GoodPrice = m_machine->getGoodPriceInMenuGeneralTable(m_machine->transaction()->GoodId);
            m_machine->transaction()->GoodPriceGeneral = m_machine->transaction()->GoodPrice;
           // m_machine->transaction()->Quantity  = 1;
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::INIT;
            m_machine->transaction()->CheckPriceServe = false;
            m_machine->transaction()->OrderInformation = "";
            if(m_machine->getShareSalePermissionInMenuGeneralTable(m_machine->transaction()->GoodId) == "true"){
                m_machine->transaction()->CheckSaleSharePermission = true;
            }else{
                m_machine->transaction()->CheckSaleSharePermission = false;
            }
            if(m_machine->getChargeTypeQuatityInMenuGeneralTable(m_machine->transaction()->GoodId) == 0){
                SelectChargeType = new select_charge_type(m_machine,m_machine->GetValueKioskAdmin("ChargeTypeListDefault","ListChargeType").split(QLatin1Char(',')));
            }else{
                SelectChargeType = new select_charge_type(m_machine,m_machine->getListChargeTypeInMenuGeneralTable(m_machine->transaction()->GoodId).split(","));
            }
            ui->stackedWidget->insertWidget(MACHINE_STATE::SELECT_CHARGE_TYPE, SelectChargeType);
            connect(SelectChargeType, SIGNAL(Signal_Select_Charge_Type(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        }
        SelectChargeType->UpdateBillAmount();
        m_timer.start();

    }else if(m_machine->state() == MACHINE_STATE::SALEINFO_QRCODE){
       // m_machine->transaction()->TransactionType = SelectChargeType->ChargeType_Select();
        InfoSaleQrCode = new infoSale_qr_code(m_machine, m_machine->transaction()->serviceCode);
        connect(InfoSaleQrCode, SIGNAL(Signal_infoSale_QRcode(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        ui->stackedWidget->insertWidget(MACHINE_STATE::SALEINFO_QRCODE, InfoSaleQrCode);
        if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER
                ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONGENERALSAB|| m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPINSAB
                ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPROMOTIONSAB||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONRECHARGESAB){
            m_machine->transaction()->CheckPriceServe = true;
            ui->stackedWidget->setCurrentIndex(m_machine->state());
            InfoSaleQrCode->updateInfoSaleQR(m_machine);
        }else{
            m_machine->transaction()->CheckPriceServe = false;
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG ;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->transaction()->MachineId;
                properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish(m_machine->transaction()->GetPriceSever()
                                    ,QString("%1.request.getPriceSever").arg(m_machine->transaction()->MachineId)
                                    ,properties);
            }
            m_timer_ReconnectMQ.start();
        }
        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::SCREEN_GET_QRCODE){
        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::PAYMENT_WAITING;
        m_machine->CreatDB();
       // QR_Code_Screen = new QR_code(this);
      //  connect(QR_Code_Screen, SIGNAL(Signal_QR_Code(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
      //  ui->stackedWidget->insertWidget(SCREEN_QRCODE, QR_Code_Screen);
        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
            LOG;
            QAmqpMessage::PropertyHash properties;
            properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
            m_correlationId = m_machine->transaction()->MachineId;
            properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
            properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
            topic_logs->publish(m_machine->transaction()->toAPIString()
                                ,QString("%1.request.generateQRCodeForTransaction").arg(m_machine->transaction()->MachineId)
                                ,properties);
        }
        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::SCREEN_QRCODE){

         QR_Code_Screen = new QR_code(m_machine->transaction()->OrderInformation, m_machine->transaction()->TransactionType);
         connect(QR_Code_Screen, SIGNAL(Signal_QR_Code(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
         ui->stackedWidget->insertWidget(MACHINE_STATE::SCREEN_QRCODE, QR_Code_Screen);
         m_timer.setInterval(m_machine->config.getQRCodeTimeout());
         m_timer.start();
         if(m_machine->transaction()->OrderInformation != ""){
             m_timer_ReconnectMQ.setInterval(120000);
             m_timer_ReconnectMQ.start();
         }

    }else if(m_machine->state() == MACHINE_STATE::CHARGE_COUPON){
        if(m_machine->last_state() == MACHINE_STATE::CHARGED_COUPON){
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::FAILED;
            m_machine->UpdateDB();
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::PAYMENT_WAITING;
            m_machine->transaction()->TransferId = "";
            Charge_Coupon->updateChargeCouponFail(m_machine);
        }else{
            //m_machine->transaction()->TransactionType = SelectChargeType->ChargeType_Select();
            Charge_Coupon = new charge_coupon(m_machine, m_machine->transaction()->serviceCode);
            connect(Charge_Coupon, SIGNAL(Signal_ChargeCoupon(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
            ui->stackedWidget->insertWidget(MACHINE_STATE::CHARGE_COUPON, Charge_Coupon);
            ui->stackedWidget->setCurrentIndex(MACHINE_STATE::CHARGE_COUPON);
            QInputMethod *input = QApplication::inputMethod();
            input->show();
           // Charge_Coupon->showKeyboard();
            if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER
                    ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONGENERALSAB|| m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPINSAB
                    ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPROMOTIONSAB||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONRECHARGESAB){
                m_machine->transaction()->CheckPriceServe = true;
                Charge_Coupon->updateChargeCoupon(m_machine);
            }else{
                if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                    LOG;
                    QAmqpMessage::PropertyHash properties;
                    properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                    m_correlationId = m_machine->transaction()->MachineId;
                    properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
                    properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                    topic_logs->publish(m_machine->transaction()->GetPriceSever()
                                        ,QString("%1.request.getPriceSever").arg(m_machine->transaction()->MachineId)
                                        ,properties);
                }
                m_timer_ReconnectMQ.start();

            }
        }
        m_timer.start();

    }else if(m_machine->state() == MACHINE_STATE::RFID_DATA){
            if(m_machine->last_state() == MACHINE_STATE::RFID_DATA_PAYMENT_WAITING){
                m_machine->transaction()->TransactionStatus = KioskTransactionStatus::FAILED;
                m_machine->UpdateDB();
                m_machine->transaction()->TransactionStatus = KioskTransactionStatus::PAYMENT_WAITING;
                m_machine->transaction()->TransferId = "";
                Rfid_Data->updateRfidData(m_machine);
            }else{
                //m_machine->transaction()->TransactionType = SelectChargeType->ChargeType_Select();
                m_khayhang.ConvertRFIDMode();
                Rfid_Data = new rfid_data_processor(m_machine);
                connect(Rfid_Data, SIGNAL(Signal_RfidData(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
                connect(Rfid_Data, SIGNAL(Signal_RfidData1(QString)), this, SLOT(onStatus(QString)));

                ui->stackedWidget->insertWidget(MACHINE_STATE::RFID_DATA, Rfid_Data);
//                QInputMethod *input = QApplication::inputMethod();
//                input->show();
               // Charge_Coupon->showKeyboard();
                if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER
                        ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONGENERALSAB|| m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPINSAB
                        ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPROMOTIONSAB||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONRECHARGESAB){
                    m_machine->transaction()->CheckPriceServe = true;
                    Rfid_Data->updateRfidData(m_machine);
                }else{
                    if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                        LOG;
                        QAmqpMessage::PropertyHash properties;
                        properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                        m_correlationId = m_machine->transaction()->MachineId;
                        properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
                        properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                        topic_logs->publish(m_machine->transaction()->GetPriceSever()
                                            ,QString("%1.request.getPriceSever").arg(m_machine->transaction()->MachineId)
                                            ,properties);
                    }
                    m_timer_ReconnectMQ.start();

                }
            }
            m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::CHARGE_MPOS){
        if(m_machine->transaction()->TransactionStatus == KioskTransactionStatus::PAYMENT_WAITING){
            m_machine->CreatDB();
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->config.getMachineId();
                properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish(m_machine->transaction()->toAPIString()
                                    ,QString("%1.request.comfirmPaymentMpos").arg(m_machine->config.getMachineId())
                                    ,properties);
            }
            m_timer.setInterval(m_machine->config.getQRCodeTimeout());
            m_timer.start();
        }else{
            //m_machine->transaction()->TransactionType = SelectChargeType->ChargeType_Select();
            m_khayhang.ConvertRFIDMode();
            Charge_mpos = new charge_mpos_processor(m_machine);
            connect(Charge_mpos, SIGNAL(Signal_ChargeMpos(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));

            ui->stackedWidget->insertWidget(MACHINE_STATE::CHARGE_MPOS, Charge_mpos);
//                QInputMethod *input = QApplication::inputMethod();
//                input->show();
           // Charge_Coupon->showKeyboard();
            if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER
                    ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONGENERALSAB|| m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPINSAB
                    ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPROMOTIONSAB||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONRECHARGESAB){
                m_machine->transaction()->CheckPriceServe = true;
                Charge_mpos->updateChargeMpos(m_machine);
            }else{
                if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                    LOG;
                    QAmqpMessage::PropertyHash properties;
                    properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                    m_correlationId = m_machine->transaction()->MachineId;
                    properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
                    properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                    topic_logs->publish(m_machine->transaction()->GetPriceSever()
                                        ,QString("%1.request.getPriceSever").arg(m_machine->transaction()->MachineId)
                                        ,properties);
                }
                m_timer_ReconnectMQ.start();

            }
        }
        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::CHARGED_COUPON){
        if(m_machine->last_state() == MACHINE_STATE::CHARGE_COUPON){
            m_machine->transaction()->OrderInformation = Charge_Coupon->getOrderInformation();
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::PAYMENT_WAITING;
            m_machine->CreatDB();
            m_machine->transaction()->PinUserRechargeCoupon = "";
            LOG<<m_machine->transaction()->OrderInformation<<"mã coupon";
            Charged_Coupon = new charged_coupon(m_machine, m_machine->transaction()->serviceCode);
            connect(Charged_Coupon, SIGNAL(Signal_ChargedCoupon(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
            ui->stackedWidget->insertWidget(MACHINE_STATE::CHARGED_COUPON, Charged_Coupon);
        }else if(m_machine->last_state() == MACHINE_STATE::PIN_USER_COUPON_SAB){
            m_machine->transaction()->PinUserRechargeCoupon = PinUserCouponSab->getPinUserCoupon();
        }
        if(m_machine->transaction()->TransactionStatus == KioskTransactionStatus::PAYMENT_WAITING){
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->transaction()->MachineId;
                properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish(m_machine->transaction()->toAPIString()
                                    ,QString("%1.request.getCouponInfo").arg(m_machine->transaction()->MachineId)
                                    ,properties);
            }
        }

        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::RFID_DATA_PAYMENT_WAITING){
        m_khayhang.ConvertQueryMode();
        if(m_machine->last_state() == MACHINE_STATE::RFID_DATA){
            m_machine->transaction()->OrderInformation = m_machine->transaction()->RfidData;
           // m_machine->transaction()->CouponCode = m_machine->transaction()->RfidData;
            m_machine->transaction()->PinUserRechargeCoupon = "";
            //m_machine->transaction()->OrderInformation = Charge_Coupon->getOrderInformation();
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::PAYMENT_WAITING;
            m_machine->CreatDB();
            Rfid_Data_Payment_Waitting = new rfid_data_payment_waitting(m_machine);
            connect(Rfid_Data_Payment_Waitting, SIGNAL(Signal_RfidDataPaymentWaittng(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
            ui->stackedWidget->insertWidget(MACHINE_STATE::RFID_DATA_PAYMENT_WAITING, Rfid_Data_Payment_Waitting);
        }else if(m_machine->last_state() == MACHINE_STATE::PIN_USER_COUPON_SAB){
            m_machine->transaction()->PinUserRechargeCoupon = PinUserCouponSab->getPinUserCoupon();
        }
        if(m_machine->transaction()->TransactionStatus == KioskTransactionStatus::PAYMENT_WAITING){
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->transaction()->MachineId;
                properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish(m_machine->transaction()->toAPIString()
                                    ,QString("%1.request.getCouponInfo").arg(m_machine->transaction()->MachineId)
                                    ,properties);
            }
        }

        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::GOOD_DIGITAL_PROCESS){
        LOG<<"llllll";
        if(m_machine->transaction()->TransactionStatus == KioskTransactionStatus::FAILED || m_machine->transaction()->TransactionStatus == KioskTransactionStatus::ERROR){
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";
                topic_logs->publish(m_machine->transaction()->toAPIString()
                                    ,QString("%1.transactions").arg(m_machine->transaction()->MachineId)
                                    ,properties);
            }
            m_machine->transaction()->TransferId = "";
            m_machine->transaction()->InputAmount = 0;
            Good_Digital_Process->updateGoodDigitalProcess(m_machine);
        }else if(m_machine->transaction()->TransactionStatus == KioskTransactionStatus::RETURN_GOOD_WAITING && m_machine->transaction()->TransactionType != KioskTransactionType::CASH){
            LOG;
            Good_Digital_Process = new good_digital_process(m_machine);
            connect(Good_Digital_Process, SIGNAL(Signal_GoodDigital_Process(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
            ui->stackedWidget->insertWidget(GOOD_DIGITAL_PROCESS, Good_Digital_Process);
            Good_Digital_Process->setGoodDigitalProcess(m_machine);

        }else if(m_machine->transaction()->TransactionStatus != KioskTransactionStatus::RETURN_GOOD_WAITING && m_machine->transaction()->TransactionType == KioskTransactionType::CASH){
            Good_Digital_Process = new good_digital_process(m_machine);
            connect(Good_Digital_Process, SIGNAL(Signal_GoodDigital_Process(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
            ui->stackedWidget->insertWidget(GOOD_DIGITAL_PROCESS, Good_Digital_Process);
            Good_Digital_Process->setGetPriceGoodDigitalProcess(m_machine);
        }
        if(m_machine->transaction()->TransactionStatus == KioskTransactionStatus::RETURN_GOOD_WAITING){
            Good_Digital_Process->setGoodDigitalProcess(m_machine);
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->transaction()->MachineId;
                properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
                    topic_logs->publish(m_machine->transaction()->toRechargeInvoiceTopupPartner()
                                        ,QString("%1.request.goodsdigital").arg(m_machine->transaction()->MachineId)
                                        ,properties);
                }else if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
                    topic_logs->publish(m_machine->transaction()->toRechargeMotorInsurance()
                                        ,QString("%1.request.insurance").arg(m_machine->transaction()->MachineId)
                                        ,properties);
                }
                else{
                    topic_logs->publish(m_machine->transaction()->toRechargeCardMobile()
                                        ,QString("%1.request.goodsdigital").arg(m_machine->transaction()->MachineId)
                                        ,properties);
                }
            }
        }else if(m_machine->last_state() == SELECT_CHARGE_TYPE){
            if(m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID || m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER
            ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONGENERALSAB|| m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPINSAB
            ||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONPROMOTIONSAB||m_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::COUPONRECHARGESAB){
                Good_Digital_Process->updateGoodDigitalProcess(m_machine);
                m_machine->transaction()->CheckPriceServe = true;
                m_machine->transaction()->IsCheckingWorkWithVTC = false;
            }else{
                m_machine->transaction()->CheckPriceServe = false;
                m_machine->transaction()->IsCheckingWorkWithVTC = false;
                m_machine->transaction()->TransactionStatus = KioskTransactionStatus::PAYMENT_WAITING;
                if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                    LOG;
                    QAmqpMessage::PropertyHash properties;
                    properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                    m_correlationId = m_machine->config.getMachineId();
                    properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                    properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                    topic_logs->publish(m_machine->transaction()->GetPriceSever()
                                        ,QString("%1.request.getPriceSever").arg(m_machine->transaction()->MachineId)
                                        ,properties);
                }else{
                    //data.insert("Price", m_machine->config.getDisplayLanguage(m_machine->CheckLanguageScreen + "_Language", "153"));
                }

            }
        }
        if(m_machine->transaction()->IsCheckingWorkWithVTC){
            m_timer.setInterval(120000);
          //  m_rkey = Qt::Key_T;
            m_timer.start();
        }else{
            m_timer.start();
        }

    }else if(m_machine->state() == MACHINE_STATE::GET_GOOD_DIGITAL){
        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
            LOG;
            QAmqpMessage::PropertyHash properties;
            properties[QAmqpMessage::DeliveryMode] = "2";
            topic_logs->publish(m_machine->transaction()->toAPIString()
                                ,QString("%1.transactions").arg(m_machine->transaction()->MachineId)
                                ,properties);
        }
        Get_Good_Digital = new get_good_digital(m_machine, m_machine->transaction()->serviceCode);
        connect(Get_Good_Digital, SIGNAL(Signal_GetGoodDigital_Process(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        ui->stackedWidget->insertWidget(MACHINE_STATE::GET_GOOD_DIGITAL, Get_Good_Digital);
        m_timer.setInterval(m_machine->config.getGetGoodTimeout());
        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::TOPUPTELCO){
        m_timer.start();
        LOG<<"màn hình nạp tiền điện thoại";
    }else if(m_machine->state() == MACHINE_STATE::POST_PAID){
        m_timer.start();
        LOG<<"màn hình nạp tiền điện thoại trả sau";
    }else if(m_machine->state() == MACHINE_STATE::BUY_CARD_MOBILE){
        m_timer.start();
        LOG<<"màn hình mua thẻ";
    }else if(m_machine->state() == MACHINE_STATE::PIN_USER_COUPON_SAB){
        m_timer.start();
        PinUserCouponSab = new pin_user_coupon_sab(m_machine);
        connect(PinUserCouponSab, SIGNAL(Signal_PinUserCoupon(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        ui->stackedWidget->insertWidget(MACHINE_STATE::PIN_USER_COUPON_SAB, PinUserCouponSab);
        ui->stackedWidget->setCurrentIndex(MACHINE_STATE::PIN_USER_COUPON_SAB);
        QInputMethod *input = QApplication::inputMethod();
        input->show();
       // PinUserCouponSab->showKeyboard();
    }else if(m_machine->state() == MACHINE_STATE::SELECT_SERVICE){
        m_timer.start();
        m_machine->transaction()->init(m_machine->saleSession()->SessionId);
    }else if(m_machine->state() == MACHINE_STATE::TOPUPPARTNER){
        if(ui->stackedWidget->currentIndex() == MACHINE_STATE::TOPUPPARTNER){
            m_machine->transaction()->customerID = ScreenTopupPartner->customerID_TopupPartner();
            m_machine->transaction()->goodType = ScreenTopupPartner->Partner_TopupPartner();
           // m_machine->transaction()->GoodPrice = ScreenPostPaid->Price_Postpaid();
          //  m_machine->transaction()->NumberPhone = ScreenPostPaid->NumberPhone_Postpaid();
            m_machine->transaction()->GoodId = m_machine->getGoodId1InMenuTable(m_machine->transaction()->Industry, m_machine->transaction()->goodType);
            m_machine->transaction()->CategoryId = m_machine->transaction()->GoodId.mid(3).toInt();
            m_machine->transaction()->GoodName  = m_machine->getGoodNameInMenuTable(m_machine->transaction()->GoodId);
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->transaction()->MachineId;
                properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish(m_machine->transaction()->GetInvoiceTopupPartner()
                                    ,QString("%1.request.goodsdigital").arg(m_machine->transaction()->MachineId)
                                    ,properties);
            }
            m_timer_ReconnectMQ.setInterval(30000);
            m_timer_ReconnectMQ.start();
        }else{
            ScreenTopupPartner->UpdateRePartner();
            LOG;
        }


        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::BILLINFO){
        ScreenBillInfo = new BillInfo(m_machine, m_machine->transaction()->Invoice);
        ui->stackedWidget->insertWidget(MACHINE_STATE::BILLINFO, ScreenBillInfo);
        connect(ScreenBillInfo, SIGNAL(Signal_Bill_Info(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));

        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::MENU){
        if (m_machine->transaction()->AvailableAmount > 0) {
            m_timer.start();
        }
        ScreenMenuGood->StartTimer();
        m_khayhang.ConvertQueryMode();
        m_machine->transaction()->init(m_machine->saleSession()->SessionId);
        LOG<< m_machine->transaction()->IdentifiedAmount<<"tiền billlllllllllllllllll";
        ScreenMenuGood->UpdateBillAmount();
    }else if(m_machine->state() == MACHINE_STATE::MENU_GOOD_GENERAL){
        LOG<<"màn hình hh vật lí";
        ScreenMenuGoodGeneral = new menu_good_general(m_machine, DatabaseDataStoragePath);
        ui->stackedWidget->insertWidget(MACHINE_STATE::MENU_GOOD_GENERAL, ScreenMenuGoodGeneral);
        connect(ScreenMenuGoodGeneral, SIGNAL(Signal_Menu_Good_General(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
       // m_machine->setState(MACHINE_STATE::MENU_GOOD_GENERAL);
       // ui->stackedWidget->setCurrentIndex(MACHINE_STATE::MENU_GOOD_GENERAL);
       // m_machine->transaction()->serviceCode = RECHARGEMOBILETYPE::GOOD_GENERAL;
        m_machine->transaction()->BuyType = "MenuGeneralBuy";
        m_machine->transaction()->serviceCode = RECHARGEMOBILETYPE::GOOD_GENERAL;
        m_timer.start();
    }
    else if (m_machine->state()== MACHINE_STATE::TESTFORM){
       LOG<<"check testform";
       ScreenTestForm = new testform(m_machine,DatabaseDataStoragePath);
       ui->stackedWidget->insertWidget(MACHINE_STATE::TESTFORM,ScreenTestForm);
       // ui->stackedWidget->setCurrentWidget(MACHINE_STATE::TESTFORM);

       connect(ScreenTestForm,SIGNAL(Signal_Test_Form_Back(MACHINE_STATE)),this,SLOT(process_state(MACHINE_STATE)));
       ui->stackedWidget->setCurrentIndex(MACHINE_STATE::MENU_GOOD_GENERAL);
       m_timer.start();
   }
    else if(m_machine->state() == MACHINE_STATE::GET_GOOD_GENERAL){
        if(m_machine->last_state() == MACHINE_STATE::MENU_GOOD_GENERAL){
            for (int i = 1; i <= m_machine->config.getTrayCount() ; i++)
            {
                bool flag = true;
                int SlotCount = m_machine->config.getSlotCountForTray(i);
                if (SlotCount > 0)
                {
                    for (int j = 0; j < SlotCount; j++)
                    {
                        if(m_machine->config.getIdForSlot(i, j) == m_machine->transaction()->GoodId){
                            if(m_machine->config.getGoodCountForSlot(i, j) > 0){
                                m_machine->transaction()->SlotId = QString::number(i) + QString::number(j);
                                flag = false;
                                break;
                            }
                        }
                    }
                }
                if(!flag)
                    break;
                //            m_ds_khay.append(k);
            }
         //   LOG<<m_machine->transaction()->SlotId<<"slot hh";
            m_machine->transaction()->GoodName  = m_machine->getGoodNameInMenuGeneralTable(m_machine->transaction()->GoodId);
            m_machine->transaction()->GoodPrice = m_machine->getGoodPriceInMenuGeneralTable(m_machine->transaction()->GoodId);
            m_machine->transaction()->GoodPriceGeneral = m_machine->transaction()->GoodPrice;
            m_machine->transaction()->Quantity  = 1;
            m_machine->transaction()->TransactionType = KioskTransactionType::CASH;
            //m_machine->transaction()->TransactionStatus = KioskTransactionStatus::INIT;
            m_machine->transaction()->CheckPriceServe = false;
            m_machine->transaction()->OrderInformation = "";
            if(m_machine->getShareSalePermissionInMenuGeneralTable(m_machine->transaction()->GoodId) == "true"){
                m_machine->transaction()->CheckSaleSharePermission = true;
            }else{
                m_machine->transaction()->CheckSaleSharePermission = false;
            }
        }
        GetGoodGeneral = new Get_Good_General(m_machine);
        ui->stackedWidget->insertWidget(MACHINE_STATE::GET_GOOD_GENERAL, GetGoodGeneral);
        connect(GetGoodGeneral, SIGNAL(Signal_GetGoodGeneral_Process(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
    //    if(m_machine->IsReturnGoodByKiosk){
//            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
//                LOG;
//                QAmqpMessage::PropertyHash properties;
//                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
//                m_correlationId = m_machine->transaction()->MachineId;
//                properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
//                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
//                topic_logs->publish(m_machine->transaction()->toReturnGoodKiosk()
//                                    ,QString("%1.command.returnGood").arg(m_machine->transaction()->KioskId)
//                                    ,properties);
//            }
//        }else{
            m_machine->finish_transaction();
            m_khayhang.returnGoodsForTransaction(m_machine->transaction());
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::SUCCESS;
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                topic_logs->publish(m_machine->transaction()->toAPIString()
                                    ,QString("%1.transactions").arg(m_machine->config.getMachineId())
                                    ,properties);
            }


//            m_khayhang.returnGoodsForTransactionAndroid(m_machine->transaction()->SlotIdList, m_machine->transaction()->QuantityList);
//            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::SUCCESS;
//            for(int i = 0; i < m_machine->transaction()->SlotIdList.size(); i++){
//                m_machine->transaction()->SlotId = QString::number(m_machine->transaction()->SlotIdList.at(i));
//                m_machine->transaction()->Quantity = m_machine->transaction()->QuantityList.at(i);
//                LOG<<m_machine->transaction()->SlotId<<m_machine->transaction()->Quantity<<"wwwwwwwwwwwwwwwwwwwwwwwwww";
//                if(i != 0){
//                    m_machine->transaction()->InputAmount = 0;
//                    m_machine->transaction()->TransferId = "";
//                }
//                m_machine->finish_transaction();
//                if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
//                    LOG;
//                    QAmqpMessage::PropertyHash properties;
//                    properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
//                    //                            topic_logs->publish(QString("{\"machineId\":\"%6\",\"transactionId\":\"%5\",\"coupon\":\"\",\"slotId\":\"%1\",\"typePay\":\"1\",\"time\":\"1234567\",\"quantity\":\"%2\",\"moneyCalculate\":\"%3\",\"moneyInput\":\"%4\",\"status\":\"1\"}")
//                    //                                                .arg(m_machine->transaction()->GoodId)
//                    //                                                .arg(m_machine->transaction()->Quantity)
//                    //                                                .arg(m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity)
//                    //                                                .arg(m_machine->transaction()->InputAmount)
//                    //                                                .arg(m_machine->transaction()->TransactionId)
//                    //                                                .arg(m_machine->config.getMachineId())
//                    //                                                ,QString("%1.transactions").arg(m_machine->config.getMachineId())
//                    //                                                );
//                    topic_logs->publish(m_machine->transaction()->toAPIString()
//                                        ,QString("%1.transactions").arg(m_machine->config.getMachineId())
//                                        ,properties);
//                }
//            }
    //    }
        m_timer.setInterval(m_machine->config.getGetGoodTimeout());
        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::ADMIN_PROCESS){
//        if(SCreenAdminProcess->GetSelected() == "Cập nhật quy cách từ VMS"){
//            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
//                LOG;
//                QAmqpMessage::PropertyHash properties;
//                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
//                m_correlationId = m_machine->transaction()->MachineId;
//                properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
//                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
//                topic_logs->publish(QString("{\"machineId\":\"%1\"}")
//                                    .arg(m_machine->config.getMachineId())
//                                    ,QString("%1.request.getconfig").arg(m_machine->transaction()->MachineId)
//                                    ,properties);
//            }else{
//                SCreenAdminProcess->ProcessAdminFail();
//            }
//        }else if(SCreenAdminProcess->GetSelected() == "Chốt doanh thu"){
//            QString SaleInfo = "Thông tin phiên chốt số: " + m_machine->saleSession()->SessionId + " - Kì: " + m_machine->saleSession()->PrePeriod
//                    +"\n-Thời gian bắt đầu: " + m_machine->saleSession()->StartTime.toString("yyyy-MM-dd hh:mm:ss")
//                    +"\n-Thời điểm hiện tại: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
//                    +"\n-Tổng doanh thu: " + StringUtils::formatNumberVND(m_machine->saleSession()->TotalAmount) + " VND"
//                    +"\n-Tổng thực thu: " + StringUtils::formatNumberVND(m_machine->saleSession()->TotalBill) + " VND";
//            SCreenAdminProcess->GetSaleInfo(SaleInfo);
//        }else if(SCreenAdminProcess->GetSelected() == "Xác nhận chốt doanh thu"){
//            m_machine->saleSession()->IsUpdateDB = false;
//            if (!m_machine->saleSession()->IsUpdateDB && ( m_machine->saleSession()->TotalAmount > 0 || m_machine->saleSession()->TotalBill > 0 ))
//            {
//                m_machine->finish_sale_session();
//            }else{

//            }

//            if (m_machine->saleSession()->IsUpdateDB && m_queue_connected &&  topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
//                LOG;
//                m_machine->saleSession()->IsSyncing = true;
//               // m_machine->finish_sale_session();
//                QAmqpMessage::PropertyHash properties;
//                properties[QAmqpMessage::DeliveryMode] = "1";   // make message persistent
//                m_correlationId = m_machine->config.getMachineId();
//                properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
//                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
//                topic_logs->publish( QString(m_machine->saleSession()->toAPIString())
//                                     ,QString("%1.request.submitsaleinfo").arg(m_machine->transaction()->MachineId)
//                                     ,properties);
//            }
//            if(m_machine->saleSession()->IsUpdateDB){
//                SCreenAdminProcess->ProcessAdminSuccess();
//                m_machine->init_sale_session();
//            }
//        }

//        m_timer.start();
    }else if(m_machine->state() == MACHINE_STATE::MOTOR_INSURANCE){
        m_timer.start();
        LOG<<"màn hình mua bảo hiểm";
    }

    if(m_machine->state() != MACHINE_STATE::SCREEN_GET_QRCODE){
        ui->stackedWidget->setCurrentIndex(m_machine->state());
    }
    LOG<<ui->stackedWidget->currentWidget()<<"chỉ số hiện tại";
}

void MainWindow::GrantPermission()
{
    LOG<<"cấp quyền";
    auto result = QtAndroid::checkPermission(QString("android.permission.REORDER_TASKS"));
    if (result == QtAndroid::PermissionResult::Denied){
        QtAndroid::PermissionResultMap resultHash = QtAndroid::requestPermissionsSync(QStringList({"android.permission.REORDER_TASKS"}));

        if (resultHash["android.permission.REORDER_TASKS"] == QtAndroid::PermissionResult::Denied)
           LOG<<"quyền bị từ chối";

        else {
            /* Here is Your method to upload to storage */
           LOG<<"quyền ok";
          //  return true;
        }
    }else{
        LOG<<"OKEEEEEEEEEEE";
    }
}

void MainWindow::UpdateMenuGoodGeneral()
{
    //ScreenMenuGoodGeneral = new menu_good_general(m_machine,"",list_image_service_byte);
   // ui->stackedWidget->insertWidget(MACHINE_STATE::MENU_GOOD_GENERAL, ScreenMenuGoodGeneral);
    //connect(ScreenMenuGoodGeneral, SIGNAL(Signal_Menu_Good_General(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
}

void MainWindow::UpdateDisplay()
{
    //Sắp xếp đúng thứ tự trước sau các màn hình.
    ScreenMenuGood = new Menu_Good(m_machine,list_PromotionImage.size(),DatabaseDataStoragePath);
    ui->stackedWidget->insertWidget(MACHINE_STATE::MENU, ScreenMenuGood);
    connect(ScreenMenuGood, SIGNAL(Signal_Menu_Good(QString)), this , SLOT(select_menu_good(QString)));

    SelectService = new select_service(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::SELECT_SERVICE, SelectService);
   // connect(SelectService, SIGNAL(Signal_Select_Service(QString)), this , SLOT(process_select_service(QString)));

    BuyCardMobile = new buy_card(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::BUY_CARD_MOBILE, BuyCardMobile);

    ScreenTopupTelco = new topup_telco(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::TOPUPTELCO, ScreenTopupTelco);

    ScreenPostPaid = new Postpaid(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::POST_PAID, ScreenPostPaid);

    ScreenTopupPartner = new topup_partner(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::TOPUPPARTNER, ScreenTopupPartner);

    ScreenBillInfo = new BillInfo(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::BILLINFO, ScreenBillInfo);

    ScreenMotorInsurance = new motor_insurance(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::MOTOR_INSURANCE, ScreenMotorInsurance);

    SelectChargeType = new select_charge_type(m_machine,m_machine->GetValueKioskAdmin("ChargeTypeListDefault","ListChargeType").split(QLatin1Char(',')));
    ui->stackedWidget->insertWidget(MACHINE_STATE::SELECT_CHARGE_TYPE, SelectChargeType);

    InfoSaleQrCode = new infoSale_qr_code(this);
   // connect(InfoSaleQrCode, SIGNAL(Signal_infoSale_QRcode(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
    ui->stackedWidget->insertWidget(MACHINE_STATE::SALEINFO_QRCODE, InfoSaleQrCode);

    QR_Code_Screen = new QR_code(this);
  //  connect(QR_Code_Screen, SIGNAL(Signal_QR_Code(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
    ui->stackedWidget->insertWidget(MACHINE_STATE::SCREEN_QRCODE, QR_Code_Screen);
   // ui->stackedWidget->insertWidget(MACHINE_STATE::SCREEN_GET_QRCODE, this);

    Charge_Coupon = new charge_coupon(this);
   // connect(Charge_Coupon, SIGNAL(Signal_ChargeCoupon(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
    ui->stackedWidget->insertWidget(MACHINE_STATE::CHARGE_COUPON, Charge_Coupon);

    Charged_Coupon = new charged_coupon(this);
    //connect(Charged_Coupon, SIGNAL(Signal_ChargedCoupon(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
    ui->stackedWidget->insertWidget(MACHINE_STATE::CHARGED_COUPON, Charged_Coupon);

    PinUserCouponSab = new pin_user_coupon_sab(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::PIN_USER_COUPON_SAB, PinUserCouponSab);

    Rfid_Data = new rfid_data_processor(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::RFID_DATA, Rfid_Data);

    Rfid_Data_Payment_Waitting = new rfid_data_payment_waitting(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::RFID_DATA_PAYMENT_WAITING, Rfid_Data_Payment_Waitting);

    Charge_mpos = new charge_mpos_processor(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::CHARGE_MPOS, Charge_mpos);

    Good_Digital_Process = new good_digital_process(this);
  //  connect(Good_Digital_Process, SIGNAL(Signal_GoodDigital_Process(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
    ui->stackedWidget->insertWidget(GOOD_DIGITAL_PROCESS, Good_Digital_Process);

    Get_Good_Digital = new get_good_digital(this);
   // connect(Get_Good_Digital, SIGNAL(Signal_GoodDigital_Process(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
    ui->stackedWidget->insertWidget(MACHINE_STATE::GET_GOOD_DIGITAL, Get_Good_Digital);

    ScreenMenuGoodGeneral = new menu_good_general(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::MENU_GOOD_GENERAL, ScreenMenuGoodGeneral);

    GetGoodGeneral = new Get_Good_General(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::GET_GOOD_GENERAL, GetGoodGeneral);

    LoginAdminScreen = new login_admin(this);
   // LoginAdminScreen->SetAdminPass(m_machine->config.getAdminPwd());
    ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_LOGIN, LoginAdminScreen);
  //  connect(LoginAdminScreen, SIGNAL(Signal_Admin_Login(MACHINE_STATE)), this, SLOT(Admin_Login_Success(MACHINE_STATE)));

    ScreenTestForm = new testform(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::TESTFORM,ScreenTestForm);

    SCreenAdminProcess = new admin_process(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_PROCESS, SCreenAdminProcess);
   // connect(SCreenAdminProcess, SIGNAL(Signal_Admin_Process(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));

    ProcessAdminFuntionSCreen = new process_admin_funtion(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_PROCESS_FUNTION, ProcessAdminFuntionSCreen);

    ProcessSettingQuantityFuntionScreen = new process_setting_quantity_funtion(this);
    ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_PROCESS_SETTING_QUANTITY_FUNTION, ProcessSettingQuantityFuntionScreen);

    m_machine->setState(MACHINE_STATE::MENU);
    process_state(MACHINE_STATE::MENU);
   // ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::setImage()
{
//    QImage m_lastFrame;
//    QImage img(":/img/gamecard.png");
//    QSize imgSize = img.size();
//    auto sz = img.byteCount();
//    uchar* a = new uchar[sz];
//    memcpy(a, img.bits(), sz);
//    QImage::Format imgFormat = QImage::Format_RGB32;
//    m_lastFrame = QImage(imgSize.width(), imgSize.height(), imgFormat);
//    memcpy(m_lastFrame.bits(), a, sz); // We write the image data into the new QImage

//    delete[] a;
//    QByteArray arr;
//    QDataStream ds(&arr, QIODevice::ReadWrite);
//    ds.writeRawData((const char*)img.bits(), img.byteCount());
//    ds.device()->seek(0);

//   // m_lastFrame = QImage(imgSize.width(), imgSize.height());
//    ds.readRawData((char*)m_lastFrame.bits(), img.byteCount());
//    //ScreenMenuGoodGeneral = new menu_good_general(m_machine,"",m_lastFrame);
//    ui->stackedWidget->insertWidget(0, ScreenMenuGoodGeneral);
//   // ui->la->setPixmap(QPixmap::fromImage(m_lastFrame));
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Back){
        if(ui->stackedWidget->currentIndex() == 0){
            if(m_timer.isActive()){
                m_timer.stop();
            }
            m_timer.setInterval(120000);
            m_timer.start();
            LoginAdminScreen = new login_admin("");
//            QByteArray password = QByteArray::fromBase64(m_machine->config.getAdminPwd().toUtf8());
//            QString pass = QString(password);

           // LoginAdminScreen->SetAdminPass(pass);
            ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_LOGIN, LoginAdminScreen);
            connect(LoginAdminScreen, SIGNAL(Signal_Admin_Login(QString, QString)), this, SLOT(Check_Login_Admin(QString, QString)));
            m_machine->setState(MACHINE_STATE::ADMIN_LOGIN);
            ui->stackedWidget->setCurrentIndex(m_machine->state());
            QInputMethod *input = QApplication::inputMethod();
            input->show();
        }
    }
}

void MainWindow::input_delay()
{
    LOG<<m_machine->state();
    m_khayhang.ConvertQueryMode();
    if(m_machine->state() == GOOD_DIGITAL_PROCESS && m_machine->transaction()->IsCheckingWorkWithVTC){

        if(m_machine->transaction()->TransactionType == KioskTransactionType::CASHandCOUPON){
            if(m_machine->transaction()->serviceCode != RECHARGEMOBILETYPE::BUYCARDMOBILE)
                m_machine->transaction()->AvailableAmount = m_machine->transaction()->AvailableAmount - m_machine->transaction()->UseValueCash;
            m_machine->BillAmount()->BillAvailable = m_machine->transaction()->AvailableAmount;
            m_machine->balanceBillAccepted_BillIdentified();
            m_machine->UpdateBillAvailable();
        }
                   // m->transaction()->InputAmount = 0;
        if(m_machine->transaction()->serviceCode != RECHARGEMOBILETYPE::BUYCARDMOBILE){
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::ERROR;
        }else{
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::FAILED;
            if(m_machine->transaction()->TransactionType == KioskTransactionType::CASH){
                m_machine->transaction()->AvailableAmount += m_machine->transaction()->GoodPrice*m_machine->transaction()->Quantity;
                m_machine->BillAmount()->BillAvailable += m_machine->transaction()->GoodPrice * m_machine->transaction()->Quantity;
                m_machine->balanceBillAccepted_BillIdentified();
                m_machine->UpdateBillAvailable();
            }
        }
        m_machine->UpdateDB();
        m_machine->transaction()->IsCheckingWorkWithVTC = false;
        m_machine->transaction()->MessageRechargeMobile = "Timeout hệ thống. Lỗi không xác định! Gọi hotline để được hỗ trợ!";
        process_state(GOOD_DIGITAL_PROCESS);

    }else if(m_machine->state() == SCREEN_QRCODE){
        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::CANCEL;
        m_machine->UpdateDB();
        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
            LOG;
            QAmqpMessage::PropertyHash properties;
            properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
            topic_logs->publish(m_machine->transaction()->toAPIString()
                                ,QString("%1.transactions").arg(m_machine->transaction()->MachineId)
                                ,properties);
        }
        m_machine->transaction()->init(m_machine->saleSession()->SessionId);
        ScreenMenuGood->StartTimer();
        m_machine->setState(MACHINE_STATE::MENU);
        ui->stackedWidget->setCurrentIndex(0);
        m_timer_ReconnectMQ.stop();
    }else if(m_machine->state() == MACHINE_STATE::GET_GOOD_GENERAL && m_machine->transaction()->TransactionStatus == KioskTransactionStatus::RETURN_GOOD_WAITING){
        m_machine->transaction()->TransactionStatus = KioskTransactionStatus::ERROR;
        m_machine->UpdateDB();
        GetGoodGeneral->ReturnGoodFail();
        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
            LOG;
            QAmqpMessage::PropertyHash properties;
            properties[QAmqpMessage::DeliveryMode] = "2";
            topic_logs->publish(m_machine->transaction()->toAPIString()
                                ,QString("%1.transactions").arg(m_machine->transaction()->MachineId)
                                ,properties);
        }
    }else if(m_machine->state() == MACHINE_STATE::MENU){
        LOG<<"aaaaa";
        if (m_machine->transaction()->AvailableAmount > 0) {
            m_machine->transaction()->SlotId    = "";
            m_machine->transaction()->GoodName  = "";
            m_machine->transaction()->GoodId = "";
            m_machine->transaction()->GoodPrice = 0;
            m_machine->transaction()->GoodPriceGeneral = 0;
            m_machine->transaction()->Quantity  = 1;
            m_machine->transaction()->InputAmount = 0;
           // m->transaction()->AvailableAmount = 0;
            m_machine->transaction()->TransactionStatus = KioskTransactionStatus::TIMEOUT; // gd nuot tien

            m_machine->transaction()->TransactionType = KioskTransactionType::CASH;

            m_machine->finish_transaction();

            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->config.getMachineId();
                properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish(m_machine->transaction()->toAPIString()
                                    ,QString("%1.transactions").arg(m_machine->config.getMachineId())
                                    ,properties);
            }
            m_machine->transaction()->AvailableAmount = 0;
            m_machine->balanceBillAccepted_BillIdentified();
        }
        m_machine->transaction()->init(m_machine->saleSession()->SessionId);
        ScreenMenuGood->UpdateBillAmount();

    }
    else{
        if (m_machine->transaction()->AvailableAmount > 0) {
            m_timer.start();
        }
        m_khayhang.ConvertQueryMode();
        m_machine->transaction()->init(m_machine->saleSession()->SessionId);
        ScreenMenuGood->StartTimer();
        m_machine->setState(MACHINE_STATE::MENU);
        ui->stackedWidget->setCurrentIndex(0);
        m_timer_ReconnectMQ.stop();
        ScreenMenuGood->UpdateBillAmount();
        //CheckTimesReconnectMQ = 0;
    }
}

void MainWindow::select_menu_good(QString select)
{
    LOG<<"fdfdf"<<select;
    if(m_timer.isActive()){
        m_timer.stop();
        m_timer.setInterval(m_machine->config.getScreenTimeout());
    }
    if(select == "setting"){

    }else if(select == "digital"){
        SelectService = new select_service(m_machine->getListGoodMenu());
        ui->stackedWidget->insertWidget(MACHINE_STATE::SELECT_SERVICE, SelectService);
        connect(SelectService, SIGNAL(Signal_Select_Service(QString)), this , SLOT(process_select_service(QString)));
        m_machine->setState(MACHINE_STATE::SELECT_SERVICE);
        ui->stackedWidget->setCurrentIndex(MACHINE_STATE::SELECT_SERVICE);
        m_machine->transaction()->BuyType = "MenuBuy";
        m_timer.start();

//        m_machine->inputBill(10000);
//        ScreenMenuGood->UpdateBillAmount();
//        SelectChargeType->UpdateBillAmount();
    }else if(select == "menugeneral"){
        ScreenMenuGoodGeneral = new menu_good_general(m_machine, DatabaseDataStoragePath);
        ui->stackedWidget->insertWidget(MACHINE_STATE::MENU_GOOD_GENERAL, ScreenMenuGoodGeneral);
        connect(ScreenMenuGoodGeneral, SIGNAL(Signal_Menu_Good_General(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
        m_machine->setState(MACHINE_STATE::MENU_GOOD_GENERAL);
        ui->stackedWidget->setCurrentIndex(MACHINE_STATE::MENU_GOOD_GENERAL);
        m_machine->transaction()->serviceCode = RECHARGEMOBILETYPE::GOOD_GENERAL;
        m_machine->transaction()->BuyType = "MenuGeneralBuy";
        m_timer.start();
    }/*else if(select == "ReturnGood"){
        m_khayhang.testReturnGoods(54,1);
    }*/
}

void MainWindow::ReSendData()
{
    if(m_timer_ReSendData.isActive())
        m_timer_ReSendData.stop();
    QString startTime = QDateTime::currentDateTime().addDays(-1).toString("yyyy-MM-dd 00:00:00");
    QString endTime = QDateTime::currentDateTime().toString("yyyy-MM-dd 00:00:00");
    ReSendTransaction(startTime,endTime);
    m_timer_ReSendData.setInterval(86400000);
    m_timer_ReSendData.start();
    LOG<<"gửi lại dữ liệu";
}

void MainWindow::ReSendTransaction(QString start, QString end)
{
    QString mes = m_machine->GetReTransaction(start,end);
    if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
        LOG;
        QAmqpMessage::PropertyHash properties;
        properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
        m_correlationId = m_machine->transaction()->MachineId;
        properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
        properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
        topic_logs->publish(mes
                            ,QString("%1.request.ReSendTransaction").arg(m_machine->transaction()->MachineId)
                            ,properties);
    }
}

void MainWindow::ReConnectMQ()
{
    LOG<<"restart MQ";
    m_client.connectToHost();

}

void MainWindow::Check_Login_Admin(QString user, QString pass)
{
    if(m_timer.isActive()){
        m_timer.stop();
        m_timer.setInterval(m_machine->config.getAdminTimeout());
    }
    if(user != "back"){
        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
            LOG;
            QAmqpMessage::PropertyHash properties;
            properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
            m_correlationId = m_machine->transaction()->MachineId;
            properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
//            LOG << m_machine->transaction()->MachineId ;
            properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
            topic_logs->publish(m_machine->transaction()->toCheckAdminLogin(user, pass)
                                ,QString("%1.request.getCouponInfo").arg(m_machine->transaction()->MachineId)
                                ,properties);
        }
//        QByteArray password = QByteArray::fromBase64(m_machine->config.getAdminPwd().toUtf8());
//        QString pw = QString(password);
//        if(user == pw && pass == pw)
//            Admin_Login_Success("all");
    }else{
        m_machine->AdminType = ADMINFUNTIONLIST::INIT_ADMIN;
        process_state(MACHINE_STATE::MENU);
    }
}

void MainWindow::Admin_Login_Success(QString list_admin_funtion)
{
    if(list_admin_funtion == "fail"){
        LoginAdminScreen->LoginAdminFail(m_machine->transaction()->MessageRechargeMobile);
        m_timer.start();
    }else{
        SCreenAdminProcess = new admin_process(m_machine, list_admin_funtion);
        ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_PROCESS, SCreenAdminProcess);
        connect(SCreenAdminProcess, SIGNAL(Signal_Admin_Process(MACHINE_STATE)), this, SLOT(process_admin(MACHINE_STATE)));
        m_machine->AdminType = ADMINFUNTIONLIST::INIT_ADMIN;
        m_timer.start();
        m_machine->setState(MACHINE_STATE::ADMIN_PROCESS);
        ui->stackedWidget->setCurrentIndex(m_machine->state());
    }

//    if(state == MACHINE_STATE::ADMIN_LOGIN){
//        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
//            LOG;
//            QAmqpMessage::PropertyHash properties;
//            properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
//            m_correlationId = m_machine->transaction()->MachineId;
//            properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
//            properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
//            topic_logs->publish(m_machine->transaction()->toCheckAdminLogin()
//                                ,QString("%1.request.getCouponInfo").arg(m_machine->transaction()->MachineId)
//                                ,properties);
//        }
//    }
//    else if(state == MACHINE_STATE::ADMIN_PROCESS){
//        SCreenAdminProcess = new admin_process(this);
//        ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_PROCESS, SCreenAdminProcess);
//        connect(SCreenAdminProcess, SIGNAL(Signal_Admin_Process(MACHINE_STATE)), this, SLOT(process_state(MACHINE_STATE)));
//        m_machine->AdminType = ADMINFUNTIONLIST::INIT_ADMIN;
//        m_timer.start();
//        m_machine->setState(state);
//        ui->stackedWidget->setCurrentIndex(m_machine->state());
//    }else if(state == MACHINE_STATE::MENU){
//        m_machine->AdminType = ADMINFUNTIONLIST::INIT_ADMIN;
//        process_state(MACHINE_STATE::MENU);
    //    }
}

void MainWindow::process_admin(MACHINE_STATE state)
{
    if(m_timer.isActive()){
        m_timer.stop();
        m_timer.setInterval(m_machine->config.getAdminTimeout());
    }
    if(state == MACHINE_STATE::ADMIN_PROCESS_FUNTION){
        ProcessAdminFuntionSCreen = new process_admin_funtion(m_machine);
        ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_PROCESS_FUNTION, ProcessAdminFuntionSCreen);
        connect(ProcessAdminFuntionSCreen, SIGNAL(Signal_Admin_Funtion_Process(MACHINE_STATE)), this, SLOT(process_Admin_Funtion(MACHINE_STATE)));
        m_timer.start();
    }else if(state == MACHINE_STATE::MENU){
        if (m_machine->transaction()->AvailableAmount > 0) {
            m_timer.start();
        }
        ScreenMenuGood->StartTimer();
        m_khayhang.ConvertQueryMode();
        m_machine->transaction()->init(m_machine->saleSession()->SessionId);
        LOG<< m_machine->transaction()->IdentifiedAmount<<"tiền billlllllllllllllllll";
        ScreenMenuGood->UpdateBillAmount();
    }
    m_machine->setState(state);
    ui->stackedWidget->setCurrentIndex(m_machine->state());
}

void MainWindow::process_Admin_Funtion(MACHINE_STATE state)
{
    if(m_timer.isActive()){
        m_timer.stop();
        m_timer.setInterval(m_machine->config.getAdminTimeout());
    }
    ProcessAdminFuntionSCreen->UpdateStatus();
    if(state == MACHINE_STATE::ADMIN_PROCESS_FUNTION){
        if(m_machine->AdminType == ADMINFUNTIONLIST::SYNC_VMS_TO_APP){
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG ;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->config.getMachineId();
                properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish(QString("{\"machineId\":\"%1\"}")
                                    .arg(m_machine->config.getMachineId())
                                    ,QString("%1.request.getconfig").arg(m_machine->config.getMachineId())
                                    ,properties);
            } else {
                ProcessAdminFuntionSCreen->SyncInfo("disconnect");
            }
        }else if(m_machine->AdminType == ADMINFUNTIONLIST::SYNC_APP_TO_VMS){
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "1";   // make message persistent
                m_correlationId = m_machine->config.getMachineId();
                properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish( QString(m_machine->config.Json(0).toJson())
                                     ,QString("%1.request.setconfig").arg(m_machine->config.getMachineId())
                                     ,properties);
            }else{
                ProcessAdminFuntionSCreen->SyncInfo("disconnect");
            }

        }else if(m_machine->AdminType == ADMINFUNTIONLIST::DAY_SALE || m_machine->AdminType == ADMINFUNTIONLIST::MONTH_SALE){
            if(m_machine->AdminType == ADMINFUNTIONLIST::DAY_SALE){
                m_machine->finish_sale_session();
            }else{
                m_machine->finish_sale_month_session();
            }
            if (m_machine->saleSession()->IsUpdateDB && m_queue_connected &&  topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                m_machine->saleSession()->IsSyncing = true;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "1";   // make message persistent
                m_correlationId = m_machine->config.getMachineId();
                properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish( QString(m_machine->saleSession()->toAPIString())
                                     ,QString("%1.request.submitsaleinfo").arg(m_machine->transaction()->MachineId)
                                     ,properties);
            }
            if(m_machine->saleSession()->IsUpdateDB){
                ProcessAdminFuntionSCreen->SaleInfo("success");
                m_machine->init_sale_session();
            }
        }
        else if(m_machine->AdminType == ADMINFUNTIONLIST::RESEND_SALE){
            if (m_queue_connected &&  topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                m_machine->saleSession()->IsSyncing = true;
               // m_machine->finish_sale_session();
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "1";   // make message persistent
                m_correlationId = m_machine->config.getMachineId();
                properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish( QString(m_machine->GetErrorSale())
                                     ,QString("%1.request.submitsaleinfo").arg(m_machine->config.getMachineId())
                                     ,properties);
            }else{
                ProcessAdminFuntionSCreen->ReSendSaleStatus("disconnect");
            }
        }else if(m_machine->AdminType == ADMINFUNTIONLIST::RESEND_TRANSACTION){
            ProcessSettingQuantityFuntionScreen = new process_setting_quantity_funtion(m_machine);
            ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_PROCESS_SETTING_QUANTITY_FUNTION, ProcessSettingQuantityFuntionScreen);
            connect(ProcessSettingQuantityFuntionScreen, SIGNAL(Signal_Admin_Setting_Quantity_Funtion_Process(MACHINE_STATE,QString,QString)), this, SLOT(process_Admin_Setting_Quantity_Funtion(MACHINE_STATE,QString, QString)));
            m_machine->setState(MACHINE_STATE::ADMIN_PROCESS_SETTING_QUANTITY_FUNTION);

        }else if(m_machine->AdminType == ADMINFUNTIONLIST::GENERAL_SETTING || m_machine->AdminType == ADMINFUNTIONLIST::KHAY_SETTING || m_machine->AdminType == ADMINFUNTIONLIST::SLOT_SETTING){
            ProcessSettingQuantityFuntionScreen = new process_setting_quantity_funtion(m_machine);
            ui->stackedWidget->insertWidget(MACHINE_STATE::ADMIN_PROCESS_SETTING_QUANTITY_FUNTION, ProcessSettingQuantityFuntionScreen);
            connect(ProcessSettingQuantityFuntionScreen, SIGNAL(Signal_Admin_Setting_Quantity_Funtion_Process(MACHINE_STATE,QString,QString)), this, SLOT(process_Admin_Setting_Quantity_Funtion(MACHINE_STATE,QString, QString)));
            m_machine->setState(MACHINE_STATE::ADMIN_PROCESS_SETTING_QUANTITY_FUNTION);
        }else if(m_machine->AdminType == ADMINFUNTIONLIST::EXIT_APP){
            exitApp();
        }
        m_timer.start();
    }else if(state == MACHINE_STATE::ADMIN_PROCESS){
        m_machine->setState(state);
        m_timer.start();
    }




    //m_machine->setState(state);
    ui->stackedWidget->setCurrentIndex(m_machine->state());
}

void MainWindow::process_Admin_Setting_Quantity_Funtion(MACHINE_STATE state, QString start_time,QString end_time)
{
    if(m_timer.isActive()){
        m_timer.stop();
        m_timer.setInterval(m_machine->config.getAdminTimeout());
    }
    if(state == MACHINE_STATE::ADMIN_PROCESS_SETTING_QUANTITY_FUNTION){
        if(m_machine->AdminType == ADMINFUNTIONLIST::RESEND_TRANSACTION){
            QString mes = m_machine->GetReTransaction(start_time,end_time);
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->transaction()->MachineId;
                properties.insert(QAmqpMessage::ReplyTo, m_machine->transaction()->MachineId);
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish(mes
                                    ,QString("%1.request.ReSendTransaction").arg(m_machine->transaction()->MachineId)
                                    ,properties);
                ProcessSettingQuantityFuntionScreen->ReSendTransactionStatus("success");
            }else{
                ProcessSettingQuantityFuntionScreen->ReSendTransactionStatus("disconnect");
            }
        }
        m_timer.start();
    }else if(state == MACHINE_STATE::MENU){
        if (m_machine->transaction()->AvailableAmount > 0) {
            m_timer.start();
        }
        ScreenMenuGood->StartTimer();
        m_khayhang.ConvertQueryMode();
        m_machine->transaction()->init(m_machine->saleSession()->SessionId);
        LOG<< m_machine->transaction()->IdentifiedAmount<<"tiền billlllllllllllllllll";
        ScreenMenuGood->UpdateBillAmount();
    }else if(state == ADMIN_PROCESS_FUNTION){
        m_timer.start();
    }


    m_machine->setState(state);
    ui->stackedWidget->setCurrentIndex(m_machine->state());
}

void MainWindow::onBillAccepted(double amount)
{
    m_machine->inputBill(amount);
    ScreenMenuGood->UpdateBillAmount();
    SelectChargeType->UpdateBillAmount();
    if(m_machine->state() == MACHINE_STATE::GOOD_DIGITAL_PROCESS){
        Good_Digital_Process->updateBillAmount();
    }

   // m_machine->input(Qt::Key_U);
    if (m_machine->config.getBillAmountEnabled())
    {
        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
            LOG ;
             QAmqpMessage::PropertyHash properties;
            properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
            m_correlationId = m_machine->config.getMachineId();
            properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
            properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
            topic_logs->publish(m_machine->BillAmount()->toBillAmount()
                                ,QString("%1.request.billresponse").arg(m_machine->config.getMachineId())
                                ,properties);
       }
    }
    //ScreenMenuGood->UpdateData("",QString::number(amount));
}

void MainWindow::onBillIdentified(double amount)
{
//    if (ui->stackedWidget->currentIndex() == 1){
//        m_saverscreen->StopTimer();
//        ui->stackedWidget->setCurrentIndex(0);
//    }
    m_machine->inputBIllIdentified(amount);
    ScreenMenuGood->UpdateBillAmount();
    SelectChargeType->UpdateBillAmount();
    if(m_machine->state() == MACHINE_STATE::GOOD_DIGITAL_PROCESS){
        Good_Digital_Process->updateBillAmount();
    }
   // m_machine->input(Qt::Key_X);
}

void MainWindow::onBillUnAccepted(double amount)
{
//    if (ui->stackedWidget->currentIndex() == 1){
//        m_saverscreen->StopTimer();
//        ui->stackedWidget->setCurrentIndex(0);
//    }
    m_machine->BillUnAccepted(amount);
    ScreenMenuGood->UpdateBillAmount();
    SelectChargeType->UpdateBillAmount();
    if(m_machine->state() == MACHINE_STATE::GOOD_DIGITAL_PROCESS){
        Good_Digital_Process->updateBillAmount();
    }
  //  m_machine->input(Qt::Key_X);
}

void MainWindow::onBillError(QString error)
{
    if (m_machine->config.getBillResponseEnabled()){
       // m_machine->errorBill(error);
        int count = m_machine->GetSignalCountErrorKiosk(error);
        m_machine->UpdateSignalCountErrorKiosk(error, count + 1);
        if(m_machine->GetSignalCountErrorKiosk(error) < m_machine->GetSignalCountMaxErrorKiosk(error)){
            m_machine->errorBill(error);
        }
    }
}

void MainWindow::ConvertStatusKey(int)
{

}

void MainWindow::ConvertStatus()
{

}

void MainWindow::onBillResponse(QString error)
{
    if (m_machine->config.getBillResponseEnabled())
    {
        int count = m_machine->GetSignalCountErrorKiosk(error);
        if(count < m_machine->GetSignalCountMaxErrorKiosk(error)){
            if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
                LOG ;
                QAmqpMessage::PropertyHash properties;
                properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
                m_correlationId = m_machine->config.getMachineId();
                properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
                properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
                topic_logs->publish(m_machine->BillAmount()->toBillResponse()
                                    ,QString("%1.request.billresponse").arg(m_machine->config.getMachineId())
                                    ,properties);
            }
        }else{
            LOG<<"error code không có trong miêu tả hoặc quá số lần tối đa đc gửi lên VMS";
        }
    }
}

void MainWindow::onRFID_Data(QString data)
{
    LOG<<data<<"ID thẻ từ";
    if(m_machine->state() == RFID_DATA){
        m_machine->transaction()->RfidData = data;
        Rfid_Data->updateReceiveRfidData(data);
       // m_machine->input(Qt::Key_S);
    }
   // ScreenMenuGood->UpdateData(data, "");
}

void MainWindow::onStatus(QString data)
{
//    m_machine->inputBill(data.toDouble());
//    ScreenMenuGood->UpdateBillAmount();
//    SelectChargeType->UpdateBillAmount();


//    if (m_machine->config.getBillAmountEnabled())
//    {
//        if (m_queue_connected && topic_logs && topic_logs->isDeclared() && topic_logs->isOpen() ) {
//            LOG ;
//             QAmqpMessage::PropertyHash properties;
//            properties[QAmqpMessage::DeliveryMode] = "2";   // make message persistent
//            m_correlationId = m_machine->config.getMachineId();
//            properties.insert(QAmqpMessage::ReplyTo, m_machine->config.getMachineId());
//            properties.insert(QAmqpMessage::CorrelationId, m_correlationId);
//            topic_logs->publish(m_machine->BillAmount()->toBillAmount()
//                                ,QString("%1.request.billresponse").arg(m_machine->config.getMachineId())
//                                ,properties);
//       }
//    }

//    m_machine->transaction()->RfidData = data;
//    Rfid_Data->updateReceiveRfidData(data);
   // GetGoodGeneral->ShowResponse(data);
    //ScreenMenuGood->UpdateStatus(data);
}

void MainWindow::exitApp()
{
    QAndroidJniObject *myJavaString;
    myJavaString = new QAndroidJniObject("org/qtproject/qt5/android/bindings/QtActivity");
    myJavaString->callMethod<void>("onDestroy");
}


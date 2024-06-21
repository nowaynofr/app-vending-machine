#include "good_digital_process.h"
#include "ui_good_digital_process.h"

good_digital_process::good_digital_process(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::good_digital_process)
{
    ui->setupUi(this);
}

good_digital_process::good_digital_process(Machine *m)
{
    LOG;
    s_machine = m;
   // ServiceType_GoodDigital = serviceType_goodDigital;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
   // Image_Sab->setGeometry(0,0,1200,660);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

    QFont font("Arial",27);
    QGroupBox *InfoQR = new QGroupBox(tr("Thông tin đơn hàng"));
    InfoQR->setStyleSheet("QGroupBox { color : green; }");
    InfoQR->setFont(font);
    QHBoxLayout *HBox_Lbl_InfoQR = new QHBoxLayout;
    Lbl_InfoGoodDigital = new QLabel(this);
    Lbl_InfoGoodDigital->setWordWrap(true);
    Lbl_InfoGoodDigital->setAlignment(Qt::AlignCenter);
    Lbl_InfoGoodDigital->setStyleSheet("QLabel { border: 3px solid black; border-radius: 25px; background: gray;color: blue;}");
    QFont font1 = Lbl_InfoGoodDigital->font();
    font1. setPointSize(32);
    font1. setBold(true);
    Lbl_InfoGoodDigital->setFont(font1);
    Lbl_InfoGoodDigital->setMinimumSize(1000,450);
    //setGetPriceGoodDigitalProcess(m);
    HBox_Lbl_InfoQR->addWidget(Lbl_InfoGoodDigital);
    InfoQR->setLayout(HBox_Lbl_InfoQR);


    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setMaximumSize(1080, 140);
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);
    QFont font2("Times",30);
    Message->setFont(font2);

    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Ok = new PushButton_OK_BACK("OK",this);
    btn_Back = new PushButton_OK_BACK("Back", this);

    HBox_Ok_Back->addWidget(btn_Back);
    HBox_Ok_Back->addWidget(btn_Ok);
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_GoodDigital_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_GoodDigital_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

//    QLabel* home = new my_qlabel("",this);
//    home->setGeometry(960,450,110,110);
//    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
//    QImage img(":/img/Button_Image/Home_Btn.jpg");
//    home->setPixmap(QPixmap::fromImage(img));
//    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(InfoQR);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
  //  setStyleSheet("QPushButton { color: blue; background-color: gray;}");
}

good_digital_process::~good_digital_process()
{
    delete ui;
}

void good_digital_process::setGetPriceGoodDigitalProcess(Machine *m)
{
    if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO){
        Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID || s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
        LOG;
    }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
        Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
        Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }
    else{
        Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }
}

void good_digital_process::updateGetPriceGoodDigitalProcess(Machine *m)
{
    if(s_machine->transaction()->AvailableAmount == s_machine->transaction()->GoodPrice){
        Message->setText("Số tiền đang có: " + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND\nẤn OK để thực hiện giao dịch");
    }else if(s_machine->transaction()->AvailableAmount > s_machine->transaction()->GoodPrice){
        Message->setText("Số tiền đang có: " + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND\n" + QString("Thừa: %1 VND.").arg(s_machine->transaction()->AvailableAmount - s_machine->transaction()->GoodPrice) + " Ấn OK để giao dịch");
    }
    else{
        Message->setText("Số tiền đang có: " + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND\n" + QString("Thiếu: %1 VND").arg(s_machine->transaction()->GoodPrice - s_machine->transaction()->AvailableAmount));
    }
    if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
        Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\nĐơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
    }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
        Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
    }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
        Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
    }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
        Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\nĐơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");

    }
}

void good_digital_process::setGoodDigitalProcess(Machine *m)
{
    if(m->transaction()->moneyCalculate == 0){
        if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO){
          //  if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND" + "\nĐang thực hiện giao dịch ...");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
          //  if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND" + "\nĐang thực hiện giao dịch ...");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
           // if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" +"Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +"VND" + "\nĐang thực hiện giao dịch ...");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            //if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND" + "\nĐang thực hiện giao dịch ...");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
          //  if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\nĐơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND" + "\nĐang thực hiện giao dịch ...");
        }
    }else{
        if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO){
          //  if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND" + "\nĐang thực hiện giao dịch ...");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            //if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND" + "\nĐang thực hiện giao dịch ...");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
          //  if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" +"Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +"VND" + "\nĐang thực hiện giao dịch ...");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
           // if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND" + "\nĐang thực hiện giao dịch ...");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
          //  if(m->transaction()->TransactionType == KioskTransactionType::QRPAY ||m->transaction()->TransactionType == KioskTransactionType::MOMO ||m->transaction()->TransactionType == KioskTransactionType::COUPON ||m->transaction()->TransactionType == KioskTransactionType::VINID || m->transaction()->TransactionType == KioskTransactionType::GRABPAY ||m->transaction()->TransactionType == KioskTransactionType::QRMB ||m->transaction()->TransactionType == KioskTransactionType::ZALOPAY)
                Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\nĐơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND" + "\nĐang thực hiện giao dịch ...");
        }
    }
}

void good_digital_process::updateGoodDigitalProcess(Machine *m)
{
    if(m->transaction()->TransactionStatus == KioskTransactionStatus::FAILED || m->transaction()->TransactionStatus == KioskTransactionStatus::ERROR){
        Message->setText(m->transaction()->MessageRechargeMobile);
    }
    if(m->transaction()->moneyCalculate == 0){
        if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\nĐơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
            Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
            Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\nĐơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");

        }
    }else{
        if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\nĐơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
            Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
            Lbl_InfoGoodDigital->setText(m->transaction()->GoodName + "\nĐơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");

        }

    }
}

void good_digital_process::updateBillAmount()
{
    if(s_machine->transaction()->AvailableAmount == s_machine->transaction()->GoodPrice){
        Message->setText("Số tiền đang có: " + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND\nẤn OK để thực hiện giao dịch");
    }else if(s_machine->transaction()->AvailableAmount > s_machine->transaction()->GoodPrice){
        Message->setText("Số tiền đang có: " + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND\n" + QString("Thừa: %1 VND.").arg(s_machine->transaction()->AvailableAmount - s_machine->transaction()->GoodPrice) + " Ấn OK để giao dịch");
    }
    else{
        Message->setText("Số tiền đang có: " + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND\n" + QString("Thiếu: %1 VND").arg(s_machine->transaction()->GoodPrice - s_machine->transaction()->AvailableAmount));
    }
}

void good_digital_process::Back_Home(QString)
{
    emit Signal_GoodDigital_Process(MACHINE_STATE::MENU);
}

void good_digital_process::on_Btn_Ok_GoodDigital_clicked()
{
    if(s_machine->transaction()->CheckPriceServe){
        if(!s_machine->transaction()->IsCheckingWorkWithVTC){
            if(s_machine->transaction()->AvailableAmount >= s_machine->transaction()->GoodPrice){
                s_machine->transaction()->TransactionType = KioskTransactionType::CASH;
                s_machine->transaction()->TransactionStatus = KioskTransactionStatus::RETURN_GOOD_WAITING;
                s_machine->CreatDB();
                s_machine->transaction()->AvailableAmount = s_machine->transaction()->ChargeAmount() > 0 ? s_machine->transaction()->ChargeAmount() : 0;
                s_machine->BillAmount()->BillAvailable = (s_machine->BillAmount()->BillAvailable - s_machine->transaction()->GoodPrice * s_machine->transaction()->Quantity) > 0 ? (s_machine->BillAmount()->BillAvailable - s_machine->transaction()->GoodPrice * s_machine->transaction()->Quantity) : 0;
                s_machine->balanceBillAccepted_BillIdentified();
                s_machine->UpdateBillAvailable();
                s_machine->transaction()->IsCheckingWorkWithVTC = true;
                emit Signal_GoodDigital_Process(MACHINE_STATE::GOOD_DIGITAL_PROCESS);
                Message->setText("");
            }else{
                Message->setText("Số tiền đang có: " + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND\n" + QString("Thiếu: %1 VND").arg(s_machine->transaction()->GoodPrice - s_machine->transaction()->AvailableAmount));
            }
        }else{
            Message->setText("Hệ thống đang xử lí, vui lòng chờ!");
        }
    }else{
        Message->setText("Đang lấy thông tin sản phẩm, vui lòng chờ...!");
    }
}

void good_digital_process::on_Btn_Back_GoodDigital_clicked()
{
    if(!s_machine->transaction()->IsCheckingWorkWithVTC){
        if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO){
            emit Signal_GoodDigital_Process(MACHINE_STATE::TOPUPTELCO);
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
            emit Signal_GoodDigital_Process(MACHINE_STATE::BUY_CARD_MOBILE);
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            emit Signal_GoodDigital_Process(MACHINE_STATE::POST_PAID);
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            emit Signal_GoodDigital_Process(MACHINE_STATE::TOPUPPARTNER);
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
            emit Signal_GoodDigital_Process(MACHINE_STATE::MOTOR_INSURANCE);
        }
    }else{
        Message->setText("Hệ thống đang xử lí, vui lòng chờ!");
    }
}

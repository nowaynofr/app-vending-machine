#include "charge_coupon.h"
#include "ui_charge_coupon.h"
#include "QTimer"
#include "QInputMethod"
charge_coupon::charge_coupon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::charge_coupon)
{
    ui->setupUi(this);
}

charge_coupon::charge_coupon(Machine *m, quint8 ServiceType)
{
    LOG;
    s_machine = m;
    CheckPushButtonOKPressed = false;

    ServiceType_ChargeCoupon = ServiceType;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
   // Image_Sab->setGeometry(0,0,1200,660);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

    QFont font("Arial",27);
    QGroupBox *ChargeCoupon = new QGroupBox(tr("Thông tin đơn hàng"));
    ChargeCoupon->setStyleSheet("QGroupBox { color : green; }");
    ChargeCoupon->setFont(font);
    QHBoxLayout *HBox_Lbl_ChargeCoupon = new QHBoxLayout;
    Lbl_ChargeCoupon = new QLabel(this);
    Lbl_ChargeCoupon->setWordWrap(true);
    Lbl_ChargeCoupon->setAlignment(Qt::AlignCenter);
    Lbl_ChargeCoupon->setStyleSheet("QLabel { border: 3px solid black; border-radius: 25px; background: gray;color: blue;}");
    QFont font1 = Lbl_ChargeCoupon->font();
    font1. setPointSize(32);
    font1. setBold(true);
    Lbl_ChargeCoupon->setFont(font1);
    Lbl_ChargeCoupon->setMinimumSize(1000,400);
    setChargeCoupon(m);
    HBox_Lbl_ChargeCoupon->addWidget(Lbl_ChargeCoupon);
    ChargeCoupon->setLayout(HBox_Lbl_ChargeCoupon);

    QGroupBox *CouponGroup = new QGroupBox(tr("Mã Coupon"));
    CouponGroup->setStyleSheet("QGroupBox { color : green; }");
    CouponGroup->setFont(font);
    QHBoxLayout *HBox_Number_Phone = new QHBoxLayout;
    QLabel *NumberPhoneLabel = new QLabel(tr("Mã Coupon:"));
    NumberPhoneLabel->setFont(font);
    lineEdit_Coupon = new QLineEdit(this);
    lineEdit_Coupon->setInputMethodHints(Qt::ImhPreferNumbers);
   // lineEdit_Coupon->setMinimumSize(600,60);
  //  QValidator *validator = new QIntValidator(1,13999999);
    //new QDoubleValidator(0,9999999999,0,this)
    lineEdit_Coupon->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 10px");
    QFont font22("Arial",28);
    lineEdit_Coupon->setFont(font22);
    lineEdit_Coupon->setFocus();
   // lineEdit_Coupon->setCursorPosition(0);
    HBox_Number_Phone->addSpacing(140);
    HBox_Number_Phone->addWidget(NumberPhoneLabel);
    HBox_Number_Phone->addWidget(lineEdit_Coupon);
    HBox_Number_Phone->addSpacing(140);
    CouponGroup->setLayout(HBox_Number_Phone);
    CouponGroup->setAlignment(Qt::AlignCenter);

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
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_ChargeCoupon_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_ChargeCoupon_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

//    QLabel* home = new my_qlabel("",this);
//    home->setGeometry(960,450,110,110);
//    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
//    QImage img(":/img/Button_Image/Home_Btn.jpg");
//    home->setPixmap(QPixmap::fromImage(img));
//    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(ChargeCoupon);
    mainLayout->addWidget(CouponGroup);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
}

charge_coupon::~charge_coupon()
{
    delete ui;
}

void charge_coupon::setChargeCoupon(Machine *m)
{
    if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::TOPUP_TELCO){
        Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::POSTPAID || ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::TOPUP_PARTNER){
        LOG;
    }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::BUYCARDMOBILE){
        Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::MOTORINSURANCE){
        Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }
    else{
        Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }
}

void charge_coupon::updateChargeCoupon(Machine *m)
{
    if(m->last_state() == MACHINE_STATE::CHARGED_COUPON){
        Message->setText(m->transaction()->MessageRechargeMobile);
    }else{
        if(m->transaction()->moneyCalculate == 0){
            if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::TOPUP_TELCO){
                m->transaction()->IsCheckingWorkWithVTC = false;
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::POSTPAID){
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::BUYCARDMOBILE){
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::TOPUP_PARTNER){
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
            }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::MOTORINSURANCE){
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }
            else{
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }
        }else{
            if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::TOPUP_TELCO){
                m->transaction()->IsCheckingWorkWithVTC = false;
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::POSTPAID){
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::BUYCARDMOBILE){
                LOG<<"mua thẻ đt";
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }else if(ServiceType_ChargeCoupon == RECHARGEMOBILETYPE::TOPUP_PARTNER){
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
            }
            else{
                Lbl_ChargeCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }
        }
    }
}

void charge_coupon::updateChargeCouponFail(Machine *m)
{
    CheckPushButtonOKPressed = false;
    Message->setText(m->transaction()->MessageRechargeMobile);
}

QString charge_coupon::getOrderInformation()
{
    return lineEdit_Coupon->text();
}

void charge_coupon::Back_Home(QString)
{
    emit Signal_ChargeCoupon(MENU);
}


void charge_coupon::on_Btn_Ok_ChargeCoupon_clicked()
{
    if(!CheckPushButtonOKPressed){
        if(s_machine->transaction()->CheckPriceServe){
            //Message->setText("Đang lấy kiểm tra thông tin mã Coupon ...");
            if(lineEdit_Coupon->text().length() > 1){
               Message->setText("");
               CheckPushButtonOKPressed = true;
               emit Signal_ChargeCoupon(CHARGED_COUPON);
               LOG<< lineEdit_Coupon->text()<<"mã cp";
            }else{
                Message->setText("Nhập mã Coupon!");
            }
        }else
            Message->setText("Đang lấy thông tin sản phẩm, vui lòng chờ trong giây lát!");
    }
}

void charge_coupon::on_Btn_Back_ChargeCoupon_clicked()
{
    emit Signal_ChargeCoupon(SELECT_CHARGE_TYPE);
    Message->setText("");
}

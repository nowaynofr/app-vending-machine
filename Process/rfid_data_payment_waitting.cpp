#include "rfid_data_payment_waitting.h"
#include "ui_rfid_data_payment_waitting.h"

rfid_data_payment_waitting::rfid_data_payment_waitting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rfid_data_payment_waitting)
{
    ui->setupUi(this);
}

rfid_data_payment_waitting::~rfid_data_payment_waitting()
{
    delete ui;
}

rfid_data_payment_waitting::rfid_data_payment_waitting(Machine *m)
{

    s_machine = m;
    //Check_GetPriceServer = false;
   // ServiceType_ChargedCoupon = ServiceType;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
   // Image_Sab->setGeometry(0,0,1200,660);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

    QFont font("Arial",27);
    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setMaximumSize(1080, 140);
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);
    QFont font2("Times",30);
    Message->setFont(font2);

    QGroupBox *ChargeCoupon = new QGroupBox(tr("Thông tin đơn hàng"));
    ChargeCoupon->setStyleSheet("QGroupBox { color : green; }");
    ChargeCoupon->setFont(font);
    QHBoxLayout *HBox_Lbl_ChargeCoupon = new QHBoxLayout;
    Lbl_ChargedCoupon = new QLabel(this);
    Lbl_ChargedCoupon->setWordWrap(true);
    Lbl_ChargedCoupon->setAlignment(Qt::AlignCenter);
    Lbl_ChargedCoupon->setStyleSheet("QLabel { border: 3px solid black; border-radius: 25px; background: gray;color: blue;}");
    QFont font1 = Lbl_ChargedCoupon->font();
    font1. setPointSize(32);
    font1. setBold(true);
    Lbl_ChargedCoupon->setFont(font1);
    Lbl_ChargedCoupon->setMinimumSize(1000,450);
    setRfidDataPaymentWaittng(m);
    HBox_Lbl_ChargeCoupon->addWidget(Lbl_ChargedCoupon);
    ChargeCoupon->setLayout(HBox_Lbl_ChargeCoupon);

//    QGroupBox *CouponGroup = new QGroupBox(tr("Nhập mã Coupon"));
//    QHBoxLayout *HBox_Number_Phone = new QHBoxLayout;
//    QLabel *NumberPhoneLabel = new QLabel(tr("Mã Coupon:"));
//    lineEdit_Coupon = new QLineEdit(this);
//    lineEdit_Coupon->setValidator(new QDoubleValidator(0,9999999999,0,this));
//    HBox_Number_Phone->addWidget(NumberPhoneLabel);
//    HBox_Number_Phone->addWidget(lineEdit_Coupon);
//    CouponGroup->setLayout(HBox_Number_Phone);


//    Message = new QLabel("",this);
//    Message->setWordWrap(true);
//    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Back = new PushButton_OK_BACK("Back", this);
    HBox_Ok_Back->addWidget(btn_Back);
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_RfidDataPaymentWaittng_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

    QLabel* home = new my_qlabel("",this);
    home->setAlignment(Qt::AlignCenter);
    home->setGeometry(960,450,110,110);
    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
    QImage img(":/img/Button_Image/Home_Btn.jpg");
    home->setPixmap(QPixmap::fromImage(img));
    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(ChargeCoupon);
   // mainLayout->addWidget(CouponGroup);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
}

void rfid_data_payment_waitting::setRfidDataPaymentWaittng(Machine *m)
{
    Message->setText("Đang kiểm tra mã thẻ...");
    if(m->transaction()->moneyCalculate == 0){
        if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
        }else{
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
        }
    }else{
        if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
        }else{
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
        }
    }
}

void rfid_data_payment_waitting::updateRfidDataPaymentWaittng(Machine *m)
{
    Message->setText(m->transaction()->MessageRechargeMobile);
    if(m->transaction()->moneyCalculate == 0){
        if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone);

        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");

        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
        }else{
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
        }
    }else{
        if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone);

        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");

        }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
        }else{
            Lbl_ChargedCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
        }
    }
}

void rfid_data_payment_waitting::Back_Home(QString)
{
    emit Signal_RfidDataPaymentWaittng(MENU);
}

void rfid_data_payment_waitting::on_Btn_Ok_RfidDataPaymentWaittng_clicked()
{

}

void rfid_data_payment_waitting::on_Btn_Back_RfidDataPaymentWaittng_clicked()
{
    emit Signal_RfidDataPaymentWaittng(SELECT_CHARGE_TYPE);
}

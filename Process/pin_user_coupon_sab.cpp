#include "pin_user_coupon_sab.h"
#include "ui_pin_user_coupon_sab.h"

pin_user_coupon_sab::pin_user_coupon_sab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pin_user_coupon_sab)
{
    ui->setupUi(this);
}

pin_user_coupon_sab::pin_user_coupon_sab(Machine *m)
{
    LOG;
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
    Lbl_PinUserCoupon = new QLabel(this);
    Lbl_PinUserCoupon->setWordWrap(true);
    Lbl_PinUserCoupon->setAlignment(Qt::AlignCenter);
    Lbl_PinUserCoupon->setStyleSheet("QLabel { border: 3px solid black; border-radius: 25px; background: gray;color: blue;}");
    QFont font1 = Lbl_PinUserCoupon->font();
    font1. setPointSize(32);
    font1. setBold(true);
    Lbl_PinUserCoupon->setFont(font1);
    Lbl_PinUserCoupon->setMinimumSize(1000,450);
    setPinUserCoupon(m);
    HBox_Lbl_ChargeCoupon->addWidget(Lbl_PinUserCoupon);
    ChargeCoupon->setLayout(HBox_Lbl_ChargeCoupon);

    QGroupBox *CouponGroup = new QGroupBox(tr("Mã Pin gắn với mã Coupon"));
    CouponGroup->setStyleSheet("QGroupBox { color : green; }");
    CouponGroup->setFont(font);
    QHBoxLayout *HBox_Number_Phone = new QHBoxLayout;
    QLabel *NumberPhoneLabel = new QLabel(tr("Mã Pin:"));
    NumberPhoneLabel->setFont(font);
    lineEdit_PinUserCoupon = new QLineEdit(this);
    //lineEdit_PinUserCoupon->setMinimumSize(600,60);
   // lineEdit_PinUserCoupon->setValidator(new QDoubleValidator(0,9999999999,0,this));
    lineEdit_PinUserCoupon->setInputMethodHints(Qt::ImhPreferNumbers);
    lineEdit_PinUserCoupon->setEchoMode(QLineEdit::Password);
    lineEdit_PinUserCoupon->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 10px");
    lineEdit_PinUserCoupon->setFocus();
    QFont font22("Arial",28);
    lineEdit_PinUserCoupon->setFont(font22);
    HBox_Number_Phone->addSpacing(190);
    HBox_Number_Phone->addWidget(NumberPhoneLabel);
    HBox_Number_Phone->addWidget(lineEdit_PinUserCoupon);
    HBox_Number_Phone->addSpacing(190);
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
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_PinUserCoupon_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_PinUserCoupon_clicked()));
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

pin_user_coupon_sab::~pin_user_coupon_sab()
{
    delete ui;
}

void pin_user_coupon_sab::setPinUserCoupon(Machine *m)
{
    if(m->transaction()->moneyCalculate == 0){
        if(m->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || m->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            Lbl_PinUserCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND" + "\n" + "Mã Coupon: "+ m->transaction()->OrderInformation);
        }else if(m->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
            Lbl_PinUserCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND" + "\n" + "Mã Coupon: "+ m->transaction()->OrderInformation);
        }else if(m->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            Lbl_PinUserCoupon->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND"+ "\n" + "Mã Coupon: "+ m->transaction()->OrderInformation);
        }else{
            Lbl_PinUserCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
        }
    }else{
        if(m->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO || m->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
            Lbl_PinUserCoupon->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND" + "\n" + "Mã Coupon: "+ m->transaction()->OrderInformation);
        }else if(m->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
            Lbl_PinUserCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND" + "\n" + "Mã Coupon: "+ m->transaction()->OrderInformation);
        }else if(m->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
            Lbl_PinUserCoupon->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND"+ "\n" + "Mã Coupon: "+ m->transaction()->OrderInformation);
        }else{
            Lbl_PinUserCoupon->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
        }
    }
}

void pin_user_coupon_sab::updatePinUserCoupon(Machine *)
{

}

QString pin_user_coupon_sab::getPinUserCoupon()
{
    return lineEdit_PinUserCoupon->text();
}

void pin_user_coupon_sab::Back_Home(QString)
{
    emit Signal_PinUserCoupon(MENU);
}

//void pin_user_coupon_sab::showKeyboard()
//{
//    LOG<<"Keyboard";
//    QInputMethod *input = QApplication::inputMethod();
//    input->show();
//}

void pin_user_coupon_sab::on_Btn_Ok_PinUserCoupon_clicked()
{
    if(lineEdit_PinUserCoupon->text().length() >= 1){
        emit Signal_PinUserCoupon(CHARGED_COUPON);
        LOG<< lineEdit_PinUserCoupon->text()<<"mã Pin";
    }else{
        Message->setText("Mời nhập mã Pin!");
    }
}

void pin_user_coupon_sab::on_Btn_Back_PinUserCoupon_clicked()
{
    emit Signal_PinUserCoupon(SELECT_CHARGE_TYPE);
}

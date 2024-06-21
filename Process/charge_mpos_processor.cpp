#include "charge_mpos_processor.h"
#include "ui_charge_mpos_processor.h"

charge_mpos_processor::charge_mpos_processor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::charge_mpos_processor)
{
    ui->setupUi(this);
}

charge_mpos_processor::charge_mpos_processor(Machine *m)
{
    LOG;
    s_machine = m;
    //show = "";
    CheckPushButtonOKPressed = false;

   // ServiceType_ChargeCoupon = ServiceType;
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
    Lbl_ChargeMpos = new QLabel(this);
    Lbl_ChargeMpos->setWordWrap(true);
    Lbl_ChargeMpos->setAlignment(Qt::AlignCenter);
    Lbl_ChargeMpos->setStyleSheet("QLabel { border: 3px solid black; border-radius: 25px; background: gray;color: blue;}");
    QFont font1 = Lbl_ChargeMpos->font();
    font1. setPointSize(32);
    font1. setBold(true);
    Lbl_ChargeMpos->setFont(font1);
    Lbl_ChargeMpos->setMinimumSize(1000,400);
    setChargeMpos(s_machine);
    HBox_Lbl_ChargeCoupon->addWidget(Lbl_ChargeMpos);
    ChargeCoupon->setLayout(HBox_Lbl_ChargeCoupon);

    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setMaximumSize(1080, 140);
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);
    QFont font2("Times",30);
    Message->setFont(font2);
   // Message->setText("Xin mời quẹt thẻ!");

    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Ok = new PushButton_OK_BACK("OK",this);
    btn_Back = new PushButton_OK_BACK("Back", this);
    HBox_Ok_Back->addWidget(btn_Back);
    HBox_Ok_Back->addWidget(btn_Ok);
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_ChargeMpos_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_ChargeMpos_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

//    QLabel* home = new my_qlabel("",this);
//    home->setGeometry(960,450,110,110);
//    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
//    QImage img(":/img/Button_Image/Home_Btn.jpg");
//    home->setPixmap(QPixmap::fromImage(img));
//    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(ChargeCoupon);
   // mainLayout->addWidget(CouponGroup);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
}

charge_mpos_processor::~charge_mpos_processor()
{
    delete ui;
}

void charge_mpos_processor::setChargeMpos(Machine *m)
{
    if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO){
        Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID || s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
        LOG;
    }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
        Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
        Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }
    else{
        Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }
}

void charge_mpos_processor::updateChargeMpos(Machine *m)
{
    if(m->transaction()->TransactionStatus == KioskTransactionStatus::PAYMENT_WAITING){
        CheckPushButtonOKPressed = false;
        Message->setText(m->transaction()->MessageRechargeMobile);
    }else{
        Message->setText("Ấn OK để thực hiện giao dịch!");
        if(m->transaction()->moneyCalculate == 0){
            if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO){
                m->transaction()->IsCheckingWorkWithVTC = false;
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
            }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::MOTORINSURANCE){
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }
            else{
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }
        }else{
            if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_TELCO){
                m->transaction()->IsCheckingWorkWithVTC = false;
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::POSTPAID){
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::BUYCARDMOBILE){
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }else if(s_machine->transaction()->serviceCode == RECHARGEMOBILETYPE::TOPUP_PARTNER){
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
            }
            else{
                Lbl_ChargeMpos->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }
        }
    }
}

void charge_mpos_processor::Back_Home(QString)
{
    emit Signal_ChargeMpos(MENU);
}

void charge_mpos_processor::on_Btn_Ok_ChargeMpos_clicked()
{
    if(!CheckPushButtonOKPressed){
        if(s_machine->transaction()->CheckPriceServe){
            CheckPushButtonOKPressed = true;
            Message->setText("Xác nhận thanh toán trên máy MPOS \nVui lòng không <Exit> khỏi màn hình!");
            s_machine->transaction()->TransactionStatus = KioskTransactionStatus::PAYMENT_WAITING;
            emit Signal_ChargeMpos(MACHINE_STATE::CHARGE_MPOS);
        }else
            Message->setText("Đang lấy thông tin sản phẩm, vui lòng chờ trong giây lát!");
    }
}

void charge_mpos_processor::on_Btn_Back_ChargeMpos_clicked()
{
    emit Signal_ChargeMpos(SELECT_CHARGE_TYPE);
    Message->setText("");
}

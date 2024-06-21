#include "select_charge_type.h"
#include "ui_select_charge_type.h"

select_charge_type::select_charge_type(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::select_charge_type)
{
    ui->setupUi(this);
}

select_charge_type::select_charge_type(Machine *m,QStringList list_charge_type)
{
    LOG;
    TextBillAvailable ="Số tiền đang có: ";
    s_machine = m;
    ServiceType = m->transaction()->serviceCode;
    //TransactionType = KioskTransactionType::UNSET;
    ListChargeTypeQR.clear();
    ListChargeTypeQR = m->GetValueKioskAdmin("ChargeTypeListDefault","ListBankType").split(QLatin1Char(','));
    ListChargeTypeQR.append(m->GetValueKioskAdmin("ChargeTypeListDefault","ListWalletType").split(QLatin1Char(',')));
    last_state = m->last_state();
    ListChargeType.clear();
    ListChargeType = list_charge_type;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
    Image_Sab->setMaximumHeight(550);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

    QFont font("Arial",26);
    QGroupBox *ChargeType = new QGroupBox(tr("Hình thức thanh toán"));
    ChargeType->setFont(font);
   // QHBoxLayout *HBox_Price = new QHBoxLayout;
    QGridLayout *grid = new QGridLayout();
    qint8 row = 0;
    for(int i = 0; i < ListChargeType.size(); i++){
        charge_type[i] = new my_qlabel(ListChargeType.at(i));        
        charge_type[i]->setWordWrap(true);
        //charge_type[i]->setMinimumSize(290,300);
        charge_type[i]->setMaximumSize(300,320);
        if(i%3 == 0){
            row++;
        }
        grid->addWidget(charge_type[i], row, i%3);
        charge_type[i]->setText(m->GetValueKioskAdmin("ChargeTypeCodeName",ListChargeType.at(i)));
        charge_type[i]->setStyleSheet("border: 3px solid black; border-radius: 25px; background: gray;color: blue;");
        charge_type[i]->setAlignment(Qt::AlignCenter);
        charge_type[i]->setFont(font);
        connect(charge_type[i], SIGNAL(home_network(QString)),this, SLOT(select_charge_type_clicked(QString)));
    }
    ChargeType->setLayout(grid);

    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setMaximumSize(1080, 140);
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);
    QFont font1("Times",30);
    Message->setFont(font1);
    Message->setText(TextBillAvailable + StringUtils::formatNumberVND(m->transaction()->IdentifiedAmount) + " VND");

    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Back = new PushButton_OK_BACK("Back", this);
   // btn_Back->setGeometry(400,1700,300,90);
    HBox_Ok_Back->addWidget(btn_Back);
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_SelectChargeType_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);
    Gr_Ok_Back->setMaximumSize(1080,220);


    QLabel* home = new my_qlabel("",this);
    home->setAlignment(Qt::AlignCenter);
    home->setGeometry(960,450,110,110);
    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
    QImage img(":/img/Button_Image/Home_Btn.jpg");
    home->setPixmap(QPixmap::fromImage(img));
    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(ChargeType);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
    //setStyleSheet("QPushButton { color: blue; background-color: gray;}");
}

select_charge_type::~select_charge_type()
{
    delete ui;
}

//quint8 select_charge_type::ChargeType_Select()
//{
//    return TransactionType;
//}

void select_charge_type::UpdateBillAmount()
{
    Message->setText(TextBillAvailable + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND");
}

void select_charge_type::Back_Home(QString)
{
    emit Signal_Select_Charge_Type(MENU);
}

void select_charge_type::on_Btn_Back_SelectChargeType_clicked()
{
    if(ServiceType == RECHARGEMOBILETYPE::TOPUP_TELCO){
        emit Signal_Select_Charge_Type(TOPUPTELCO);
    }else if(ServiceType == RECHARGEMOBILETYPE::BUYCARDMOBILE){
        emit Signal_Select_Charge_Type(MACHINE_STATE::BUY_CARD_MOBILE);
    }else if(ServiceType == RECHARGEMOBILETYPE::POSTPAID){
        emit Signal_Select_Charge_Type(MACHINE_STATE::POST_PAID);
    }else if(ServiceType == RECHARGEMOBILETYPE::TOPUP_PARTNER){
        emit Signal_Select_Charge_Type(MACHINE_STATE::TOPUPPARTNER);
    }else if(ServiceType == RECHARGEMOBILETYPE::MOTORINSURANCE){
        emit Signal_Select_Charge_Type(MACHINE_STATE::MOTOR_INSURANCE);
    }
    else{
        emit Signal_Select_Charge_Type(MACHINE_STATE::MENU_GOOD_GENERAL);
    }
}

void select_charge_type::select_charge_type_clicked(QString Charge_Type)
{
   // Message->setText("");
    if(Charge_Type.toInt() == KioskTransactionType::CASH){
        s_machine->transaction()->TransactionType = KioskTransactionType::CASH;
        if(ServiceType == RECHARGEMOBILETYPE::GOOD_GENERAL){
            if(s_machine->transaction()->AvailableAmount >= (s_machine->transaction()->GoodPrice *s_machine->transaction()->Quantity)){
                emit Signal_Select_Charge_Type(MACHINE_STATE::GET_GOOD_GENERAL);
            }else{
                Message->setText(TextBillAvailable + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND\n" + QString("Thiếu: %1 VND").arg(s_machine->transaction()->GoodPrice - s_machine->transaction()->AvailableAmount));
            }
        }else{
            emit Signal_Select_Charge_Type(MACHINE_STATE::GOOD_DIGITAL_PROCESS);
        }

    }else if(Charge_Type.toInt() == KioskTransactionType::COUPON){
        s_machine->transaction()->TransactionType = KioskTransactionType::COUPON;

        emit Signal_Select_Charge_Type(CHARGE_COUPON);
    }else if(Charge_Type.toInt() == KioskTransactionType::RFID){
        s_machine->transaction()->TransactionType = KioskTransactionType::RFID;
        emit Signal_Select_Charge_Type(RFID_DATA);

    }else if(Charge_Type.toInt() == KioskTransactionType::MPOS){
        s_machine->transaction()->TransactionType = KioskTransactionType::MPOS;
        emit Signal_Select_Charge_Type(CHARGE_MPOS);

    }
    else{
        if(ListChargeTypeQR.size() != 0){
            for(int i = 0; i < ListChargeTypeQR.size(); i++){
                if(Charge_Type == ListChargeTypeQR.at(i)){
                    s_machine->transaction()->TransactionType = QString(Charge_Type).toInt();
                    emit Signal_Select_Charge_Type(SALEINFO_QRCODE);
                }
            }
        }
    }
   // LOG<<Charge_Type<<"hình thức thanh toán";
}

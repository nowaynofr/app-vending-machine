#include "infosale_qr_code.h"
#include "ui_infosale_qr_code.h"

infoSale_qr_code::infoSale_qr_code(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::infoSale_qr_code)
{
    ui->setupUi(this);  
}

infoSale_qr_code::infoSale_qr_code(Machine *m,quint8 ServiceType)
{
    LOG;
    s_machine = m;
    Check_GetQRCodeFalse = false;
    ServiceType_QR = ServiceType;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

    QFont font("Arial",27);
    QGroupBox *InfoQR = new QGroupBox(tr("Thông tin đơn hàng"));
    InfoQR->setStyleSheet("QGroupBox { color : green; }");
    InfoQR->setFont(font);
    QHBoxLayout *HBox_Lbl_InfoQR = new QHBoxLayout;
    Lbl_InfoQR = new QLabel(this);
    Lbl_InfoQR->setWordWrap(true);
    Lbl_InfoQR->setAlignment(Qt::AlignCenter);
    Lbl_InfoQR->setStyleSheet("QLabel { border: 3px solid black; border-radius: 25px; background: gray;color: blue;}");
    QFont font1 = Lbl_InfoQR->font();
    font1. setPointSize(32);
    font1. setBold(true);
    Lbl_InfoQR->setFont(font1);
    Lbl_InfoQR->setMinimumSize(1000,450);
    setInfoSaleQR(m);
    HBox_Lbl_InfoQR->addWidget(Lbl_InfoQR);
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
    btn_Back = new PushButton_OK_BACK("Back", this);
    HBox_Ok_Back->addWidget(btn_Back);
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_infoSale_QRcode_clicked()));
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
   // setStyleSheet("QPushButton { color: blue; background-color: gray;}");
}

infoSale_qr_code::~infoSale_qr_code()
{
    delete ui;
}

void infoSale_qr_code::setInfoSaleQR(Machine *m)
{
    if(ServiceType_QR == RECHARGEMOBILETYPE::TOPUP_TELCO){
        Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }else if(ServiceType_QR == RECHARGEMOBILETYPE::POSTPAID || ServiceType_QR == RECHARGEMOBILETYPE::TOPUP_PARTNER){
        LOG;
    }else if(ServiceType_QR == RECHARGEMOBILETYPE::BUYCARDMOBILE){
        Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }else{
        Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: Đang lấy thông tin sản phẩm ...");
    }
}

void infoSale_qr_code::updateInfoSaleQR(Machine *m)
{
    LOG<<"updateInfoSaleQR";
    if(Check_GetQRCodeFalse){
        Lbl_InfoQR->setText("Lỗi hệ thống!");
        Message->setText("Truy vấn thông tin sản phẩm thất bại, mời chọn sản phẩm khác!");
    }else{
        if(m->transaction()->moneyCalculate == 0){
            if(ServiceType_QR == RECHARGEMOBILETYPE::TOPUP_TELCO){
                m->transaction()->IsCheckingWorkWithVTC = false;
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
                //Message->setText("Click <OK> để thanh toán");
            }else if(ServiceType_QR == RECHARGEMOBILETYPE::POSTPAID){
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }else if(ServiceType_QR == RECHARGEMOBILETYPE::BUYCARDMOBILE){
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }else if(ServiceType_QR == RECHARGEMOBILETYPE::TOPUP_PARTNER){
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
            }else{
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->Quantity * m->transaction()->GoodPrice) +" VND");
            }
        }else{
            if(ServiceType_QR == RECHARGEMOBILETYPE::TOPUP_TELCO){
                m->transaction()->IsCheckingWorkWithVTC = false;
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
                //Message->setText("Click <OK> để thanh toán");
            }else if(ServiceType_QR == RECHARGEMOBILETYPE::POSTPAID){
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }else if(ServiceType_QR == RECHARGEMOBILETYPE::BUYCARDMOBILE){
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }else if(ServiceType_QR == RECHARGEMOBILETYPE::TOPUP_PARTNER){
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND");
            }else{
                Lbl_InfoQR->setText(m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) +" VND");
            }
        }
        Message->setText("Đang lấy thông tin QR Code ...");
        emit Signal_infoSale_QRcode(SCREEN_GET_QRCODE);
    }
}

void infoSale_qr_code::Back_Home(QString)
{
    emit Signal_infoSale_QRcode(MENU);
}

//void infoSale_qr_code::on_Btn_Ok_infoSale_QRcode_clicked()
//{
//    if(Check_GetPriceServer){
//        Message->setText("Đang lấy thông tin QR Code ...");
//        emit Signal_infoSale_QRcode(SCREEN_GET_QRCODE);
//    }else
//        Message->setText("Đang lấy thông tin sản phẩm, vui lòng chờ trong giây lát!");
//}

void infoSale_qr_code::on_Btn_Back_infoSale_QRcode_clicked()
{
    emit Signal_infoSale_QRcode(SELECT_CHARGE_TYPE);
    Message->setText("");
}



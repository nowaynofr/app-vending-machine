#include "get_good_digital.h"
#include "ui_get_good_digital.h"

get_good_digital::get_good_digital(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::get_good_digital)
{
    ui->setupUi(this);
}

get_good_digital::get_good_digital(Machine *m, quint8 ServiceType)
{
    LOG;
    ServiceTypeGetGoodDigital = ServiceType;
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
    Lbl_InfoGetGoodDigital = new QLabel(this);
    Lbl_InfoGetGoodDigital->setWordWrap(true);
    Lbl_InfoGetGoodDigital->setAlignment(Qt::AlignCenter);
    Lbl_InfoGetGoodDigital->setStyleSheet("QLabel { border: 3px solid black; border-radius: 25px; background: gray;color: blue;}");
    QFont font1 = Lbl_InfoGetGoodDigital->font();
    font1. setPointSize(32);
    font1. setBold(true);
    Lbl_InfoGetGoodDigital->setFont(font1);
    Lbl_InfoGetGoodDigital->setMinimumSize(1000,450);
    setGetGoodDigital(m);
    HBox_Lbl_InfoQR->addWidget(Lbl_InfoGetGoodDigital);
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
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_GetGoodDigital_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

    QLabel* home = new my_qlabel("",this);
    home->setAlignment(Qt::AlignCenter);
    home->setGeometry(960,450,110,110);
    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
    QImage img(":/img/Button_Image/Home_Btn.jpg");
    home->setPixmap(QPixmap::fromImage(img));
    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(InfoQR);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
  //  setStyleSheet("QPushButton { color: blue; background-color: gray;}");
}

get_good_digital::~get_good_digital()
{
    delete ui;
}

void get_good_digital::setGetGoodDigital(Machine *m)
{
    if(ServiceTypeGetGoodDigital == RECHARGEMOBILETYPE::TOPUP_TELCO || ServiceTypeGetGoodDigital == RECHARGEMOBILETYPE::POSTPAID){
        Lbl_InfoGetGoodDigital->setText("Trạng thái giao dịch: Thành công \n" + m->transaction()->GoodName + "\n" + "Số điện thoại: " + m->transaction()->NumberPhone + "\n" + "Thời gian: "+ QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    }else if(ServiceTypeGetGoodDigital == RECHARGEMOBILETYPE::BUYCARDMOBILE){
        QString cardcode = m->transaction()->CardCode;
        int first = cardcode.indexOf("-");
        QString code = cardcode.mid(0, first);
        int second = cardcode.indexOf("-", first + 1);
        QString serial = cardcode.mid(first + 1, second - first - 1);
        QString datetime = cardcode.mid(second + 1, 10);
        Lbl_InfoGetGoodDigital->setText("--" + m->transaction()->GoodName +"--\nMã thẻ: " + code + "\n" + "Serial: " + serial + "\n" + "HSD: " + datetime + "\n" + "Thời gian: "+ QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    }else if(ServiceTypeGetGoodDigital == RECHARGEMOBILETYPE::TOPUP_PARTNER){
        Lbl_InfoGetGoodDigital->setText("Giao dịch Thành công \n" + m->transaction()->GoodName + "\n" + "Mã khách hàng: " + m->transaction()->customerID + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->amount_and_fee) +" VND" + "\n" + "Thời gian: "+ QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    }else if(ServiceTypeGetGoodDigital == RECHARGEMOBILETYPE::MOTORINSURANCE){
        Lbl_InfoGetGoodDigital->setText("Trạng thái giao dịch: Thành công \n" + m->transaction()->GoodName + "\n" + "Đơn hàng: " + StringUtils::formatNumberVND(m->transaction()->GoodPrice) +" VND" + "\n" + "Thời gian: "+ QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));

    }
}

void get_good_digital::Back_Home(QString)
{
    emit Signal_GetGoodDigital_Process(MENU);
}

void get_good_digital::on_Btn_Ok_GetGoodDigital_clicked()
{

}

void get_good_digital::on_Btn_Back_GetGoodDigital_clicked()
{
    emit Signal_GetGoodDigital_Process(SELECT_SERVICE);
}

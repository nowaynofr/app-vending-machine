#include "menu_good.h"
#include "ui_menu_good.h"

Menu_Good::Menu_Good(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu_Good)
{
    LOG;
    ui->setupUi(this);
}

Menu_Good::Menu_Good(Machine* m,quint8 quatity_UrlPromotionImage,QString directory):
    m_timer(this)
{
    s_machine = m;
    index_image = 0;
    TextBillAvailable ="Số tiền đang có: ";
    quatity_image = quatity_UrlPromotionImage;
    DatabaseDataStoragePath = directory;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    lb_SaverCreen = new QLabel(this);
    lb_SaverCreen->setAlignment(Qt::AlignCenter);
    lb_SaverCreen->setMaximumSize(1080,560);
    lb_SaverCreen->setScaledContents(true);
    QImage image(DatabaseDataStoragePath + "/" + "promotion" + QString::number(index_image) +".png");
    if(image.isNull()){
        image.load(":/img/S&B.png");
    }
    lb_SaverCreen->setPixmap(QPixmap::fromImage(image));

    QLabel* Image_Digital = new my_qlabel("digital",this);
    Image_Digital->setFrameStyle(QFrame::Box);
    Image_Digital->setScaledContents(true);
    Image_Digital->setStyleSheet("QLabel { border-image : url(:/img/Digital.png); color : red;border: 3px solid black; border-radius: 30px }");
//    QPixmap pix_menu(":/img/Digital.png");
//    Image_Digital->setPixmap(pix_menu);
    connect(Image_Digital, SIGNAL(home_network(QString)),this, SLOT(select_menugood(QString)));

    QLabel* Image_GoodGeneral= new my_qlabel("menugeneral",this);
    Image_GoodGeneral->setFrameStyle(QFrame::Box);
  //  Image_GoodGeneral->setLineWidth(10);
    Image_GoodGeneral->setScaledContents(true);
    Image_GoodGeneral->setStyleSheet("QLabel { border-image : url(:/img/GoodGeneral.jpg); color : red;border: 3px solid black; border-radius: 30px }");
//    QPixmap pix_menu_general(":/img/GoodGeneral.jpg");
//    Image_GoodGeneral->setPixmap(pix_menu_general);
    connect(Image_GoodGeneral, SIGNAL(home_network(QString)),this, SLOT(select_menugood(QString)));


    QGroupBox *ServiceGroup = new QGroupBox(tr("Chọn dịch vụ"));
    ServiceGroup->setAlignment(Qt::AlignCenter);
    ServiceGroup->setStyleSheet("QGroupBox { color : green; }");
    QFont font("Arial",34);
    ServiceGroup->setFont(font);
    QHBoxLayout *Service = new QHBoxLayout;
    Service->addWidget(Image_Digital);
    Service->addWidget(Image_GoodGeneral);
    ServiceGroup->setLayout(Service);

    lb_Promotion = new QLabel(this);
    lb_Promotion->setFrameStyle(QFrame::Box);
    lb_Promotion->setMaximumSize(1080,500);
    lb_Promotion->setFont(font);
    lb_Promotion->setAlignment(Qt::AlignCenter);
    lb_Promotion->setText(TextBillAvailable + StringUtils::formatNumberVND(m->transaction()->IdentifiedAmount) + " VND");

    //Test nhả hàng, Bill, thẻ từ Android

//    QLabel* NhaHang= new my_qlabel("ReturnGood",this);
//    NhaHang->setFrameStyle(QFrame::Box);

//  //  Image_GoodGeneral->setLineWidth(10);
//    NhaHang->setScaledContents(true);
//    NhaHang->setStyleSheet("QLabel { border-image : url(:/img/Settings-icon.png); color : red;border: 3px solid black; border-radius: 30px }");
// //    QPixmap pix_menu_general(":/img/GoodGeneral.jpg");
// //    Image_GoodGeneral->setPixmap(pix_menu_general);
//    connect(NhaHang, SIGNAL(home_network(QString)),this, SLOT(select_menugood(QString)));

//    lb_RFID = new QLabel("Dữ liệu thẻ từ RFID",this);
//    lb_RFID->setFrameStyle(QFrame::Box);
//    lb_RFID->setMaximumSize(1080,100);
//    lb_RFID->setAlignment(Qt::AlignCenter);

//    lb_BillResponse = new QLabel("Phản hồi Bill",this);
//    lb_BillResponse->setFrameStyle(QFrame::Box);
//    lb_BillResponse->setMaximumSize(1080,100);
//    lb_BillResponse->setAlignment(Qt::AlignCenter);

//    lb_BillAmount = new QLabel("Giá trị tiền",this);
//    lb_BillAmount->setFrameStyle(QFrame::Box);
//    lb_BillAmount->setMaximumSize(1080,100);
//    lb_BillAmount->setAlignment(Qt::AlignCenter);

//    lb_Status = new QLabel("Trạng thái",this);
//    lb_Status->setFrameStyle(QFrame::Box);
//    lb_Status->setMaximumSize(1080,300);
//    lb_Status->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(lb_SaverCreen);
    mainLayout->addWidget(ServiceGroup);
    mainLayout->addWidget(lb_Promotion);

//    mainLayout->addWidget(NhaHang);
//    mainLayout->addWidget(lb_RFID);
//    mainLayout->addWidget(lb_BillResponse);
//    mainLayout->addWidget(lb_BillAmount);
//    mainLayout->addWidget(lb_Status);

   // mainLayout->addWidget(lb_Promotion);
    setLayout(mainLayout);
    this->setStyleSheet("background-color: orange");
    m_timer.setInterval(m->config.getSaverScreen());
    if(!image.isNull() || quatity_image != 1)
        m_timer.start();
    connect (&m_timer, SIGNAL(timeout()), this, SLOT(display_image()));
}

Menu_Good::~Menu_Good()
{
    delete ui;
}

void Menu_Good::UpdateQuatityImage(quint8 quatity)
{
    quatity_image = quatity;
}

void Menu_Good::StartTimer()
{
    m_timer.start();
}

void Menu_Good::UpdateBillAmount()
{
    LOG<< s_machine->transaction()->IdentifiedAmount<<"tiền bill";
    lb_Promotion->setText(TextBillAvailable + StringUtils::formatNumberVND(s_machine->transaction()->IdentifiedAmount) + " VND");
}

//void Menu_Good::UpdateData(QString RFID, QString BillAmount)
//{
//    lb_BillAmount->setText("Số tiền: " + BillAmount + "  response: ");
//    lb_RFID->setText("ID thẻ: " + RFID);
//}

//void Menu_Good::UpdateBill(QString BillResponse)
//{
//    BillStatus += BillResponse;
//    lb_BillResponse->setText("Bill Response: " + BillStatus);
//}

//void Menu_Good::UpdateStatus(QString a)
//{
//    status += a;
//    lb_Status->setText(status);
//}

void Menu_Good::select_menugood(QString select)
{
    m_timer.stop();
    emit Signal_Menu_Good(select);
}

void Menu_Good::display_image()
{
    if(index_image == (quatity_image - 1)){
        index_image = 0;
    }else{
        index_image++;
    }
    QImage image(DatabaseDataStoragePath + "/" + "promotion" + QString::number(index_image) +".png");
    if(image.isNull()){
        image.load(":/img/S&B.png");
    }
    lb_SaverCreen->setPixmap(QPixmap::fromImage(image));
}



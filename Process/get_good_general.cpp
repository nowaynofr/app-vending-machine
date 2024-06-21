#include "get_good_general.h"
#include "ui_get_good_general.h"

Get_Good_General::Get_Good_General(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Get_Good_General)
{
    ui->setupUi(this);
}

Get_Good_General::Get_Good_General(Machine *m)
{
    show = "";
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
    Lbl_Info = new QLabel(this);
    Lbl_Info->setWordWrap(true);
    Lbl_Info->setAlignment(Qt::AlignCenter);
    Lbl_Info->setStyleSheet("QLabel { border: 3px solid black; border-radius: 25px; background: gray;color: blue;}");
    QFont font1 = Lbl_Info->font();
    font1. setPointSize(32);
    font1. setBold(true);
    Lbl_Info->setFont(font1);
    Lbl_Info->setMinimumSize(1000,450);
    setInfoSale(m);
    HBox_Lbl_InfoQR->addWidget(Lbl_Info);
    InfoQR->setLayout(HBox_Lbl_InfoQR);

    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setMaximumSize(1080, 140);
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);
    QFont font2("Times",34);
    Message->setFont(font2);
    Message->setText("Mời nhận hàng!");
    Message->setAlignment(Qt::AlignCenter);

    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
  //  btn_Ok = new QPushButton("OK",this);
    btn_Back = new PushButton_OK_BACK("Back", this);
    HBox_Ok_Back->addWidget(btn_Back);
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_GetGoodGeneral_clicked()));
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
}

Get_Good_General::~Get_Good_General()
{
    delete ui;
}

void Get_Good_General::OutOfGood()
{
    Message->setText("Trả hàng thất bại!");
}

void Get_Good_General::ReturnGoodFail()
{
    Message->setText("Trả hàng thất bại. Gọi hotline để được hỗ trợ!");
}

void Get_Good_General::ReturnGoodSuccess()
{
    Message->setText("Xin mời nhận hàng!");
}

void Get_Good_General::ShowResponse(QString s)
{
    show += " -- "+ s;
    Message->setText(show);
}

void Get_Good_General::Back_Home(QString)
{
    emit Signal_GetGoodGeneral_Process(MACHINE_STATE::MENU);
}

void Get_Good_General::setInfoSale(Machine *m)
{
    if(m->transaction()->moneyCalculate == 0){
        Lbl_Info->setText(m->transaction()->GoodName + "\n" + StringUtils::formatNumberVND(m->transaction()->GoodPrice*m->transaction()->Quantity) + " VND");
    }else{
        Lbl_Info->setText(m->transaction()->GoodName + "\n" + StringUtils::formatNumberVND(m->transaction()->moneyCalculate) + " VND");
    }
}

void Get_Good_General::on_Btn_Back_GetGoodGeneral_clicked()
{
    emit Signal_GetGoodGeneral_Process(MACHINE_STATE::MENU);
}

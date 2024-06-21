#include "topup_partner.h"
#include "ui_topup_partner.h"

topup_partner::topup_partner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::topup_partner)
{
    ui->setupUi(this);
}

topup_partner::topup_partner(Machine *m)
{
    LOG;
    CheckPushButtonOKPressed = false;
    LOG<<"khởi tạo màn hình thanh toán hóa đơn";
    ui->setupUi(this);
    Industry_Partner = m->transaction()->Industry;
    Partner = "";
    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
    Image_Sab->setMaximumHeight(550);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

    QLabel* Title = new QLabel(this);
    Title->setText(Industry_Partner);
    Title->setMaximumSize(1080, 110);
    QFont fontTitle("Nyala",32);
    Title->setFont(fontTitle);
    Title->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    Title->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Title->setLineWidth(2);
    Title->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QFont font("Arial",26);
    QGroupBox *homeNetworkGroup = new QGroupBox(tr("Nhà cung cấp dịch vụ"));
    homeNetworkGroup->setFont(font);

    QGroupBox *NumberPhoneGroup = new QGroupBox(tr("Mã khách hàng"));
    NumberPhoneGroup->setStyleSheet("QGroupBox { color : green; }");
    NumberPhoneGroup->setFont(font);

//    QGroupBox *OrderGroup = new QGroupBox(tr("Nhập số tiền thanh toán"));
//    OrderGroup->setStyleSheet("QGroupBox { color : green; }");
//    OrderGroup->setFont(font);

    QGridLayout *grid = new QGridLayout();
    qint8 row = 0;
    for(int i = 0; i < m_db.GetListGoodType(Industry_Partner).size(); i++){
        partner[i] = new my_qlabel(m_db.GetListGoodType(Industry_Partner).at(i),this);
        partner[i]->setScaledContents(true);
       // partner[i]->setFrameStyle(QFrame::Box);
        //partner[i]->setLineWidth(1);
        partner[i]->setWordWrap(true);
        partner[i]->setMinimumSize(200,210);
        partner[i]->setMaximumSize(300,210);
        partner[i]->setText(m_db.GetListGoodType(Industry_Partner).at(i));
        partner[i]->setStyleSheet("border: 1px solid black; border-radius: 25px; background: gray;color: blue;");
       // partner[i]->setStyleSheet("QLabel { background-color : gray; color : blue; }");
        partner[i]->setAlignment(Qt::AlignCenter);
        partner[i]->setFont(font);
        if(i%3 == 0){
            row++;
        }
        grid->addWidget(partner[i], row, i%3);
        connect(partner[i], SIGNAL(home_network(QString)),this, SLOT(select_Partner(QString)));

    }
    homeNetworkGroup->setLayout(grid);

    QHBoxLayout *HBox_Number_Phone = new QHBoxLayout;
    QLabel *NumberPhoneLabel = new QLabel(tr("Mã khách hàng:"));
    NumberPhoneLabel->setFont(font);
    lineEdit_Number_Phone = new QLineEdit(this);
   // lineEdit_Number_Phone->setInputMethodHints(Qt::ImhPreferNumbers);
   // lineEdit_Number_Phone->setValidator(new QDoubleValidator(0,9999999999,0,this));
    QFont font22("Arial",28);
    lineEdit_Number_Phone->setFont(font22);
    lineEdit_Number_Phone->setMaximumSize(500,60);
    lineEdit_Number_Phone->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 10px");
    lineEdit_Number_Phone->setFocus();
    HBox_Number_Phone->addSpacing(110);
    HBox_Number_Phone->addWidget(NumberPhoneLabel);
    HBox_Number_Phone->addSpacing(15);
    HBox_Number_Phone->addWidget(lineEdit_Number_Phone);
    HBox_Number_Phone->addSpacing(110);
    NumberPhoneGroup->setLayout(HBox_Number_Phone);
    NumberPhoneGroup->setMaximumHeight(220);

    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setMaximumSize(1080, 140);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);
    QFont fontMes("Times",30);
    Message->setFont(fontMes);

    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Ok = new PushButton_OK_BACK("OK",this);
    btn_Back = new PushButton_OK_BACK("Back", this);
    HBox_Ok_Back->addWidget(btn_Back);
    HBox_Ok_Back->addWidget(btn_Ok);
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_TopupPartner_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_TopupPartner_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

    QLabel* home = new my_qlabel("",this);
    home->setAlignment(Qt::AlignCenter);
    home->setGeometry(960,450,110,110);
    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
    QImage img(":/img/Button_Image/Home_Btn.jpg");
    home->setPixmap(QPixmap::fromImage(img));
    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(Title);
    mainLayout->addWidget(homeNetworkGroup);
    mainLayout->addWidget(NumberPhoneGroup);
   // mainLayout->addWidget(TopupPartner);

    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
}

topup_partner::~topup_partner()
{
    delete ui;
}

QString topup_partner::Partner_TopupPartner()
{
    return Partner;
}


QString topup_partner::customerID_TopupPartner()
{
    return  lineEdit_Number_Phone->text();
}

void topup_partner::UpdateGetBillInfoFail(Machine *m)
{
    Message->setText(m->transaction()->MessageRechargeMobile);
    CheckPushButtonOKPressed = false;
}

void topup_partner::UpdateRePartner()
{
   // m->transaction()->customerID = "";
   // m->transaction()->CategoryId = 0;
    CheckPushButtonOKPressed = false;
    Message->setText("");

}

void topup_partner::select_Partner(QString select)
{
    for(int i = 0; i < m_db.GetListGoodType(Industry_Partner).size(); i++){
        if(select == m_db.GetListGoodType(Industry_Partner).at(i)){
            partner[i]->setStyleSheet("border: 6px solid red; border-radius: 25px; background: gray;color: blue;");
           // partner[i]->setScaledContents(true);
          //  partner[i]->setFrameStyle(QFrame::Box);
          //  partner[i]->setStyleSheet ("QFrame {border: 6px solid red;}");
            //partner[i]->setLineWidth(6);
        }else{
            partner[i]->setStyleSheet("border: 1px solid black; border-radius: 25px; background: gray;color: blue;");
//            partner[i]->setScaledContents(true);
//            partner[i]->setFrameStyle(QFrame::Box);
//            partner[i]->setStyleSheet ("QFrame {border: 1px solid black;}");
           // partner[i]->setLineWidth(1);
        }
    }
    if(Message->text().contains("Chọn nhà cung cấp dịch vụ!")){
        Message->setText("");
    }
    Partner = select;
}

void topup_partner::Back_Home(QString)
{
    emit Signal_TopupPartner(MENU);
}

void topup_partner::on_Btn_Ok_TopupPartner_clicked()
{
     if(!CheckPushButtonOKPressed){
        if(Partner == ""){
            Message->setText("Chọn nhà cung cấp dịch vụ!");
        }else if(lineEdit_Number_Phone->text() == ""){
            Message->setText("Nhập mã khách hàng!");
        }
        else{
            CheckPushButtonOKPressed = true;
            Message->setText("Đang lấy thông tin hóa đơn...");
            emit Signal_TopupPartner(TOPUPPARTNER);
        }
     }
}

void topup_partner::on_Btn_Back_TopupPartner_clicked()
{
    emit Signal_TopupPartner(SELECT_SERVICE);
}


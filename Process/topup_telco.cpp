#include "topup_telco.h"
#include "ui_topup_telco.h"

topup_telco::topup_telco(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::topup_telco)
{
    ui->setupUi(this);
}

topup_telco::topup_telco(Machine *m)
{
    LOG<<"khởi tạo màn hình nạp trả trc";
    ui->setupUi(this);
    Price = 0;
    HomeNetwork = "";

    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
    Image_Sab->setMaximumHeight(550);
   // Image_Sab->setGeometry(0,0,1200,660);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);


    QLabel* Title = new QLabel(this);
    Title->setText(m->transaction()->Industry);
    Title->setMaximumSize(1080, 110);
    QFont fontTitle("Nyala",32);
    Title->setFont(fontTitle);
    Title->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    Title->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Title->setLineWidth(2);
    Title->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QFont font("Arial",26);
    QGroupBox *homeNetworkGroup = new QGroupBox(tr("Nhà mạng"));
   // homeNetworkGroup->setAlignment(Qt::AlignCenter);
   // font.setStyleHint(QFont::Monospace);
   // homeNetworkGroup->setStyleSheet("QGroupBox { color : green; }");
    homeNetworkGroup->setFont(font);
//    homeNetworkGroup->setMinimumSize(1055,350);
//    homeNetworkGroup->setMaximumSize(1055,350);
    QHBoxLayout *HBox_homeNetwork = new QHBoxLayout;

    for(int i = 0; i < m_db.GetListGoodType("Nạp tiền điện thoại trả trước").size(); i++){
        if(m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i).contains("Vina")
        || m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i).contains("Viettel")
        || m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i).contains("Mobifone")
        || m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i).contains("Vietnamobile")
        || m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i).contains("GMobile")){
            home_network[i] = new my_qlabel(m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i),this);
            home_network[i]->setScaledContents(true);
          //  home_network[i]->setFrameStyle(QFrame::Box);
           // home_network[i]->setLineWidth(1);
            home_network[i]->setStyleSheet ("QFrame {border: 1px solid black;}");
            QImage image(":/img/HomeNetwork/" +m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i).mid(19) +".png");
            home_network[i]->setPixmap(QPixmap::fromImage(image));
            HBox_homeNetwork->addWidget(home_network[i]);
            connect(home_network[i], SIGNAL(home_network(QString)),this, SLOT(select_home_network(QString)));
        }
    }
    homeNetworkGroup->setLayout(HBox_homeNetwork);
  //  homeNetworkGroup->setStyleSheet("color: green; background-color: rgb (254,248,134);");
    QGroupBox *NumberPhoneGroup = new QGroupBox(tr("Nhập số điện thoại"));
 //   NumberPhoneGroup->setStyleSheet("QGroupBox { color : green; }");
    NumberPhoneGroup->setFont(font);
   // NumberPhoneGroup->setMinimumSize(1080,200);

    QHBoxLayout *HBox_Number_Phone = new QHBoxLayout;
    QLabel *NumberPhoneLabel = new QLabel(tr("SĐT:"));
    NumberPhoneLabel->setFont(font);
    lineEdit_Number_Phone = new QLineEdit(this);
    lineEdit_Number_Phone->setInputMethodHints(Qt::ImhPreferNumbers);
    //lineEdit_Number_Phone->setValidator(new QDoubleValidator(0,9999999999,0,this));
    QFont font22("Arial",28);
    lineEdit_Number_Phone->setFont(font22);
    //lineEdit_Number_Phone->setMinimumSize(500,60);
    lineEdit_Number_Phone->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 10px");
    lineEdit_Number_Phone->setFocus();
    HBox_Number_Phone->addSpacing(225);
    HBox_Number_Phone->addWidget(NumberPhoneLabel);
    HBox_Number_Phone->addWidget(lineEdit_Number_Phone);
    HBox_Number_Phone->addSpacing(225);
    NumberPhoneGroup->setLayout(HBox_Number_Phone);
    NumberPhoneGroup->setMaximumHeight(220);


    QGroupBox *PriceGroup = new QGroupBox(tr("Mệnh giá"));
  //  PriceGroup->setStyleSheet("QGroupBox { color : green; }");
    PriceGroup->setFont(font);
   // PriceGroup->setMinimumSize(1080,400);
   // QHBoxLayout *HBox_Price = new QHBoxLayout;


    grid = new QGridLayout();
    qint8 row = 0;
    for(int i = 0; i < m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước","Nạp tiền trả trước Vina").size(); i++){
        price[i] = new my_qlabel(m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước","Nạp tiền trả trước Vina").at(i), i);
        price[i]->setFrameShape(QFrame::Box);
        price[i]->setScaledContents(true);
        price[i]->setWordWrap(true);
       // price[i]->adjustSize();

        if(i%3 == 0){
            row++;
        }
        grid->addWidget(price[i], row, i%3);
        price[i]->setText(QString::number(m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước","Nạp tiền trả trước Vina").at(i)));
        price[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
        //price[i]->setStyleSheet("QLabel { background-color : gray; color : blue; }");
        price[i]->setAlignment(Qt::AlignCenter);
        price[i]->setFont(font);
       // HBox_Price->addWidget(price[i]);
        connect(price[i], SIGNAL(price(quint32,quint8)),this, SLOT(select_price(quint32,quint8)));
        //connect(price[i], SIGNAL(clicked(QString)),this, SLOT(select_price(QString,m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước","Nạp tiền trả trước Vina").at(i), i)));
    }
    PriceGroup->setLayout(grid);
   // PriceGroup->setStyleSheet("color: green; background-color: gray");

    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setMaximumSize(1080, 140);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);
    QFont font1("Times",30);
    Message->setFont(font1);

    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Ok = new PushButton_OK_BACK("OK",this);
    btn_Back = new PushButton_OK_BACK("Back", this);
    HBox_Ok_Back->addWidget(btn_Back);
    HBox_Ok_Back->addWidget(btn_Ok);
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_Topuptelco_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_Topuptelco_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

    QLabel* home = new my_qlabel("",this);
    home->setAlignment(Qt::AlignCenter);
    home->setGeometry(960,450,110,110);
    home->setAlignment(Qt::AlignCenter);
    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
    QImage img(":/img/Button_Image/Home_Btn.jpg");
    home->setPixmap(QPixmap::fromImage(img));
    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(Title);
    mainLayout->addWidget(homeNetworkGroup);
    mainLayout->addWidget(NumberPhoneGroup);
    mainLayout->addWidget(PriceGroup);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
    setLayout(mainLayout);
}

topup_telco::~topup_telco()
{
    delete ui;
}


QString topup_telco::HomeNetwork_TopupTelco()
{
    return HomeNetwork;
}

quint32 topup_telco::Price_TopupTelco()
{
    return Price;
}

QString topup_telco::NumberPhone_TopupTelco()
{
    return lineEdit_Number_Phone->text();
}

void topup_telco::on_Btn_Ok_Topuptelco_clicked()
{
    if(HomeNetwork == ""){
        Message->setText("Xin mời chọn nhà mạng!");
    }else if(lineEdit_Number_Phone->text().length() >= 15 || lineEdit_Number_Phone->text().length() <= 7){
        Message->setText("Kiểm tra lại số điện thoại!");
    }else if(Price == 0){
        Message->setText("Xin mời chọn mệnh giá nạp tiền!");
    }else{
        Message->setText("");
        emit Signal_ToupupTelco(SELECT_CHARGE_TYPE);
    }

}

void topup_telco::on_Btn_Back_Topuptelco_clicked()
{
    emit Signal_ToupupTelco(SELECT_SERVICE);
}

void topup_telco::select_home_network(QString select)
{
   // LOG<<select<<"chọn nhà mạng";
    for (int i = 0; i < grid->count(); i++)
    {
       grid->itemAt(i)->widget()->deleteLater();
    }
    for(int i = 0; i < m_db.GetListGoodType("Nạp tiền điện thoại trả trước").size(); i++){
        if(select == m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i)){
         //   home_network[i]->setScaledContents(true);
           // home_network[i]->setFrameStyle(QFrame::Box);
          //  home_network[i]->setLineWidth(5);
          //  QString StyleSheet = "QLabel { border-image : url(:/img/HomeNetwork/" + m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i).mid(19) +".png); color : red;border: 1px solid red; border-radius: 15px}";
          //  home_network[i]->setStyleSheet(StyleSheet);
            //home_network[i]->setStyleSheet("QLabel { border-image : url(:/img/data3g.png); color : red;border: 30px solid black; border-radius: 30px }");
            home_network[i]->setStyleSheet ("QFrame {border: 6px solid red;}");
        }else{
         //   home_network[i]->setScaledContents(true);
          //  home_network[i]->setFrameStyle(QFrame::Box);
         //   QString StyleSheet = "QLabel { border-image : url(:/img/HomeNetwork/" + m_db.GetListGoodType("Nạp tiền điện thoại trả trước").at(i).mid(19) +".png); color : black;border: 20px solid black; border-radius: 15px }";
           // home_network[i]->setStyleSheet(StyleSheet);
          //  home_network[i]->setStyleSheet("QLabel { border-image : url(:/img/data3g.png); color : red;border: 3px solid black; border-radius: 30px }");
          //  home_network[i]->setLineWidth(1);
            home_network[i]->setStyleSheet ("QFrame {border: 1px solid black;}");
        }
    }
    if(Message->text().contains("Xin mời chọn nhà mạng!")){
        Message->setText("");
    }
    HomeNetwork = select;

    QFont font("Arial",26);
    qint8 row = 0;
    for(int i = 0; i < m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước",HomeNetwork).size(); i++){
            price[i] = new my_qlabel(m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước",HomeNetwork).at(i), i);
            price[i]->setFrameShape(QFrame::Box);
            price[i]->setWordWrap(true);

            if(i%3 == 0){
                row++;
            }
            grid->addWidget(price[i], row, i%3);
            price[i]->setText(QString::number(m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước",HomeNetwork).at(i)));
            price[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
          //  price[i]->setStyleSheet("QLabel { background-color : gray; color : blue; }");
            price[i]->setAlignment(Qt::AlignCenter);
            price[i]->setFont(font);
           // HBox_Price->addWidget(price[i]);
            connect(price[i], SIGNAL(price(quint32,quint8)),this, SLOT(select_price(quint32,quint8)));
            //connect(price[i], SIGNAL(clicked(QString)),this, SLOT(select_price(QString,m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước","Nạp tiền trả trước Vina").at(i), i)));
    }
    Price = 0;

}

void topup_telco::select_price(quint32 _price,quint8 index)
{
    for(int i = 0; i < m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước",HomeNetwork).size(); i++){
        if(index == i){
            price[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: red;color: blue;}");
           // price[i]->setStyleSheet("QLabel { background-color : red; color : blue; }");
        }else{
            price[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
            //price[i]->setStyleSheet("QLabel { background-color : gray; color : blue; }");
        }
    }
   // price[index]->setStyleSheet("QLabel { background-color : red; color : blue; }");
    if(Message->text().contains("Xin mời chọn mệnh giá nạp tiền!")){
        Message->setText("");
    }
    LOG<<_price<<"chọn giá";
    Price = _price;
}

void topup_telco::Back_Home(QString)
{
    emit Signal_ToupupTelco(MENU);
}

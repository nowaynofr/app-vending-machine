#include "buy_card.h"
#include "ui_buy_card.h"

buy_card::buy_card(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::buy_card)
{
    LOG<<"kokooko";
    ui->setupUi(this);
}

buy_card::buy_card(Machine *m)
{
    LOG<<"khởi tạo màn hình mua thẻ đt";
    ui->setupUi(this);
    Price = 0;
    if(m->transaction()->Industry == ""){
        Industry_BuyCard = "Mua thẻ điện thoại";
    }else
        Industry_BuyCard = m->transaction()->Industry;
    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
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
    QGroupBox *homeNetworkGroup = new QGroupBox(tr("Chọn loại thẻ"));
    homeNetworkGroup->setFont(font);
    QHBoxLayout *HBox_homeNetwork = new QHBoxLayout;
    if(Industry_BuyCard == "Mua thẻ điện thoại"){
        for(int i = 0; i < m_db.GetListGoodType(Industry_BuyCard).size(); i++){
            LOG<<"jihu";
            home_network[i] = new my_qlabel(m_db.GetListGoodType(Industry_BuyCard).at(i),this);
            home_network[i]->setScaledContents(true);
//            home_network[i]->setFrameStyle(QFrame::Box);
//            home_network[i]->setLineWidth(1);
            home_network[i]->setStyleSheet ("QFrame {border: 1px solid black;}");
            if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("VietnamMobile")){
                QImage image(":/img/HomeNetwork/Vietnamobile.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("Gmobile")){
                QImage image(":/img/HomeNetwork/GMobile.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else{
                QImage image(":/img/HomeNetwork/" +m_db.GetListGoodType(Industry_BuyCard).at(i).mid(7) +".png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }

            HBox_homeNetwork->addWidget(home_network[i]);
            connect(home_network[i], SIGNAL(home_network(QString)),this, SLOT(select_home_network(QString)));

        }
    }else if(Industry_BuyCard == "Mua thẻ Data 3G"){
        for(int i = 0; i < m_db.GetListGoodType(Industry_BuyCard).size(); i++){
            home_network[i] = new my_qlabel(m_db.GetListGoodType(Industry_BuyCard).at(i),this);
            home_network[i]->setScaledContents(true);
//            home_network[i]->setFrameStyle(QFrame::Box);
//            home_network[i]->setLineWidth(1);
            home_network[i]->setStyleSheet ("QFrame {border: 1px solid black;}");
            if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("Viettel")){
                QImage image(":/img/Data3G/3Gviettel.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("Vinaphone")){
                QImage image(":/img/Data3G/3GVina.jpg");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("Mobifone")){
                QImage image(":/img/Data3G/3gMobi.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }

            HBox_homeNetwork->addWidget(home_network[i]);
            connect(home_network[i], SIGNAL(home_network(QString)),this, SLOT(select_home_network(QString)));

        }
    }else if(Industry_BuyCard == "Mua thẻ Game"){
        GridGameCard = new QGridLayout();
        qint8 row = 0;
        for(int i = 0; i < m_db.GetListGoodType(Industry_BuyCard).size(); i++){
            home_network[i] = new my_qlabel(m_db.GetListGoodType(Industry_BuyCard).at(i),this);
            home_network[i]->setScaledContents(true);
//            home_network[i]->setFrameStyle(QFrame::Box);
//            home_network[i]->setLineWidth(1);
            home_network[i]->setStyleSheet ("QFrame {border: 1px solid black;}");
            if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("Zing")){
                QImage image(":/img/GameCard/Zing.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("Gate")){
                QImage image(":/img/GameCard/Gate.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("VCoin")){
                QImage image(":/img/GameCard/VCoin.jpg");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("OnCash")){
                QImage image(":/img/GameCard/OnCash.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("(Garena)")){
                QImage image(":/img/GameCard/Garena.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("Appota")){
                QImage image(":/img/GameCard/Appota.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("SohaCoin")){
                QImage image(":/img/GameCard/SohaCoin.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("Scoin")){
                QImage image(":/img/GameCard/Scoin.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("FUNCARD")){
                QImage image(":/img/GameCard/Funcard.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("Gosu")){
                QImage image(":/img/GameCard/GOSU.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_BuyCard).at(i).contains("KUL")){
                QImage image(":/img/GameCard/KulCard.png");
                home_network[i]->setPixmap(QPixmap::fromImage(image));
            }

            if(i%4 == 0){
                row++;
            }
            GridGameCard->addWidget(home_network[i], row, i%4);
            //HBox_homeNetwork->addWidget(home_network[i]);
            connect(home_network[i], SIGNAL(home_network(QString)),this, SLOT(select_home_network(QString)));

        }
        homeNetworkGroup->setLayout(GridGameCard);
        //homeNetworkGroup->setMaximumSize(1080,900);
    }
    if(Industry_BuyCard != "Mua thẻ Game")
        homeNetworkGroup->setLayout(HBox_homeNetwork);


    QGroupBox *PriceGroup = new QGroupBox(tr("Chọn mệnh giá"));
    PriceGroup->setStyleSheet("QGroupBox { color : green; }");
    PriceGroup->setFont(font);
   // PriceGroup->setMinimumSize(1080,400);
   // QHBoxLayout *HBox_Price = new QHBoxLayout;
    grid = new QGridLayout();
    qint8 row = 0;
    for(int i = 0; i < m_db.GetListGoodPrice(Industry_BuyCard,m_db.GetListGoodType(Industry_BuyCard).at(0)).size(); i++){
            price[i] = new my_qlabel(m_db.GetListGoodPrice(Industry_BuyCard,m_db.GetListGoodType(Industry_BuyCard).at(0)).at(i), i);
          //  price[i]->setFrameShape(QFrame::Box);
           // price[i]->setScaledContents(true);
            price[i]->setWordWrap(true);
           // price[i]->adjustSize();

            if(i%3 == 0){
                row++;
            }
            grid->addWidget(price[i], row, i%3);
            price[i]->setText(QString::number(m_db.GetListGoodPrice(Industry_BuyCard,m_db.GetListGoodType(Industry_BuyCard).at(0)).at(i)));
            price[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
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
    //Message->setText("Xin mời chọn nhà mạng!");

    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Ok = new PushButton_OK_BACK("OK",this);
    btn_Back = new PushButton_OK_BACK("Back", this);

    HBox_Ok_Back->addWidget(btn_Back);
    HBox_Ok_Back->addWidget(btn_Ok);
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_BuyCard_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_BuyCard_clicked()));
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
   // mainLayout->addWidget(NumberPhoneGroup);
    mainLayout->addWidget(PriceGroup);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
}

buy_card::~buy_card()
{
    delete ui;
}

QString buy_card::HomeNetwork_BuyCard()
{
    return HomeNetwork;
}

quint32 buy_card::Price_BuyCard()
{
    return Price;
}

void buy_card::select_home_network(QString select)
{
    LOG<<select<<"chọn nhà mạng";
    for (int i = 0; i < grid->count(); i++)
    {
       grid->itemAt(i)->widget()->deleteLater();
    }
    for(int i = 0; i < m_db.GetListGoodType(Industry_BuyCard).size(); i++){
        if(select == m_db.GetListGoodType(Industry_BuyCard).at(i)){
//            LOG<<select<<m_db.GetListGoodType(Industry_BuyCard).at(i)<<"hjhjhj"<<i;
//            home_network[i]->setScaledContents(true);
//            home_network[i]->setFrameStyle(QFrame::Box);
            home_network[i]->setStyleSheet ("QFrame {border: 6px solid red;}");
           // home_network[i]->setLineWidth(5);
        }else{
//            home_network[i]->setScaledContents(true);
//            home_network[i]->setFrameStyle(QFrame::Box);
            home_network[i]->setStyleSheet ("QFrame {border: 1px solid black;}");
           // home_network[i]->setLineWidth(1);
        }
    }
    if(Message->text().contains("Chọn nhà mạng!")){
        Message->setText("");
    }
    HomeNetwork = select;

   // grid->removeWidget()
    QFont font("Arial",26);
    qint8 row = 0;
    LOG<<m_db.GetListGoodPrice(Industry_BuyCard,HomeNetwork).size()<<"số lượng giá";
    for(int i = 0; i < m_db.GetListGoodPrice(Industry_BuyCard,HomeNetwork).size(); i++){
            price[i] = new my_qlabel(m_db.GetListGoodPrice(Industry_BuyCard,HomeNetwork).at(i), i);
          //  price[i]->setFrameShape(QFrame::Box);
           // price[i]->setScaledContents(true);
            price[i]->setWordWrap(true);
           // price[i]->adjustSize();

            if(i%3 == 0){
                row++;
            }
            grid->addWidget(price[i], row, i%3);
            price[i]->setText(QString::number(m_db.GetListGoodPrice(Industry_BuyCard,HomeNetwork).at(i)));
            price[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
            price[i]->setAlignment(Qt::AlignCenter);
            price[i]->setFont(font);
           // HBox_Price->addWidget(price[i]);
            connect(price[i], SIGNAL(price(quint32,quint8)),this, SLOT(select_price(quint32,quint8)));
            //connect(price[i], SIGNAL(clicked(QString)),this, SLOT(select_price(QString,m_db.GetListGoodPrice("Nạp tiền điện thoại trả trước","Nạp tiền trả trước Vina").at(i), i)));
    }
    Price = 0;
}

void buy_card::select_price(quint32 _price, quint8 index)
{
    if(HomeNetwork != ""){
        for(int i = 0; i < m_db.GetListGoodPrice(Industry_BuyCard,HomeNetwork).size(); i++){
            if(index == i){
                price[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: red;color: blue;}");
            }else{
                price[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
            }
        }
      //  price[index]->setStyleSheet("QLabel { background-color : red; color : blue; }");
        if(Message->text().contains("Chọn mệnh giá nạp tiền!")){
            Message->setText("");
        }
    //    LOG<<_price<<"chọn giá";
        Price = _price;
        if(Message->text().contains("Chọn mệnh giá thẻ!")){
            Message->setText("");
        }
    }else{
        Message->setText("Chọn nhà mạng!");
    }
}

void buy_card::Back_Home(QString)
{
    emit Signal_BuyCard(MENU);
}

void buy_card::on_Btn_Ok_BuyCard_clicked()
{
    if(HomeNetwork == ""){
        Message->setText("Chọn nhà mạng!");
    }else if(Price == 0){
        Message->setText("Chọn mệnh giá thẻ!");
    }else{
        Message->setText("");
        emit Signal_BuyCard(SELECT_CHARGE_TYPE);
    }
}

void buy_card::on_Btn_Back_BuyCard_clicked()
{
    emit Signal_BuyCard(SELECT_SERVICE);
}


#include "postpaid.h"
#include "ui_postpaid.h"

Postpaid::Postpaid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Postpaid)
{
    ui->setupUi(this);
}

Postpaid::Postpaid(Machine *m)
{
    LOG<<"khởi tạo màn hình thanh toán hóa đơn";
    ui->setupUi(this);
    Industry_Postpaid = m->transaction()->Industry;
    post_paid = "";
    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
   // Image_Sab->setGeometry(0,0,1200,660);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

    QLabel* Title = new QLabel(this);
    Title->setText(Industry_Postpaid);
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
    homeNetworkGroup->setFont(font);

    QHBoxLayout *HBox_homeNetwork = new QHBoxLayout;
    QGroupBox *NumberPhoneGroup = new QGroupBox(tr("Số điện thoại"));
    NumberPhoneGroup->setStyleSheet("QGroupBox { color : green; }");
    NumberPhoneGroup->setFont(font);
   // NumberPhoneGroup->setMinimumSize(1080,200);

    QGroupBox *OrderGroup = new QGroupBox(tr("Số tiền thanh toán"));
    OrderGroup->setStyleSheet("QGroupBox { color : green; }");
    OrderGroup->setFont(font);
  //  OrderGroup->setMinimumSize(1080,200);

    if(Industry_Postpaid == "Nạp tiền điện thoại trả sau"){
        for(int i = 0; i < m_db.GetListGoodType(Industry_Postpaid).size(); i++){
            postpaid[i] = new my_qlabel(m_db.GetListGoodType(Industry_Postpaid).at(i),this);
            postpaid[i]->setScaledContents(true);
            postpaid[i]->setStyleSheet ("QFrame {border: 1px solid black;}");
//            postpaid[i]->setFrameStyle(QFrame::Box);
//            postpaid[i]->setLineWidth(1);
            if(m_db.GetListGoodType(Industry_Postpaid).at(i).contains("Vina")){
                QImage image(":/img/HomeNetwork/Vina.png");
                postpaid[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_Postpaid).at(i).contains("Mobifone")){
                QImage image(":/img/HomeNetwork/Mobifone.png");
                postpaid[i]->setPixmap(QPixmap::fromImage(image));
            }else if(m_db.GetListGoodType(Industry_Postpaid).at(i).contains("Viettel")){
                QImage image(":/img/HomeNetwork/Viettel.png");
                postpaid[i]->setPixmap(QPixmap::fromImage(image));
            }

            HBox_homeNetwork->addWidget(postpaid[i]);
            connect(postpaid[i], SIGNAL(home_network(QString)),this, SLOT(select_Partner(QString)));

        }
        homeNetworkGroup->setLayout(HBox_homeNetwork);

        QHBoxLayout *HBox_Number_Phone = new QHBoxLayout;
        QLabel *NumberPhoneLabel = new QLabel(tr("SĐT:"));
        NumberPhoneLabel->setFont(font);
        lineEdit_Number_Phone = new QLineEdit(this);
        lineEdit_Number_Phone->setInputMethodHints(Qt::ImhPreferNumbers);
       // lineEdit_Number_Phone->setValidator(new QDoubleValidator(0,9999999999,0,this));
        QFont font22("Arial",28);
        lineEdit_Number_Phone->setFont(font22);
        lineEdit_Number_Phone->setMaximumSize(500,60);
        lineEdit_Number_Phone->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 10px");
        lineEdit_Number_Phone->setFocus();
        HBox_Number_Phone->addSpacing(150);
        HBox_Number_Phone->addWidget(NumberPhoneLabel);
        HBox_Number_Phone->addSpacing(60);
        HBox_Number_Phone->addWidget(lineEdit_Number_Phone);
        HBox_Number_Phone->addSpacing(265);
        NumberPhoneGroup->setLayout(HBox_Number_Phone);
        NumberPhoneGroup->setMaximumHeight(220);


        QHBoxLayout *HBox_Order = new QHBoxLayout;
        QLabel *OrderLabel = new QLabel(tr("Số tiền:"));
        OrderLabel->setFont(font);
        QLabel *VNDLabel = new QLabel(tr("VND"));
        VNDLabel->setFont(font);
        lineEdit_Price = new QLineEdit(this);
       // lineEdit_Price->setValidator(new QDoubleValidator(0,9999999999,0,this));

        lineEdit_Price->setFont(font22);
        lineEdit_Price->setMaximumSize(500,60);
        lineEdit_Price->setInputMethodHints(Qt::ImhPreferNumbers);
        lineEdit_Price->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 10px");
        //connect(lineEdit_Price, SIGNAL(textChanged()), this, SLOT(LineEdit_Price_VND()));
        connect(lineEdit_Price, &QLineEdit::textChanged, this, &Postpaid::LineEdit_Price_VND);
        HBox_Order->addSpacing(150);
        HBox_Order->addWidget(OrderLabel);
        HBox_Order->addWidget(lineEdit_Price);
        HBox_Order->addWidget(VNDLabel);
        HBox_Order->addSpacing(150);
        OrderGroup->setLayout(HBox_Order);
        OrderGroup->setMaximumHeight(220);
    }

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
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_Postpaid_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_Postpaid_clicked()));
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
    mainLayout->addWidget(OrderGroup);

    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
}

Postpaid::~Postpaid()
{
    delete ui;
}

QString Postpaid::Partner_Postpaid()
{
    return post_paid;
}

quint32 Postpaid::Price_Postpaid()
{
    QString price = lineEdit_Price->text().remove(",");
    return price.toDouble();
}

QString Postpaid::NumberPhone_Postpaid()
{
    return  lineEdit_Number_Phone->text();
}

void Postpaid::select_Partner(QString select)
{
    for(int i = 0; i < m_db.GetListGoodType(Industry_Postpaid).size(); i++){
        if(select == m_db.GetListGoodType(Industry_Postpaid).at(i)){
         //   postpaid[i]->setScaledContents(true);
          //  postpaid[i]->setFrameStyle(QFrame::Box);
            postpaid[i]->setStyleSheet ("QFrame {border: 6px solid red;}");
            //postpaid[i]->setLineWidth(5);
        }else{
          //  postpaid[i]->setScaledContents(true);
           // postpaid[i]->setFrameStyle(QFrame::Box);
            postpaid[i]->setStyleSheet ("QFrame {border: 1px solid black;}");
            //postpaid[i]->setLineWidth(1);
        }
    }
    if(Message->text().contains("Chọn dịch vụ!")){
        Message->setText("");
    }
    post_paid = select;
}

void Postpaid::Back_Home(QString)
{
    emit Signal_Postpaid(MENU);
}

void Postpaid::on_Btn_Ok_Postpaid_clicked()
{
    bool ok = false;
    quint32 price = lineEdit_Price->text().remove(',').toInt(&ok);
    if(post_paid == ""){
        if(Industry_Postpaid == "Nạp tiền điện thoại trả sau")
            Message->setText("Chọn dịch vụ!");
    }else if(lineEdit_Number_Phone->text().length() >= 11 || lineEdit_Number_Phone->text().length() <= 9){
        if(Industry_Postpaid == "Nạp tiền điện thoại trả sau")
            Message->setText("Kiểm tra lại số điện thoại!");
    }else if(lineEdit_Price->text() == ""){
        if(Industry_Postpaid == "Nạp tiền điện thoại trả sau")
            Message->setText("Nhập số tiền thanh toán!");
    }else if(lineEdit_Price->text().startsWith("0") || !ok){
        if(Industry_Postpaid == "Nạp tiền điện thoại trả sau")
            Message->setText("Nhập số tiền thanh toán không hợp lệ, mời nhập lại!");
    }
    else{
        Message->setText("");
        emit Signal_Postpaid(SELECT_CHARGE_TYPE);
    }
}

void Postpaid::on_Btn_Back_Postpaid_clicked()
{
    emit Signal_Postpaid(SELECT_SERVICE);
}

void Postpaid::LineEdit_Price_VND()
{
    QString text = lineEdit_Price->text();

    if(text.length() == 4){
        if(text.startsWith(",")){
            text.remove(",");
        }else
            text.insert(1, ",");
    }else if(text.length() > 4 && text.length() < 8){
        text.remove(",");
        text.insert(text.length() - 3,",");
    }else if(text.length() >= 8 && text.length() <= 10){
        text.remove(",");

        text.insert(text.length() - 3,",");
        if(text.length() > 7)
            text.insert(text.length() - 7,",");
    }else if(text.length() > 10){
        text = text.left(10);
    }
    lineEdit_Price->setText(text);

}

#include "billinfo.h"
#include "ui_billinfo.h"

BillInfo::BillInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillInfo)
{
    ui->setupUi(this);
}

BillInfo::BillInfo(Machine* m, QString Bill_Info)
{
    LOG;
    MesBillInfo = Bill_Info;
    _SelectBillIndex = -1;

    QJsonDocument doc = QJsonDocument::fromJson(MesBillInfo.toUtf8());
    QJsonObject obj = doc.object();
    QJsonObject customer = obj["customer"].toObject();
    QJsonArray BillArray = obj["bills"].toArray();
    BillQuatity = BillArray.size();


    QVBoxLayout *mainLayout = new QVBoxLayout;
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


    QGroupBox* gridGroupBox = new QGroupBox(tr("Thông tin hóa đơn"));
    QFont font("Arial",32);
   // gridGroupBox->setStyleSheet("QGroupBox { color : green; }");
    gridGroupBox->setFont(font);
    //gridGroupBox->setMinimumSize(1080,760);
    QGridLayout *grid = new QGridLayout();
    qint8 row = 0;
    for(int i = 0; i < BillArray.size(); i++){
        QJsonObject BillObject = BillArray[i].toObject();
        billInfo[i] = new my_qlabel(BillObject["amount"].toString().toInt(),i);
        if(i%2 == 0){
            row++;
        }
        grid->addWidget(billInfo[i], row, i%2);
        billInfo[i]->setFrameShape(QFrame::Box);
        billInfo[i]->setWordWrap(true);
        billInfo[i]->setScaledContents(true);
        billInfo[i]->setAlignment(Qt::AlignLeft);
        billInfo[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 25px; background: gray;color: blue;}");
        if(BillArray.size() == 1){
            QFont fontBillInfo("Times",32);
            fontBillInfo. setBold(true);
            billInfo[i]->setFont(fontBillInfo);
        }else if(BillArray.size() == 2){
            QFont fontBillInfo("Times",24);
            fontBillInfo. setBold(true);
            billInfo[i]->setFont(fontBillInfo);
        }else{
            QFont fontBillInfo("Times",20);
            fontBillInfo. setBold(true);
            billInfo[i]->setFont(fontBillInfo);
        }
        billInfo[i]->setText(m->transaction()->GoodName + "\n-Tên KH: " + customer["customer_name"].toString()
                + "\n-Địa chỉ: " + customer["customer_address"].toString() + "\n-Số hóa đơn: " + BillObject["bill_number"].toString()
                + "\n-Kì hóa đơn: " + BillObject["period"].toString()
                + "\n-Số tiền: " + StringUtils::formatNumberVND(BillObject["amount"].toString().toInt()) +" VND"
                + "\n-Phí dịch vụ: "  + StringUtils::formatNumberVND(BillObject["amount_and_fee"].toString().toInt() - BillObject["amount"].toString().toInt()) +" VND"
                + "\n-Tổng số tiền: " + StringUtils::formatNumberVND(BillObject["amount_and_fee"].toString().toInt()) +" VND");
        connect(billInfo[i], SIGNAL(price(quint32,quint8)),this, SLOT(SelectBill_Info(quint32,quint8)));

    }

    gridGroupBox->setLayout(grid);

    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setMaximumSize(1080, 140);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(5);
    QFont font1("Times",30);
    Message->setFont(font1);
    if(BillArray.size() != 1){
        Message->setText("Chọn hóa đơn muốn thanh toán!");
    }else{
        Message->setText("Bấm OK để thanh toán hóa đơn!");
    }


    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Ok = new PushButton_OK_BACK("OK",this);
    btn_Back = new PushButton_OK_BACK("Back", this);
    HBox_Ok_Back->addWidget(btn_Back);
    HBox_Ok_Back->addWidget(btn_Ok);
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_Bill_Info_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_Bill_Info_clicked()));
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
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);

    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
}

BillInfo::~BillInfo()
{
    delete ui;
}

void BillInfo::SelectBill_Info(quint32, quint8 index)
{
    for(int i = 0; i < BillQuatity; i++){
        if(index == i){
            billInfo[i]->setStyleSheet("QLabel { background-color : red; color : blue; }");
        }else{
            billInfo[i]->setStyleSheet("QLabel { background-color : gray; color : blue; }");
        }
    }
    billInfo[index]->setStyleSheet("QLabel { background-color : red; color : blue; }");
    Message->setText("");
    _SelectBillIndex = index;
   // emit Signal_Bill_Info(MACHINE_STATE::SELECT_CHARGE_TYPE);
}

void BillInfo::on_Btn_Ok_Bill_Info_clicked()
{
    if(BillQuatity == 1){
        _SelectBillIndex = 0;
    }
    if(_SelectBillIndex != -1){
        Message->setText("");
        emit Signal_Bill_Info(MACHINE_STATE::SELECT_CHARGE_TYPE);
    }else{
        Message->setText("Chọn hóa đơn muốn thanh toán!");
    }
}

void BillInfo::on_Btn_Back_Bill_Info_clicked()
{
    emit Signal_Bill_Info(MACHINE_STATE::TOPUPPARTNER);
}

int BillInfo::SelectBillIndex()
{
    return _SelectBillIndex;
}

void BillInfo::Back_Home(QString)
{
    emit Signal_Bill_Info(MACHINE_STATE::MENU);
}

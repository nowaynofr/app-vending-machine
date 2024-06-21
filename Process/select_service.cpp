#include "select_service.h"
#include "ui_select_service.h"

select_service::select_service(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::select_service)
{
    ui->setupUi(this);
}

select_service::select_service(QList<QString> list_service):
    ui(new Ui::select_service)

{
    LOG;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setMaximumHeight(550);
    Image_Sab->setFrameShape(QFrame::Box);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

    QGroupBox* gridGroupBox = new QGroupBox(tr("Danh sách dịch vụ"));
    QFont font("Arial",32);
    gridGroupBox->setFont(font);
    gridGroupBox->setMinimumSize(1010,1080);
    QGridLayout *grid = new QGridLayout();
    qint8 row = 0;
    for(int i = 0; i < list_service.size(); i++){

        LOG<<list_service.at(i)<<"jijijij";
        service[i] = new my_qlabel(list_service.at(i),this);
        if(i%3 == 0){
            row++;
        }
        grid->addWidget(service[i], row, i%3);
        service[i]->setScaledContents(true);
      //  service[i]->setFrameShape(QFrame::Box);
        if(list_service.at(i) == "Nạp tiền điện thoại trả trước"){
         //   QImage image(":/img/topup-telco.png");
         //   service[i]->setPixmap(QPixmap::fromImage(image));
            service[i]->setStyleSheet("QLabel { border-image : url(:/img/topup-telco.png); color : red;border: 3px solid black; border-radius: 30px }");
        }else if(list_service.at(i) == "Mua thẻ điện thoại"){
            service[i]->setStyleSheet("QLabel { border-image : url(:/img/buycard.png); color : red;border: 3px solid black; border-radius: 30px }");
//            QImage image(":/img/buycard.png");
//            service[i]->setPixmap(QPixmap::fromImage(image));
        }else if(list_service.at(i) == "Mua thẻ Data 3G"){
            service[i]->setStyleSheet("QLabel { border-image : url(:/img/data3g.png); color : red;border: 3px solid black; border-radius: 30px }");
//            QImage image(":/img/data3g.png");
//            service[i]->setPixmap(QPixmap::fromImage(image));
        }else if(list_service.at(i) == "Mua thẻ Game"){
            service[i]->setStyleSheet("QLabel { border-image : url(:/img/gamecard.png); color : red;border: 3px solid black; border-radius: 30px }");
//            QImage image(":/img/gamecard.png");
//            service[i]->setPixmap(QPixmap::fromImage(image));
        }else if(list_service.at(i) == "Nạp tiền điện thoại trả sau"){
            service[i]->setStyleSheet("QLabel { border-image : url(:/img/postpaid.png); color : red;border: 3px solid black; border-radius: 30px }");
//            QImage image(":/img/postpaid.png");
//            service[i]->setPixmap(QPixmap::fromImage(image));
        }else if(list_service.at(i).contains("tiền điện",Qt::CaseInsensitive)){
            service[i]->setStyleSheet("QLabel { border-image : url(:/img/electric.png); color : red;border: 3px solid black; border-radius: 30px }");
//            QImage image(":/img/electric.png");
//            service[i]->setPixmap(QPixmap::fromImage(image));
        }else if(list_service.at(i).contains("tiền nước",Qt::CaseInsensitive)){
            service[i]->setStyleSheet("QLabel { border-image : url(:/img/water.png); color : red;border: 3px solid black; border-radius: 30px }");
//            QImage image(":/img/water.png");
//            service[i]->setPixmap(QPixmap::fromImage(image));
        }else if(list_service.at(i).contains("Bảo hiểm",Qt::CaseInsensitive)){
            service[i]->setStyleSheet("QLabel { border-image : url(:/img/motorinsurance.png); color : red;border: 3px solid black; border-radius: 30px }");
//            QImage image(":/img/water.png");
//            service[i]->setPixmap(QPixmap::fromImage(image));
        }

        connect(service[i], SIGNAL(home_network(QString)),this, SLOT(SelectService(QString)));

    }


  //  QLabel* Image_Promotion = new QLabel("",this);
  //  Image_Promotion->setFrameStyle(QFrame::Box | QFrame::Sunken);
 //   Image_Promotion->setLineWidth(2);
    gridGroupBox->setLayout(grid);
    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Back = new PushButton_OK_BACK("Back", this);
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_SelectService_clicked()));
   // btn_Back->setGeometry(400,1700,300,90);
    HBox_Ok_Back->addWidget(btn_Back);
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

    QLabel* home = new my_qlabel("",this);
    home->setAlignment(Qt::AlignCenter);
    home->setGeometry(960,450,110,110);
    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
    QImage img(":/img/Button_Image/Home_Btn.jpg");
    home->setPixmap(QPixmap::fromImage(img));
    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(gridGroupBox);
   // mainLayout->addWidget(Image_Promotion);
    mainLayout->addWidget(Gr_Ok_Back);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");

    setLayout(mainLayout);

}

select_service::~select_service()
{
    delete ui;
}

void select_service::Back_Home(QString)
{
    emit Signal_Select_Service("back_select_service");
}

void select_service::SelectService(QString service)
{
    emit Signal_Select_Service(service);
}

void select_service::on_Btn_Back_SelectService_clicked()
{
    LOG<<"ghghghg";
    emit Signal_Select_Service("back_select_service");
}



#include "admin_process.h"
#include "ui_admin_process.h"

admin_process::admin_process(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_process)
{
    ui->setupUi(this);
}

admin_process::admin_process(Machine *m, QString list_admin_funtion)
{
    s_machine = m;
    ListSelect.clear();
    if(list_admin_funtion == "all"){
        ListSelect.insert(ADMINFUNTIONLIST::SYNC,"Đồng bộ quy cách với VMS");
        ListSelect.insert(ADMINFUNTIONLIST::SETTING_QUATITY,"Cài đặt số lượng sản phẩm");
        ListSelect.insert(ADMINFUNTIONLIST::SALE,"Chốt doanh thu và dữ liệu");
        ListSelect.insert(ADMINFUNTIONLIST::CHECKING_MACHINE,"Kiểm tra máy");
      //  ListSelect.insert(ADMINFUNTIONLIST::SETTING_SYSTEM,"Cài đặt hệ thống");
       // ListSelect.insert(ADMINFUNTIONLIST::CHECKING_MACHINE,"Kiểm tra máy");
    }else{
        QList<QString> list;
        list = list_admin_funtion.split(",");
        if(list.contains(QString::number(ADMINFUNTIONLIST::SYNC))){
            ListSelect.insert(ADMINFUNTIONLIST::SYNC,"Đồng bộ quy cách với VMS");
        }else{
            ListSelect.insert(ADMINFUNTIONLIST::SYNC,"null");
        }
        if(list.contains(QString::number(ADMINFUNTIONLIST::SETTING_QUATITY))){
            ListSelect.insert(ADMINFUNTIONLIST::SETTING_QUATITY,"Cài đặt số lượng sản phẩm");
        }else{
            ListSelect.insert(ADMINFUNTIONLIST::SETTING_QUATITY,"null");
        }
        if(list.contains(QString::number(ADMINFUNTIONLIST::SALE))){
            ListSelect.insert(ADMINFUNTIONLIST::SALE,"Chốt doanh thu và dữ liệu");
        }else{
            ListSelect.insert(ADMINFUNTIONLIST::SALE,"null");
        }
        if(list.contains(QString::number(ADMINFUNTIONLIST::CHECKING_MACHINE))){
            ListSelect.insert(ADMINFUNTIONLIST::CHECKING_MACHINE,"Kiểm tra máy");
        }else{
            ListSelect.insert(ADMINFUNTIONLIST::CHECKING_MACHINE,"null");
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout;
//    QLabel* Image_Sab = new QLabel(this);
//    Image_Sab->setFrameShape(QFrame::Box);
//    QPixmap pix(":/img/S&B.png");
//    Image_Sab->setPixmap(pix);

    QLabel* Title = new QLabel(this);
    Title->setText("Cài đặt hệ thống");
    Title->setMaximumSize(1080, 110);
    QFont fontTitle("Nyala",32);
    Title->setFont(fontTitle);
    Title->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    Title->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Title->setLineWidth(2);
    Title->setAlignment(Qt::AlignCenter);

    QFont font1("Times",26);
    QGroupBox *Gr_PushButton = new QGroupBox(tr(""));
    QVBoxLayout *HBox_PushButton = new QVBoxLayout;

    for(int i = 0; i < ListSelect.size(); i++){
        if(ListSelect.at(i) != "null"){
            Select[i] = new my_qlabel(ListSelect.at(i),this);
            Select[i]->setMinimumSize(900,200);
            Select[i]->setMaximumSize(900,200);
            Select[i]->setText(ListSelect.at(i));
            HBox_PushButton->addWidget(Select[i]);
            connect(Select[i], SIGNAL(home_network(QString)),this, SLOT(ProcessSelect(QString)));
            Select[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
            Select[i]->setFont(font1);
        }
    }
    HBox_PushButton->setAlignment(Qt::AlignCenter);
    Gr_PushButton->setLayout(HBox_PushButton);

//    Message = new QLabel("",this);
//    Message->setWordWrap(true);
//    Message->setMinimumSize(1080, 500);
//    Message->setMaximumSize(1080, 500);
//    Message->setStyleSheet("QLabel { background-color : gray; color : red; }");
//    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
//    Message->setLineWidth(5);
//    Message->setFont(font1);



    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
  //  btn_Ok = new PushButton_OK_BACK("OK",this);
    btn_Back = new PushButton_OK_BACK("Back", this);

    HBox_Ok_Back->addWidget(btn_Back,Qt::AlignCenter);
    HBox_Ok_Back->setAlignment(Qt::AlignCenter);
  //  HBox_Ok_Back->addWidget(btn_Ok);
  //  connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_Admin_Process_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_Admin_Process_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

   // mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(Title);
    mainLayout->addWidget(Gr_PushButton);
   // mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);

    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;}");
}

admin_process::~admin_process()
{
    delete ui;
}

void admin_process::ProcessAdminSuccess()
{

}

void admin_process::ProcessAdminFail()
{

}

void admin_process::GetSaleInfo(QString saleInfo)
{

}

QString admin_process::GetSelected()
{
   // return Selected;
}

void admin_process::ProcessSelect(QString select)
{
    s_machine->AdminType = ListSelect.indexOf(select);
    emit Signal_Admin_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
}

void admin_process::on_Btn_Ok_Admin_Process_clicked()
{
}

void admin_process::on_Btn_Back_Admin_Process_clicked()
{
    emit Signal_Admin_Process(MACHINE_STATE::MENU);
}

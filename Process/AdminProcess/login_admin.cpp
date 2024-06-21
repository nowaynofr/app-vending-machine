#include "login_admin.h"
#include "ui_login_admin.h"

login_admin::login_admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_admin)
{
    ui->setupUi(this); 
}

login_admin::login_admin(QString)
{
    //AdminPass = "";
//    QInputMethod *input = QApplication::inputMethod();
//    input->show();
    IsCheckWaitResponseVMS = false;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

    QFont font("Arial",30);
    QFont font22("Arial",24);
    QGroupBox *PassGroup = new QGroupBox(tr("Nhập tài khoản Coupon"));
    PassGroup->setFont(font);

    QVBoxLayout *VBox_user = new QVBoxLayout;

    lineEdit_User = new QLineEdit(this);
    lineEdit_User->setFont(font22);
    lineEdit_User->setMaximumSize(500,125);
    lineEdit_User->setMinimumSize(500,125);
    lineEdit_User->setInputMethodHints(Qt::ImhPreferNumbers);
    lineEdit_User->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 10px");
    lineEdit_User->setPlaceholderText("Nhập mã Coupon");
    lineEdit_User->setFocus();


    lineEdit_Pass = new QLineEdit(this);
    lineEdit_Pass->setFont(font22);
    lineEdit_Pass->setMaximumSize(500,125);
    lineEdit_Pass->setMinimumSize(500,125);
    lineEdit_Pass->setInputMethodHints(Qt::ImhPreferNumbers);
    lineEdit_Pass->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 10px");
    lineEdit_Pass->setPlaceholderText("Nhập mã Pin");
    lineEdit_Pass->setEchoMode(QLineEdit::Password);

    VBox_user->addWidget(lineEdit_User);
    VBox_user->addWidget(lineEdit_Pass);
    VBox_user->setAlignment(Qt::AlignCenter);

    PassGroup->setLayout(VBox_user);
    PassGroup->setAlignment(Qt::AlignCenter);
  //  PassGroup->setMaximumHeight(350);

    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    Ok_login = new PushButton_OK_BACK("Đăng nhập",this);
    Back = new PushButton_OK_BACK("Quay lại", this);
   // HBox_Ok_Back->addWidget(Ok_login);
    HBox_Ok_Back->addWidget(Back);
    HBox_Ok_Back->addWidget(Ok_login);
    connect(Ok_login, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_login_clicked()));
    connect(Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_login_clicked()));
    Gr_Ok_Back->setMaximumHeight(200);

    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setMaximumSize(1080, 100);
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);
    QFont font2("Times",32);
    Message->setFont(font2);
    Message->setAlignment(Qt::AlignCenter);

    lb_Promotion = new QLabel(this);
    lb_Promotion->setFrameStyle(QFrame::Box);
    lb_Promotion->setMaximumSize(1080,400);
    lb_Promotion->setStyleSheet("background-color: orange");

    Gr_Ok_Back->setLayout(HBox_Ok_Back);
    mainLayout->addWidget(Image_Sab);
    //mainLayout->addWidget(UserGroup);
    mainLayout->addWidget(PassGroup);
    mainLayout->addWidget(Gr_Ok_Back);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(lb_Promotion);
  //  mainLayout->addWidget(Message);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
    //this->setStyleSheet("background-color: orange");
    setLayout(mainLayout);
}

login_admin::~login_admin()
{
    delete ui;
}

void login_admin::SetIsCheckWaitResponseVMSToFail()
{
    IsCheckWaitResponseVMS = false;
}

//void login_admin::SetAdminPass(QString pass)
//{
//   // AdminPass = pass;
//}

void login_admin::LoginAdminFail(QString mes)
{
    IsCheckWaitResponseVMS = false;
    Message->setText(mes);
}

void login_admin::on_Btn_Ok_login_clicked()
{
    if(!IsCheckWaitResponseVMS){
        if(lineEdit_User->text().isEmpty()){
            Message->setText("Nhập mã Coupon");
        }else if(lineEdit_Pass->text().isEmpty()){
            Message->setText("Nhập mã Pin");
        }else{
            IsCheckWaitResponseVMS = true;
            Message->setText("Đang kiểm tra thông tin ...");
            emit Signal_Admin_Login(lineEdit_User->text(), lineEdit_Pass->text());
        }
    }
}

void login_admin::on_Btn_Back_login_clicked()
{

    emit Signal_Admin_Login("back","");
}

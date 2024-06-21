#include "motor_insurance.h"
#include "ui_motor_insurance.h"

motor_insurance::motor_insurance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::motor_insurance)
{
    ui->setupUi(this);
}

motor_insurance::motor_insurance(Machine *m)
{
    LOG<<"Khơi tạo mạn hình mua bao hiem ";
    s_machine = m;
    OwnerAddress =OwnerBirth = OwnerId = OwnerMail = OwnerName = OwnerPhoneNumber = "";
    LicensePlate = DurationOfInsurance = MotorType = "";
    //InsurancePrice = 66000;
    QVBoxLayout *mainLayout = new QVBoxLayout;
//    QLabel* Image_Sab = new QLabel(this);
//    Image_Sab->setFrameShape(QFrame::Box);
//    QPixmap pix(":/img/S&B.png");
//    Image_Sab->setPixmap(pix);

    QLabel* Title = new QLabel(this);
    Title->setText(m->transaction()->Industry);
    Title->setMaximumSize(1080, 110);
    QFont fontTitle("Nyala",32);
    Title->setFont(fontTitle);
    Title->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    Title->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Title->setLineWidth(2);
    Title->setAlignment(Qt::AlignCenter);

    QVBoxLayout *line_edit = new QVBoxLayout;
    QFont font22("Arial",24);

    name = new my_qlineedit(":/img/Button_Image/Home_Btn.jpg","Tên chủ xe",this);
    phone_number = new my_qlineedit(":/img/Button_Image/Home_Btn.jpg","Số điện thoại chủ xe",this);
    address = new my_qlineedit(":/img/Button_Image/Home_Btn.jpg","Địa chỉ chủ xe",this);
    email = new my_qlineedit(":/img/Button_Image/Home_Btn.jpg","Email chủ xe",this);
    id = new my_qlineedit(":/img/Button_Image/Home_Btn.jpg","CMT/CCCD chủ xe",this);
    license_plate = new my_qlineedit(":/img/Button_Image/Home_Btn.jpg","Biển số xe. Ví dụ: 29S1-85646",this);
    birth = new QDateEdit(this);
    birth->setDisplayFormat("dd/MM/yyyy");
    //birth->setCalendarPopup(true);
    birth->setFont(font22);
    birth->setStyleSheet("color: black; background-color: yellow");
    birth->setMaximumSize(840,130);
    birth->setMinimumSize(820,130);
    duration = new QComboBox(this);
    duration->setFont(font22);
    duration->setStyleSheet("color: black; background-color: yellow");
    duration->addItem("Thời hạn");
    duration->addItem("Bảo hiểm xe máy 1 năm");
    duration->addItem("Bảo hiểm xe máy 2 năm");
    duration->addItem("Bảo hiểm xe máy 3 năm");
    duration->setMaximumSize(840,130);
    duration->setMinimumSize(840,130);
    duration->setCurrentIndex(0);
    connect(duration,SIGNAL(currentIndexChanged(int)), this, SLOT(PriceChange(int)));
    QString goodId = s_machine->getGoodId1InMenuTable(s_machine->transaction()->Industry,duration->currentText());
    quint32 InsurancePrice = s_machine->getGoodPriceInMenuTable(goodId);

    price = new QLabel(this);
    price->setText(StringUtils::formatNumberVND(InsurancePrice) + " VND");
    price->setFont(font22);
    price->setMaximumSize(840,130);
    price->setMinimumSize(840,130);
    price->setFrameShape(QFrame::Box);
    price->setStyleSheet("color: black; background-color: yellow");
    motor_type = new QComboBox(this);
    motor_type->addItem("Loại xe");
    motor_type->addItem("Xe trên 50cc");
    motor_type->addItem("Xe dưới 50cc");
    motor_type->addItem("Xe 3 bánh");
    motor_type->setFont(font22);
    motor_type->setMaximumSize(840,130);
    motor_type->setMinimumSize(840,130);
    motor_type->setStyleSheet("color: black; background-color: yellow");

    line_edit->addWidget(name);
    line_edit->addWidget(phone_number);
    line_edit->addWidget(address);
    line_edit->addWidget(email);
    line_edit->addWidget(id);
    line_edit->addWidget(license_plate);
    line_edit->addWidget(birth);
    line_edit->addWidget(duration);
    line_edit->addWidget(price);
    line_edit->addWidget(motor_type);
    line_edit->setAlignment(Qt::AlignCenter);

    QGroupBox *form = new QGroupBox(tr(""));
    form->setLayout(line_edit);
    //form->setAlignment(Qt::AlignCenter);

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
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_MotorInsurance_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_MotorInsurance_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);



    mainLayout->addWidget(Title);
    mainLayout->addWidget(form);
    mainLayout->addWidget(Message);
    mainLayout->addWidget(Gr_Ok_Back);
    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");

    setLayout(mainLayout);

}

motor_insurance::~motor_insurance()
{
    delete ui;
}

QString motor_insurance::GetOwnerOfMotorInfo()
{
    OwnerName = name->GetLineEditContent();
    OwnerAddress = address->GetLineEditContent();
    OwnerBirth = birth->text();
    OwnerId = id->GetLineEditContent();
    OwnerMail = email->GetLineEditContent();
    OwnerPhoneNumber = phone_number->GetLineEditContent();
    LicensePlate = license_plate->GetLineEditContent();
    DurationOfInsurance = duration->currentText();
    MotorType = motor_type->currentText();
    QVariantMap obj;
    obj.insert("name",OwnerName);
    obj.insert("address",OwnerAddress);
    obj.insert("birthday",OwnerBirth);
    obj.insert("cmt",OwnerId);
    obj.insert("email",OwnerMail);
    obj.insert("phoneNumber",OwnerPhoneNumber);
    obj.insert("bienso",LicensePlate);

    if(DurationOfInsurance.contains("1 năm")){
        obj.insert("expiry","1");
    }else if(DurationOfInsurance.contains("2 năm")){
        obj.insert("expiry","2");
    }else if(DurationOfInsurance.contains("3 năm")){
        obj.insert("expiry","3");
    }
    //obj.insert("expiry",DurationOfInsurance);
    if(MotorType.contains("Xe trên 50cc")){
        obj.insert("type","50");
    }else if(MotorType.contains("Xe dưới 50cc")){
        obj.insert("type","0");
    }else if(MotorType.contains("Xe 3 bánh")){
        obj.insert("type","3b");
    }
    //obj.insert("type",MotorType);
   // obj.insert("money",InsurancePrice);

    obj.insert("nameHD",OwnerName);
    obj.insert("addressHD",OwnerAddress);
    obj.insert("birthdayHD",OwnerBirth);
    obj.insert("cmtHD",OwnerId);
    obj.insert("emailHD",OwnerMail);
    obj.insert("phoneNumberHD",OwnerPhoneNumber);

    LOG<<OwnerName<<OwnerBirth<<DurationOfInsurance<<MotorType<<"yyyyy";
    return QJsonDocument(QJsonObject::fromVariantMap(obj)).toJson();


}

QString motor_insurance::getDurationOfInsurance()
{
    return DurationOfInsurance;
}

void motor_insurance::PriceChange(int)
{
    QString goodId = s_machine->getGoodId1InMenuTable(s_machine->transaction()->Industry,duration->currentText());
    quint32 InsurancePrice = s_machine->getGoodPriceInMenuTable(goodId);
    price->setText(StringUtils::formatNumberVND(InsurancePrice) + " VND");

}

void motor_insurance::on_Btn_Ok_MotorInsurance_clicked()
{
    GetOwnerOfMotorInfo();
    if(OwnerName == ""){
        Message->setText("Nhập tên chủ xe!");
    }else if(OwnerPhoneNumber == ""){
        Message->setText("Nhập số điện thoại chủ xe!");
    }else if(OwnerAddress == ""){
        Message->setText("Nhập địa chỉ chủ xe!");
    }else if(OwnerMail == ""){
        Message->setText("Nhập email chủ xe!");
    }else if(OwnerId == ""){
        Message->setText("Nhập CMT/CCCD chủ xe!");
    }else if(LicensePlate == ""){
        Message->setText("Nhập biển số xe!");
    }else if(OwnerBirth == ""){
        Message->setText("Nhập ngày sinh chủ hợp đồng!");
    }else if(DurationOfInsurance == "Thời hạn"){
        Message->setText("Chọn thời hạn bảo hiểm!");
    }/*else if(InsurancePrice == 0){
        Message->setText("Kiểm tra lại số điện thoại!");ư
    }*/
    else if(MotorType == "Loại xe"){
        Message->setText("Chọn loại xe!");
    }else{
        Message->setText("");
        emit Signal_MotorInsurance(SELECT_CHARGE_TYPE);
    }
}

void motor_insurance::on_Btn_Back_MotorInsurance_clicked()
{
    emit Signal_MotorInsurance(SELECT_SERVICE);
}

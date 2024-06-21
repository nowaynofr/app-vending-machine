#include "process_admin_funtion.h"
#include "ui_process_admin_funtion.h"

process_admin_funtion::process_admin_funtion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::process_admin_funtion)
{
    ui->setupUi(this);
}

process_admin_funtion::process_admin_funtion(Machine *m)
{
    s_machine = m;
    IsCheckWaitResponseVMS = false;
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

    if(m->AdminType == ADMINFUNTIONLIST::SYNC){
        Title->setText("Đồng bộ quy cách");
        for(int i = 0; i < 2; i++){
            if(i == 0){
                Select[i] = new my_qlabel("VMStoAPP",this);
                Select[i]->setText("Đồng bộ từ VMS -> Máy bán hàng");
            }else{
                Select[i] = new my_qlabel("APPtoVMS",this);
                Select[i]->setText("Đồng bộ từ Máy bán hàng -> VMS");
            }
            Select[i]->setMaximumSize(900,200);
            Select[i]->setMinimumSize(900,200);
            HBox_PushButton->addWidget(Select[i]);
            connect(Select[i], SIGNAL(home_network(QString)),this, SLOT(ProcessSelect(QString)));
            Select[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
            Select[i]->setFont(font1);
        }
    }else if(m->AdminType == ADMINFUNTIONLIST::SALE){
        Title->setText("Số liệu bán hàng");
        for(int i = 0; i < 4; i++){
            if(i == 0){
                Select[i] = new my_qlabel("DaySale",this);
                Select[i]->setText("Chốt doanh thu ngày");
            }else if(i == 1){
                Select[i] = new my_qlabel("MonthSale",this);
                Select[i]->setText("Chốt doanh thu tháng");
            }else if(i == 2){
                Select[i] = new my_qlabel("ResendSale",this);
                Select[i]->setText("Gửi lại phiên chốt doanh thu");
            }else{
                Select[i] = new my_qlabel("ResendTransaction",this);
                Select[i]->setText("Gửi lại lịch sử giao dịch");
            }
            Select[i]->setMaximumSize(900,200);
            Select[i]->setMinimumSize(900,200);
            HBox_PushButton->addWidget(Select[i]);
            connect(Select[i], SIGNAL(home_network(QString)),this, SLOT(ProcessSelect(QString)));
            Select[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
            Select[i]->setFont(font1);
        }
    }else if(m->AdminType == ADMINFUNTIONLIST::SETTING_QUATITY){
        Title->setText("Cài đặt số lượng");
        for(int i = 0; i < 3; i++){
            if(i == 0){
                Select[i] = new my_qlabel("GeneralSetting",this);
                Select[i]->setText("Cài đặt số lượng chung");
            }else if(i == 1){
                Select[i] = new my_qlabel("KhaySetting",this);
                Select[i]->setText("Cài đặt số lượng theo khay");
            }else{
                Select[i] = new my_qlabel("SlotSetting",this);
                Select[i]->setText("Cài đặt số lượng theo Slot");
            }
            Select[i]->setMaximumSize(900,200);
            Select[i]->setMinimumSize(900,200);
            HBox_PushButton->addWidget(Select[i]);
            connect(Select[i], SIGNAL(home_network(QString)),this, SLOT(ProcessSelect(QString)));
            Select[i]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
            Select[i]->setFont(font1);
        }
    }else if(m->AdminType == ADMINFUNTIONLIST::CHECKING_MACHINE){
        Select[0] = new my_qlabel("ExitApp",this);
        Select[0]->setText("Thoát App");

        Select[0]->setMaximumSize(900,200);
        Select[0]->setMinimumSize(900,200);
        HBox_PushButton->addWidget(Select[0]);
        connect(Select[0], SIGNAL(home_network(QString)),this, SLOT(ProcessSelect(QString)));
        Select[0]->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: blue;}");
        Select[0]->setFont(font1);
    }
    HBox_PushButton->setAlignment(Qt::AlignCenter);
    Gr_PushButton->setLayout(HBox_PushButton);

    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setText("Chọn chức năng!");
    Message->setAlignment(Qt::AlignCenter);
    Message->setMinimumSize(1080, 500);
    Message->setMaximumSize(1080, 500);
    Message->setStyleSheet("QLabel { background-color : gray; color : red; }");
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(5);
    Message->setFont(font1);

    if(m->AdminType == ADMINFUNTIONLIST::SALE){       
        lineEdit_Sale = new QLineEdit(this);
        lineEdit_Sale->setFont(font1);
        lineEdit_Sale->setMaximumSize(1080,125);
        lineEdit_Sale->setMinimumSize(1080,125);
        lineEdit_Sale->setInputMethodHints(Qt::ImhPreferNumbers);
        lineEdit_Sale->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 10px");
        connect(lineEdit_Sale, &QLineEdit::textChanged, this, &process_admin_funtion::Update_LineEdit_Sale);
        lineEdit_Sale->setAlignment(Qt::AlignCenter);
        lineEdit_Sale->setFocus();
    }

    Status = new QLabel("",this);
    Status->setWordWrap(true);
    Status->setMaximumSize(1080, 200);
    Status->setMinimumSize(1080, 200);
    Status->setStyleSheet("QLabel { background-color : white; color : red; }");
    Status->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Status->setLineWidth(2);
    QFont font2("Times",26);
    Status->setFont(font2);


    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
    btn_Ok = new PushButton_OK_BACK("OK",this);
    btn_Back = new PushButton_OK_BACK("Back", this);

    HBox_Ok_Back->addWidget(btn_Back);
    HBox_Ok_Back->addWidget(btn_Ok);
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_Admin_Funtion_Process_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_Admin_Funtion_Process_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

   // mainLayout->addWidget(Image_Sab);
    mainLayout->addWidget(Title);
    mainLayout->addWidget(Gr_PushButton);
    mainLayout->addWidget(Message);
    if(m->AdminType == ADMINFUNTIONLIST::SALE)
        mainLayout->addWidget(lineEdit_Sale,Qt::AlignCenter);
    mainLayout->addWidget(Status);
    mainLayout->addWidget(Gr_Ok_Back);

    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;}");
}

process_admin_funtion::~process_admin_funtion()
{
    delete ui;
}

void process_admin_funtion::SyncInfo(QString text)
{
    IsCheckWaitResponseVMS = false;
    Message->setText("Chọn chức năng!");
    if(text == "disconnect"){
        Status->setText("Máy đang mất kết nối \nVui lòng kiểm tra lại mạng");
    }else if(text == "success"){
        Status->setText("Đồng bộ thông tin thành công!");
    }else if(text == "error"){
        Status->setText("Đồng bộ thông tin thất bại! \nĐang lỗi hệ thống");
    }else{
        Status->setText("Đồng bộ thông tin thất bại! \n" + text);
    }
}

void process_admin_funtion::SaleInfo(QString text)
{
    if(text == "success"){
        Status->setText("Chốt doanh thu thành công");
    }else{
        Status->setText("Chốt doanh thu thất bại");
    }
}

void process_admin_funtion::ReSendSaleStatus(QString text)
{
    IsCheckWaitResponseVMS = false;
    if(text == "disconnect"){
        Status->setText("Máy đang mất kết nối \nVui lòng kiểm tra lại mạng");
    }else if(text == "success"){
        Status->setText("Gửi lại phiên chốt doanh thu thành công!");
    }else{
        Status->setText("Gửi lại phiên chốt doanh thu thất bại!");
    }
}

void process_admin_funtion::UpdateStatus()
{
    Status->setText("");
}

void process_admin_funtion::ProcessSelect(QString select)
{
    Status->setText("");
    if(s_machine->saleSession()->PrePeriod == ""){
        s_machine->saleSession()->PrePeriod = QDate::currentDate().toString("yyyyMM");
    }
    if(select == "VMStoAPP"){
        IsCheckWaitResponseVMS = false;
        if(!IsCheckWaitResponseVMS){
            IsCheckWaitResponseVMS = true;
            s_machine->AdminType = ADMINFUNTIONLIST::SYNC_VMS_TO_APP;
            Message->setText("Đang thực hiện đồng bộ quy cách VMS xuống Máy bán hàng...");
            emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
        }
    }else if(select == "APPtoVMS"){
        IsCheckWaitResponseVMS = false;
        if(!IsCheckWaitResponseVMS){
            IsCheckWaitResponseVMS = true;
            s_machine->AdminType = ADMINFUNTIONLIST::SYNC_APP_TO_VMS;
            Message->setText("Đang thực hiện đồng bộ quy cách Máy bán hàng lên VMS..");
            emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
        }
    }
    else if(select == "DaySale"){
        s_machine->AdminType = ADMINFUNTIONLIST::DAY_SALE;
        QString SaleInfo = "Phiên chốt số: " + s_machine->saleSession()->SessionId + " - Kì: " + s_machine->saleSession()->PrePeriod
                +"\n-Thời gian bắt đầu: " + s_machine->saleSession()->StartTime.toString("yyyy-MM-dd hh:mm:ss")
                +"\n-Thời điểm hiện tại: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                +"\n-Tổng doanh thu: " + StringUtils::formatNumberVND(s_machine->saleSession()->TotalAmountShare) + " VND"
                +"\n-Tổng thực thu: " + StringUtils::formatNumberVND(s_machine->saleSession()->TotalBill) + " VND";
        Message->setText(SaleInfo);
        lineEdit_Sale->hide();
        // emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
    }else if(select == "MonthSale"){
        //lineEdit_Sale->setPlaceholderText("Nhập mã Coupon");
        s_machine->AdminType = ADMINFUNTIONLIST::MONTH_SALE;
        QString Period;
        Period = QDate::currentDate().toString("yyyyMM");
        int year = Period.mid(0, 4).toInt();
        int month = Period.mid(4,2).toInt();

        if(month == 12){
            year += 1;
            month = 01;
        }else{
            month += 1;
        }
        QString lastPeriod = "";
        if(month < 10){
            lastPeriod = QString::number(year) + "0" + QString::number(month);
        }else{
            lastPeriod = QString::number(year) + QString::number(month);
        }
        s_machine->saleSession()->LastPeriod = lastPeriod;
       // m->set_current_input(lastPeriod);
//           QString LastPeriod = "";
//            if(month < 10){
//                LastPeriod = QString::number(year) + "-0" + QString::number(month);
//            }else{
//                LastPeriod = QString::number(year) + "-" + QString::number(month);
//            }

       // data_map.insert("Input",LastPeriod);
        QString MonthSaleInfo = "Thông tin phiên chốt số: " + s_machine->saleSession()->SessionId + " - Kì: " + s_machine->saleSession()->PrePeriod
                +"\n-Tổng doanh thu: " + StringUtils::formatNumberVND(s_machine->saleSession()->TotalAmountShare) + " VND"
                +"\n-Tổng thực thu: " + StringUtils::formatNumberVND(s_machine->saleSession()->TotalBill) + " VND"
                +"\n-Kì thu hiện tại: " + s_machine->saleSession()->PrePeriod
                +"\n-Tổng doanh thu kì: "  + StringUtils::formatNumberVND(s_machine->saleSession()->PeriodTotalAmountShare) + " VND"
                +"\n-Kì thu tiếp theo: " + lastPeriod
                ;
        lineEdit_Sale->show();
        lineEdit_Sale->setText(lastPeriod);
        Message->setText(MonthSaleInfo);
    }else if(select == "ResendSale"){
        s_machine->AdminType = ADMINFUNTIONLIST::RESEND_SALE;
        int SaleMax = s_machine->GetSaleMax().toInt();
        SaleMax--;
        lineEdit_Sale->show();
        lineEdit_Sale->setText(QString::number(SaleMax));
        //lineEdit_Sale->setPlaceholderText("Nhập mã phiên chốt muốn gửi lại ");
        //lineEdit_Sale->setText(QString::number(SaleMax));
       // s_machine->set_current_input(QString::number(SaleMax));
       // s_machine->GetInfoSale();
        QString DBSale = s_machine->GetSaleInfo(QString::number(SaleMax));
        QJsonDocument sale = QJsonDocument::fromJson(DBSale.toUtf8());
        QJsonObject saleObj = sale.object();


        QString StartTime = saleObj["start_time"].toString();
        QString EndTime = saleObj["end_time"].toString();
        int total_amount = saleObj["share_total_amount"].toInt();
        int total_bill = saleObj["total_bill"].toInt();
        QString staff_code = saleObj["staff_code"].toString();

        QString ReSendSaleInfo = "Thông tin phiên chốt số: " + QString::number(SaleMax)
                +"\n-Thời gian bắt đầu: " + StartTime
                +"\n-Thời gian kết thúc: " + EndTime
                +"\n-Tổng doanh thu: " + StringUtils::formatNumberVND(total_amount) + " VND"
                +"\n-Tổng thực thu: " + StringUtils::formatNumberVND(total_bill) + " VND";
        Message->setText(ReSendSaleInfo);

    }else if(select == "ResendTransaction"){
        s_machine->AdminType = ADMINFUNTIONLIST::RESEND_TRANSACTION;
        emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);

    }else if(select == "GeneralSetting"){
        s_machine->AdminType = ADMINFUNTIONLIST::GENERAL_SETTING;
        emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
    }else if(select == "KhaySetting"){
        s_machine->AdminType = ADMINFUNTIONLIST::KHAY_SETTING;
        emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
    }else if(select == "SlotSetting"){
        s_machine->AdminType = ADMINFUNTIONLIST::SLOT_SETTING;
        emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
    }else if(select == "ExitApp"){
        s_machine->AdminType = ADMINFUNTIONLIST::EXIT_APP;
        emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
    }


   // }else if(s_machine->AdminType == ADMINFUNTIONLIST::SETTING_QUATITY){

   // }
}

void process_admin_funtion::on_Btn_Ok_Admin_Funtion_Process_clicked()
{
    if(s_machine->AdminType == ADMINFUNTIONLIST::DAY_SALE){
        s_machine->saleSession()->IsUpdateDB = false;
        if (!s_machine->saleSession()->IsUpdateDB && ( s_machine->saleSession()->TotalAmount > 0 || s_machine->saleSession()->TotalBill > 0 )){
            emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
        }else{
            Status->setText("Chốt doanh thu thất bại \nTổng doanh thu hoặc tổng thực thu phải > 0");
        }
    }else if(s_machine->AdminType == ADMINFUNTIONLIST::MONTH_SALE){
        if(s_machine->saleSession()->LastPeriod.length() >= 6 && s_machine->saleSession()->PeriodTotalAmount > 0){
            emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
        }else if(s_machine->saleSession()->LastPeriod.length() < 6){
            Status->setText("Chốt doanh thu thất bại \nKì tiếp theo không hợp lệ!");
        }else{
            Status->setText("Chốt doanh thu thất bại \nDoanh số kì phải lớn hơn 0!");
        }
    }else if(s_machine->AdminType == ADMINFUNTIONLIST::RESEND_SALE){
        IsCheckWaitResponseVMS = false;
        if(!IsCheckWaitResponseVMS){
            IsCheckWaitResponseVMS = true;
            bool ok = false;
            int count = lineEdit_Sale->text().toInt(&ok);
            int SaleMax = s_machine->GetSaleMax().toInt();
            if(count != 0){
                if (ok && count < SaleMax) {
                    emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION);
                    Status->setText("Đang thực hiện gửi lại phiên chốt số " + lineEdit_Sale->text() +" ...");
                }else{
                    Status->setText("Mã phiên chốt không hợp lệ!");
                }
            }else{
                Status->setText("Nhập mã phiên > 0!");
            }
        }
    }
}

void process_admin_funtion::on_Btn_Back_Admin_Funtion_Process_clicked()
{
    IsCheckWaitResponseVMS = false;
    s_machine->AdminType = ADMINFUNTIONLIST::INIT_ADMIN;
    emit Signal_Admin_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS);
}

void process_admin_funtion::Update_LineEdit_Sale()
{
    if(s_machine->AdminType == ADMINFUNTIONLIST::MONTH_SALE){
        s_machine->saleSession()->LastPeriod = lineEdit_Sale->text();
        QString MonthSaleInfo = "Thông tin phiên chốt số: " + s_machine->saleSession()->SessionId + " - Kì: " + s_machine->saleSession()->PrePeriod
                +"\n-Tổng doanh thu: " + StringUtils::formatNumberVND(s_machine->saleSession()->TotalAmountShare) + " VND"
                +"\n-Tổng thực thu: " + StringUtils::formatNumberVND(s_machine->saleSession()->TotalBill) + " VND"
                +"\n-Kì thu hiện tại: " + s_machine->saleSession()->PrePeriod
                +"\n-Tổng doanh thu kì: "  + StringUtils::formatNumberVND(s_machine->saleSession()->PeriodTotalAmountShare) + " VND"
                +"\n-Kì thu tiếp theo: " + lineEdit_Sale->text()
                ;
        Message->setText(MonthSaleInfo);
    }else if(s_machine->AdminType == ADMINFUNTIONLIST::RESEND_SALE){
        s_machine->set_current_input(lineEdit_Sale->text());
        QString DBSale = s_machine->GetSaleInfo(lineEdit_Sale->text());
        if(DBSale != ""){
            QJsonDocument sale = QJsonDocument::fromJson(DBSale.toUtf8());
            QJsonObject saleObj = sale.object();


            QString StartTime = saleObj["start_time"].toString();
            QString EndTime = saleObj["end_time"].toString();
            int total_amount = saleObj["share_total_amount"].toInt();
            int total_bill = saleObj["total_bill"].toInt();
            QString staff_code = saleObj["staff_code"].toString();

            QString ReSendSaleInfo = "Thông tin phiên chốt số: " + lineEdit_Sale->text()
                    +"\n-Thời gian bắt đầu: " + StartTime
                    +"\n-Thời gian kết thúc: " + EndTime
                    +"\n-Tổng doanh thu: " + StringUtils::formatNumberVND(total_amount) + " VND"
                    +"\n-Tổng thực thu: " + StringUtils::formatNumberVND(total_bill) + " VND";
            Message->setText(ReSendSaleInfo);
        }else{
            Message->setText("Mã phiên chốt không hợp lệ!");
        }
    }
}

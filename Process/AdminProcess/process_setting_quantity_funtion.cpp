#include "process_setting_quantity_funtion.h"
#include "ui_process_setting_quantity_funtion.h"

process_setting_quantity_funtion::process_setting_quantity_funtion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::process_setting_quantity_funtion)
{
    ui->setupUi(this);
}

process_setting_quantity_funtion::process_setting_quantity_funtion(Machine *m)
{
    s_machine = m;

    QVBoxLayout *mainLayout = new QVBoxLayout;
//    QLabel* Title = new QLabel(this);
//    Title->setText("Cài đặt số lượng");
//    Title->setMaximumSize(1080, 110);
//    QFont fontTitle("Nyala",32);
//    Title->setFont(fontTitle);
//    Title->setStyleSheet("QLabel { background-color : yellow; color : black; }");
//    Title->setFrameStyle(QFrame::Box | QFrame::Sunken);
//    Title->setLineWidth(2);
//    Title->setAlignment(Qt::AlignCenter);

    QFont font1("Times",26);
    QGroupBox *Gr_Setting_Quantity = new QGroupBox(tr("Nhập số lượng cài đặt"));
    Gr_Setting_Quantity->setFont(font1);
    Gr_Setting_Quantity->setAlignment(Qt::AlignCenter);
   // QVBoxLayout *VBox_Setting_Quantity = new QVBoxLayout;

//    QGroupBox *Gr_Resend_Transaction = new QGroupBox(tr("Gửi lại giao dịch lên VMS"));
//    Gr_Resend_Transaction->setFont(font1);
//    Gr_Resend_Transaction->setAlignment(Qt::AlignCenter);
    QGroupBox *StartTime_Gr = new QGroupBox(tr("Nhập ngày bắt đầu"));
    StartTime_Gr->setAlignment(Qt::AlignCenter);
    StartTime_Gr->setFont(font1);
    QGroupBox *EndTime_Gr = new QGroupBox(tr("Nhập ngày kết thúc"));
    EndTime_Gr->setAlignment(Qt::AlignCenter);
    EndTime_Gr->setFont(font1);
    if(m->AdminType == ADMINFUNTIONLIST::GENERAL_SETTING){
        QHBoxLayout *HBox_Setting_Quantity = new QHBoxLayout;
        spb_general_quantity = new QSpinBox(this);
        spb_general_quantity->setValue(99);
        spb_general_quantity->setRange(0, 999);
        spb_general_quantity->setFont(font1);
        spb_general_quantity->setMinimumSize(200,200);
        spb_general_quantity->setMaximumSize(200,200);
        connect(spb_general_quantity, &QSpinBox::textChanged, this, &process_setting_quantity_funtion::onSpinBoxValueChanged,Qt::QueuedConnection);
        //connect(spb_general_quantity, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)), Qt::QueuedConnection);
      //  spb_general_quantity->setFocus();
        QPalette palspin = spb_general_quantity->palette();
        spb_general_quantity->setStyleSheet("QSpinBox { border: 5px solid red; border-radius: 5px; background-color: yellow; color:green; }"
                               "QSpinBox::up-arrow { border-left: 17px solid none;"
                               "border-right: 17px solid none; border-bottom: 17px solid black; width: 0px; height: 0px; }"
                               "QSpinBox::up-arrow:hover { border-left: 17px solid none;"
                               "border-right: 17px solid none; border-bottom: 17px solid black; width: 0px; height: 0px; }"
                               "QSpinBox::up-button { width: 60px; height: 60px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.25 "+getRGBhexColor(palspin.light().color())+", stop: 1 "+getRGBhexColor(palspin.midlight().color())+") }"
                               "QSpinBox::up-button:hover { width: 60px; height: 60px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.25 "+getRGBhexColor(palspin.light().color())+", stop: 1 "+getRGBhexColor(palspin.shadow().color())+") }"

                               "QSpinBox::down-arrow { border-left: 17px solid none;"
                               "border-right: 17px solid none; border-top: 17px solid black; width: 0px; height: 0px; }"
                               "QSpinBox::down-arrow:hover { border-left: 17px solid none;"
                               "border-right: 17px solid none; border-top: 17px solid black; width: 0px; height: 0px; }"
                               "QSpinBox::down-button { width: 60px; height: 60px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.25 "+getRGBhexColor(palspin.light().color())+", stop: 1 "+getRGBhexColor(palspin.midlight().color())+") }"
                               "QSpinBox::down-button:hover { width: 60px; height: 60px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.25 "+getRGBhexColor(palspin.light().color())+", stop: 1 "+getRGBhexColor(palspin.shadow().color())+") }"
        );

        lb_general_quantity = new QLabel("Số lượng chung",this);
        lb_general_quantity->setWordWrap(true);
        lb_general_quantity->setFont(font1);
        lb_general_quantity->setMinimumSize(200,200);
        lb_general_quantity->setMaximumSize(200,200);
        lb_general_quantity->setStyleSheet("QLabel { background-color : gray; color : red; }");
        HBox_Setting_Quantity->addWidget(lb_general_quantity);
        HBox_Setting_Quantity->addWidget(spb_general_quantity);
        HBox_Setting_Quantity->setAlignment(Qt::AlignCenter);
      //  VBox_Setting_Quantity->addWidget(HBox_Setting_Quantity);
        Gr_Setting_Quantity->setLayout(HBox_Setting_Quantity);


    }else if(m->AdminType == ADMINFUNTIONLIST::KHAY_SETTING){
        grid = new QGridLayout();
        qint8 row = 0;
        for(int i = 0; i < m->config.getTrayCount(); i++){
            spb_quantity[i] = new my_qspinbox("Khay\n" + QString::number(i + 1), 99,this);
            if(i%3 == 0){
                row++;
            }
            grid->addWidget(spb_quantity[i], row, i%3);
        }
        Gr_Setting_Quantity->setLayout(grid);

    }else if(m->AdminType == ADMINFUNTIONLIST::SLOT_SETTING){
        grid = new QGridLayout();
        qint8 row = 0;
        for (int k = 1; k <= s_machine->config.getTrayCount(); k ++)
            for (int s = 0; s < s_machine->config.getSlotCountForTray(k); s ++){
                quint8 slot = (k-1)*10 + s;
                spb_quantity[slot] = new my_qspinbox("Slot\n" + QString::number(k*10+s), s_machine->config.getGoodCountForSlot(k,s),this);
                if(s%5 == 0){
                    row++;
                }
                grid->addWidget(spb_quantity[slot], row, s%5);
            }
        Gr_Setting_Quantity->setLayout(grid);
    }else if(m->AdminType == ADMINFUNTIONLIST::RESEND_TRANSACTION){
//        tx_info = new QLabel("",this);
//        tx_info->setWordWrap(true);
//        tx_info->setText("Chọn chức năng!");
//        tx_info->setAlignment(Qt::AlignCenter);
//        tx_info->setMinimumSize(1080, 500);
//        tx_info->setMaximumSize(1080, 500);
//        tx_info->setStyleSheet("QLabel { background-color : gray; color : red; }");
//        tx_info->setFrameStyle(QFrame::Box | QFrame::Sunken);
//        tx_info->setLineWidth(5);
//        tx_info->setFont(font1);


        QHBoxLayout *HBox_StartTime = new QHBoxLayout;
        StartTime = new QDateEdit(this);
        StartTime->setDisplayFormat("yyyy-MM-dd");
        StartTime->setDate(QDate::currentDate().addDays(-1));
        //birth->setCalendarPopup(true);
        StartTime->setFont(font1);
        StartTime->setStyleSheet("color: red; background-color: white");
        StartTime->setMaximumSize(680,130);
        StartTime->setMinimumSize(680,130);
        StartTime->setAlignment(Qt::AlignCenter);
//        spb_start_transactionId = new my_qspinbox("Số giao dịch bắt đầu", 1 ,this);
//        spb_end_transactionId = new my_qspinbox("Số giao dịch kết thúc", 1 ,this);
        QHBoxLayout *HBox_EndTime = new QHBoxLayout;
        EndTime = new QDateEdit(this);
        EndTime->setDisplayFormat("yyyy-MM-dd");
        EndTime->setDate(QDate::currentDate());
        //birth->setCalendarPopup(true);
        EndTime->setFont(font1);
        EndTime->setStyleSheet("color: red; background-color: white");
        EndTime->setMaximumSize(680,130);
        EndTime->setMinimumSize(680,130);
        EndTime->setAlignment(Qt::AlignCenter);

        HBox_StartTime->addSpacing(200);
        HBox_StartTime->addWidget(StartTime);
        HBox_StartTime->addSpacing(200);

        HBox_EndTime->addSpacing(200);
        HBox_EndTime->addWidget(EndTime);
        HBox_EndTime->addSpacing(200);
        StartTime_Gr->setLayout(HBox_StartTime);
        EndTime_Gr->setLayout(HBox_EndTime);
    }

    Status = new QLabel("",this);
    Status->setWordWrap(true);
    Status->setMaximumSize(1080, 100);
    Status->setMinimumSize(1080, 100);
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
    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_Admin_Setting_Quantity_Funtion_Process_clicked()));
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_Admin_Setting_Quantity_Funtion_Process_clicked()));
    Gr_Ok_Back->setLayout(HBox_Ok_Back);

    if(m->AdminType == ADMINFUNTIONLIST::GENERAL_SETTING || m->AdminType == ADMINFUNTIONLIST::KHAY_SETTING || m->AdminType == ADMINFUNTIONLIST::SLOT_SETTING){
        mainLayout->addWidget(Gr_Setting_Quantity);
    }else if(m->AdminType == ADMINFUNTIONLIST::RESEND_TRANSACTION){
        //mainLayout->addWidget(tx_info);
        mainLayout->addWidget(StartTime_Gr);
        mainLayout->addWidget(EndTime_Gr);
    }
    mainLayout->addWidget(Status);
    mainLayout->addWidget(Gr_Ok_Back);

    setLayout(mainLayout);
    setStyleSheet("QGroupBox { color: green; background-color: orange;}");
}

process_setting_quantity_funtion::~process_setting_quantity_funtion()
{
    delete ui;
}

QString process_setting_quantity_funtion::getRGBhexColor(const QColor color) {
    QString col("#");

    if(color.red() == 0)
        col.append("00");
    else
        col.append(QString::number(color.red(), 16));

    if(color.green() == 0)
        col.append("00");
    else
        col.append(QString::number(color.green(), 16));
    if(color.blue() == 0)
        col.append("00");
    else
        col.append(QString::number(color.blue(), 16));
    return col;
}

void process_setting_quantity_funtion::ReSendTransactionStatus(QString status)
{
    if(status == "success"){
        Status->setText("Gửi lại lịch sử giao dịch thành công");
    }else if(status == "fail"){
        Status->setText("Gửi lại lịch sử giao dịch thất bại \nKhông có giao dịch");
    }else if(status == "disconnect"){
        Status->setText("Gửi lại lịch sử giao dịch thất bại \nMáy đang mất kết nối");
    }
}

void process_setting_quantity_funtion::on_Btn_Ok_Admin_Setting_Quantity_Funtion_Process_clicked()
{
   // Status->setText("");
    if(s_machine->AdminType == ADMINFUNTIONLIST::GENERAL_SETTING){
        if(spb_general_quantity->value() != 99){
            for (int k = 1; k <= s_machine->config.getTrayCount(); k ++)
                for (int s = 0; s < s_machine->config.getSlotCountForTray(k); s ++){
                    if(spb_general_quantity->value() != s_machine->config.getGoodCountForSlot(k,s)){
                       s_machine->UpdateGoodQuatity(s_machine->config.getIdForSlot(k,s), s_machine->GetGoodQuatity(s_machine->config.getIdForSlot(k,s)) + spb_general_quantity->value() - s_machine->config.getGoodCountForSlot(k,s));
                        s_machine->config.setGoodCountForSlot(k, s,spb_general_quantity->value());
                    }
                }
            Status->setText("Cài đặt thành công!");
        }else{
            Status->setText("Nhập số lượng cài đặt!");
        }
    }else if(s_machine->AdminType == ADMINFUNTIONLIST::KHAY_SETTING){
        bool flag = false;
        for (int k = 1; k <= s_machine->config.getTrayCount(); k ++){
            if(spb_quantity[k - 1]->GetQSpinBoxValue() != 99){
                for (int s = 0; s < s_machine->config.getSlotCountForTray(k); s ++){
                    if(spb_quantity[k - 1]->GetQSpinBoxValue() != s_machine->config.getGoodCountForSlot(k,s)){
                        s_machine->UpdateGoodQuatity(s_machine->config.getIdForSlot(k,s), s_machine->GetGoodQuatity(s_machine->config.getIdForSlot(k,s)) + spb_quantity[k - 1]->GetQSpinBoxValue() - s_machine->config.getGoodCountForSlot(k,s));
                        s_machine->config.setGoodCountForSlot(k, s, spb_quantity[k - 1]->GetQSpinBoxValue());
                    }
                }
                flag = true;
            }
        }
        if(flag){
            Status->setText("Cài đặt thành công!");
        }else{
            Status->setText("Nhập số lượng cài đặt");
        }

    }else if(s_machine->AdminType == ADMINFUNTIONLIST::SLOT_SETTING){
        bool flag = false;
        for (int k = 1; k <= s_machine->config.getTrayCount(); k ++)
            for (int s = 0; s < s_machine->config.getSlotCountForTray(k); s ++){
                quint8 slot = (k-1)*10 + s;
                if(spb_quantity[slot]->IsValueChanged() && spb_quantity[slot]->GetQSpinBoxValue() >= 0){
                    s_machine->config.setGoodCountForSlot(k, s, spb_quantity[slot]->GetQSpinBoxValue());
                    s_machine->UpdateGoodQuatity(s_machine->config.getIdForSlot(k,s), s_machine->GetGoodQuatity(s_machine->config.getIdForSlot(k,s)) + spb_quantity[slot]->ValueChanged());
                    flag = true;
                }
            }
        if(flag)
            Status->setText("Cài đặt thành công!");
        else
            Status->setText("Chưa thay đổi cài đặt hoặc số lượng cài đặt < 0!");
    }else if(s_machine->AdminType == ADMINFUNTIONLIST::RESEND_TRANSACTION){
        QString start_time = StartTime->text() + " 00:00:00";
        QString end_time = EndTime->text() + " 00:00:00";
        //LOG<<start_time <<end_time <<"ffffffff";
        emit Signal_Admin_Setting_Quantity_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_SETTING_QUANTITY_FUNTION, start_time, end_time);

    }
    if(s_machine->AdminType == ADMINFUNTIONLIST::GENERAL_SETTING || s_machine->AdminType == ADMINFUNTIONLIST::KHAY_SETTING || s_machine->AdminType == ADMINFUNTIONLIST::SLOT_SETTING){
        s_machine->config.save();
        s_machine->SetListGoodIdPriority();
    }
}

void process_setting_quantity_funtion::on_Btn_Back_Admin_Setting_Quantity_Funtion_Process_clicked()
{
    s_machine->AdminType = ADMINFUNTIONLIST::SETTING_QUATITY;
    emit Signal_Admin_Setting_Quantity_Funtion_Process(MACHINE_STATE::ADMIN_PROCESS_FUNTION,"" ,"");
}

void process_setting_quantity_funtion::onSpinBoxValueChanged()
{
    spb_general_quantity->findChild<QLineEdit*>()->deselect();
}

//void process_setting_quantity_funtion::keyPressEvent(QKeyEvent *ev)
//{
//    if(ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return){
//        LOG<<"ggggg";
//        QInputMethod *input = QApplication::inputMethod();
//        input->hide();
//    }else if(ev->key() == Qt::Key_1){
//        LOG<<"hhhhhhhhhhhh";
//    }
//}

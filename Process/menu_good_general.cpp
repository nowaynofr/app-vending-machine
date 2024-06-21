#include "menu_good_general.h"
#include "ui_menu_good_general.h"
#include"my_qlabel.h"
menu_good_general::menu_good_general(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu_good_general)
{
    ui->setupUi(this);
}

menu_good_general::menu_good_general(Machine *m, QString directory)
{
  //  Select_Good = "";
    s_machine = m;
    DatabaseDataStoragePath = directory;
    ListGoodIdPriority = m->ReturnListGooIdPriority();
    LOG<<ListGoodIdPriority.size()<<"ggggg";
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QPushButton *button = new QPushButton("click here");
    button->setGeometry(100, 100, 120, 40);
    QLabel* Title = new QLabel(this);
    Title->setText("  CHỌN MẶT HÀNG CẦN MUA");
    Title->setMaximumSize(1080, 120);
    QFont fontTitle("Times",32);
    fontTitle.setStyleHint(QFont::Monospace);
    Title->setFont(fontTitle);
    Title->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    Title->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Title->setLineWidth(2);
    Title->setAlignment(Qt::AlignLeft);

    QFont fontMenuGoodGroup("Arial",26);
 //   QFont fontGood("Arial",22);

    QGroupBox* ListMenuGoodGroup = new QGroupBox(tr(""));
    ListMenuGoodGroup->setAlignment(Qt::AlignCenter);
 //   ListMenuGoodGroup->setFont(fontMenuGoodGroup);
   // ListMenuGoodGroup->setStyleSheet("QGroupBox::title {subcontrol-position: center;}");
   // ListMenuGoodGroup->setAlignment(Qt::AlignCenter);
//    ListPriority = m_db.GetListPriority();

//    std::sort(ListPriority.begin(), ListPriority.end());

//    ListGoodIdPriority.clear();
//    for(int i = 0; i < ListPriority.size(); i++){
//        ListGoodIdPriority.append(m_db.GetListGoodIdPriority(ListPriority.at(i)));
//    }
//    LOG<<ListGoodIdPriority.size()<<ListPriority.size()<<"kkkkk";
    grid = new QGridLayout();
    qint8 row = 0;
    for (int i = 0; i < ListGoodIdPriority.size(); i++){
        QImage image(DatabaseDataStoragePath + "/" + ListGoodIdPriority.at(i) +".png");
        if(image.isNull()){
            image.load(":/img/NoGoodImage.png");
        }
        QString goodInfo = m_db.getGoodNameInMenuGeneralTable(ListGoodIdPriority.at(i)) + "\n" +
                StringUtils::formatNumberVND(m_db.getGoodPriceInMenuGeneralTable(ListGoodIdPriority.at(i)).toInt()) + " VND";
        menu[i] = new my_qlabel(ListGoodIdPriority.at(i),image,goodInfo);
        menu[i]->setStyleSheet("border: 3px solid black; border-radius: 25px; background: white;");
      //  menu[i]->setFrameShape(QFrame::Box);
       // menu[i]->setLineWidth(1);
       // menu[i]->setScaledContents(true);
       // menu[i]->setWordWrap(true);
        menu[i]->setMaximumSize(320,270);
        menu[i]->setMinimumSize(320,270);
        if(i%3 == 0){
            row++;
        }
        grid->addWidget(menu[i], row, i%3);
        grid->setColumnMinimumWidth(i,50);
        grid->setRowMinimumHeight(i,50);
        grid->setColumnStretch(i,50);
        grid->setRowStretch(i,50);
        grid->setAlignment(Qt::AlignCenter);
   //     menu[i]->setPixmap(QPixmap::fromImage(image));
//            menu[index + j]->setText(m_db.getGoodNameInMenuGeneralTable(m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).at(j)) +"\n" +
//                             StringUtils::formatNumberVND(m_db.getGoodPriceInMenuGeneralTable(m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).at(j)).toInt()) + " VND");
//           menu[index + j]->setStyleSheet("QLabel { background-color : gray; color : blue; }");
//          menu[index + j]->setAlignment(Qt::AlignLeft);
//         menu[index + j]->setFont(fontGood);
        connect(menu[i], SIGNAL(home_network(QString)),this, SLOT(select_good_clicked(QString)));
    }
    ListMenuGoodGroup->setLayout(grid);
    ListMenuGoodGroup->setMinimumWidth(1020);
    ListMenuGoodGroup->setMinimumHeight(1600);
    ScrollAreaMenu = new QScrollArea(this);
    ScrollAreaMenu->setWidget(ListMenuGoodGroup);
    ScrollAreaMenu->setAlignment(Qt::AlignCenter);
    ScrollAreaMenu->setStyleSheet("QScrollBar:vertical {border: 2px solid grey;background: white;width: 40px;}"
                                  "QScrollBar:horizontal {border: 2px solid grey;background: white;height: 40px;}"
                                  "QScrollBar::handle:horizontal {    background: #32CC99;    min-width: 50px;max-width: 50px;}"
                                  "QScrollBar::handle:vertical {    background: #32CC99;    min-width: 50px;max-width: 50px;}"
                              //    "QScrollBar::add-line:horizontal {border: 2px solid grey;background: #32CC99;width: 20px;subcontrol-position: right;subcontrol-origin: margin;}"

                                //  "QScrollBar::sub-line:horizontal {border: 2px solid grey;background: #32CC99;width: 20px;subcontrol-position: left;subcontrol-origin: margin;}"
);
   // ScrollAreaMenu->verticalScrollBar()->setRange(150,150);
   // ScrollAreaMenu->horizontalScrollBar()->setRange(150,150);
  //  ScrollAreaMenu->horizontalScrollBar()->setValue(300);
  //  ScrollAreaMenu->horizontalScrollBar()->setMaximumSize(300,300);
   // ScrollAreaMenu->verticalScrollBar()->setMinimumSize(200,200);
   // ScrollAreaMenu->verticalScrollBar()->setValue(100);
 //   ScrollAreaMenu->Scro
//    QLabel* home = new my_qlabel("",this);
//    home->setGeometry(960,450,110,110);
//    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
//    QImage img(":/img/Button_Image/Home_Btn.jpg");
//    home->setPixmap(QPixmap::fromImage(img));
//    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

//    for ( int i = 0; i < m_db.GetListGoodMenuGeneral().size(); i++){
//        GroupIndustry[i] = new QGroupBox(m_db.GetListGoodMenuGeneral().at(i));
//        GroupIndustry[i]->setStyleSheet("QGroupBox { color : green; }");
//        GroupIndustry[i]->setFont(fontIndustry);
//       // GroupIndustry[i]->setAlignment(Qt::AlignCenter);

//        QGridLayout *grid = new QGridLayout();
//        qint8 row = 0;
//        if(i != 0){
//            index += m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i - 1)).size();
//        }
//        for(int j = 0; j < m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).size(); j++){
//           // quint8 index = m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i - 1)).size() + j;
//            LOG<<m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).at(j)<<"list mã sp";
//            menu[index + j] = new my_qlabel(m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).at(j));
//            menu[index + j]->setFrameShape(QFrame::Box);
//            menu[index + j]->setLineWidth(1);
//            menu[index + j]->setScaledContents(true);
//            menu[index + j]->setWordWrap(true);
//            menu[index + j]->setMaximumSize(235,230);
//            menu[index + j]->setMinimumSize(235,230);
//           // price[i]->adjustSize();
//           // price[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
//            if(j%4 == 0){
//                row++;
//            }
//            grid->addWidget(menu[index + j], row, j%4);
//            QImage image(DatabaseDataStoragePath + "/" + m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).at(j) +".png");
//            if(image.isNull()){
//                image.load(":/img/S&B.png");
//            }
//            menu[index + j]->setPixmap(QPixmap::fromImage(image));
////            menu[index + j]->setText(m_db.getGoodNameInMenuGeneralTable(m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).at(j)) +"\n" +
////                             StringUtils::formatNumberVND(m_db.getGoodPriceInMenuGeneralTable(m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).at(j)).toInt()) + " VND");
// //           menu[index + j]->setStyleSheet("QLabel { background-color : gray; color : blue; }");
//  //          menu[index + j]->setAlignment(Qt::AlignLeft);
//   //         menu[index + j]->setFont(fontGood);
//            connect(menu[index + j], SIGNAL(home_network(QString)),this, SLOT(select_good_clicked(QString)));
//        }
//        GroupIndustry[i]->setLayout(grid);
//        GroupIndustry[i]->setMinimumWidth(1050);
//        ScrollAreaMenu[i] = new QScrollArea(this);
//        ScrollAreaMenu[i]->setWidget(GroupIndustry[i]);

//    }

    QGroupBox *NumberPhoneGroup = new QGroupBox(tr("Nhập số lượng"));
    NumberPhoneGroup->setFont(fontMenuGoodGroup);
    QHBoxLayout *HBox_Number_Phone = new QHBoxLayout;
//    QLabel *NumberPhoneLabel = new QLabel(tr("Số lượng:"));
//    NumberPhoneLabel->setFont(fontMenuGoodGroup);
    btn_next= new QPushButton("next",this);
    btn_next->setMaximumSize(200,200);
    btn_next->setMinimumSize(200,200);
    btn_next->setFont(fontTitle);
    connect(btn_next, SIGNAL(clicked()),this, SLOT(on_Btn_next_click()));


    btn_increase_quantity = new QPushButton("+",this);
    btn_decrease_quantity = new QPushButton("-", this);
    btn_increase_quantity->setMaximumSize(80,80);
    btn_increase_quantity->setMinimumSize(80,80);
    btn_decrease_quantity->setMaximumSize(80,80);
    btn_decrease_quantity->setMinimumSize(80,80);

    btn_increase_quantity->setFont(fontTitle);
    btn_decrease_quantity->setFont(fontTitle);

    connect(btn_increase_quantity, SIGNAL(clicked()),this, SLOT(on_Btn_increase_quantity_Menu_General_clicked()));
    //HBox_Ok_Back->addWidget(btn_Back);
    connect(btn_decrease_quantity, SIGNAL(clicked()),this, SLOT(on_Btn_decrease_quantity_Menu_General_clicked()));
    btn_increase_quantity->setStyleSheet("border: 3px solid black; border-radius: 25px; background: gray;color: red;");
    btn_decrease_quantity->setStyleSheet("border: 3px solid black; border-radius: 25px; background: gray;color: red;");

   // spb_quantity = new my_qspinbox("Số lượng", 1 ,this);
    lineEdit_Quantity = new QLineEdit(this);
    lineEdit_Quantity->setFont(fontMenuGoodGroup);
    lineEdit_Quantity->setMaximumSize(200,80);
    lineEdit_Quantity->setMinimumSize(200,80);
    lineEdit_Quantity->setInputMethodHints(Qt::ImhPreferNumbers);
    lineEdit_Quantity->setStyleSheet("color: red; background-color: yellow;border: 2px solid blue; border-radius: 15px");
   // connect(lineEdit_Quantity, &QLineEdit::textChanged, this, &process_admin_funtion::Update_LineEdit_Sale);
    lineEdit_Quantity->setAlignment(Qt::AlignCenter);
    lineEdit_Quantity->setText("1");
  //  lineEdit_Quantity->setFocus();
  //  lineEdit_Quantity->setPlaceholderText("Số lượng");
    HBox_Number_Phone->addSpacing(330);
    HBox_Number_Phone->addWidget(btn_next);
    HBox_Number_Phone->addSpacing(330);
    HBox_Number_Phone->addWidget(btn_decrease_quantity);
  //  HBox_Number_Phone->addSpacing(5);
    HBox_Number_Phone->addWidget(lineEdit_Quantity);
   // HBox_Number_Phone->addSpacing(5);
    HBox_Number_Phone->addWidget(btn_increase_quantity);
    HBox_Number_Phone->addSpacing(330);
    NumberPhoneGroup->setLayout(HBox_Number_Phone);
  //  NumberPhoneGroup->setMaximumHeight(120);


    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setMaximumSize(1080, 120);
    Message->setMinimumSize(1080, 120);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);
    //Message->setAlignment(Qt::AlignCenter);
    QFont font1("Times",26);
    Message->setFont(font1);

//    QGroupBox *Gr_Ok_Back = new QGroupBox(tr(""));
//    QHBoxLayout *HBox_Ok_Back = new QHBoxLayout;
//    btn_Ok = new QPushButton("OK",this);
//    btn_Back = new QPushButton("Back", this);
//    btn_Ok->setMaximumSize(300,70);
//    btn_Ok->setMinimumSize(300,70);
//    btn_Back->setMaximumSize(300,70);
//    btn_Back->setMinimumSize(300,70);
//    HBox_Ok_Back->addWidget(btn_Back);
//    HBox_Ok_Back->addWidget(btn_Ok);
//    connect(btn_Ok, SIGNAL(clicked()),this, SLOT(on_Btn_Ok_Menu_General_clicked()));
//    //HBox_Ok_Back->addWidget(btn_Back);
//    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_Menu_General_clicked()));
//    btn_Ok->setStyleSheet("QPushButton { color: blue; background-color: gray;}");
//    btn_Back->setStyleSheet("QPushButton { color: blue; background-color: gray;}");
//    Gr_Ok_Back->setLayout(HBox_Ok_Back);
    QLabel* home = new my_qlabel("",this);
    home->setAlignment(Qt::AlignCenter);
    home->setGeometry(960,1800,110,110);
    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
    QImage img(":/img/Button_Image/Home_Btn.jpg");
    home->setPixmap(QPixmap::fromImage(img));
    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));


    mainLayout->addWidget(Title);
    mainLayout->addWidget(ScrollAreaMenu);
    mainLayout->addWidget(NumberPhoneGroup);
    mainLayout->addWidget(Message);
  //  mainLayout->addWidget(Gr_Ok_Back);

    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
    setLayout(mainLayout);
}

menu_good_general::~menu_good_general()
{
    delete ui;
}

QString menu_good_general::GetSelectGood()
{
    return "";
}

void menu_good_general::on_Btn_Ok_Menu_General_clicked()
{
//    if(Select_Good == ""){
//        Message->setText("Chọn sản phẩm muốn mua!");
//    }else{
//        Message->setText("");
//        emit Signal_Menu_Good_General(MACHINE_STATE::SELECT_CHARGE_TYPE);
//    }
}

void menu_good_general::on_Btn_Back_Menu_General_clicked()
{
    emit Signal_Menu_Good_General(MACHINE_STATE::MENU);
}
void menu_good_general::on_Btn_next_click()
{

    emit Signal_Menu_Good_General(MACHINE_STATE::TESTFORM);
}
void menu_good_general::on_Btn_increase_quantity_Menu_General_clicked()
{
    int quantity = lineEdit_Quantity->text().toInt();
    quantity++;
    lineEdit_Quantity->setText(QString::number(quantity));
}

void menu_good_general::on_Btn_decrease_quantity_Menu_General_clicked()
{
    int quantity = lineEdit_Quantity->text().toInt();
    quantity--;
    if(quantity == 0){
        quantity = 1;
    }
    lineEdit_Quantity->setText(QString::number(quantity));
}

void menu_good_general::Back_Home(QString)
{
    emit Signal_Menu_Good_General(MACHINE_STATE::MENU);
}

void menu_good_general::select_good_clicked(QString select)
{
//    for(int j = 0; j < ListGoodIdPriority.size(); j++){
//       // quint8 index = m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i - 1)).size() + j;
//        if(select == ListGoodIdPriority.at(j)){
//            menu[j]->setFrameStyle(QFrame::Box);
//            menu[j]->setStyleSheet ("QFrame {border: 6px solid red;}");
//            //menu[j]->setLineWidth(6);
////            Message->setText(m_db.getGoodNameInMenuGeneralTable(select) + " --- " +
////            StringUtils::formatNumberVND(m_db.getGoodPriceInMenuGeneralTable(select).toInt()) + " VND");
//        }else{
//            menu[j]->setFrameStyle(QFrame::Box);
//            menu[j]->setStyleSheet ("QFrame {border: 1px solid black;}");
//            //menu[j]->setLineWidth(1);
//        }
//    }
//    quint8 index = 0;
//    for ( int i = 0; i < m_db.GetListGoodMenuGeneral().size(); i++){
//        if(i != 0)
//            index += m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i - 1)).size();
//        for(int j = 0; j < m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).size(); j++){
//           // quint8 index = m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i - 1)).size() + j;
//            if(select == m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).at(j)){
//                menu[index + j]->setFrameStyle(QFrame::Box);
//                menu[index + j]->setLineWidth(5);
//                Message->setText(m_db.getGoodNameInMenuGeneralTable(select) + " - " +
//                StringUtils::formatNumberVND(m_db.getGoodPriceInMenuGeneralTable(select).toInt()) + " VND");
//            }else{
//                menu[index + j]->setFrameStyle(QFrame::Box);
//                menu[index + j]->setLineWidth(1);
//            }
//            LOG<<m_db.GetListGoodIdMenuGoodGeneral(m_db.GetListGoodMenuGeneral().at(i)).at(j)<<select<<"kfjgk";
//        }
//    }
   // Select_Good = select;
    s_machine->transaction()->GoodId = select;
    s_machine->transaction()->SlotId = "";
    quint8 quantity_max = 0;
    for (int i = 1; i <= s_machine->config.getTrayCount() ; i++)
    {
        int SlotCount = s_machine->config.getSlotCountForTray(i);
        if (SlotCount > 0)
        {
            for (int j = 0; j < SlotCount; j++)
            {
                if(s_machine->config.getIdForSlot(i, j) == s_machine->transaction()->GoodId){
                    if(s_machine->config.getGoodCountForSlot(i, j) > quantity_max){
                        quantity_max = s_machine->config.getGoodCountForSlot(i, j);
                    }
                }
            }
        }
    }
    bool ok = false;
    quint8 quantity = lineEdit_Quantity->text().toInt(&ok);
   // quint8 quantity = spb_quantity->GetQSpinBoxValue();
  //  quint8 quantity_rest = quantity;
    if(ok){
        if(quantity > 0){
            if(quantity_max > 0){
                if(quantity > 0 && quantity <= quantity_max){
                    for (int i = 1; i <= s_machine->config.getTrayCount() ; i++)
                    {
                        bool flag = true;
                        int SlotCount = s_machine->config.getSlotCountForTray(i);
                        if (SlotCount > 0)
                        {
                            for (int j = 0; j < SlotCount; j++)
                            {
                                if(s_machine->config.getIdForSlot(i, j) == s_machine->transaction()->GoodId){
                                    if(s_machine->config.getGoodCountForSlot(i, j) >= quantity){
                                        s_machine->transaction()->Quantity = quantity;
                                        s_machine->transaction()->SlotId = QString::number(i) + QString::number(j);
                                        flag = false;
                                        break;
                                    }
                                }
                            }
                        }
                        if(!flag)
                            break;
                    }
                }else{
                    Message->setText(QString("Nhập số lượng > 0 và <= %1!").arg(quantity_max));
                }
            }else{
                Message->setText("Chọn sản phẩm thất bại. Sản phẩm đang cài sai số lượng!");
            }
        }else{
            Message->setText("Nhập số lượng sản phẩm > 0!");
        }
    }else{
        Message->setText("Nhập số lượng sản phẩm không hợp lệ!");
    }
    if(s_machine->transaction()->SlotId != ""){
        emit Signal_Menu_Good_General(MACHINE_STATE::SELECT_CHARGE_TYPE);
    }

//    s_machine->transaction()->GoodId = select;
//    s_machine->transaction()->SlotId = "";
//    s_machine->transaction()->SlotIdList.clear();
//    s_machine->transaction()->QuantityList.clear();
//    bool ok = false;
//    quint8 quantity = lineEdit_Quantity->text().toInt(&ok);
//    quint8 quantity_rest = quantity;
//    if(ok){
//        if(quantity > 0 && quantity <= s_machine->GetGoodQuatity(select)){
//            for (int i = 1; i <= s_machine->config.getTrayCount() ; i++)
//            {
//                bool flag = true;
//                int SlotCount = s_machine->config.getSlotCountForTray(i);
//                if (SlotCount > 0)
//                {
//                    for (int j = 0; j < SlotCount; j++)
//                    {
//                        if(s_machine->config.getIdForSlot(i, j) == s_machine->transaction()->GoodId){
//                            if(s_machine->config.getGoodCountForSlot(i, j) > 0){
//                                if(s_machine->transaction()->QuantityList.size() == 0){
//                                    quantity_rest = quantity;
//                                }else{
//                                    for(int k = 0; k < s_machine->transaction()->QuantityList.size();k++){
//                                        quantity_rest -= s_machine->transaction()->QuantityList.at(k);
//                                    }
//                                }
//                                if(s_machine->config.getGoodCountForSlot(i, j) >= quantity_rest){
//                                    s_machine->transaction()->SlotIdList.append(i*10 + j);
//                                    s_machine->transaction()->QuantityList.append(quantity_rest);
//                                    flag = false;
//                                    break;
//                                }else{
//                                    s_machine->transaction()->SlotIdList.append(i*10 + j);
//                                    s_machine->transaction()->QuantityList.append(s_machine->config.getGoodCountForSlot(i, j));
//                                }
//                            }
//                        }
//                    }
//                }
//                if(!flag)
//                    break;
//            }
//            for(int k = 0; k < s_machine->transaction()->QuantityList.size();k++){
//                LOG<<s_machine->transaction()->SlotIdList.at(k)<<s_machine->transaction()->QuantityList.at(k)<<"wwwwww";
//            }
//        }else{
//            Message->setText(QString("Nhập số lượng > 0 và <= %1!").arg(s_machine->GetGoodQuatity(select)));
//        }
//    }else{
//        Message->setText("Nhập số lượng sản phẩm không hợp lệ!");
//    }

//    if(s_machine->transaction()->SlotIdList.size() != 0){
//        s_machine->transaction()->Quantity = quantity;
//        emit Signal_Menu_Good_General(MACHINE_STATE::SELECT_CHARGE_TYPE);
//    }

//    if(s_machine->transaction()->SlotId == ""){
//        Message->setText("Chọn sản phẩm thất bại. Sản phẩm đang cài sai số lượng!");
//    }else if(!ok){
//        Message->setText("Nhập số lượng sản phẩm không hợp lệ!");
//    }else if(quantity == 0 || quantity > s_machine->GetGoodQuatity(select)){
//        Message->setText(QString("Nhập số lượng > 0 và <= %1!").arg(s_machine->GetGoodQuatity(select)));
//    }else{
//        s_machine->transaction()->Quantity = quantity;
//        LOG<<quantity<<"số lượng sản phẩm";
//        emit Signal_Menu_Good_General(MACHINE_STATE::SELECT_CHARGE_TYPE);
//    }
//    if(s_machine->transaction()->SlotId != ""){
//        emit Signal_Menu_Good_General(MACHINE_STATE::SELECT_CHARGE_TYPE);
//        if(s_machine->transaction()->AvailableAmount >= s_machine->getGoodPriceInMenuGeneralTable(select)){

//            emit Signal_Menu_Good_General(MACHINE_STATE::GET_GOOD_GENERAL);
//        }else{
//            emit Signal_Menu_Good_General(MACHINE_STATE::SELECT_CHARGE_TYPE);
//        }
//    }else{
//        Message->setText("Chọn sản phẩm thất bại. Sản phẩm đang cài sai số lượng!");
//    }
  //  LOG<<Select_Good<<"mã sản phẩm";
}

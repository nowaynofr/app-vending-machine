#include "testform.h"
#include "Machine/machine.h"
#include "my_qlabel.h"
#include "ui_testform.h"

testform::testform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::testform)
{
    ui->setupUi(this);
}
testform::testform(Machine *m, QString directory)
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

    QGroupBox *NumberPhoneGroup = new QGroupBox(tr(""));
    NumberPhoneGroup->setFont(fontMenuGoodGroup);
    QHBoxLayout *HBox_Number_Phone = new QHBoxLayout;

    Message = new QLabel("",this);
    Message->setWordWrap(true);
    Message->setMaximumSize(1080, 120);
    Message->setMinimumSize(1080, 120);
    Message->setStyleSheet("QLabel { background-color : white; color : red; }");
    Message->setFrameStyle(QFrame::Box | QFrame::Sunken);
    Message->setLineWidth(2);

    QFont font1("Times",26);
    Message->setFont(font1);


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


    setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
    setLayout(mainLayout);
}

// testform::testform(Machine*m, QString directory){
//     s_machine = m;
//     DatabaseDataStoragePath = directory;
//     ListGoodIdPriority = m->ReturnListGooIdPriority();
//     LOG<<ListGoodIdPriority.size()<<"ggggg";
//     QVBoxLayout *mainLayout = new QVBoxLayout;
//     QPushButton *button = new QPushButton("click here");
//     button->setGeometry(100, 100, 120, 40);
//     QLabel* Title = new QLabel(this);
//     Title->setText("  CHỌN MẶT HÀNG CẦN MUA");
//     Title->setMaximumSize(1080, 120);
//     QFont fontTitle("Times",32);
//     fontTitle.setStyleHint(QFont::Monospace);
//     Title->setFont(fontTitle);
//     Title->setStyleSheet("QLabel { background-color : yellow; color : black; }");
//     Title->setFrameStyle(QFrame::Box | QFrame::Sunken);
//     Title->setLineWidth(2);
//     Title->setAlignment(Qt::AlignLeft);

//     QFont fontMenuGoodGroup("Arial",26);
//     QGroupBox* ListMenuGoodGroup = new QGroupBox(tr(""));
//     ListMenuGoodGroup->setAlignment(Qt::AlignCenter);
//     grid = new QGridLayout();
//     qint8 row = 0;
//     for (int i = 0; i < ListGoodIdPriority.size(); i++){
//         QImage image(DatabaseDataStoragePath + "/" + ListGoodIdPriority.at(i) +".png");
//         if(image.isNull()){
//             image.load(":/img/NoGoodImage.png");
//         }
//         QString goodInfo = m_db.getGoodNameInMenuGeneralTable(ListGoodIdPriority.at(i)) + "\n" +
//                            StringUtils::formatNumberVND(m_db.getGoodPriceInMenuGeneralTable(ListGoodIdPriority.at(i)).toInt()) + " VND";
//         menu[i] = new my_qlabel(ListGoodIdPriority.at(i),image,goodInfo);
//         menu[i]->setStyleSheet("border: 3px solid black; border-radius: 25px; background: white;");
//         menu[i]->setMaximumSize(320,270);
//         menu[i]->setMinimumSize(320,270);
//         if(i%3 == 0){
//             row++;
//         }
//         grid->addWidget(menu[i], row, i%3);
//         grid->setColumnMinimumWidth(i,50);
//         grid->setRowMinimumHeight(i,50);
//         grid->setColumnStretch(i,50);
//         grid->setRowStretch(i,50);
//         grid->setAlignment(Qt::AlignCenter);
//     }
//     ListMenuGoodGroup->setLayout(grid);
//     ListMenuGoodGroup->setMinimumWidth(1020);
//     ListMenuGoodGroup->setMinimumHeight(1600);

//     QLabel* home = new my_qlabel("",this);
//     home->setAlignment(Qt::AlignCenter);
//     home->setGeometry(960,1800,110,110);
//     home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
//     QImage img(":/img/Button_Image/Home_Btn.jpg");
//     home->setPixmap(QPixmap::fromImage(img));
//     mainLayout->addWidget(Title);
//     mainLayout->addWidget(ScrollAreaMenu);

//     mainLayout->addWidget(Message);
//     //  mainLayout->addWidget(Gr_Ok_Back);

//     setStyleSheet("QGroupBox { color: green; background-color: orange;qproperty-alignment: AlignCenter;}");
//     setLayout(mainLayout);
// }

testform::~testform()
{
    delete ui;
}



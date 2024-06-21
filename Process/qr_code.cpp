#include "qr_code.h"
#include "ui_qr_code.h"
#include <qrcode/QrCode.h>
using namespace qrcodegen;
QR_code::QR_code(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QR_code)
{
    ui->setupUi(this);
}

QR_code::QR_code(QString qrcode,quint8 chargetype)
{
    LOG;
    QRCode = qrcode;
    ImageQR_Name = m_db.getValueKioskAdmin("ChargeTypeImageName", QString::number(chargetype));
    QLabel* Image_Sab = new QLabel(this);
    Image_Sab->setFrameShape(QFrame::Box);
    QPixmap pix(":/img/S&B.png");
    Image_Sab->setPixmap(pix);

//    QLabel* Image_QR = new QLabel(this);
//    Image_QR->setFrameShape(QFrame::Box);
//    Image_QR->setGeometry(140,710,800,480);
//    QImage image(":/img/qrimage/background_qr.jpg");
//    QPixmap pixQR(":/img/qrimage/background_qr.jpg");
//    Image_QR->setPixmap(QPixmap::fromImage(image));

    btn_Back = new PushButton_OK_BACK("Back", this);
    connect(btn_Back, SIGNAL(clicked()),this, SLOT(on_Btn_Back_QRcode_clicked()));
    btn_Back->setGeometry(390,1700,300,90);

//    QLabel* home = new my_qlabel("",this);
//    home->setGeometry(960,450,110,110);
//    home->setStyleSheet("border: 3px solid black; border-radius: 15px; background: white;color: red;");
//    QImage img(":/img/Button_Image/Home_Btn.jpg");
//    home->setPixmap(QPixmap::fromImage(img));
//    connect(home, SIGNAL(home_network(QString)),this, SLOT(Back_Home(QString)));

    this->setStyleSheet("color: green; background-color: orange;");
}

QR_code::~QR_code()
{
    delete ui;
}

void QR_code::SetImage()
{

}

void QR_code::paintEvent(QPaintEvent *)
{
    LOG<<"vẽ QR";
    if(QRCode != ""){
        QPainter painter_imageQR(this);
        QImage image;
        QString path = ":/img/qrimage/" + ImageQR_Name;
        image.load(path);
//        if(ChargeType == KioskTransactionType::QRPAY){
//             image.load(":/img/qrimage/background_qr.jpg");
//        }else if(ChargeType == KioskTransactionType::MOMO){
//             image.load(":/img/qrimage/background_momo.jpg");
//        }else if(ChargeType == KioskTransactionType::VINID){
//             image.load(":/img/qrimage/background_vinid.jpg");
//        }else if(ChargeType == KioskTransactionType::GRABPAY){
//             image.load(":/img/qrimage/background_grabpay.jpg");
//        }else if(ChargeType == KioskTransactionType::ZALOPAY){
//             image.load(":/img/qrimage/background_zalopay.jpg");
//        }
        LOG <<image.width() << image.height();
        painter_imageQR.drawImage(QRect(140,710,800,480),image);

        QPainter painter(this);
        QrCode qr = QrCode::encodeText(QRCode.toUtf8().data(), QrCode::Ecc::MEDIUM);
        LOG << QRCode<<"mã QR";
        const int s=qr.size>0?qr.size:1;
        const double w=320;
        const double h=320;
        const double aspect=w/h;
        const double size=((aspect>1.0)?h:w);
        const double scale=size/(s+2);
        // NOTE: For performance reasons my implementation only draws the foreground parts in supplied color.
        // It expects background to be prepared already (in white or whatever is preferred).
        painter.setPen(Qt::black);
        painter.setBrush( QBrush( Qt::black, Qt::BDiagPattern ) );
        painter.fillRect(380,800,320,320,QBrush( Qt::white));
        for(int y=0; y<s; y++) {
            for(int x=0; x<s; x++) {
                const int color=qr.getModule(x, y);  // 0 for white, 1 for black
                if(0!=color) {
                    //                qDebug() << x << " - "<< y;
                    const double rx1=(x+1)*scale, ry1=(y+1)*scale;
                    QRectF r(380+rx1, 800+ry1, scale, scale);
                    painter.fillRect(r,QBrush( Qt::black));
                }
            }
        }
    }else{
        QPainter painter_imageQR(this);
        QImage image;
        QString path = ":/img/qrimage/" + ImageQR_Name;
        image.load(path);
//        if(ChargeType == KioskTransactionType::QRPAY){
//             image.load(":/img/qrimage/background_qr.jpg");
//        }else if(ChargeType == KioskTransactionType::MOMO){
//             image.load(":/img/qrimage/background_momo.jpg");
//        }else if(ChargeType == KioskTransactionType::VINID){
//             image.load(":/img/qrimage/background_vinid.jpg");
//        }else if(ChargeType == KioskTransactionType::GRABPAY){
//             image.load(":/img/qrimage/background_grabpay.jpg");
//        }else if(ChargeType == KioskTransactionType::ZALOPAY){
//             image.load(":/img/qrimage/background_zalopay.jpg");
//        }
        LOG <<image.width() << image.height();
        painter_imageQR.drawImage(QRect(140,710,800,480),image);

        QPainter painter(this);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Roboto",17));
        painter.drawText(
                    QRect(385, 950, 800, 100),
                    Qt::AlignLeft | Qt::TextWordWrap,
                    "Dịch vụ chưa hỗ trợ!");

    }
}

void QR_code::aaa()
{
    LOG<<"aaaaa";
    this->update();
}

void QR_code::Back_Home(QString)
{
    emit Signal_QR_Code(MENU);
}

void QR_code::on_Btn_Ok_QRcode_clicked()
{

}

void QR_code::on_Btn_Back_QRcode_clicked()
{
    emit Signal_QR_Code(SELECT_CHARGE_TYPE);
}

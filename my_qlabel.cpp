#include "my_qlabel.h"

my_qlabel::my_qlabel(QString string,QWidget *parent):
    QLabel(parent)
{
   // this->setStyleSheet("QLabel { border: 3px solid black; border-radius: 15px; background: gray;color: red;}");
    Key_MenuGood = "";
    text_label = string;
}

my_qlabel::my_qlabel(QString goodId, QImage image, QString goodName)
{
    Key_MenuGood = "menu_good_general";
    text_label = goodId;
    goodImage = image;
    good_Name = goodName;
}

my_qlabel::my_qlabel(quint32 price, quint8 index)
{
    Key_MenuGood = "";
    Price = price;
    Index = index;
}

void my_qlabel::mousePressEvent(QMouseEvent *ev)
{
    emit home_network(text_label);
    emit price(Price,Index);
}
void my_qlabel::paintEvent(QPaintEvent *event)
{
    if(Key_MenuGood == "menu_good_general"){
        QLabel::paintEvent(event);

         // Draw the image
        QPainter painter(this);
        int x = (this->width() - goodImage.width())/2;
       // int y = this->height() - img.height();
        painter.drawImage(QPoint(x, 5), goodImage);

        painter.setPen(QPen(Qt::yellow, 2, Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(5, (this->height() * 2)/3 + 10, this->width() - 5, (this->height() * 2)/3 + 10);

        QFont fontGood("Helvetica [Cronyx]",12, QFont::Bold);
        //fontGood.setStyleHint(QFont::Monospace);
        painter.setFont(fontGood);
        painter.setPen(Qt::black);
        painter.drawText(1,(this->height() * 2)/3 + 15,this->width(), this->height()/3 - 15, Qt::AlignCenter | Qt::AlignTop | Qt:: TextWordWrap, good_Name);
    }else{
        QLabel::paintEvent(event);
    }

}

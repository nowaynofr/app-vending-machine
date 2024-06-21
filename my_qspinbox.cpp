#include "my_qspinbox.h"
#include "QLineEdit"

my_qspinbox::my_qspinbox(QString lb_text,int value, QWidget *parent)
{
    spb_value = value;
    QHBoxLayout *spinbox = new QHBoxLayout;
    QLabel *icon = new QLabel(this);
    icon->setScaledContents(true);
    icon->setText(lb_text);
//    icon->setMinimumSize(80,120);
//    icon->setMaximumSize(80,120);
    icon->setStyleSheet("QLabel { background-color : gray; color : red; }");

    QFont font22("Arial",22);
    spinBox = new QSpinBox(this);
    spinBox->setFont(font22);
    spinBox->setValue(value);
    if(lb_text.startsWith("Số giao dịch")){
        spinBox->setRange(1, 9999999);
    }else{
        spinBox->setRange(0, 999);
        connect(spinBox, &QSpinBox::textChanged, this, &my_qspinbox::onSpinBoxValueChanged,Qt::QueuedConnection);
    }
  //  connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)), Qt::QueuedConnection);
  //  spinBox -> findChild <QLineEdit*>()-> setReadOnly ( true ) ;
//    spinBox->setMinimumSize(100,120);
//    spinBox->setMaximumSize(100,120);
    QPalette palspin = spinBox->palette();
    spinBox->setStyleSheet("QSpinBox { border: 2px solid red; border-radius: 5px; background-color: yellow;color:green; }"
                           "QSpinBox::up-arrow { border-left: 17px solid none;"
                           "border-right: 17px solid none; border-bottom: 17px solid black; width: 0px; height: 0px; }"
                           "QSpinBox::up-arrow:hover { border-left: 17px solid none;"
                           "border-right: 17px solid none; border-bottom: 17px solid black; width: 0px; height: 0px; }"
                           "QSpinBox::up-button { width: 40px; height: 40px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.25 "+getRGBhexColor(palspin.light().color())+", stop: 1 "+getRGBhexColor(palspin.midlight().color())+") }"
                           "QSpinBox::up-button:hover { width: 40px; height: 40px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.25 "+getRGBhexColor(palspin.light().color())+", stop: 1 "+getRGBhexColor(palspin.shadow().color())+") }"

                           "QSpinBox::down-arrow { border-left: 17px solid none;"
                           "border-right: 17px solid none; border-top: 17px solid black; width: 0px; height: 0px; }"
                           "QSpinBox::down-arrow:hover { border-left: 17px solid none;"
                           "border-right: 17px solid none; border-top: 17px solid black; width: 0px; height: 0px; }"
                           "QSpinBox::down-button { width: 40px; height: 40px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.25 "+getRGBhexColor(palspin.light().color())+", stop: 1 "+getRGBhexColor(palspin.midlight().color())+") }"
                           "QSpinBox::down-button:hover { width: 40px; height: 40px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.25 "+getRGBhexColor(palspin.light().color())+", stop: 1 "+getRGBhexColor(palspin.shadow().color())+") }"
    );

   // line_edit->addSpacing(100);
    spinbox->addWidget(icon);
    spinbox->addWidget(spinBox);
    spinbox->setSpacing(0);
    spinbox->setAlignment(Qt::AlignCenter);

    this->setAlignment(Qt::AlignCenter);
//    this->setMaximumSize(190,130);
//    this->setMinimumSize(190,130);

    if(lb_text.startsWith("Khay")){
        icon->setMinimumSize(100,140);
        icon->setMaximumSize(100,140);
        spinBox->setMinimumSize(120,140);
        spinBox->setMaximumSize(120,140);
        this->setMaximumSize(240,160);
        this->setMinimumSize(240,160);
    }else if(lb_text.contains("Số lượng")){
        QFont font("Arial",22);
        icon->setFont(font);
        icon->setMinimumSize(200,110);
        icon->setMaximumSize(200,110);
        spinBox->setMinimumSize(150,110);
        spinBox->setMaximumSize(150,110);
        this->setMaximumSize(370,130);
        this->setMinimumSize(370,130);
    }else if(lb_text.startsWith("Số giao dịch")){
        QFont font("Arial",22);
        icon->setFont(font);
        icon->setWordWrap(true);
        icon->setMinimumSize(200,110);
        icon->setMaximumSize(200,110);
        spinBox->setMinimumSize(150,110);
        spinBox->setMaximumSize(150,110);
        this->setMaximumSize(370,130);
        this->setMinimumSize(370,130);
    }
    else{
        icon->setMinimumSize(80,120);
        icon->setMaximumSize(80,120);
        spinBox->setMinimumSize(100,120);
        spinBox->setMaximumSize(100,120);
        this->setMaximumSize(200,140);
        this->setMinimumSize(200,140);
    }

    //this->setStyleSheet("background-color: gray;border: 2px solid blue; border-radius: 5px");
    setLayout(spinbox);
}

int my_qspinbox::GetQSpinBoxValue()
{
    return spinBox->value();
}

QString my_qspinbox::getRGBhexColor(const QColor color)
{
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

bool my_qspinbox::IsValueChanged()
{
    if(spb_value != spinBox->value()){
        return true;
    }else{
        return false;
    }
}

int my_qspinbox::ValueChanged()
{
    return spinBox->value() - spb_value;
}

void my_qspinbox::onSpinBoxValueChanged()
{
    spinBox->findChild<QLineEdit*>()->deselect();
}


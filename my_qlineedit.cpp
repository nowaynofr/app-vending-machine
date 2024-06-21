#include "my_qlineedit.h"


my_qlineedit::my_qlineedit(QString urlIcon,QString context, QWidget *parent)
{
    QHBoxLayout *line_edit = new QHBoxLayout;
    QLabel *icon = new QLabel(this);
    icon->setScaledContents(true);
    QImage image(urlIcon);
    icon->setPixmap(QPixmap::fromImage(image));
    icon->setMinimumSize(120,120);
    icon->setMaximumSize(120,120);

    QFont font22("Arial",22);
    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(context);
    lineEdit->setFont(font22);
    lineEdit->setStyleSheet("color: black; background-color: yellow;border: 2px solid blue; border-radius: 10px");

    lineEdit->setMaximumSize(700,120);
    lineEdit->setMinimumSize(700,120);

   // line_edit->addSpacing(100);
    line_edit->addWidget(icon);
    line_edit->addWidget(lineEdit);
    line_edit->setSpacing(0);
    line_edit->setAlignment(Qt::AlignCenter);

    this->setAlignment(Qt::AlignCenter);
    this->setMaximumSize(840,140);
    this->setMinimumSize(840,140);
    this->setStyleSheet("background-color: gray;border: 2px solid blue; border-radius: 10px");
    setLayout(line_edit);
}

QString my_qlineedit::GetLineEditContent()
{
    return lineEdit->text();
}

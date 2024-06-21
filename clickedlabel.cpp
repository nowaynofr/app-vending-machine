#include "clickedlabel.h"

ClickedLabel::ClickedLabel()
{

}
void ClickedLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

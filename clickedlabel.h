#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H


#include <QWidget>
#include <QLabel>

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent=0): QLabel(parent){}
    ~ClickedLabel() {}
signals:
    void clicked(ClickedLabel* click);
protected:
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // CLICKEDLABEL_H

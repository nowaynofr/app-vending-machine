#ifndef DIALOG_ADMIN_H
#define DIALOG_ADMIN_H

#include <QDialog>
#include <QAndroidJniObject>
#include <QtAndroidExtras>
namespace Ui {
class Dialog_Admin;
}

class Dialog_Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Admin(QWidget *parent = nullptr);
    ~Dialog_Admin();
    QString PassAdmin;
    void ResetNewDialog();
signals:
    void AdminProcess();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_Admin *ui;
};

#endif // DIALOG_ADMIN_H

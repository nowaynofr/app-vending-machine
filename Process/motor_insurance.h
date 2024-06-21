#ifndef MOTOR_INSURANCE_H
#define MOTOR_INSURANCE_H

#include <QWidget>
#include "Transaction/machine_state.h"
#include "Machine/machine.h"
#include "my_qlabel.h"
#include "my_qlineedit.h"
#include "Transaction/stringutils.h"
namespace Ui {
class motor_insurance;
}

class motor_insurance : public QWidget
{
    Q_OBJECT

public:
    explicit motor_insurance(QWidget *parent = nullptr);
    motor_insurance(Machine*);
    ~motor_insurance();
    QString GetOwnerOfMotorInfo();
    QString getDurationOfInsurance();
signals:
    void Signal_MotorInsurance(MACHINE_STATE);
private slots:
   // void Back_Home(QString);
    void PriceChange(int);
    void on_Btn_Ok_MotorInsurance_clicked();
    void on_Btn_Back_MotorInsurance_clicked();
private:
    Ui::motor_insurance *ui;
    Machine *s_machine;
  //  QString goodId;
    QLabel *price;

    QString OwnerName;
    QString OwnerPhoneNumber;
    QString OwnerAddress;
    QString OwnerMail;
    QString OwnerId;
    QString LicensePlate;
    QString OwnerBirth;
    QString DurationOfInsurance;
 //   quint32 InsurancePrice;
    QString MotorType;

    my_qlineedit *name;
    my_qlineedit *phone_number;
    my_qlineedit *address;
    my_qlineedit *email;
    my_qlineedit *id;
    my_qlineedit *license_plate;
    QDateEdit *birth;
    QComboBox * duration;
    QComboBox * motor_type;
    QPushButton *btn_Back;
    QPushButton *btn_Ok;
    QLabel *Message;
};

#endif // MOTOR_INSURANCE_H

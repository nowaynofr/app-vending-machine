//#ifdef BILLVALIDATOR_H
#include "billvalidator.h"
#include "Transaction/log.h"

BillValidator::BillValidator(QObject *parent)
    : QObject(parent)
    , waitTimeout(1000)
    , stopThread(false)
    ,CheckIdentifiedAmount(false)
    ,CheckSendResponse(true)
    , m_mode(INIT)
    , m_retry(0)
    , amount(0)
    ,preStatus("")
    ,currentStatus("")


{
    LOG;
   // config.loadListBillAmount();
    moveToThread(&m_thread);
    connect(&m_thread, SIGNAL(started()), this, SLOT(run()));

}

BillValidator::~BillValidator()
{
    LOG;
    stop();
}

void BillValidator::setup(const QString portName, int baudrate)
{
    m_serial.moveToThread(&m_thread);
    m_serial.setPortName(portName);
    m_serial.setBaudRate(baudrate);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);
    m_serial.setStopBits(QSerialPort::OneStop);

}

void BillValidator::start()
{
    LOG ;
    stopThread = false;
    m_thread.start();
}

void BillValidator::stop()
{
    LOG;
    stopThread = true;
    m_thread.wait();      // if you want synchronous stop
}

bool BillValidator::check_open()
{

    return m_serial.isOpen();
   // LOG<< m_serial.isOpen()<<"hhhhhh";
}

QByteArray BillValidator::send_wait(QByteArray data, bool &ok)
{
    ok = check_open();
    if (ok)
    {
        ok = false;
        // send command

       // LOG << "write start";
        m_serial.write(data);
        // wait response for timeout
        if (m_serial.waitForBytesWritten(waitTimeout)) {
            if (m_serial.waitForReadyRead(4*waitTimeout)) {

                QByteArray responseData = m_serial.readAll();
                while (m_serial.waitForReadyRead(10))
                    responseData += m_serial.readAll();
                ok = true;
                if (m_retry > 0) m_retry --;
                return responseData;
            } else {
                emit timeout(tr("Wait read response timeout %1")
                             .arg(QTime::currentTime().toString()));
                m_retry++;
                if (m_retry == 5) {
                    m_mode = INIT;
                    return "";

                }
                LOG << "OK fffg2gg"<<m_retry;
            }
        } else {
            emit timeout(tr("Wait write request timeout %1")
                         .arg(QTime::currentTime().toString()));
            m_retry++;
            if (m_retry == 5) {
                m_mode = INIT;
                return "";
            }
        LOG << "OK fffdddggg";
        }
    }
    return "";
}



void BillValidator::do_init()
{
    m_mode = INIT;
    m_retry = 0;
 //   LOG << "Bill check open!";
    if (check_open()) {
        LOG << "Bill opened, forced close!"<<check_open();
        m_serial.close();
    }

    QThread::msleep(1000);
//    LOG << "Bill start open!";
    if (!m_serial.open(QIODevice::ReadWrite)) {
//        LOG << "Cant open device, sleep for 3s. Reason:" << m_serial.errorString();
        QThread::msleep(3000);
        return ;
    }
    LOG << "Bill send init command!";
    // send init command
    bool ok = false;
    QByteArray response = send_wait(QByteArray::fromHex(BILL_COMMAND_INIT),ok);
    if (ok) {
        LOG << "Bill init:oke" << response.toHex();
        amount = 0;
        m_mode = QUERY;
    }
    LOG << "Bill init:" << response.toHex()<<ok;
    QThread::msleep(1000);
    return;
}


void BillValidator::do_query()
{
    bool ok = false;
    QByteArray response = send_wait(QByteArray::fromHex(BILL_COMMAND_STATUS),ok);
    ResponseBill = response.toHex();
    emit bill_response(ResponseBill);
   // LOG << "Bill status:" << response.toHex();
    m_mode = QUERY;
    if ( ok ) {
        if (response.startsWith(QByteArray::fromHex(BILL_STATUS_BUSY))) {
            if(CheckIdentifiedAmount){
                emit bill_unAccepted(get_bill_amount());
                CheckIdentifiedAmount = false;
            }
            m_retry++;
            m_retry++;
            if (m_retry == 9) {
                LOG << "Reset bill kkkkkk"<<m_retry;
                m_mode = INIT;
                return;
            }
        } else if (response.startsWith(QByteArray::fromHex(BILL_STATUS_REJECTED))) {
            if(CheckIdentifiedAmount){
                emit bill_unAccepted(get_bill_amount());
                CheckIdentifiedAmount = false;
            }
            emit bill_error(QString::number(11));
            m_bill_type = -1;
        } else if (response.startsWith(QByteArray::fromHex(BILL_RESPONSE_ACK))) {
            if(CheckIdentifiedAmount){
                emit bill_unAccepted(get_bill_amount());
                CheckIdentifiedAmount = false;
            }
            preStatus = response.toHex();
        }else if(response.toHex().length() == 4){
            if(CheckIdentifiedAmount){
                emit bill_unAccepted(get_bill_amount());
                CheckIdentifiedAmount = false;
            }
            emit bill_error(QString(response.toHex()));
            emit bill_status(QString(response.toHex()));
        }
        else {
            char z1 = response.at(0);
            LOG << "Response value:eeeeee" << response.toHex() <<(int) z1;
            if (z1 >= 0x80 && z1 < 0x90) {
                m_bill_type = z1 & 0x0f;
                amount = get_bill_amount();
                LOG << "Bill stacked value:rrrrrr" << m_bill_type<< "total amount:" << amount;
                if (amount > 0 && amount <= 200000){
                    emit bill_accepted(get_bill_amount());
                    m_retry = 0;
                    CheckIdentifiedAmount = false;
                }
            } else if (z1 >= 0x90 && z1 < 0xa0) {
                LOG << "Bill escrow position:tttttt" << (int) (z1 & 0x0f);
                m_bill_type = z1 & 0x0f;
                amount = get_bill_amount();
                LOG << "Bill escrow value:yyyyyy" << m_bill_type<< "total amount:" << amount;
                if (amount > 0 && amount <= 200000){
                    CheckIdentifiedAmount = true;
                    emit bill_identified(get_bill_amount());

                }
                response = send_wait(QByteArray::fromHex(BILL_COMMAND_STACKED),ok);
                if (ok)
                    LOG << "Bill send stacked:uuuuuu" <<response.toHex();
                    QThread::msleep(1000);

            } else {

                for(int i = 0; i < config.listReponseBill.size(); i++){
                    QString responseBill = response.toHex();
                    if (responseBill.contains(config.listReponseBill.at(i))){
                        emit bill_accepted(config.listAmountResponseBill.at(i).toDouble());
                        CheckIdentifiedAmount = false;
                        CheckSendResponse = false;
                    }
                }
                currentStatus = response.toHex();
                if(currentStatus !=  preStatus){
                    emit bill_error(currentStatus);
                    preStatus = currentStatus;
                    if(CheckSendResponse)
                        emit bill_status(currentStatus);
                    CheckSendResponse = true;
                }
                if(CheckIdentifiedAmount){
                    emit bill_unAccepted(get_bill_amount());
                    CheckIdentifiedAmount = false;
                }

            }
            //V1.2 Kết thúc
        }
    }
}

double BillValidator::get_bill_amount()
{
    switch (m_bill_type) {
    case 0:
        return 1000;
    case 1:
        return 2000;
    case 2:
        return 5000;
    case 3:
        return 10000;
    case 4:
        return 20000;
    case 5:
        return 50000;
    case 6:
        return 100000;
    case 7:
        return 200000;
    default:
        return 0;
    }
}

void BillValidator::run()
{
    LOG<<config.listAmountResponseBill<<config.listReponseBill<<"danh sách giá trị phản hồi Bill";
    while (!stopThread ) {
        switch(m_mode)
        {
        case INIT:
            do_init();
            break;
        case QUERY:
            do_query();
            break;
        default:
            break;
        }
        QThread::msleep(10);
    }
    LOG << "Bill end";
}
//#endif // BILLVALIDATOR_H

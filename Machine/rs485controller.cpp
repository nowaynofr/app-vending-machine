//#ifdef RS485CONTROLLER_H
#include "rs485controller.h"
#include "Transaction/log.h"
#include <QThread>
//#ifdef __WIRING_PI_H__
//#include <wiringPi.h>
//#endif
RS485Controller::RS485Controller(QObject *parent)
    : QObject(parent)
    , waitTimeout(100)
    , stopThread(false)
    , CheckScan(true)
    , CheckReturnGood(false)
    , m_mode(SCAN)
    , m_slotId(0)
    , m_count(0)
    , m_status(this)

{
    LOG;
    quantity_list.clear();
    slot_id_list.clear();
    moveToThread(&m_thread);
    connect(&m_thread, SIGNAL(started()), this, SLOT(run()));

}

RS485Controller::~RS485Controller()
{
    LOG;
    stop();
}

void RS485Controller::setup(const QString portName, const quint32 baudrate)
{
//#ifdef __WIRING_PI_H__
//    pinMode(SENSOR_CONTROL, OUTPUT); // system("gpio mode 42 out");
//    digitalWrite(SENSOR_CONTROL, LOW); // system("gpio write 42 0");
//#endif
    m_serial.moveToThread(&m_thread);
    //    connect(&m_serial, SIGNAL(error(QSerialPort::SerialPortError)),
    //            this, SLOT(handleError(QSerialPort::SerialPortError)));
    m_serial.setPortName(portName);
    m_serial.setBaudRate(baudrate);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);
    m_serial.setStopBits(QSerialPort::OneStop);

}

void RS485Controller::start()
{
    LOG ;
    stopThread = false;
    m_thread.start();
}

void RS485Controller::stop()
{
    LOG;
    stopThread = true;
    m_thread.wait();      // if you want synchronous stop
}

bool RS485Controller::check_open()
{
    return m_serial.isOpen();
}

QByteArray RS485Controller::send_wait(QByteArray data, bool &ok)
{
    ok = check_open();
    if (ok)
    {
        ok = false;
        // send command

//                LOG << "write start" << data.toHex();
     //   digitalWrite(SENSOR_CONTROL, LOW);
      //  delay(waitTimeout);
        m_serial.write(data);

        //        // wait response for timeout
        if (m_serial.waitForBytesWritten(waitTimeout*2)) {
            //delay(waitTimeout);
            //digitalWrite(SENSOR_CONTROL, HIGH);
            QThread::msleep(100);
            //delay(waitTimeout);
            //            LOG << "write ok";
            // read response
          //  emit status("ghi ok");
            if (m_serial.waitForReadyRead(waitTimeout*4)) {
                //LOG << "read ok";
                QByteArray responseData = m_serial.readAll();
                while (m_serial.waitForReadyRead(10))
                    responseData += m_serial.readAll();
                ok = true;
//                LOG << "OK" << responseData.toHex();
                //                digitalWrite(SENSOR_CONTROL, LOW);
               // emit status(responseData.toHex()+ " đọc oke");
                return responseData;
            } else {
                //                LOG << "Wait read response timeout ";
                //                             .arg(QTime::currentTime().toString()));
            }
        } else {
            //            LOG << "Wait read response timeout ";
            //            emit timeout(tr("Wait write request timeout %1")
            //                         .arg(QTime::currentTime().toString()));
        }
        //        digitalWrite(SENSOR_CONTROL, LOW);
    }
    return "";
}

void RS485Controller::run()
{
    if (!m_serial.open(QIODevice::ReadWrite)) {
        LOG << m_serial.errorString();
       // emit status(m_serial.errorString() + "-lỗi mở cổng");
        return ;
    }
    LOG << "Sensor network start!";
    char sensor_address = 0;
    bool ok = false;
    QByteArray response ;
    QByteArray data;

   // bool isHigh = true;
    int index = 0;

    int indexListReturnGood = 0;

    while (!stopThread) {
        if(CheckReturnGood){
            m_mode = RETURN_GOODS;
            m_slotId = slot_id_list.at(indexListReturnGood);
            m_count  = quantity_list.at(indexListReturnGood);
            LOG<<m_slotId<<m_count<<indexListReturnGood<<"eeeeee";
            indexListReturnGood++;
            if(!slot_id_list.isEmpty()){
                if(indexListReturnGood == slot_id_list.size()){
                    CheckReturnGood = false;
                    indexListReturnGood = 0;
                }
            }

        }
        switch(m_mode){
        case SCAN:
        {
            //char add = (char) isHigh? sensor_address : sensor_address << 4;
            m_nodes.clear();
            for (sensor_address = 0; sensor_address < 16; sensor_address ++)
            {
                data.resize(0);
                data.append(SENSOR_COMMAND_START);
                data.append(sensor_address);
                data.append(SENSOR_COMMAND_QUERY);
                data.append((char)SENSOR_COMMAND_QUERY_LENGTH);
                data.append(SENSOR_COMMAND_STOP);
                response = send_wait(data,ok);
                if (ok) {
                    LOG << "add high" << sensor_address<<QString(sensor_address)<<int(sensor_address);
                    if(int(sensor_address) != 8)
                        m_nodes.append(sensor_address);
                }

            }
//            for (sensor_address = 0; sensor_address < 16; sensor_address ++)
//            {
//                data.resize(0);
//                data.append(SENSOR_COMMAND_START);
//                data.append(sensor_address << 4);
//                data.append(SENSOR_COMMAND_QUERY);
//                data.append((char)SENSOR_COMMAND_QUERY_LENGTH);
//                data.append(SENSOR_COMMAND_STOP);
//                response = send_wait(data,ok);
//                if (ok) {
//                    LOG << "add low" << sensor_address << 4<<QString(sensor_address<< 4)<<int(sensor_address<< 4);
//                    m_nodes.append(sensor_address << 4);
//                }
//            }
            CheckScan = false;

            m_mode = QUERY;
            index = 0;

            break;
        }
        case QUERY:
        {
           // emit status(QString::number(m_nodes.length()) + "-số id slave");
            if(m_nodes.length() > 0){
                char add = m_nodes.at(index);//(char) isHigh? sensor_address : sensor_address << 4;
                data.resize(0);
                data.append(SENSOR_COMMAND_START);
                data.append(add);
                data.append(SENSOR_COMMAND_QUERY);
                data.append((char)SENSOR_COMMAND_QUERY_LENGTH);
                data.append(SENSOR_COMMAND_STOP);
                response = send_wait(data,ok);
                if (response.length() > 0 ) {
                    if (int(response[3]) > 1) {
                        if(int(response[3]) == 16 && int(add) == 2){
                            if (m_status.updateMachineStatus(response.mid(4, response[3])))
                                emit statusChange(m_status.Json);
                          //  LOG<<m_status.Json<<"nhiệt độ";
                        }/*else{
                            if(m_status.updateRFID_Data(response.mid(4, response[3]))){
                                emit RFID_Data(m_status.Json_RFID_Data);
                            }
                        }*/
                   // LOG<<m_status.Json<<"aq123";
                    }
    //                LOG << (int)sensor_address << "Resopnse for " << (int)response[1] << "command:" << (int)response[2] << "length:" << (int)response[3]
    //                 << "Data:" << (int)response[4] << m_status.Json;

                }
                //if (ok)
                //    m_nodes.append(sensor_address);

                //sensor_address++;
                index++;
                if (index == m_nodes.length()) {
                    index = 0;
                }
             //   LOG<<"query RS485";
                QThread::msleep(500);
            }else QThread::msleep(500);

           // LOG<<"query RS485";
            break;
        }

        case RFID_MODE:
        {
           // emit status(QString::number(m_nodes.length()) + "-số id slave");
          //  if(m_nodes.length() > 0){
              //  char add = m_nodes.at(index);//(char) isHigh? sensor_address : sensor_address << 4;
                data.resize(0);
                data.append(SENSOR_COMMAND_START);
                data.append(RFID_SLAVE);
                data.append(SENSOR_COMMAND_QUERY);
                data.append((char)SENSOR_COMMAND_QUERY_LENGTH);
                data.append(SENSOR_COMMAND_STOP);
                response = send_wait(data,ok);
                if (response.length() > 0 ) {
                    if (int(response[3]) > 1) {
                        if(m_status.updateRFID_Data(response.mid(4, response[3]))){
                            emit RFID_Data(m_status.Json_RFID_Data);
                        }
                    }
    //                LOG << (int)sensor_address << "Resopnse for " << (int)response[1] << "command:" << (int)response[2] << "length:" << (int)response[3]
    //                 << "Data:" << (int)response[4] << m_status.Json;

                }
                //if (ok)
                //    m_nodes.append(sensor_address);

                //sensor_address++;
//                index++;
//                if (index == m_nodes.length()) {
//                    index = 0;
//                }
             //   LOG<<"query RS485";
                QThread::msleep(1000);
          //  }else QThread::msleep(500);

           // LOG<<"query RS485";
            break;
        }

        case RETURN_GOODS:
        {
            data.resize(0);
            data.append(SENSOR_COMMAND_START);
            data.append((char)0x00);
            data.append(SENSOR_COMMAND_RETURN_GOODS);
            data.append(SENSOR_COMMAND_RETURN_GOODS_LENGTH);
            if (m_slotId >= 10) {
                QByteArray bytes;
                bytes.resize(2);
                char low = m_slotId%10 +1;
                char high = m_slotId/10;
                data.append(high << 4 | low);
                data.append(m_count);
                //                    data.append(bytes);
            }
            data.append(SENSOR_COMMAND_STOP);
            response = send_wait(data,ok);
//            if (response.length() > 0 ) {
//                emit status(response.toHex());
//            }

            LOG << "Resopnse for" << (int)response[1] << "command:" << (int)response[2] << "length:" << (int)response[3]
            << "Data:" << response.mid(4, response[3]);
            LOG<<m_slotId<<m_count<<"nhả hàngggggggggggggg";
            //if (ok)
            //    m_nodes.append(sensor_address);
            m_slotId = 0;
            m_count = 0;
            m_mode = QUERY;
            QThread::msleep(1000);
//            stopThread = true;
            //            sensor_address++;
            //            if (sensor_address == 16)
            //                sensor_address = 0;
            //            isHigh != isHigh;
            break;
        }
        }

//    LOG << RETURN_GOODS;
    }
    LOG << "Sensor network end";
}

quint8 RS485Controller::returnGoodsForTransaction(Transaction* transaction)
{
    LOG;
    return returnGoods(transaction->SlotId.toInt(), transaction->Quantity);
}

void RS485Controller::returnGoodsForTransactionAndroid(QList<quint16> SlotIdList, QList<quint8> QuantityList)
{
    LOG<<"qqqqqqqqqqqqq";
    m_mode = RETURN_GOODS;
    slot_id_list = SlotIdList;
    quantity_list = QuantityList;
    CheckReturnGood = true;
}

quint8 RS485Controller::returnGoods(quint32 slotId, quint8 count)
{

    quint8 ret = 0;
    m_mode = RETURN_GOODS;
    m_slotId = slotId;
    m_count = count;

//    if(CheckScan){
//        CheckReturnGood = true;
//        ListReturnGood.append(m_slotId);
//        ListReturnGood.append(m_count);
//    }else{
//        CheckReturnGood = false;
//    }
    ret = count;
    LOG<<m_slotId<<m_count;
    return ret;
}


quint8 RS485Controller::testReturnGoods(quint32 slotId, quint8 count)
{
    quint8 ret = 0;
    m_mode = RETURN_GOODS;
    m_slotId = slotId;
    m_count = count;
    ret = count;
    LOG<<m_slotId<<m_count<<"test lo xo";
    return ret;
}

void RS485Controller::ConvertRFIDMode()
{
    m_mode = RFID_MODE;
}

void RS485Controller::ConvertQueryMode()
{
    m_mode = QUERY;
}

//bool RS485Controller::ReturnGoodAndroid(quint32 slotId, quint8 count)
//{
//    bool ret = true;
//    if(m_mode == RETURN_GOODS){
//        ret = false;
//    }else{
//        m_mode = RETURN_GOODS;
//        m_slotId = slotId;
//        m_count = count;
//    }
//    LOG<<m_slotId<<m_count<<"trả hàng App Android";
//    return ret;
//}
void RS485Controller::safeClose()
{
    if (m_serial.isOpen())
        m_serial.close();
}

//void RS485Controller::handleError(QSerialPort::SerialPortError error)
//{
//    if (error == QSerialPort::ResourceError) {
//        LOG << m_serial.errorString();
//        safeClose();
//    }
//}

//#endif // RS485Controller_H

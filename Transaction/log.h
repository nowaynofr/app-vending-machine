#ifndef LOG_H
#define LOG_H
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <string.h>


#define TIME QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

//#define LOG  if (qgetenv("KIOSK_DEBUG").isEmpty()); else qDebug() << __TIME__ << QThread::currentThreadId() << __FILENAME__ << __LINE__ << __FUNCTION__
#define LOG qDebug() << TIME << QThread::currentThreadId() << __FILENAME__ << __LINE__ << __PRETTY_FUNCTION__
#endif // LOG_H


#include "stringutils.h"
#include "log.h"
#include <QLocale>
#include "transaction.h"

QString StringUtils::formatVND(QString amount)
{
    QLocale locale("vi_VN");
    return locale.toString(amount.replace('.',"").toDouble(), 'f',0);
}

QString StringUtils::formatDoubleVND(double number)
{
    QLocale locale("vi_VN");
    return locale.toString(number, 'f',0);
}

QString StringUtils::formatNumberVND(int number)
{
    return formatDoubleVND((double) number);
}

QString StringUtils::formatTransactionType(int type)
{
    LOG << type;
    switch(type)
    {
    case KioskTransactionType::CASH:
        return "TT Tiền mặt";
    case KioskTransactionType::QRPAY:
        return "TT QR Pay";
    case KioskTransactionType::COUPON:
        return "TT Coupon";
    default:
        return "";
    }
}

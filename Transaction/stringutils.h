#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <QString>

class StringUtils
{
public:
    static QString formatVND(QString amount);
    static QString formatNumberVND(int number);
    static QString formatDoubleVND(double number);
    static QString formatTransactionType(int type);
};

#endif // STRINGUTILS_H

#ifndef KKMPARAMETERS_H
#define KKMPARAMETERS_H
#include "connection.h"
#include "string.h"
#include "position.h"
#include "vector"

enum documentType{
    SHIFT_OPEN = 0,
    SHIFT_CLOSE = 1,
    INSERT_CASH = 3,
    WITHDRAW_CASH =4,
    X_REPORT = 5,
    SALE = 6,
    Return = 7
};

/*
 * Класс в котором сосредоточены все параметры передаваемые в ККТ
 */
class KkmParameters
{

public:
    KkmParameters();

private:
    Connection connections_;
    std::wstring buyerAddress_;
    documentType documentType_;
    double payCashMoney_;
    double payBankCardMoney_;
    std::wstring cashierINN_;
    std::wstring cashierName_;
    std::vector<Position> position_;
};

#endif // KKMPARAMETERS_H

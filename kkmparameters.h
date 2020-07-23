#ifndef KKMPARAMETERS_H
#define KKMPARAMETERS_H
#include"connection.h"
#include"string.h"
#include"position.h"
#include"vector"
#include"enumkkm.h"
#include <codecvt>

/*
 * Класс в котором сосредоточены все параметры передаваемые в ККТ:
 * -Настройки подключения
 * -Список товарных позиций
 * -Тип и сумма оплат
 * -Данные о кассире
 * -Тип печатаемого документа
 */
class KkmParameters
{

public:
    KkmParameters();
    void setConnection(const Connection &connections);
    void setBuyerAddress(const std::wstring &buyerAddress);
    void setCheckType(CheckType checkType);
    void setPayCashMoney(double payCashMoney);
    void setPayBankCardMoney(double payBankCardMoney);
    void setCashierINN(const std::wstring &cashierINN);
    void setCashierName(const std::wstring &cashierName);
    void addPosition(const Position &position);
    void setPositionsList(const std::vector<Position> &position);
    void clearPositionsList();

    Connection getConnection() const noexcept;
    std::wstring getBuyerAddress() const noexcept;
    CheckType getCheckType() const noexcept;
    double getPayCashMoney() const noexcept;
    double getPayBankCardMoney() const noexcept;
    std::wstring getCashierINN() const noexcept;
    std::wstring getCashierName() const noexcept;
    std::vector<Position> getPositionsList() const noexcept;

private:
    Connection connections_;
    std::wstring buyerAddress_;
    CheckType checkType_;
    double payCashMoney_ = 0;
    double payBankCardMoney_ = 0;
    std::wstring cashierINN_;
    std::wstring cashierName_;
    std::vector<Position> position_;
};

#endif // KKMPARAMETERS_H

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
    void setConnection(const Connection &connections) noexcept;
    void setBuyerAddress(const std::wstring &buyerAddress) noexcept;
    void setCheckType(CheckType checkType) noexcept;
    void setPayCashMoney(double payCashMoney) noexcept;
    void setPayBankCardMoney(double payBankCardMoney) noexcept;
    void setCashierINN(const std::wstring &cashierINN) noexcept;
    void setCashierName(const std::wstring &cashierName) noexcept;
    void addPosition(const Position &position) noexcept;
    void setPositionsList(const std::vector<Position> &position) noexcept;
    void clearPositionsList() noexcept;

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

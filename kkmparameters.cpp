#include "kkmparameters.h"

KkmParameters::KkmParameters(){

}

void KkmParameters::setConnection(const Connection &connections) noexcept{
    connections_ = connections;
}

void KkmParameters::setBuyerAddress(const std::wstring &buyerAddress) noexcept{
    buyerAddress_ = buyerAddress;
}

void KkmParameters::setCheckType(CheckType checkType) noexcept{
    checkType_ = checkType;
}

void KkmParameters::setPayCashMoney(double payCashMoney) noexcept{
    payCashMoney_ = payCashMoney;
}

void KkmParameters::setPayBankCardMoney(double payBankCardMoney) noexcept{
    payBankCardMoney_ = payBankCardMoney;
}

void KkmParameters::setCashierINN(const std::wstring &cashierINN) noexcept{
    cashierINN_ = cashierINN;
}

void KkmParameters::setCashierName(const std::wstring &cashierName) noexcept{
    cashierName_ = cashierName;
}

void KkmParameters::addPosition(const Position &position) noexcept{
    position_.push_back(position);
}

void KkmParameters::setPositionsList(const std::vector<Position> &position) noexcept{
    position_ = position;
}

void KkmParameters::clearPositionsList() noexcept{
    position_.clear();
}

Connection KkmParameters::getConnection() const noexcept{
    return connections_;
}

std::wstring  KkmParameters::getBuyerAddress() const noexcept{
    return buyerAddress_;
}

CheckType KkmParameters::getCheckType() const noexcept{
    return checkType_;
}

double KkmParameters::getPayCashMoney() const noexcept{
    return payCashMoney_;
}

double KkmParameters::getPayBankCardMoney() const noexcept{
    return payBankCardMoney_;
}

std::wstring KkmParameters::getCashierINN() const noexcept{
    return cashierINN_;
}

std::wstring KkmParameters::getCashierName() const noexcept{
    return cashierName_;
}

std::vector<Position> KkmParameters::getPositionsList() const noexcept{
    return position_;
}

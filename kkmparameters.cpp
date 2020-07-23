#include "kkmparameters.h"

KkmParameters::KkmParameters(){

}

void KkmParameters::setConnection(const Connection &connections){
    connections_ = connections;
}

void KkmParameters::setBuyerAddress(const std::wstring &buyerAddress){
    buyerAddress_ = buyerAddress;
}

void KkmParameters::setCheckType(CheckType checkType){
    checkType_ = checkType;
}

void KkmParameters::setPayCashMoney(double payCashMoney){
    if(payCashMoney < 0){
        throw std::runtime_error("Сумма наличными не может быть отрицательной");
    }
    payCashMoney_ = payCashMoney;
}

void KkmParameters::setPayBankCardMoney(double payBankCardMoney){
    if(payBankCardMoney < 0){
        throw std::runtime_error("Сумма безналичными не может быть отрицательной") ;
    }
    payBankCardMoney_ = payBankCardMoney;
}

void KkmParameters::setCashierINN(const std::wstring &cashierINN){
    if(cashierINN.length()!= 10 || cashierINN.length()!=12){
        throw std::runtime_error("Неверная длина ИНН") ;
    }
    if(cashierINN.find_first_not_of(L"0123456789") != std::string::npos){
        throw std::runtime_error("Невалидный ИНН. ИНН должен содержать только цифры") ;
    }
    cashierINN_ = cashierINN;
}

void KkmParameters::setCashierName(const std::wstring &cashierName){
    cashierName_ = cashierName;
}

void KkmParameters::addPosition(const Position &position){
    position_.push_back(position);
}

void KkmParameters::setPositionsList(const std::vector<Position> &position){
    position_ = position;
}

void KkmParameters::clearPositionsList(){
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

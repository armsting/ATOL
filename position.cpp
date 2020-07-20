#include "position.h"

/*Класс в котором сохраняется вся информация о товарной позиции
*/

Position::Position(){
}


Position::Position(const std::wstring &name, double price, double quantity, VATRate vat):
    name_(name), vat_(vat){
    setPrice(price);
    setQuantity(quantity);
}

void Position::setName(const std::wstring &name){
    name_ = name;
}

void Position::setPrice(double price){
    if(price < 0){
        throw std::runtime_error("Цена у товарной позиции не может быть отрицательной");
    }
    price_ = price;
}

void Position::setQuantity(double quantity){
    if(quantity <= 0){
        throw std::runtime_error("Количество у товарной позиции не может быть >=0");
    }
    quantity_ = quantity;
}

void Position::setTax_type(VATRate vat){
    vat_ = vat;
}

std::wstring Position::getName() const noexcept{
    return name_;
}

double Position::getPrice() const noexcept{
     return price_;
}

double Position::getQuantity() const noexcept{
    return quantity_;
}

VATRate Position::getTax_type() const noexcept{
    return vat_;
}

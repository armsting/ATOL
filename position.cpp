#include "position.h"

/* ласс описывает параметры товарной позиции
*/

Position::Position(){
}


Position::Position(const std::wstring &name, double price, double quantity, VATRate vat):vat_(vat){
    setName(name);
    setPrice(price);
    setQuantity(quantity);
}

void Position::setName(const std::wstring &name){
    if(name.length() == 0){
        throw ("Имя товарной позиции не задано");
    }
    name_ = name;
}

void Position::setPrice(double price){
    if(price < 0){
        throw ("Цена товарной позиции не может быть отрицательной");
    }
    price_ = price;
}

void Position::setQuantity(double quantity){
    if(quantity <= 0){
        throw ("Количество у товарной позиции не может быть <=0");
    }
    quantity_ = quantity;
}

void Position::setTax_type(VATRate vat) noexcept{
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

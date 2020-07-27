#include "position.h"

/* ласс описывает параметры товарной позиции
*/

Position::Position(){
}


Position::Position(const std::wstring &name, double price, double quantity, VATRate vat) noexcept :vat_(vat), name_(name) {
    setPrice(price);
    setQuantity(quantity);
}

void Position::setName(const std::wstring &name) noexcept{
    name_ = name;
}

void Position::setPrice(double price) noexcept{
    if(price < 0){
        throw ("÷ена товарной позиции не может быть отрицательной");
    }
    price_ = price;
}

void Position::setQuantity(double quantity) noexcept{
    if(quantity <= 0){
        throw (" оличество у товарной позиции не может быть >=0");
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

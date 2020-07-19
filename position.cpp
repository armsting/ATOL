#include "position.h"

/*Класс в котором сохраняется вся информация о товарной позиции
*/

Position::Position(){
}


Position::Position(const std::wstring &name, const double &price, const double &quantity, tax_type vat):
    name_(name), price_(price), quantity_(quantity), vat_(vat){
}


void Position::setName(const std::wstring &name){
    name_ = name;
}

void Position::setPrice(const double &price){
    price_ = price;
}

void Position::setQuantity(const double &quantity){
    quantity_ = quantity;
}

void Position::setTax_type(tax_type vat){
    vat_ = vat;
}

std::wstring Position::getName(){
    return name_;
}

double Position::getPrice(){
     return price_;
}

double Position::getQuantity(){
    return quantity_;
}

tax_type Position::getTax_type(){
    return vat_;
}

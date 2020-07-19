#include "position.h"

/*Класс в котором сохраняется вся информация о товарной позиции
*/

Position::Position()
{
    name = L"";
    price = 0;
    quantity = 0;
    vat = TAX_NO;
}


Position::Position(std::wstring _name, double _price, double _quantity, tax_type _vat)
{
    this->name = _name;
    this->price = _price;
    this->quantity = _quantity;
    this->vat = _vat;
}


void Position::setName(std::wstring _name){
    this->name = _name;
}

void Position::setPrice(double _price){
    this->price = _price;
}

void Position::setQuantity(double _quantity){
    this->quantity = _quantity;
}

void Position::setTax_type(tax_type _vat){
    this->vat = _vat;
}

std::wstring Position::getName(){
    return this->name;
}

double Position::getPrice()
{
     return this->price;
}

double Position::getQuantity(){
    return this->quantity;
}

tax_type Position::getTax_type(){
    return this->vat;
}

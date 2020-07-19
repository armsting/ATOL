#ifndef POSITION_H
#define POSITION_H
#include<string>

enum tax_type
{
    TAX_NO,
    TAX_VAT0,
    TAX_VAT10,
    TAX_VAT20
};

/*Класс в котором сохраняется вся информация о товарной позиции */
class Position
{
public:
    Position();
    Position(std::wstring name, double price, double quantity, tax_type vat);
    void setName(std::wstring name);
    void setPrice(double price);
    void setQuantity(double quantity);
    void setTax_type(tax_type vat);

    std::wstring getName();
    double getPrice();
    double getQuantity();
    tax_type getTax_type();

private:
    std::wstring name;
    double price;
    double quantity;
    tax_type vat;
};

#endif // POSITION_H

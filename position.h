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
    Position(const std::wstring &name, const double &price, const double &quantity, tax_type vat);
    void setName(const std::wstring &name);
    void setPrice(const double &price);
    void setQuantity(const double &quantity);
    void setTax_type(tax_type vat);

    std::wstring getName();
    double getPrice();
    double getQuantity();
    tax_type getTax_type();

private:
    std::wstring name_;
    double price_;
    double quantity_;
    tax_type vat_;
};

#endif // POSITION_H

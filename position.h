#ifndef POSITION_H
#define POSITION_H
#include<string>
#include"enumkkm.h"
#include <codecvt>


/*  ласс описывает параметры товарной позиции */
class Position
{
public:
    Position();
    Position(const std::wstring &name, double price, double quantity, VATRate vat) noexcept;
    void setName(const std::wstring &name) noexcept;
    void setPrice(double price) noexcept;
    void setQuantity(double quantity) noexcept;
    void setTax_type(VATRate vat) noexcept;

    std::wstring getName() const noexcept;
    double getPrice() const noexcept;
    double getQuantity() const noexcept;
    VATRate getTax_type() const noexcept;

private:
    std::wstring name_;
    double price_;
    double quantity_;
    VATRate vat_;
};

#endif // POSITION_H

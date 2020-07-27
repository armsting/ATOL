#pragma once
#include<string>
#include"enumkkm.h"
#include <codecvt>

/*
 * Класс описывает настройки подключения к ККМ
 */

class Connection
{
public:
    Connection();
    Connection(const std::wstring &serialPort) noexcept;
    Connection(const std::wstring &serialPort, Baudrate baudrate) noexcept;
    void setSerialPort(const std::wstring &serialPort) noexcept;
    void setBaudrate(Baudrate baudrate) noexcept;

    std::wstring getSerialPort() const noexcept;
    Baudrate getBaudrate() const noexcept;

private:
    std::wstring serialPort_;
    Baudrate baudrate_;
};

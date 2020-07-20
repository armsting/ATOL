#ifndef CONNECTION_H
#define CONNECTION_H
#include<string>
#include"enumkkm.h"

/*
 * Класс описывающий параметры связи с ККТ
 */

class Connection
{
public:
    Connection();
    Connection(const std::wstring &serialPort);
    Connection(const std::wstring &serialPort, Baudrate baudrate);
    void setSerialPort(const std::wstring &serialPort);
    void setBaudrate(Baudrate baudrate);

    std::wstring getSerialPort() const noexcept;
    Baudrate getBaudrate() const noexcept;

private:
    std::wstring serialPort_;
    Baudrate baudrate_;
};

#endif // CONNECTION_H

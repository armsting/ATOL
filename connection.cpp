#include "connection.h"

/*
 * Класс описывает настройки подключения к ККМ
*/
Connection::Connection():baudrate_(Baudrate::PORT_BR_115200){
}

Connection::Connection(const std::wstring &serialPort):
    baudrate_(Baudrate::PORT_BR_115200), serialPort_(serialPort){
}

Connection::Connection(const std::wstring& serialPort, Baudrate baudrate):
    baudrate_(baudrate), serialPort_(serialPort){
}

void Connection::setSerialPort(const std::wstring& serialPort){
    serialPort_ = serialPort;
}

void Connection::setBaudrate(Baudrate baudrate){
    baudrate_= baudrate;
}

std::wstring Connection::getSerialPort() const noexcept{
    return serialPort_;
}

Baudrate Connection::getBaudrate() const noexcept{
    return baudrate_;
}

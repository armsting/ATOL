#include "connection.h"

/*
 * Реализация класса описывающего параметры связи с ККТ
*/
Connection::Connection():baudrate_(Baudrate::PORT_BR_115200){
}

Connection::Connection(const std::wstring &serialPort):
    serialPort_(serialPort), baudrate_(Baudrate::PORT_BR_115200){

}

Connection::Connection(const std::wstring& serialPort, Baudrate baudrate):
    serialPort_(serialPort), baudrate_(baudrate){
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

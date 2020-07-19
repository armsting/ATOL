#include "connection.h"

/*
 * Реализация класса описывающего параметры связи с ККТ
*/
Connection::Connection(){
}


Connection::Connection(const std::wstring& serialPort, baudrate baudrate):
    serialPort_(serialPort), baudrate_(baudrate){
}

void Connection::setSerialPort(const std::wstring& serialPort){
    serialPort_ = serialPort;
}

void Connection::setBaudrate(baudrate baudrate){
    baudrate_= baudrate;
}

std::wstring Connection::getSerialPort(){
    return serialPort_;
}

baudrate Connection::getBaudrate(){
    return baudrate_;
}

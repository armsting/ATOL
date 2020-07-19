#ifndef CONNECTION_H
#define CONNECTION_H
#include<string>

enum baudrate
{
    BAUDRATE_1200 = 1200,
    BAUDRATE_2400 = 2400,
    BAUDRATE_4800 = 4800,
    BAUDRATE_9600 = 9600,
    BAUDRATE_19200 = 19200,
    BAUDRATE_38400 = 38400,
    BAUDRATE_57600 = 57600,
    BAUDRATE_115200 = 115200,
    BAUDRATE_230400 = 230400,
    BAUDRATE_460800 = 460800,
    BAUDRATE_921600 = 921600
};

/*
 * Класс описывающий параметры связи с ККТ
 */

class Connection
{
public:
    Connection();
    Connection(const std::wstring &serialPort, baudrate baudrate);
    void setSerialPort(const std::wstring &serialPort);
    void setBaudrate(baudrate baudrate);
    std::wstring getSerialPort();
    baudrate getBaudrate();

private:
    std::wstring serialPort_;
    baudrate baudrate_;
};

#endif // CONNECTION_H

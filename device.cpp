#include "device.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>

/*Вспомогательные методы для работы оборудования*/

void getComPortList(std::vector<std::wstring> &comPortList)
{
    comPortList.clear();

    for(auto port: QSerialPortInfo::availablePorts()){
        comPortList.push_back(port.portName().toStdWString());
    }
}


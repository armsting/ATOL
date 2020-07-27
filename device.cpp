#include "device.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>

/*¬спомогательные методы дл¤ работы оборудовани¤*/

void getComPortList(std::vector<std::wstring> &comPortList)
{
    comPortList.clear();

    for(auto port: QSerialPortInfo::availablePorts()){
        comPortList.push_back(port.portName().toStdWString());
    }
}


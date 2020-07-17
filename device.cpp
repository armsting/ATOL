#include "device.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>

/*Метод возвращает списко com портов*/

void getComPortList(QVector<QString> *comPortList)
{
    comPortList->clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        comPortList->append(info.portName());
    }
}


#include "device.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>

/*Вспомогательные методы для работы оборудования*/

namespace Device {

void getComPortList(std::vector<std::wstring> &comPortList)
{
    comPortList.clear();

    for(auto port: QSerialPortInfo::availablePorts()){
        comPortList.push_back(port.portName().toStdWString());
    }
}


bool validationINN(const std::wstring &CashierINN){

    if (CashierINN.length() == 0)
        return true;

    if (CashierINN.length() != 10 && CashierINN.length() != 12){
        return false;
    }

    if (CashierINN.find_first_not_of(L"0123456789") != std::wstring::npos){

        return false;
    }
    /*
    int controlSum_1 = 0, controlSum_2 = 0;

    if (CashierINN.length() == 10){
        controlSum_1 = (int)CashierINN[0] * 2 + (int)CashierINN[1] * 4 + (int)CashierINN[2] * 10 +
                (int)CashierINN[3] * 3 + (int)CashierINN[4] * 5 + (int)CashierINN[5] * 9 +
                (int)CashierINN[6] * 4 + (int)CashierINN[7] * 6 + (int)CashierINN[8] * 8;

        controlSum_2 = controlSum_1 / 11;

        controlSum_2 *= 11;

        if(std::abs(controlSum_1 - controlSum_2) != (int)CashierINN[9]){

            return false;
        }*/
    return true;
    }
}

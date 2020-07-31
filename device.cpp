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
        controlSum_1 = (CashierINN[0] - L'0')* 2 + (CashierINN[1] - L'0') * 4 + (CashierINN[2] - L'0') * 10 +
                (CashierINN[3] - L'0') * 3 + (CashierINN[4] - L'0') * 5 + (CashierINN[5] - L'0') * 9 +
                (CashierINN[6] - L'0') * 4 + (CashierINN[7] - L'0') * 6 + (CashierINN[8] - L'0') * 8;

        controlSum_2 = controlSum_1 / 11;

        controlSum_2 *= 11;

        if(std::abs(controlSum_1 - controlSum_2) != CashierINN[9] - L'0'){
            return false;
        }
    }

    if (CashierINN.length() == 12){
        controlSum_1 = (CashierINN[0] - '0')* 7 + (CashierINN[1] - '0') * 2 + (CashierINN[2] - '0') * 4 +
                (CashierINN[3] - '0') * 10 + (CashierINN[4] - '0') * 3 + (CashierINN[5] - '0') * 5 +
                (CashierINN[6] - '0') * 9 + (CashierINN[7] - '0') * 4 + (CashierINN[8] - '0') * 6 +
                (CashierINN[9] - '0') * 8;

        controlSum_2 = controlSum_1 / 11;

        controlSum_2 *= 11;

        if(std::abs(controlSum_1 - controlSum_2) != CashierINN[9] - '0'){
            return false;
        }
    }

    return true;
}

}

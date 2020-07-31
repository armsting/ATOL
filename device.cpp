#include "device.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>

/*Вспомогательные методы для работы оборудования*/

namespace  {

bool isValidINN10(const std::wstring &CashierINN){

    if (CashierINN.length() != 10){
        return false;
    }

    int controlSum_1 = 0, controlSum_2 = 0; //Переменные для вычисления контрольной цифры


    controlSum_1 = (CashierINN[0] - L'0')* 2 + (CashierINN[1] - L'0') * 4 + (CashierINN[2] - L'0') * 10 +
            (CashierINN[3] - L'0') * 3 + (CashierINN[4] - L'0') * 5 + (CashierINN[5] - L'0') * 9 +
             (CashierINN[6] - L'0') * 4 + (CashierINN[7] - L'0') * 6 + (CashierINN[8] - L'0') * 8;

    controlSum_2 = controlSum_1 / 11;

    controlSum_2 *= 11;

    if(std::abs(controlSum_1 - controlSum_2) != CashierINN[9] - L'0'){
            return false;
        }

    return true;
}

bool isValidINN12(const std::wstring &CashierINN){

    if (CashierINN.length() != 12){
        return false;
    }

    int controlSum_1 = 0, controlSum_2 = 0; //Переменные для вычисления контрольной цифры

    controlSum_1 = (CashierINN[0] - '0')* 7 + (CashierINN[1] - '0') * 2 + (CashierINN[2] - '0') * 4 +
                (CashierINN[3] - '0') * 10 + (CashierINN[4] - '0') * 3 + (CashierINN[5] - '0') * 5 +
                (CashierINN[6] - '0') * 9 + (CashierINN[7] - '0') * 4 + (CashierINN[8] - '0') * 6 +
                (CashierINN[9] - '0') * 8;

    controlSum_2 = controlSum_1 / 11;

    controlSum_2 *= 11;

    if(controlSum_2 == 10){
         if((CashierINN[10] - '0') !=0){
                return false;
           }
    }
    else{
        if((CashierINN[10] - '0') != std::abs(controlSum_1 - controlSum_2)){
                return false;
            }
        }

    controlSum_1 = (CashierINN[0] - '0')* 3 + (CashierINN[1] - '0') * 7 + (CashierINN[2] - '0') * 2 +
                (CashierINN[3] - '0') * 4 + (CashierINN[4] - '0') * 10 + (CashierINN[5] - '0') * 3 +
                (CashierINN[6] - '0') * 5 + (CashierINN[7] - '0') * 9 + (CashierINN[8] - '0') * 4 +
                (CashierINN[9] - '0') * 6 + (CashierINN[10] - '0') * 8;

    controlSum_2 = controlSum_1 / 11;

    controlSum_2 *= 11;

    if(controlSum_2 == 10){
         if((CashierINN[11] - '0') !=0){
                return false;
           }
    }
    else{
        if((CashierINN[11] - '0') != std::abs(controlSum_1 - controlSum_2)){
                return false;
            }
        }

    return true;
}
}


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

    if (CashierINN.find_first_not_of(L"0123456789") != std::wstring::npos){

        return false;
    }

    if (isValidINN10(CashierINN) || isValidINN12(CashierINN)){
        return true;
    }

    return false;
}
}

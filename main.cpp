#include "mainwindow.h"
#include <iostream>
#include <device.h>
#include "atol.h"
#include "windows.h"
#include <codecvt>

int main(int argc, char *argv[])
{
    Connection connect;
    connect.setSerialPort(L"COM6");
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    std::wstring t = myconv.from_bytes("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");

    Position position_1(t, 1000, 2, VATRate::VAT120);

    KkmParameters param;

    param.setConnection(connect);
    param.addPosition(position_1);
    param.setCashierName(t);
    param.setPayBankCardMoney(2000);
    param.setCheckType(CheckType::SALE_RETURN);

    Atol::formReceipt(param);

    Atol::shiftClose(param);

    /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}

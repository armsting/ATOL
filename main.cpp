#include "mainwindow.h"
#include <iostream>
#include <device.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

int main(int argc, char *argv[])
{
    QVector<QString> list;

    getComPortList(&list);
    std::cout<<"Привет\n";

    /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}

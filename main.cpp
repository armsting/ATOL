#include "mainwindow.h"
#include <iostream>
#include <device.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "libfptr10.h"

int main(int argc, char *argv[])
{
    QVector<QString> list;

    getComPortList(&list);

    libfptr_handle fptr;
    libfptr_create(&fptr);

    std::cout<<libfptr_get_version_string()<<"\n";

    /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    libfptr_destroy(&fptr);
}

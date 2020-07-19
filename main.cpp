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
    wchar_t settings[1024] = {0};
    swprintf(&settings[0], 1024, L"{\"%ls\": %d, \"%ls\": %d, \"%ls\": \"%ls\", \"%ls\": %d}",
        LIBFPTR_SETTING_MODEL, LIBFPTR_MODEL_ATOL_AUTO,
        LIBFPTR_SETTING_PORT, LIBFPTR_PORT_COM,
        LIBFPTR_SETTING_COM_FILE, L"COM5",
        LIBFPTR_SETTING_BAUDRATE, LIBFPTR_PORT_BR_115200)
    libfptr_set_settings(fptr, settings);
    /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    libfptr_destroy(&fptr);
}

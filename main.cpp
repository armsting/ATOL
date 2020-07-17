#include "mainwindow.h"
#include "libfptr10.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    libfptr_handle fptr;
    libfptr_create(&fptr);

    std::cout<<libfptr_get_version_string()<<std::endl;

    libfptr_destroy(&fptr);//дестрой
    /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}

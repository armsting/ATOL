#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    /*
    double t1 = 1.091876;

    //std::string s = "";

    char s[20];
    sprintf (&s[0], "%.2lf", t1);

    std::cout<<"Result: "<<s<<std::endl;*/
}

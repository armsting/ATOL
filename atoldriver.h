#ifndef ATOLDRIVER_H
#define ATOLDRIVER_H

#include "libfptr10.h"


class AtolDriver{


public:
    AtolDriver();
    void setSettings();
    void shiftOpen();
    void shiftClose();
    void cashInsert();
    void cashWithdraw();
    void x_report();
    void printDocement();
    void initDriver();
    bool pingKKM();

    private:
    libfptr_handle fptr;

~AtolDriver();

};

#endif // ATOLDRIVER_H

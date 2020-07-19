#ifndef ATOLDRIVER_H
#define ATOLDRIVER_H

#include "libfptr10.h"


class Atol{

public:
    static void shiftOpen();
    static void shiftClose();
    static void cashInsert();
    static void cashWithdraw();
    static void x_report();
    static void printDocement();
    static bool pingKKM();

private:
    void initDriver(const libfptr_handle &fptr);
    void destroyDriver (const libfptr_handle &fptr);
    void kktSetSettings();
    void open();
};

#endif // ATOLDRIVER_H

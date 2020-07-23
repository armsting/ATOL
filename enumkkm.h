#ifndef ENUMKKM_H
#define ENUMKKM_H

enum class Baudrate{
    PORT_BR_1200 = 1200,
    PORT_BR_2400 = 2400,
    PORT_BR_4800 = 4800,
    PORT_BR_9600 = 9600,
    PORT_BR_19200 = 19200,
    PORT_BR_38400 = 38400,
    PORT_BR_57600 = 57600,
    PORT_BR_115200 = 115200,
    PORT_BR_230400 = 230400,
    PORT_BR_460800 = 460800,
    PORT_BR_921600 = 921600
};

enum class VATRate{
    VATNO = -1,
    VAT0 = 0,
    VAT10 = 10,
    VAT110 = 110,
    VAT20 = 20,
    VAT120 = 120
};

enum class CheckType{
    SALE = 0,
    SALE_RETURN = 1,
    SHIFT_OPEN = 2,
    SHIFT_CLOSE = 3
};

#endif // ENUMKKM_H

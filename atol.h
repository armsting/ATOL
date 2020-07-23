#ifndef ATOLDRIVER_H
#define ATOLDRIVER_H

#include "libfptr10.h"
#include "kkmparameters.h"
#include "enumkkm.h"
#include <string>


/*
 * Класс реализует методы основные методы работы с ККМ АТОЛ
*/
class Atol{

public:
    static int shiftOpen(const KkmParameters &kkmParameters, std::wstring &error);
    static int shiftClose(const KkmParameters &kkmParameters, std::wstring &error);
    static int cashInsert(const KkmParameters &kkmParameters, std::wstring &error);
    static int cashWithdraw(const KkmParameters &kkmParameters, std::wstring &error);
    static int x_report(const KkmParameters &kkmParameters, std::wstring &error);
    static int isConnection(const Connection &connection, std::wstring &error);
    static int formReceipt(const KkmParameters &kkmParameters, std::wstring &error);

private:
    static int connection(const KkmParameters &kkmParameters, libfptr_handle fptr);
    static int registerCashier(const KkmParameters &kkmParameters, libfptr_handle fptr);
    static void disconnection(libfptr_handle fptr);
    static int openCheck(const KkmParameters &kkmParameters, libfptr_handle fptr);
    static int registeringPositions(const KkmParameters &kkmParameters, libfptr_handle fptr);
    static libfptr_tax_type convertVatToAtol(VATRate vat);
    static int paymentRegistration(const KkmParameters &kkmParameters, libfptr_handle fptr);
    static std::wstring getAnError(libfptr_handle fptr);
    static int closeFiscalDocument(libfptr_handle fptr, CheckType type);

};

#endif // ATOLDRIVER_H

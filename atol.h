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
    static int shiftOpen(const KkmParameters &kkmParameters, std::wstring &error) noexcept;
    static int shiftClose(const KkmParameters &kkmParameters, std::wstring &error) noexcept;
    static int cashInsert(const KkmParameters &kkmParameters, std::wstring &error) noexcept;
    static int cashWithdraw(const KkmParameters &kkmParameters, std::wstring &error) noexcept;
    static int x_report(const KkmParameters &kkmParameters, std::wstring &error) noexcept;
    static int isConnection(const Connection &connection, std::wstring &error) noexcept;
    static int formReceipt(const KkmParameters &kkmParameters, std::wstring &error) noexcept;

private:
    static int connection(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept;
    static int registerCashier(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept;
    static void disconnection(libfptr_handle fptr) noexcept;
    static int openCheck(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept;
    static int registeringPositions(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept;
    static libfptr_tax_type convertVatToAtol(VATRate vat) noexcept;
    static int paymentRegistration(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept;
    static std::wstring getAnError(libfptr_handle fptr) noexcept;
    static int closeFiscalDocument(libfptr_handle fptr, CheckType type) noexcept;

};

#endif // ATOLDRIVER_H

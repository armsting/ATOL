#ifndef ATOLDRIVER_H
#define ATOLDRIVER_H

#include "libfptr10.h"
#include "kkmparameters.h"
#include "enumkkm.h"


class Atol{

public:
    static void shiftOpen(const KkmParameters &kkmParameters);
    static void shiftClose(const KkmParameters &kkmParameters);
    static void cashInsert(const KkmParameters &kkmParameters);
    static void cashWithdraw(const KkmParameters &kkmParameters);
    static void x_report(const KkmParameters &kkmParameters);
    static bool isConnection(const KkmParameters &kkmParameters);
    static void formReceipt(const KkmParameters &kkmParameters);

private:
    static bool connection(const KkmParameters &kkmParameters, libfptr_handle fptr);
    static void registerCashier(const KkmParameters &kkmParameters, libfptr_handle fptr);
    static void disconnection(libfptr_handle fptr);
    static void openCheck(const KkmParameters &kkmParameters, libfptr_handle fptr);
    static void registeringPositions(const KkmParameters &kkmParameters, libfptr_handle fptr);
    static libfptr_tax_type convertVatToAtol(VATRate vat);
    static void paymentRegistration(const KkmParameters &kkmParameters, libfptr_handle fptr);
};

#endif // ATOLDRIVER_H

#include "atol.h"
#include <iostream>


/*
 * Класс для работы с ККМ АТОЛ
*/

void Atol::shiftOpen(const KkmParameters &kkmParameters){ //Открытие смены
    libfptr_handle fptr; // Инициализация драйвера
    libfptr_create(&fptr);

    Atol::connection(kkmParameters, fptr);

    Atol::registerCashier(kkmParameters, fptr); //Регистрируем кассира

    libfptr_open_shift(fptr); //Открываем смену

    libfptr_check_document_closed(fptr); //Закрываем чек

    Atol::disconnection(fptr);//Закрыли соеденение и уничтожили драйвер
}

void Atol::shiftClose(const KkmParameters &kkmParameters){//Закрытие смены
    libfptr_handle fptr; // Инициализация драйвера
    libfptr_create(&fptr);

    Atol::connection(kkmParameters, fptr);

    Atol::registerCashier(kkmParameters, fptr); //Регистрируем кассира

    libfptr_set_param_int(fptr, LIBFPTR_PARAM_REPORT_TYPE, LIBFPTR_RT_CLOSE_SHIFT);
    libfptr_report(fptr);

    libfptr_check_document_closed(fptr); //Закрываем чек

    Atol::disconnection(fptr);//Закрыли соеденение и уничтожили драйвер
}

void Atol::cashInsert(const KkmParameters &kkmParameters){//Внесение
    libfptr_handle fptr; // Инициализация драйвера
    libfptr_create(&fptr);

    Atol::connection(kkmParameters, fptr);

    libfptr_set_param_double(fptr, LIBFPTR_PARAM_SUM, kkmParameters.getPayCashMoney());
    libfptr_cash_income(fptr);

    Atol::disconnection(fptr);//Закрыли соеденение и уничтожили драйвер
}

void Atol::cashWithdraw(const KkmParameters &kkmParameters){//Изъятие
    libfptr_handle fptr; // Инициализация драйвера
    libfptr_create(&fptr);

    Atol::connection(kkmParameters, fptr);

    libfptr_set_param_double(fptr, LIBFPTR_PARAM_SUM, kkmParameters.getPayCashMoney());
    libfptr_cash_outcome(fptr);

    Atol::disconnection(fptr);//Закрыли соеденение и уничтожили драйвер
}

void Atol::x_report(const KkmParameters &kkmParameters){//Печать Х-отчёта
    libfptr_handle fptr; // Инициализация драйвера
    libfptr_create(&fptr);

    Atol::connection(kkmParameters, fptr);

    libfptr_set_param_int(fptr, LIBFPTR_PARAM_REPORT_TYPE, LIBFPTR_RT_X);
    libfptr_report(fptr);

    Atol::disconnection(fptr);//Закрыли соеденение и уничтожили драйвер
}

void Atol::formReceipt(const KkmParameters &kkmParameters){//Печать чека продажи/возврата продажи
    libfptr_handle fptr; // Инициализация драйвера
    libfptr_create(&fptr);

    Atol::connection(kkmParameters, fptr);
    Atol::registerCashier(kkmParameters, fptr); //Регистрируем кассира
    Atol::openCheck(kkmParameters, fptr);//Открыли чек нужного нам типа (SALE / SALE_RETURN)
    Atol::registeringPositions(kkmParameters, fptr);//Зарегали все товарные позиции
    Atol::paymentRegistration(kkmParameters, fptr);//Зарегали оплату
    libfptr_close_receipt(fptr);//Закрыли чек

    Atol::disconnection(fptr);//
}

void Atol::openCheck(const KkmParameters &kkmParameters, libfptr_handle fptr){//Открытие чека
    switch (kkmParameters.getCheckType()) {
    case CheckType::SALE:
         libfptr_set_param_int(fptr, LIBFPTR_PARAM_RECEIPT_TYPE, LIBFPTR_RT_SELL);
         libfptr_open_receipt(fptr);
         break;
    case CheckType::SALE_RETURN:
         libfptr_set_param_int(fptr, LIBFPTR_PARAM_RECEIPT_TYPE, LIBFPTR_RT_SELL_RETURN);
         libfptr_open_receipt(fptr);
         break;
    default:
         break;
    }
}

void Atol::registeringPositions(const KkmParameters &kkmParameters, libfptr_handle fptr){//Регистрация товарных позиций
    auto positions = kkmParameters.getPositionsList();

    for(auto pos: positions) {
        libfptr_set_param_str(fptr, LIBFPTR_PARAM_COMMODITY_NAME, std::wstring(pos.getName()).c_str());
        libfptr_set_param_double(fptr, LIBFPTR_PARAM_PRICE, pos.getPrice());
        libfptr_set_param_double(fptr, LIBFPTR_PARAM_QUANTITY, pos.getQuantity());
        libfptr_set_param_int(fptr, LIBFPTR_PARAM_TAX_TYPE, Atol::convertVatToAtol(pos.getTax_type()));
        libfptr_registration(fptr);
    }
}

void Atol::paymentRegistration(const KkmParameters &kkmParameters, libfptr_handle fptr){//Если сумма по безналу не
    if(kkmParameters.getPayBankCardMoney() != 0){
        libfptr_set_param_int(fptr, LIBFPTR_PARAM_PAYMENT_TYPE, LIBFPTR_PT_ELECTRONICALLY);
        libfptr_set_param_double(fptr, LIBFPTR_PARAM_PAYMENT_SUM, kkmParameters.getPayBankCardMoney());
        libfptr_payment(fptr);
    }
    else{
        libfptr_set_param_int(fptr, LIBFPTR_PARAM_PAYMENT_TYPE, LIBFPTR_PT_CASH);
        libfptr_set_param_double(fptr, LIBFPTR_PARAM_PAYMENT_SUM, kkmParameters.getPayCashMoney());
        libfptr_payment(fptr);
    }
}

libfptr_tax_type Atol::convertVatToAtol(VATRate vat){
    switch (vat) {
    case VATRate::VAT0:
        return libfptr_tax_type::LIBFPTR_TAX_VAT0;
    case VATRate::VAT10:
        return  libfptr_tax_type::LIBFPTR_TAX_VAT10;
    case VATRate::VAT20:
        return libfptr_tax_type::LIBFPTR_TAX_VAT20;
    case VATRate::VAT110:
        return libfptr_tax_type::LIBFPTR_TAX_VAT110;
    case VATRate::VAT120:
        return libfptr_tax_type::LIBFPTR_TAX_VAT120;
    default:
        return libfptr_tax_type::LIBFPTR_TAX_NO;
    }
}

bool Atol::connection(const KkmParameters &kkmParameters, libfptr_handle fptr){ //Применяем настройки подключения к ККМ и устанавливаем с ней соеденение. Если соеденение установлено возвращаем true, в противном случае false

    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_MODEL, std::to_wstring(LIBFPTR_MODEL_ATOL_AUTO).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_PORT, std::to_wstring(LIBFPTR_PORT_COM).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_COM_FILE, std::wstring(kkmParameters.getConnection().getSerialPort()).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_BAUDRATE, std::to_wstring(static_cast<int>(kkmParameters.getConnection().getBaudrate())).c_str());
    libfptr_apply_single_settings(fptr);

    libfptr_open(fptr);

    return libfptr_is_opened(fptr);
}

void Atol::disconnection(libfptr_handle fptr){
    libfptr_close(fptr); //завершение соеденения
    libfptr_destroy(&fptr);//деинициализация драйвера
}

void Atol::registerCashier(const KkmParameters &kkmParameters, libfptr_handle fptr){ //Регистрация кассира

    libfptr_set_param_str(fptr, 1021, std::wstring(kkmParameters.getCashierName()).c_str());
    libfptr_set_param_str(fptr, 1203, std::wstring(kkmParameters.getCashierINN()).c_str());
    libfptr_operator_login(fptr);
}


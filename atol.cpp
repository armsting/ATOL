#include "atol.h"
#include <iostream>


/*
 * Класс реализует методы основные методы работы с ККМ АТОЛ
*/

int Atol::shiftOpen(const KkmParameters &kkmParameters, std::wstring &error) noexcept{ //Метод открытия смены
    libfptr_handle fptr; //Инициализируем драйвер

    if (libfptr_create(&fptr) < 0){ //Проверка инициализация драйвера
        error = getAnError(fptr);
        return -1;
    }

    if (Atol::connection(kkmParameters, fptr) < 0){//Устанавливаем соединение с ККМ
        error = getAnError(fptr);
        libfptr_destroy(&fptr);//Деинициализация драйвера
        return -1;
    }

    if (Atol::closeFiscalDocument(fptr, CheckType::SHIFT_OPEN) < 0){//Если предыдущий чек не был закрыт, закрываем его
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    if (Atol::registerCashier(kkmParameters, fptr) < 0){//Регистрация кассира
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    if (libfptr_open_shift(fptr) < 0){//Открываем смену
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    if (Atol::closeFiscalDocument(fptr, CheckType::SHIFT_OPEN) < 0){//Закрываем чек
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера

    return 0;
}

int Atol::shiftClose(const KkmParameters &kkmParameters, std::wstring &error) noexcept{//Метод закрытия смены
    libfptr_handle fptr; //Инициализируем драйвер

    if (libfptr_create(&fptr) < 0){ //Проверка инициализация драйвера
        error = getAnError(fptr);
        return -1;
    }

    if (Atol::connection(kkmParameters, fptr) < 0){//Устанавливаем соединение с ККМ
        error = getAnError(fptr);
        libfptr_destroy(&fptr);//Деинициализация драйвера
        return -1;
    }

    if (Atol::closeFiscalDocument(fptr, CheckType::SHIFT_CLOSE) < 0){//Если предудущий чек не был закрыт, то закрываем его
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    if (Atol::registerCashier(kkmParameters, fptr) < 0){//Регистрация кассира
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    libfptr_set_param_int(fptr, LIBFPTR_PARAM_REPORT_TYPE, LIBFPTR_RT_CLOSE_SHIFT);//Параметр закрытия смены

    if (libfptr_report(fptr) < 0){//Закрываем смену
        error = getAnError(fptr);
        Atol::disconnection(fptr);
        return -1;
    }

    if (Atol::closeFiscalDocument(fptr, CheckType::SHIFT_CLOSE) < 0){//Закрываем чек
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера

    return 0;
}

int Atol::cashInsert(const KkmParameters &kkmParameters, std::wstring &error) noexcept{//Внесение наличности
    libfptr_handle fptr; //Инициализируем драйвер

    if (libfptr_create(&fptr) < 0){ //Проверка инициализация драйвера
        error = getAnError(fptr);
        return -1;
    }

    if (Atol::connection(kkmParameters, fptr) < 0){//Устанавливаем соединение с ККМ
        error = getAnError(fptr);
        libfptr_destroy(&fptr);//Деинициализация драйвера
        return -1;
    }

    libfptr_set_param_double(fptr, LIBFPTR_PARAM_SUM, kkmParameters.getPayCashMoney());//Записываем сумму

    if(libfptr_cash_income(fptr) < 0){//Вносим наличность
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера

    return 0;
}

int Atol::cashWithdraw(const KkmParameters &kkmParameters, std::wstring &error) noexcept{//Изъятие наличности
    libfptr_handle fptr; //Инициализируем драйвер

    if (libfptr_create(&fptr) < 0){ //Проверка инициализация драйвера
        error = getAnError(fptr);
        return -1;
    }

    if (Atol::connection(kkmParameters, fptr) < 0){//Устанавливаем соединение с ККМ
        error = getAnError(fptr);
        libfptr_destroy(&fptr);//Деинициализация драйвера
        return -1;
    }

    libfptr_set_param_double(fptr, LIBFPTR_PARAM_SUM, kkmParameters.getPayCashMoney());

    if(libfptr_cash_outcome(fptr) < 0){//Изымаем наличность
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера

    return 0;
}

int Atol::x_report(const KkmParameters &kkmParameters, std::wstring &error) noexcept{//Печатаем Х-отчёт

    libfptr_handle fptr; //Инициализируем драйвер

    if (libfptr_create(&fptr) < 0){ //Проверка инициализация драйвера
        error = getAnError(fptr);
        return -1;
    }

    if (Atol::connection(kkmParameters, fptr) < 0){//Устанавливаем соединение с ККМ
        error = getAnError(fptr);
        libfptr_destroy(&fptr);//Деинициализация драйвера
        return -1;
    }

    libfptr_set_param_int(fptr, LIBFPTR_PARAM_REPORT_TYPE, LIBFPTR_RT_X);

    if(libfptr_report(fptr) < 0){//Печатаем Х-отчёт
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера

    return 0;
}

int Atol::formReceipt(const KkmParameters &kkmParameters, std::wstring &error) noexcept{//Формирование фискального чека
    libfptr_handle fptr; //Инициализируем драйвер

    if (libfptr_create(&fptr) < 0){ //Проверка инициализация драйвера
        error = getAnError(fptr);
        return -1;
    }

    if (Atol::connection(kkmParameters, fptr) < 0){//Устанавливаем соединение с ККМ
        error = getAnError(fptr);
        libfptr_destroy(&fptr);//Деинициализация драйвера
        return -1;
    }

    if (Atol::closeFiscalDocument(fptr, CheckType::SALE) < 0){//Если предыдущий чек не был закрыл, то закрываем/аннулируем его
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    if (Atol::registerCashier(kkmParameters, fptr) < 0){//Регистрация кассира
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    if (Atol::openCheck(kkmParameters, fptr) < 0){//Открытие чека (SALE / SALE_RETURN)
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    if (Atol::registeringPositions(kkmParameters, fptr) <0){//Регистрация товарных позиций
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    if (Atol::paymentRegistration(kkmParameters, fptr)){//Регистрация оплат
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }


    if (Atol::closeFiscalDocument(fptr, CheckType::SALE) < 0){//Закрываем чек (для продажи и возврата одинаково)
        error = getAnError(fptr);
        Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера
        return -1;
    }

    Atol::disconnection(fptr);//Дисконнект и деинициализация драйвера

    return 0;
}

int Atol::openCheck(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept{//Открытие чека с определённым типом

    switch (kkmParameters.getCheckType()) {
    case CheckType::SALE:
         libfptr_set_param_int(fptr, LIBFPTR_PARAM_RECEIPT_TYPE, LIBFPTR_RT_SELL);
         return  libfptr_open_receipt(fptr);
    case CheckType::SALE_RETURN:
         libfptr_set_param_int(fptr, LIBFPTR_PARAM_RECEIPT_TYPE, LIBFPTR_RT_SELL_RETURN);
         return libfptr_open_receipt(fptr);
    default:
        return -1;
    }
}

int Atol::registeringPositions(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept{//Регистрация товарных позиций
    auto positions = kkmParameters.getPositionsList();

    for(auto pos: positions) {
        libfptr_set_param_str(fptr, LIBFPTR_PARAM_COMMODITY_NAME, std::wstring(pos.getName()).c_str());
        libfptr_set_param_double(fptr, LIBFPTR_PARAM_PRICE, pos.getPrice());
        libfptr_set_param_double(fptr, LIBFPTR_PARAM_QUANTITY, pos.getQuantity());
        libfptr_set_param_int(fptr, LIBFPTR_PARAM_TAX_TYPE, Atol::convertVatToAtol(pos.getTax_type()));
        if (libfptr_registration(fptr) < 0){
            return -1;
         }
    }
    return 0;
}

int Atol::paymentRegistration(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept{//Регистрация оплат
    if(kkmParameters.getPayBankCardMoney() != 0){
        libfptr_set_param_int(fptr, LIBFPTR_PARAM_PAYMENT_TYPE, LIBFPTR_PT_ELECTRONICALLY);
        libfptr_set_param_double(fptr, LIBFPTR_PARAM_PAYMENT_SUM, kkmParameters.getPayBankCardMoney());
        if (libfptr_payment(fptr) < 0){
            return -1;
        }
    }
    else{
        libfptr_set_param_int(fptr, LIBFPTR_PARAM_PAYMENT_TYPE, LIBFPTR_PT_CASH);
        libfptr_set_param_double(fptr, LIBFPTR_PARAM_PAYMENT_SUM, kkmParameters.getPayCashMoney());
        if (libfptr_payment(fptr) < 0){
            return -1;
        }
    }
    return 0;
}

libfptr_tax_type Atol::convertVatToAtol(VATRate vat) noexcept{//Конвентируем наши ставки НДС в АТОЛовские
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

int Atol::connection(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept{ //Подключение к ККМ АТОЛ

    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_MODEL, std::to_wstring(LIBFPTR_MODEL_ATOL_AUTO).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_PORT, std::to_wstring(LIBFPTR_PORT_COM).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_COM_FILE, std::wstring(kkmParameters.getConnection().getSerialPort()).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_BAUDRATE, std::to_wstring(static_cast<int>(kkmParameters.getConnection().getBaudrate())).c_str());

    if (libfptr_apply_single_settings(fptr) !=0 ){ //Проверяем успешность выполнения метода
        return -1;
    }

    if (libfptr_open(fptr) !=0 ){ //Проверяем успешность выполнения метода
        return -1;
    }

    return libfptr_is_opened(fptr);
}

void Atol::disconnection(libfptr_handle fptr) noexcept{//Метод завершающий соединение с драйвером АТОЛа

    libfptr_close(fptr); //Дисконнект
    libfptr_destroy(&fptr);//Деинициализация драйвера
}

int Atol::registerCashier(const KkmParameters &kkmParameters, libfptr_handle fptr) noexcept{ //Регистрация Кассира

    libfptr_set_param_str(fptr, 1021, std::wstring(kkmParameters.getCashierName()).c_str());
    libfptr_set_param_str(fptr, 1203, std::wstring(kkmParameters.getCashierINN()).c_str());
    return libfptr_operator_login(fptr);
}

std::wstring Atol::getAnError(libfptr_handle fptr) noexcept{//Выводим сообщение об ошибке в случае таковой

    std::wstring error_message;
    std::vector<wchar_t> str(1);

    int size = libfptr_error_description(fptr, &str[0], str.size());
    if (size > str.size()){
           str.resize(size);
           libfptr_error_description(fptr, &str[0], str.size());
        }

    for(auto i: str)
        error_message += i;

    error_message = L"Код ошибки: " + std::to_wstring(libfptr_error_code(fptr)) + L": " + error_message;
    return std::wstring(error_message);
}

int Atol::closeFiscalDocument(libfptr_handle fptr, CheckType type) noexcept{//Метод закрывающий/отменяющий/допечатывающий предыдущий документ

    if(type == CheckType::SALE || type == CheckType::SALE_RETURN){//Закрываем документ согласно его типу
        libfptr_close_receipt(fptr);
    }

    if(libfptr_check_document_closed(fptr) < 0) {
        return -1;
    }

    if (libfptr_get_param_bool(fptr, LIBFPTR_PARAM_DOCUMENT_CLOSED) == 0) { //Док не закрылся, отменяем его
      libfptr_cancel_receipt(fptr);
      return 0;
    }

    if (libfptr_get_param_bool(fptr, LIBFPTR_PARAM_DOCUMENT_PRINTED) == 0) {
      // Можно сразу вызвать метод допечатывания документа, он завершится с ошибкой, если это невозможно
      if(libfptr_continue_print(fptr) < 0) {
          return -1;
      }
    }

    return 0;
}

int Atol::isConnection(const Connection &connection, std::wstring &error) noexcept{//Лайт метод для проверки соединения с ККМ АТОЛ
    libfptr_handle fptr; //Инициализируем драйвер

    if (libfptr_create(&fptr) < 0){ //Проверка инициализация драйвера
        error = getAnError(fptr);
        return -1;
    }

    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_MODEL, std::to_wstring(LIBFPTR_MODEL_ATOL_AUTO).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_PORT, std::to_wstring(LIBFPTR_PORT_COM).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_COM_FILE, std::wstring(connection.getSerialPort()).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_BAUDRATE, std::to_wstring(static_cast<int>(connection.getBaudrate())).c_str());

    if (libfptr_apply_single_settings(fptr) !=0 ){ //Проверяем успешность выполнения метода применения настроек
        return -1;
    }

    if (libfptr_open(fptr) !=0 ){ //Проверяем успешность открытия соединения
        return -1;
    }

    libfptr_close(fptr); //Дисконнект
    libfptr_destroy(&fptr);//Деинициализация драйвера

    return libfptr_is_opened(fptr);
}

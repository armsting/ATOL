#include "atol.h"
#include <iostream>


/*
 * Класс для работы с ККМ АТОЛ
*/

void Atol::shiftOpen(){
    libfptr_handle fptr;
    libfptr_create(&fptr);

    libfptr_set_param_str(fptr, 1021, L"Кассир Иванов И.");
    libfptr_set_param_str(fptr, 1203, L"123456789047");
    libfptr_operator_login(fptr);

    libfptr_open_shift(fptr);

    libfptr_check_document_closed(fptr);

    libfptr_destroy(&fptr);
}

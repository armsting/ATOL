#include "atoldriver.h"
#include <iostream>

AtolDriver::AtolDriver(){

    libfptr_create(&fptr);
}



/*применить настройки подключения к ККТ АТОЛ
 */
void AtolDriver::setSettings(){

  //  libfptr_set_single_setting(fptr, LIBFPTR_SETTING_MODEL, std::to_wstring(LIBFPTR_MODEL_ATOL_AUTO).c_str());
   /* libfptr_set_single_setting(fptr, LIBFPTR_SETTING_PORT, std::to_wstring(LIBFPTR_PORT_COM).c_str());
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_COM_FILE, L"COM5");
    libfptr_set_single_setting(fptr, LIBFPTR_SETTING_BAUDRATE, LIBFPTR_PORT_BR_115200);
    libfptr_apply_single_settings(fptr);*/
}

void AtolDriver::shiftOpen(){

}

void AtolDriver::shiftClose(){

}

void AtolDriver::cashInsert(){

}

void AtolDriver::cashWithdraw(){

}

void AtolDriver::x_report(){

}

void AtolDriver::printDocement(){

}

bool AtolDriver::pingKKM(){

    bool isOpened = false;
    libfptr_open(fptr);
    isOpened = libfptr_is_opened(fptr);
    libfptr_close(fptr);

    return isOpened;
}

AtolDriver::~AtolDriver(){
    libfptr_close(fptr);
    libfptr_destroy(&fptr);
}

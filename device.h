#pragma once
#include <QVector>
#include <cmath>
#include <codecvt>
#include <locale>
#include <bits/stdc++.h>

namespace Device {

    void getComPortList(std::vector<std::wstring> &comPortList); //Метод возвращает вектор с активными ком портами системы

    bool validationINN(const std::wstring &CashierINN);//Валидация ИНН
}


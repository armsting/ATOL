#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <device.h>
#include "atol.h"
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <QMessageBox>
#include <QString>
#include <QTextCodec>
#include <codecvt>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    getComPortList(comPortList);

    ui->setupUi(this);

    ui->comboBox_COMPort->clear();//Очистка списка COM портов

    for(auto COMPort: comPortList){//Заполняем список COM портов системы
       ui->comboBox_COMPort->addItem(QString::fromStdWString(COMPort));
    }


    QFont f("MS Shell Dlg 2", 10);

    ui->label_CurrentCashier_Name_INN->setFont(f);
    ui->label_pingKKM->setFont(f);
    ui->label_pingKKM->setAlignment(Qt::AlignHCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shiftOpenButton_clicked()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;

    if (Atol::shiftOpen(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode("Ошибка печати отчёта об открытии смены")),
                    tr(str.c_str()),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("Повторить")));
            messageBox.setButtonText(QMessageBox::No, (codec->toUnicode("Отмена")));

        if(messageBox.exec() == QMessageBox::Yes){
            MainWindow::on_shiftOpenButton_clicked();
            return;
        }
        else {
            return;
        }
    }

    QMessageBox messageBox(QMessageBox::Information,
                (codec->toUnicode("Retail luxury")),
                (codec->toUnicode("Смена открыта")),
                QMessageBox::Yes,
                this);
     messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("ОК")));
     messageBox.exec();
}

void MainWindow::on_x_reportButton_clicked()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;

    if (Atol::x_report(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode("Ошибка при печати Х-отчёта")),
                    tr(str.c_str()),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("Повторить")));
            messageBox.setButtonText(QMessageBox::No, (codec->toUnicode("Отмена")));

        if(messageBox.exec() == QMessageBox::Yes){
            MainWindow::on_x_reportButton_clicked();
            return;
        }
        else {
            return;
        }
    }

    QMessageBox messageBox(QMessageBox::Information,
                (codec->toUnicode("Retail luxury")),
                (codec->toUnicode("Х-отчёт успешно распечатан")),
                QMessageBox::Yes,
                this);
     messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("ОК")));
     messageBox.exec();
}

void MainWindow::on_Insert_Withdraw_cash_clicked()
{

}

void MainWindow::on_payButton_clicked()
{

}

void MainWindow::on_refresh_COMPort_listButton_clicked()
{
    getComPortList(comPortList);//Обновили список COM портов

    ui->comboBox_COMPort->clear();//Очистка списка COM портов

    for(auto COMPort: comPortList){//Заполняем список COM портов системы
       ui->comboBox_COMPort->addItem(QString::fromStdWString(COMPort));
    }
}

void MainWindow::on_applySettingsButton_clicked()
{
    connection.setSerialPort(ui->comboBox_COMPort->currentText().toStdWString().c_str());//Задали текущий COM порт

    connection.setBaudrate(MainWindow::convertIntToBaudrate(ui->comboBox_Baudrate->currentText().toInt())); //Задали скорость текущего COM порта

    kkmparameters.setConnection(connection);

    ui->lineEdit_this_COMPort->setText(ui->comboBox_COMPort->currentText());//Прописали текущий COM порт

    ui->lineEdit_this_Baudrate->setText(ui->comboBox_Baudrate->currentText());//Прописали текущую скорость порта
}

void MainWindow::on_pingKKMButton_clicked()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;

    Connection connect;

    connect.setSerialPort(ui->comboBox_COMPort->currentText().toStdWString().c_str());

    connect.setBaudrate(MainWindow::convertIntToBaudrate(ui->comboBox_Baudrate->currentText().toInt()));

    if (Atol::isConnection(connect, error) == 0){
        ui->label_pingKKM->setStyleSheet("color: rgb(0, 100, 0)");
        ui->label_pingKKM->setText(codec->toUnicode("Связь есть"));
    }
    else{
        ui->label_pingKKM->setStyleSheet("color: rgb(255, 0, 0)");
        ui->label_pingKKM->setText(codec->toUnicode("Связи нет\n") + convert.to_bytes(error).c_str());
    }
}

Baudrate MainWindow::convertIntToBaudrate(int baudrate_){
    switch (baudrate_) { //Задаём скорость порта
        case 1200 :
            return Baudrate::PORT_BR_1200;
        case 2400:
            return Baudrate::PORT_BR_2400;
        case 4800:
            return Baudrate::PORT_BR_4800;
        case 9600:
            return Baudrate::PORT_BR_9600;
        case 19200:
            return Baudrate::PORT_BR_19200;
        case 38400:
            return Baudrate::PORT_BR_38400;
        case 57600:
            return Baudrate::PORT_BR_57600;
        case 115200:
            return Baudrate::PORT_BR_115200;
        case 230400:
            return Baudrate::PORT_BR_230400;
        case 460800:
            return Baudrate::PORT_BR_460800;
        case 921600:
            return Baudrate::PORT_BR_921600;
    }

    return Baudrate::PORT_BR_115200;
}

void MainWindow::on_shiftCloseButton_clicked()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;

    if (Atol::shiftClose(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode("Ошибка печати Z-отчёта")),
                    tr(str.c_str()),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("Повторить")));
            messageBox.setButtonText(QMessageBox::No, (codec->toUnicode("Отмена")));

        if(messageBox.exec() == QMessageBox::Yes){
            MainWindow::on_shiftCloseButton_clicked();
            return;
        }
        else {
            return;
        }
    }

    QMessageBox messageBox(QMessageBox::Information,
                (codec->toUnicode("Retail luxury")),
                (codec->toUnicode("Смена закрыта")),
                QMessageBox::Yes,
                this);
     messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("OK")));
     messageBox.exec();
}

void MainWindow::on_pushButton_setCashier_clicked(){

    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;

    std::wstring CashierName = ui->lineEdit_askCashierName->text().toStdWString().c_str();
    std::wstring CashierINN  = ui->lineEdit_askCashierINN->text().toStdWString().c_str();

    std::wstring we = ui->lineEdit_askCashierName->text().toStdWString().c_str();

    if ((CashierName == L"" && CashierINN == L"") || (CashierName == L"" && CashierINN != L"")){
        return;
    }

    if (!MainWindow::validationINN(CashierINN)){
        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode("Retail luxury")),
                    (codec->toUnicode("ИНН невалиден")),
                    QMessageBox::Yes,
                    this);
         messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("OK")));
         messageBox.exec();
         return;
    }


    kkmparameters.setCashierName(CashierName);
    kkmparameters.setCashierINN(CashierINN);

    if(CashierINN == L""){
        ui->label_CurrentCashier_Name_INN->setText(codec->toUnicode("Текущий кассир:   ") +
                                                   convert.to_bytes(CashierName).c_str());
    }
    else{
        ui->label_CurrentCashier_Name_INN->setText(codec->toUnicode("Текущий кассир:   ") +
                                                   convert.to_bytes(CashierName).c_str() + codec->toUnicode(",   ИНН:  ") + convert.to_bytes(CashierINN).c_str());
    }
    ui->label_CurrentCashier_Name_INN->setStyleSheet("color: rgb(0, 100, 0)");
}

bool MainWindow::validationINN(const std::wstring &CashierINN){

    if (CashierINN.length() == 0)
        return true;

    if (CashierINN.length() != 10 && CashierINN.length() != 12){
        return false;
    }

    if (CashierINN.find_first_not_of(L"0123456789") != std::wstring::npos)
        return false;

    return true;
}

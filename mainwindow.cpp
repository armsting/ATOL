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
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shiftOpenButton_clicked()
{
    std::wstring error;
    Connection connect(L"COM6");
    setlocale( LC_ALL,"Russian" );
    Position position_1(L"Позиция°", 1000, 2, VATRate::VAT120);

    KkmParameters param;

    param.setConnection(connect);
    param.addPosition(position_1);
    param.setCashierName(L"Юра ааап");
    param.setPayBankCardMoney(2000);
    param.setCheckType(CheckType::SALE_RETURN);

    if (Atol::shiftOpen(param, error) < 0){
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
        std::string str = convert.to_bytes(error);

        QMessageBox msgBox;
        msgBox.setWindowTitle(codec->toUnicode("Ошибка открытия смены"));
        msgBox.setText(str.c_str());
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes){
            MainWindow::on_shiftOpenButton_clicked();
        }else {
        // do something else
        }
    }
}

void MainWindow::on_x_reportButton_clicked()
{
    std::wstring error;
    Connection connect(L"COM6");
    Position position_1(L"Позиция°", 1000, 2, VATRate::VAT120);

    KkmParameters param;
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    param.setConnection(connect);
    param.addPosition(position_1);
    param.setCashierName(L"Юра ааап");
    param.setPayBankCardMoney(2000);
    param.setCheckType(CheckType::SALE_RETURN);

    if (Atol::x_report(param, error) < 0){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
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
        }else {
            return;
        }
    }

    QMessageBox messageBox(QMessageBox::Information,
                (codec->toUnicode("Retail luxury")),
                (codec->toUnicode("Х-отчёт успешно распечатан")),
                QMessageBox::Yes,
                this);
     messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("Ок")));
     messageBox.exec();
}

void MainWindow::on_settingsButton_clicked()
{
    std::wstring error;
    Connection connect(L"COM6");
    Position position_1(L"Позиция55", 1000, 2, VATRate::VAT120);
    Position position_2(L"Позиция//*/", 1000, 2, VATRate::VATNO);
    Position position_3(L"Позиция666", 1000, 2, VATRate::VAT120);

    KkmParameters param;
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    param.setConnection(connect);
    param.addPosition(position_1);
    param.addPosition(position_2);
    param.addPosition(position_3);
    param.setCashierName(L"Просто Юра беза");
    param.setPayCashMoney(12000);
    param.setCheckType(CheckType::SALE);

    if (Atol::formReceipt(param, error) < 0){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
        std::string str = convert.to_bytes(error);

        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode("Не удалось чек зарегать")),
                    tr(str.c_str()),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("Повторить")));
            messageBox.setButtonText(QMessageBox::No, (codec->toUnicode("Отмена")));

        if(messageBox.exec() == QMessageBox::Yes){
            MainWindow::on_settingsButton_clicked();
            return;
        }else {
            return;
        }
    }
}

void MainWindow::on_shiftClose_clicked()
{
    std::wstring error;
    Connection connect(L"COM6");

    KkmParameters param;
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    param.setConnection(connect);
    param.setCashierName(L"Просто Юра беза");
    param.setPayBankCardMoney(6000);
    param.setCheckType(CheckType::SALE);

    if (Atol::shiftClose(param, error) < 0){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
        std::string str = convert.to_bytes(error);

        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode("Не удалось закрыть смену")),
                    tr(str.c_str()),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("Повторить")));
            messageBox.setButtonText(QMessageBox::No, (codec->toUnicode("Отмена")));

        if(messageBox.exec() == QMessageBox::Yes){
            MainWindow::on_shiftClose_clicked();
            return;
        }else {
            return;
        }
    }
}

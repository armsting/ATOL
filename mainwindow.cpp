#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <device.h>
#include "atol.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Device::getComPortList(comPortList);

    ui->setupUi(this);

    init();//Первичная инициализация интерфейса при включении программы

    cash_insert_form = new CashInsertWithdraw();//Создание формы для внесений/изъятий

    /*Связываем сигнал от кнопки Внести формы для внесений/изъятий со слотом Внесение головной формы и передаём сумму внесённых денег*/
    connect(cash_insert_form, SIGNAL(on_click_Insert_cash(double)), this, SLOT(on_Insert_cash(double)));

    /*Связываем сигнал от кнопки Изъять формы для внесений/изъятий со слотом Изъятие головной формы и передаём сумму изъятых денег*/
    connect(cash_insert_form, SIGNAL(on_click_Withdraw_cash(double)), this, SLOT(on_Withdraw_cash(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cash_insert_form;
}

void MainWindow::on_shiftOpenButton_clicked()
{
    if (Atol::shiftOpen(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        if(message("Ошибка печати отчёта об открытии смены", str, QMessageBox::Warning, true) == QMessageBox::Yes){
            MainWindow::on_shiftOpenButton_clicked();
            return;
        }
        else {
            return;
        }
    }

    message("Retail luxury", "Смена открыта", QMessageBox::Information, false);
}

void MainWindow::on_x_reportButton_clicked()
{
    if (Atol::x_report(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        if(message("Ошибка при печати Х-отчёта", str, QMessageBox::Warning, true) == QMessageBox::Yes){
            MainWindow::on_x_reportButton_clicked();
            return;
        }
        else {
            return;
        }
    }

    message("Retail luxury", "Х-отчёт успешно распечатан", QMessageBox::Information, false);
}

void MainWindow::on_refresh_COMPort_listButton_clicked()
{
    Device::getComPortList(comPortList);//Обновили список COM портов

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
    Connection connect;

    connect.setSerialPort(ui->comboBox_COMPort->currentText().toStdWString().c_str());

    connect.setBaudrate(MainWindow::convertIntToBaudrate(ui->comboBox_Baudrate->currentText().toInt()));

    if (Atol::isConnection(connect, error) == 0){
        ui->label_pingKKM->setStyleSheet("color: rgb(0, 100, 0)");
        ui->label_pingKKM->setText(codec->toUnicode("\nСвязь есть"));
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
    if (Atol::shiftClose(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        if(message("Ошибка печати Z-отчёта", str, QMessageBox::Warning, true) == QMessageBox::Yes){
            MainWindow::on_shiftCloseButton_clicked();
            return;
        }
        else {
            return;
        }
    }

    message("Retail luxury", "Смена закрыта", QMessageBox::Information, false);
}

void MainWindow::on_pushButton_setCashier_clicked(){

    std::wstring CashierName = ui->lineEdit_askCashierName->text().toStdWString().c_str();
    std::wstring CashierINN  = ui->lineEdit_askCashierINN->text().toStdWString().c_str();

    std::wstring we = ui->lineEdit_askCashierName->text().toStdWString().c_str();

    if ((CashierName == L"" && CashierINN == L"") || (CashierName == L"" && CashierINN != L"")){
        return;
    }

    if (!Device::validationINN(CashierINN)){
        message("Retail luxury", "ИНН невалиден", QMessageBox::Warning, false);
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
}

void MainWindow::on_Insert_Withdraw_cashButton_clicked()
{
    cash_insert_form->show();//Запуск формы внесения/иъятия
}

void MainWindow::on_Insert_cash(double cash){
/*
   kkmparameters.setPayCashMoney(cash);

   if (Atol::cashInsert(kkmparameters, error) < 0){

       std::string str = convert.to_bytes(error);

       if(message("Ошибка внесения наличности", str, QMessageBox::Warning, true) == QMessageBox::Yes){
           MainWindow::on_Insert_cash(cash);
           return;
        }
        else {
           return;
        }
    }
*/
    message("Retail luxury", "Внесено: " + std::to_string(cash) + " рублей", QMessageBox::Information, false);
    cash_insert_form->raise();
}

void MainWindow::on_Withdraw_cash(double cash){
/*
    kkmparameters.setPayCashMoney(cash);

    if (Atol::cashWithdraw(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        if(message("Ошибка изъятия наличности", str, QMessageBox::Warning, true) == QMessageBox::Yes){
            MainWindow::on_Withdraw_cash(cash);
            return;
        }
        else {
            return;
           }
       }
*/
     message("Retail luxury", "Изъято: " + std::to_string(cash) + " рублей", QMessageBox::Information, false);
     cash_insert_form->raise();
}

//  Переопределяем событие закрытия основной формы. Если закрыли основную форму, то закрываем и другие формы, тем самым завершая выполения программы
void MainWindow::closeEvent( QCloseEvent* event )
{
    cash_insert_form->close();
}

// Метод отображения информационных окон и окон запроса действия
int MainWindow::message(const std::string &title,const std::string &message, QMessageBox::Icon icon, bool request_for_action){
    if(request_for_action){
        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode(title.c_str())),
                    tr(message.c_str()),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("Повторить")));
            messageBox.setButtonText(QMessageBox::No, (codec->toUnicode("Отмена")));
            return messageBox.exec();
    }

    QMessageBox messageBox(icon,
                (codec->toUnicode(title.c_str())),
                (codec->toUnicode(message.c_str())),
                QMessageBox::Yes,
                this);
     messageBox.setWindowFlag(Qt::WindowStaysOnTopHint);
     messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("OK")));
     return messageBox.exec();
}

void MainWindow::init(){
    ui->comboBox_COMPort->clear();//Очистка списка COM портов

    for(auto COMPort: comPortList){//Заполняем список COM портов системы
       ui->comboBox_COMPort->addItem(QString::fromStdWString(COMPort));
    }

    QFont f("MS Shell Dlg 2", 10);

    ui->label_CurrentCashier_Name_INN->setFont(f);
    ui->label_pingKKM->setFont(f);
    ui->label_pingKKM->setAlignment(Qt::AlignHCenter);
    ui->label_CurrentCashier_Name_INN->setStyleSheet("color: rgb(0, 100, 0)");
}

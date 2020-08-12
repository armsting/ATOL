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

    payment_form = new Payment();//Создание формы оплаты

    /*Связываем сигнал от кнопки Внести формы для внесений/изъятий со слотом Внесение головной формы и передаём сумму внесённых денег*/
    connect(cash_insert_form, SIGNAL(on_click_Insert_cash(double)), this, SLOT(on_Insert_cash(double)));

    /*Связываем сигнал от кнопки Изъять формы для внесений/изъятий со слотом Изъятие головной формы и передаём сумму изъятых денег*/
    connect(cash_insert_form, SIGNAL(on_click_Withdraw_cash(double)), this, SLOT(on_Withdraw_cash(double)));

    /*Связываем сигнал от кнопки Оплата основной формы и слот от формы Оплаты с передеачей туда суммы к оплате*/
    connect(this, SIGNAL(paymentSum(double, CheckType)), payment_form, SLOT(getPaymentSum(double, CheckType)));

    /*Связываем сигнал от кнопки Оплатить формы оплаты со слотом pay_a_receipt головной формы и передаём сумму нала/безнала*/
    connect(payment_form, SIGNAL(form_of_payment(double, double)), this, SLOT(pay_a_receipt(double, double)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cash_insert_form;
    delete payment_form;
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
    cash_insert_form->raise();
}

void MainWindow::on_Insert_cash(double cash){

   kkmparameters.setPayCashMoney(cash);

   if (Atol::cashInsert(kkmparameters, error) < 0){

       std::string str = convert.to_bytes(error);

       if(message("Ошибка внесения наличности", str, QMessageBox::Warning, true) == QMessageBox::Yes){
           MainWindow::on_Insert_cash(cash);
           return;
        }
        else {
           cash_insert_form->close();
           return;
        }
    }

   char sum[20];

   sprintf (&sum[0], "%.2lf", cash);

   message("Retail luxury", "Внесено: " + std::string(sum) + " рублей", QMessageBox::Information, false);
   cash_insert_form->close();
}

void MainWindow::on_Withdraw_cash(double cash){

    kkmparameters.setPayCashMoney(cash);

    if (Atol::cashWithdraw(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        if(message("Ошибка изъятия наличности", str, QMessageBox::Warning, true) == QMessageBox::Yes){
            MainWindow::on_Withdraw_cash(cash);
            return;
        }
        else {
            cash_insert_form->close();
            return;
           }
       }

    char sum[20];

    sprintf (&sum[0], "%.2lf", cash);

    message("Retail luxury", "Изъято: " + std::string(sum) + " рублей", QMessageBox::Information, false);
    cash_insert_form->close();
}

//  Переопределяем событие закрытия основной формы. Если закрыли основную форму, то закрываем и другие формы, тем самым завершая выполения программы
void MainWindow::closeEvent( QCloseEvent* event )
{
    cash_insert_form->close();
    payment_form->close();
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

    on_pushButton_addPosition_clicked();//Добавляем одну пустую строку при запуске программы
}

void MainWindow::on_payButton_clicked()
{
    double price;
    double quantity;
    double payment_sum = 0;

    kkmparameters.clearPositionsList();
    Position position;

    if (ui->tableWidget_saleList->rowCount() == 0){
        message("Ошибка", "Список товарных позиций пуст.", QMessageBox::Warning, false);
        return;
    }

    for(int row = ui->tableWidget_saleList->rowCount() - 1; row >= 0; row--){

        try {
            price = get_price(row);
            quantity = get_quantity(row);

            position.setName(get_product_name(row));
            position.setPrice(get_price(row));
            position.setQuantity(get_quantity(row));
            position.setTax_type(getVATRate(row));

        } catch (const char *str) {

           message("Ошибка", &str[0], QMessageBox::Warning, false);
           return;
        } catch (...){
            message("Ошибка", "Неизвестная ошибка", QMessageBox::Warning, false);
            return;
        }

        payment_sum += price * quantity;
        kkmparameters.addPosition(position);
    }

    payment_form->clear();
    payment_form->show();
    payment_form->raise();

    if(ui->comboBox_checkType->currentText().toStdString() == "ПРИХОД"){
        emit paymentSum(payment_sum, CheckType::SALE);
        kkmparameters.setCheckType(CheckType::SALE);
    }

    if(ui->comboBox_checkType->currentText().toStdString() == "РАСХОД"){
        emit paymentSum(payment_sum, CheckType::BUY);
        kkmparameters.setCheckType(CheckType::BUY);
    }

    if(ui->comboBox_checkType->currentText().toStdString() == "ВОЗВРАТ ПРИХОДА"){
        emit paymentSum(payment_sum, CheckType::SALE_RETURN);
        kkmparameters.setCheckType(CheckType::SALE_RETURN);
    }

    if(ui->comboBox_checkType->currentText().toStdString() == "ВОЗВРАТ РАСХОДА"){
        emit paymentSum(payment_sum, CheckType::BUY_RETURN);
        kkmparameters.setCheckType(CheckType::BUY_RETURN);
    }
}

void MainWindow::pay_a_receipt(double be_paid_in_cash_, double be_paid_in_bank_){

    kkmparameters.setPayCashMoney(be_paid_in_cash_);
    kkmparameters.setPayBankCardMoney(be_paid_in_bank_);

    if (Atol::formReceipt(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        if(message("Ошибка регистрации чека", str, QMessageBox::Warning, true) == QMessageBox::Yes){
            MainWindow::pay_a_receipt(be_paid_in_cash_, be_paid_in_bank_);
            return;
        }
        else {
            payment_form->close();
            return;
           }
       }
    payment_form->close();
    message("Retail luxury", "Регистрация чека прошла успешно!\nВыйдайте чек покупателю", QMessageBox::Information, false);

    on_pushButton_clearTable_clicked();
}

void MainWindow::on_pushButton_addPosition_clicked()
{
    int rowCount = ui->tableWidget_saleList->rowCount();

    ui->tableWidget_saleList->insertRow(0);
    QComboBox *enumNDS = new QComboBox();
    enumNDS->addItem("БЕЗ НДС");
    enumNDS->addItem("НДС-20%");
    enumNDS->addItem("НДС-10%");
    enumNDS->addItem("НДС-0%");

    QLineEdit *number = new QLineEdit();
    QLineEdit *price = new QLineEdit();
    QLineEdit *quantity = new QLineEdit();
    QLineEdit *product_name = new QLineEdit();

    number->setText(std::to_string(rowCount + 1).c_str());

    price->setText("1,00");
    quantity->setText("1,000");


    product_name->setText("Условный товар");

    number->setFrame( false );
    price->setFrame( false );
    quantity->setFrame( false );
    product_name->setFrame( false );

    number->setReadOnly(true);

    QDoubleValidator* doubleValidator_price = new QDoubleValidator(0, 40000000, 2);
    QDoubleValidator* doubleValidator_quantity = new QDoubleValidator(0.001, 9999, 3);

    doubleValidator_price->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator_quantity->setNotation(QDoubleValidator::StandardNotation);

    price->setValidator(doubleValidator_price);
    quantity->setValidator(doubleValidator_quantity);

    ui->tableWidget_saleList->setCellWidget(0, 0, number);
    ui->tableWidget_saleList->setCellWidget(0, 1, product_name);
    ui->tableWidget_saleList->setCellWidget(0, 2 , price);
    connect(price, SIGNAL(textChanged(QString)), this, SLOT(calculate_paymentSum()));

    ui->tableWidget_saleList->setCellWidget(0, 3 , quantity);
    connect(quantity, SIGNAL(textChanged(QString)), this, SLOT(calculate_paymentSum()));

    ui->tableWidget_saleList->setCellWidget(0, 4 , enumNDS);


    ui->tableWidget_saleList->setColumnWidth(0, 50);
    ui->tableWidget_saleList->setColumnWidth(1, 510);
    ui->tableWidget_saleList->setColumnWidth(2, 80);
    ui->tableWidget_saleList->setColumnWidth(3, 80);
    ui->tableWidget_saleList->setColumnWidth(4, 80);
    ui->tableWidget_saleList->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);

    calculate_paymentSum();
}

void MainWindow::on_pushButton_rowDelete_clicked()
{
   int row = ui->tableWidget_saleList->rowCount();

   if(row == 0){      
       on_pushButton_addPosition_clicked();
       return;
   }

   if(row == 1){
       clearTableRow(1);
       on_pushButton_addPosition_clicked();
       return;
   }

   clearTableRow(1);

   calculate_paymentSum();
}

void MainWindow::on_pushButton_clearTable_clicked(){

    for(int row = ui->tableWidget_saleList->rowCount(); row > 0; row--){
         clearTableRow(row);
       }
    on_pushButton_addPosition_clicked();
}

void MainWindow::clearTableRow(int row){

    ui->tableWidget_saleList->removeCellWidget(row - 1, 0);
    ui->tableWidget_saleList->removeCellWidget(row - 1, 1);
    ui->tableWidget_saleList->removeCellWidget(row - 1, 2);
    ui->tableWidget_saleList->removeCellWidget(row - 1, 3);
    ui->tableWidget_saleList->removeCellWidget(row - 1, 4);

    ui->tableWidget_saleList->removeRow(row - 1);
}

const std::wstring MainWindow::get_product_name(int row){

    QWidget *widget = ui->tableWidget_saleList->cellWidget(row, 1);
    QLineEdit *lineEdit = static_cast<QLineEdit*>(widget);

    return lineEdit->text().toStdWString();
}

double MainWindow::get_price(int row){

    QWidget *widget = ui->tableWidget_saleList->cellWidget(row, 2);
    QLineEdit *lineEdit = static_cast<QLineEdit*>(widget);

    std::string price = lineEdit->text().toStdString();
    price = regex_replace(price, std::regex(","), ".");

    try {
        stod(price);
    } catch (...) {
        throw ("Цена у товарной позиции не задана");
    }

    return stod(price);
}

double MainWindow::get_quantity(int row){

    QWidget *widget = ui->tableWidget_saleList->cellWidget(row, 3);
    QLineEdit *lineEdit = static_cast<QLineEdit*>(widget);

    std::string quantity = lineEdit->text().toStdString();
    quantity = regex_replace(quantity, std::regex(","), ".");

    try {
        stod(quantity);
    } catch (...) {
        throw "Количество у товарной позиции не задано";
    }

    return stod(quantity);
}

VATRate MainWindow::getVATRate(int row){

    QWidget *widget = ui->tableWidget_saleList->cellWidget(row, 4);
    QComboBox *enumNDS = static_cast<QComboBox*>(widget);
    std::string NDS = enumNDS->currentText().toStdString();

    if(NDS == "НДС-0%"){
        return VATRate::VAT0;
    }

    if(NDS == "НДС-20%"){
        return VATRate::VAT20;
    }

    if(NDS == "НДС-10%"){
        return VATRate::VAT10;
    }

    return VATRate::VATNO;
}

void MainWindow::calculate_paymentSum(){

    double price;
    double quantity;
    double payment_sum = 0;
    char sum[20];

    ui->label_total_for_the_receipt->setStyleSheet("color: rgb(255, 69, 0)");

    for(int row = ui->tableWidget_saleList->rowCount() - 1; row >= 0; row--){
        try {
            price = get_price(row);
            quantity = get_quantity(row);

        } catch (...){
            ui->label_total_for_the_receipt->setText( QString::fromStdString("ИТОГО: 0,00"));
            return;
        }

        payment_sum += price * quantity;
    }

    sprintf (&sum[0], "%.2lf", payment_sum);

    ui->label_total_for_the_receipt->setText( QString::fromStdString("ИТОГО: ") + std::string(sum).c_str());
}

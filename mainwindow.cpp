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

    ui->comboBox_COMPort->clear();//������� ������ COM ������

    for(auto COMPort: comPortList){//��������� ������ COM ������ �������
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
                    (codec->toUnicode("������ ������ ������ �� �������� �����")),
                    tr(str.c_str()),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("���������")));
            messageBox.setButtonText(QMessageBox::No, (codec->toUnicode("������")));

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
                (codec->toUnicode("����� �������")),
                QMessageBox::Yes,
                this);
     messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("��")));
     messageBox.exec();
}

void MainWindow::on_x_reportButton_clicked()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;

    if (Atol::x_report(kkmparameters, error) < 0){

        std::string str = convert.to_bytes(error);

        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode("������ ��� ������ �-������")),
                    tr(str.c_str()),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("���������")));
            messageBox.setButtonText(QMessageBox::No, (codec->toUnicode("������")));

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
                (codec->toUnicode("�-����� ������� ����������")),
                QMessageBox::Yes,
                this);
     messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("��")));
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
    getComPortList(comPortList);//�������� ������ COM ������

    ui->comboBox_COMPort->clear();//������� ������ COM ������

    for(auto COMPort: comPortList){//��������� ������ COM ������ �������
       ui->comboBox_COMPort->addItem(QString::fromStdWString(COMPort));
    }
}

void MainWindow::on_applySettingsButton_clicked()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    connection.setSerialPort(convert.from_bytes(ui->comboBox_COMPort->currentText().toStdString())); //������ ������� COM ����

    connection.setBaudrate(MainWindow::convertIntToBaudrate(ui->comboBox_Baudrate->currentText().toInt())); //������ �������� �������� COM �����

    kkmparameters.setConnection(connection);
    ui->lineEdit_this_COMPort->setText(ui->comboBox_COMPort->currentText());//��������� ������� COM ����
    ui->lineEdit_this_Baudrate->setText(ui->comboBox_Baudrate->currentText());//��������� ������� �������� �����
}

void MainWindow::on_pingKKMButton_clicked()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    Connection connect;

    connect.setSerialPort(convert.from_bytes(ui->comboBox_COMPort->currentText().toStdString()));
    connect.setBaudrate(MainWindow::convertIntToBaudrate(ui->comboBox_Baudrate->currentText().toInt()));

    if (Atol::isConnection(connect, error) == 0){
        ui->label_pingKKM->setStyleSheet("color: rgb(0, 100, 0)");
        ui->label_pingKKM->setText(codec->toUnicode("����� ����"));
    }
    else{
        ui->label_pingKKM->setStyleSheet("color: rgb(255, 0, 0)");
        ui->label_pingKKM->setText(codec->toUnicode("����� ���\n") + convert.to_bytes(error).c_str());
    }
}

Baudrate MainWindow::convertIntToBaudrate(int Baudrate){
    switch (Baudrate) { //����� �������� �����
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
                    (codec->toUnicode("������ ������ Z-������")),
                    tr(str.c_str()),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("���������")));
            messageBox.setButtonText(QMessageBox::No, (codec->toUnicode("������")));

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
                (codec->toUnicode("����� �������")),
                QMessageBox::Yes,
                this);
     messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("OK")));
     messageBox.exec();
}

void MainWindow::on_pushButton_setCashier_clicked(){

    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::string CashierName = ui->lineEdit_askCashierName->text().toStdString();
    std::string CashierINN  = ui->lineEdit_askCashierINN->text().toStdString();

    if ((CashierName == "" && CashierINN == "") || (CashierName == "" && CashierINN != "")){
        return;
    }

    if (!MainWindow::validationINN(CashierINN)){
        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode("Retail luxury")),
                    (codec->toUnicode("��� ���������")),
                    QMessageBox::Yes,
                    this);
         messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("OK")));
         messageBox.exec();
         return;
    }


    kkmparameters.setCashierName(convert.from_bytes(CashierName));
    kkmparameters.setCashierINN(convert.from_bytes(CashierINN));

    if(CashierINN == ""){
        ui->label_CurrentCashier_Name_INN->setText(codec->toUnicode("������� ������:   ") +
                                                   QString(CashierName.c_str()));
    }
    else{
        ui->label_CurrentCashier_Name_INN->setText(codec->toUnicode("������� ������:   ") +
                                                   QString(CashierName.c_str()) + codec->toUnicode(",   ���:  ") + QString(CashierINN.c_str()));
    }
    ui->label_CurrentCashier_Name_INN->setStyleSheet("color: rgb(0, 100, 0)");
}

bool MainWindow::validationINN(const std::string &CashierINN){

    if (CashierINN.length() == 0)
        return true;

    if (CashierINN.length() != 10 && CashierINN.length() != 12){
        return false;
    }

    if (CashierINN.find_first_not_of("0123456789") != std::string::npos)
        return false;

    return true;
}

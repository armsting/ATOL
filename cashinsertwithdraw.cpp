#include "cashinsertwithdraw.h"
#include "ui_cashinsertwithdraw_form.h"

CashInsertWithdraw::CashInsertWithdraw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CashInsertWithdraw)
{
    ui->setupUi(this);
    QDoubleValidator* doubleValidator = new QDoubleValidator(0, 40000000, 2);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_cash->setValidator(doubleValidator);
}

CashInsertWithdraw::~CashInsertWithdraw()
{
    delete ui;
}

void CashInsertWithdraw::on_pushButton_Clear_clicked()
{
    ui->lineEdit_cash->setText("0,00");
}

void CashInsertWithdraw::on_pushButton_50_clicked()
{
    insertCashSum(50);
}

void CashInsertWithdraw::on_pushButton_cashInsert_clicked()
{
    std::string str = ui->lineEdit_cash->text().toStdString();
    str = regex_replace(str, std::regex(","), ".");

    emit on_click_Insert_cash(stod(str));
}

void CashInsertWithdraw::on_pushButton_cashWithdraw_clicked()
{
    std::string str = ui->lineEdit_cash->text().toStdString();
    str = regex_replace(str, std::regex(","), ".");

    emit on_click_Withdraw_cash(stod(str));
}

void CashInsertWithdraw::on_pushButton_100_clicked()
{
    insertCashSum(100);
}

void CashInsertWithdraw::insertCashSum(double cash){

    std::string str = ui->lineEdit_cash->text().toStdString();
    str = regex_replace(str, std::regex(","), ".");
    double cash_sum;

    try {
        cash_sum = stod(str);
        cash_sum +=  cash;

    } catch (...) {
        on_pushButton_Clear_clicked();
        return;
    }

    char sum[20];

    sprintf (&sum[0], "%.2lf", cash_sum);
    ui->lineEdit_cash->setText(QString::fromStdString(sum));
}

void CashInsertWithdraw::on_pushButton_500_clicked()
{
    insertCashSum(500);
}

void CashInsertWithdraw::on_pushButton_1000_clicked()
{
    insertCashSum(1000);
}

void CashInsertWithdraw::on_pushButton_2000_clicked()
{
    insertCashSum(2000);
}

void CashInsertWithdraw::on_pushButton_5000_clicked()
{
    insertCashSum(5000);
}

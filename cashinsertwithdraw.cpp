#include "cashinsertwithdraw.h"
#include "ui_cashinsertwithdraw_form.h"

CashInsertWithdraw::CashInsertWithdraw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CashInsertWithdraw)
{
    ui->setupUi(this);
}

CashInsertWithdraw::~CashInsertWithdraw()
{
    delete ui;
}

void CashInsertWithdraw::on_pushButton_Clear_clicked()
{
    ui->lineEdit_cash->setText("0.00");
}

void CashInsertWithdraw::on_pushButton_50_clicked()
{
    cash = double(ui->lineEdit_cash->text().toDouble());
    cash += 50.00;
    ui->lineEdit_cash->setText(QString::fromStdString(std::to_string(cash)));
}

void CashInsertWithdraw::on_pushButton_cashInsert_clicked()
{
    on_click();
}

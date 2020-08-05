#include "payment.h"
#include "ui_payment.h"

Payment::Payment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
}

Payment::~Payment()
{
    delete ui;
}

void Payment::on_pushButton_pay_clicked()
{

}

void Payment::getPaymentSum(double paymentSum){

    ui->label_for_payment_sum->setText(("К ОПЛАТЕ: " + std::to_string(paymentSum)).c_str());

}

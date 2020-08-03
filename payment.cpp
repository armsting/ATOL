#include "payment.h"
#include "ui_payment.h"

payment::payment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::payment)
{
    ui->setupUi(this);
}

payment::~payment()
{
    delete ui;
}

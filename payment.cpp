#include "payment.h"
#include "ui_payment.h"

Payment::Payment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);

    QDoubleValidator* doubleValidator = new QDoubleValidator(0, 40000000, 2);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_bank_money->setValidator(doubleValidator);
    ui->lineEdit_cash_money->setValidator(doubleValidator);

    ui->lineEdit_bank_money->setText("0,00");
    ui->lineEdit_cash_money->setText("0,00");
    ui->lineEdit_cash_money->setFocus();
}

Payment::~Payment()
{
    delete ui;
}

void Payment::getPaymentSum(double _paymentSum, CheckType checkType){

    char sum[20];

    sprintf (&sum[0], "%.2lf", _paymentSum);

    paymentSum_ = _paymentSum;


    ui->label_form_of_payment->setText(("НАЛИЧНЫМИ: " + std::string(sum)).c_str());

    ui->label_for_payment_sum->setStyleSheet("color: rgb(39, 100, 100)");
    ui->label_form_of_payment->setStyleSheet("color: rgb(30, 144, 255)");
    ui->label_CheckType->setStyleSheet("color: rgb(255, 69, 0)");

    ui->label_for_payment_sum->setText(QString::fromStdString("К ОПЛАТЕ: " + std::string(sum)));

    switch (checkType) {
        case CheckType::BUY_RETURN:{
            ui->label_CheckType->setText("ВОЗВРАТ РАСХОДА ");
            break;
        }
        case CheckType::SALE_RETURN:{
            ui->label_CheckType->setText("ВОЗВРАТ ПРИХОДА ");
            break;
        }
        case CheckType::BUY:{
            ui->label_CheckType->setText("РАСХОД ");
            break;
        }
        default:{
            ui->label_CheckType->setText("ПРИХОД ");
            break;
        }
}
}

void Payment::on_lineEdit_cash_money_textChanged(const QString &arg1)
{
   layout_of_the_sums();
}

void Payment::on_lineEdit_bank_money_textChanged(const QString &arg1)
{
   layout_of_the_sums();
}

void Payment::layout_of_the_sums(){

    std::string std_be_paid_in_cash = ui->lineEdit_cash_money->text().toStdString();
    std::string std_be_paid_in_bank_ = ui->lineEdit_bank_money->text().toStdString();

    std_be_paid_in_cash = regex_replace(std_be_paid_in_cash, std::regex(","), ".");
    std_be_paid_in_bank_ = regex_replace(std_be_paid_in_bank_, std::regex(","), ".");

    try {
        be_paid_in_cash_ = stod(std_be_paid_in_cash);

    } catch (...) {
        ui->lineEdit_cash_money->setText("0,00");
        be_paid_in_cash_ = 0;
    }

    try {
        be_paid_in_bank_ = stod(std_be_paid_in_bank_);

    } catch (...) {
        ui->lineEdit_bank_money->setText("0,00");
         be_paid_in_bank_ = 0;
    }

    char sum[20];
    char sum_bank[20];

    if(be_paid_in_cash_ == 0 && be_paid_in_bank_ == 0){
         sprintf (&sum[0], "%.2lf", paymentSum_);
         ui->label_form_of_payment->setText(("НАЛИЧНЫМИ: " + std::string(sum)).c_str());
         return;
    }

    if(std::abs(be_paid_in_cash_ - paymentSum_) <= 0.009 && be_paid_in_bank_ == 0){
         sprintf (&sum[0], "%.2lf", paymentSum_);
         ui->label_form_of_payment->setText(("НАЛИЧНЫМИ: " + std::string(sum)).c_str());
         return;
    }

    if(paymentSum_ > (be_paid_in_cash_ + be_paid_in_bank_) && paymentSum_ - (be_paid_in_cash_ + be_paid_in_bank_) >= 0.009){
         sprintf (&sum[0], "%.2lf",  paymentSum_ - (be_paid_in_cash_ + be_paid_in_bank_));
         ui->label_form_of_payment->setText(("ЕЩЁ ВНЕСТИ: " + std::string(sum)).c_str());
         return;
    }

    if(paymentSum_ < ( be_paid_in_cash_+ be_paid_in_bank_)){
         sprintf (&sum[0], "%.2lf", ( be_paid_in_cash_+ be_paid_in_bank_) - paymentSum_);
         ui->label_form_of_payment->setText(("СДАЧА: " + std::string(sum)).c_str());
         return;
    }

    if(be_paid_in_cash_ == 0 && be_paid_in_bank_ != 0){
         sprintf (&sum[0], "%.2lf", be_paid_in_bank_);
         ui->label_form_of_payment->setText(("БЕЗНАЛИЧНЫМИ: " + std::string(sum)).c_str());
         return;
    }

    if(be_paid_in_cash_ != 0 && be_paid_in_bank_ != 0){
         sprintf (&sum[0], "%.2lf", be_paid_in_cash_);
         sprintf (&sum_bank[0], "%.2lf", be_paid_in_bank_);
         ui->label_form_of_payment->setText(("НАЛ: " + std::string(sum) + "\nБЕЗНАЛ: " + std::string(sum_bank)).c_str());
         return;
    }
}

void Payment::on_pushButton_pay_clicked()
{
        QMessageBox messageBox(QMessageBox::Warning,
                    (codec->toUnicode("Неверная сумма оплаты")),
                    (codec->toUnicode("Косяк")),
                    QMessageBox::Yes,
                    this);
         messageBox.setWindowFlag(Qt::WindowStaysOnTopHint);
         messageBox.setButtonText(QMessageBox::Yes, (codec->toUnicode("OK")));
         messageBox.exec();
}

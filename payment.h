#ifndef PAYMENT_H
#define PAYMENT_H

#include <QMainWindow>
#include <QString>
#include <enumkkm.h>
#include <regex>

namespace Ui {
class Payment;
}

class Payment : public QMainWindow
{
    Q_OBJECT

public:
    explicit Payment(QWidget *parent = nullptr);
    ~Payment();

private slots:
    void on_pushButton_pay_clicked();
    void getPaymentSum(double paymentSum, CheckType checkType);

    void on_lineEdit_cash_money_textChanged(const QString &arg1);

    void on_lineEdit_bank_money_textChanged(const QString &arg1);

private:
    Ui::Payment *ui;
    double paymentSum_ = 0;
    double be_paid_in_cash_ = 0;
    double be_paid_in_bank_ = 0;
};

#endif // PAYMENT_H

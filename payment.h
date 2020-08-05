#ifndef PAYMENT_H
#define PAYMENT_H

#include <QMainWindow>
#include <QString>

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
    void getPaymentSum(double paymentSum);

private:
    Ui::Payment *ui;
};

#endif // PAYMENT_H

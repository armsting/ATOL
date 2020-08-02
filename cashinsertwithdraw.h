#pragma

#include <QMainWindow>
#include <QString>
#include <regex>

namespace Ui {
class CashInsertWithdraw;
}

class CashInsertWithdraw : public QMainWindow
{
    Q_OBJECT

public:
    explicit CashInsertWithdraw(QWidget *parent = nullptr);
    ~CashInsertWithdraw();

private slots:
    void on_pushButton_Clear_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_cashInsert_clicked();

    void on_pushButton_cashWithdraw_clicked();

    void on_pushButton_100_clicked();

    void on_pushButton_500_clicked();

    void on_pushButton_1000_clicked();

    void on_pushButton_2000_clicked();

    void on_pushButton_5000_clicked();

signals:
    void on_click_Insert_cash(double cash);
    void on_click_Withdraw_cash(double cash);

private:
    Ui::CashInsertWithdraw *ui;
    std::string getFractionalPart(std::string &str);
    void insertCashSum(double cash);
};

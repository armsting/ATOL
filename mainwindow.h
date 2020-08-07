#pragma once
#include <QMainWindow>
#include "kkmparameters.h"
#include "connection.h"
#include "enumkkm.h"
#include <QTextCodec>
#include <QMessageBox>
#include "cashinsertwithdraw.h"
#include <codecvt>
#include <QString>
#include <locale>
#include <payment.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_shiftOpenButton_clicked();

    void on_x_reportButton_clicked();

    void on_refresh_COMPort_listButton_clicked();

    void on_applySettingsButton_clicked();

    void on_pingKKMButton_clicked();

    void on_shiftCloseButton_clicked();

    void on_pushButton_setCashier_clicked();

    void on_Insert_Withdraw_cashButton_clicked();

    void closeEvent(QCloseEvent* event);

    void on_Insert_cash(double cash);

    void on_Withdraw_cash(double cash);

    int message(const std::string &title, const std::string &message, QMessageBox::Icon icon, bool request_for_action);

    void init();

    void on_payButton_clicked();

signals:
    void paymentSum(double paymentSum, CheckType checkType);

private:
    Ui::MainWindow *ui;
    std::vector<std::wstring> comPortList;
    KkmParameters kkmparameters;
    Connection connection;
    std::wstring error;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    Baudrate convertIntToBaudrate(int baudrate_);
    CashInsertWithdraw *cash_insert_form;
    Payment *payment_form;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;//Конвертация между wstring и string
};

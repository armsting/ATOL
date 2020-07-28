#pragma once
#include <QMainWindow>
#include "kkmparameters.h"
#include "connection.h"
#include "enumkkm.h"
#include <QTextCodec>

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

    void on_Insert_Withdraw_cash_clicked();

    void on_payButton_clicked();

    void on_refresh_COMPort_listButton_clicked();

    void on_applySettingsButton_clicked();

    void on_pingKKMButton_clicked();

    void on_shiftCloseButton_clicked();

    void on_pushButton_setCashier_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::wstring> comPortList;
    KkmParameters kkmparameters;
    Connection connection;
    std::wstring error;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    Baudrate convertIntToBaudrate(int baudrate_);
};

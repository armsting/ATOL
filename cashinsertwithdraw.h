#pragma

#include <QMainWindow>
#include <QString>

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

signals:
    void on_click();

private:
    Ui::CashInsertWithdraw *ui;
    double cash;
};

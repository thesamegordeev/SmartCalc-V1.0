#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>

namespace Ui {
class Deposit;
}

class Deposit : public QWidget
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr);
    ~Deposit();

private slots:
    void on_clear_clicked();

    void on_calculate_clicked();

    void on_capitalisation_stateChanged(int arg1);

private:
    Ui::Deposit *ui;
};

QDate NextRepWithd(QDate now, int period);
QDate NextPayDate(QDate now, int period);

#endif // DEPOSIT_H

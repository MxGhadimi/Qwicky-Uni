#ifndef SHOWCUSTOMER_H
#define SHOWCUSTOMER_H

#include <QWidget>
#include "commonincludes.h"

namespace Ui {
class Showcustomer;
}

class Showcustomer : public QWidget
{
    Q_OBJECT

public:
    explicit Showcustomer(QWidget *parent = nullptr);
    ~Showcustomer();
    void showData(int input_customer_id);
    void addCustomer();

private slots:
    void on_Edit_PB_clicked();

    void on_Delete_PB_clicked();

    void on_Add_PB_clicked();

private:
    Ui::Showcustomer *ui;
    QString first_name;
    QString last_name;
    QString phone_number;
    QString address;
    double credit;
    double debt;
    QString username;
    QString password;
    int customer_id;
};

#endif // SHOWCUSTOMER_H

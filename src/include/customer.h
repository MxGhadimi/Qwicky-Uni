#ifndef CUSTOMER_H
#define CUSTOMER_H


#include <QWidget>
#include "commonincludes.h"

namespace Ui {
class Customer;
}

class Customer : public QWidget
{
    Q_OBJECT

public:
    explicit Customer(QWidget *parent = nullptr);
    ~Customer();
    void writeData(QString input_first_name, QString input_last_name, QString input_phone_number, QString input_address, double input_credit, double input_debt, QString input_username, QString input_password);
    void readData(int input_customer_id);
    void showData();
    void updateFirstName(QString input_first_name, int customer_id);
    void updateLastName(QString input_last_name, int customer_id);
    void updatePhoneNumber(QString input_phone_number, int customer_id);
    void updateAddress(QString input_address, int customer_id);
    void updateCredit(double input_credit, int customer_id);
    void updateDebt(double input_debt, int customer_id);
    void updateUsername(const QString &input_username, int customer_id);

private slots:
    void on_Edit_PB_clicked();

    void on_Delete_PB_clicked();

private:
    Ui::Customer *ui;

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

#endif // CUSTOMER_H

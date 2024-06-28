#include "showcustomer.h"
#include "ui_showcustomer.h"
#include "customer.h"

Showcustomer::Showcustomer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Showcustomer)
{
    ui->setupUi(this);
    ui->Username_LE->setEnabled(false);
    ui->Name_LE->setEnabled(false);
    ui->Lastname_LE->setEnabled(false);
    ui->Phonenumber_LE->setEnabled(false);
    ui->Address_LE->setEnabled(false);
    ui->Credit_LE->setEnabled(false);
    ui->Debt_LE->setEnabled(false);
    ui->Customerid_L->setEnabled(false);

    ui->Password_L->hide();
    ui->Password_LE->hide();

    ui->Add_PB->hide();
}

Showcustomer::~Showcustomer()
{
    delete ui;
}

void Showcustomer::addCustomer() {
    ui->Add_PB->show();
    ui->Password_L->show();
    ui->Password_LE->show();
    ui->Username_LE->setEnabled(true);
    ui->Name_LE->setEnabled(true);
    ui->Lastname_LE->setEnabled(true);
    ui->Phonenumber_LE->setEnabled(true);
    ui->Address_LE->setEnabled(true);
    ui->Credit_LE->setEnabled(true);
    ui->Debt_LE->setEnabled(true);
    ui->Customerid_L->setEnabled(true);
    ui->Edit_PB->hide();
}


void Showcustomer::showData(int input_customer_id) {
    customer_id = input_customer_id;
    QSqlQuery q(QSqlDatabase::database("customer"));
    q.prepare("SELECT * FROM Customers WHERE id = :id");
    q.bindValue(":id", customer_id);
    if (!q.exec()) qDebug() << "Error executing query: " << q.lastError().text();

    if (q.next()) {
        first_name = q.value("first_name").toString();
        last_name = q.value("last_name").toString();
        phone_number = q.value("phone_number").toString();
        address = q.value("address").toString();
        credit = q.value("credit").toDouble();
        debt = q.value("debt").toDouble();
        username = q.value("username").toString();
        password = q.value("password").toString();

        ui->Username_LE->setText(username);
        ui->Name_LE->setText(first_name);
        ui->Lastname_LE->setText(last_name);
        ui->Phonenumber_LE->setText(phone_number);
        ui->Address_LE->setText(address);
        ui->Credit_LE->setText(QString::number(credit));
        ui->Debt_LE->setText(QString::number(debt));
        ui->Customerid_L->setText(QString::number(customer_id));
    }
    else qDebug() << "No rows found in the table";
    show();
}

void Showcustomer::on_Edit_PB_clicked() {
    static bool edit_mode_on = false;
    if(!edit_mode_on) {
        ui->Edit_PB->setText("Done");
        ui->Username_LE->setEnabled(true);
        ui->Name_LE->setEnabled(true);
        ui->Lastname_LE->setEnabled(true);
        ui->Phonenumber_LE->setEnabled(true);
        ui->Address_LE->setEnabled(true);
        ui->Credit_LE->setEnabled(true);
        ui->Debt_LE->setEnabled(true);
        ui->Customerid_L->setEnabled(true);
        edit_mode_on = true;
    }
    else {
        ui->Edit_PB->setText("Edit");
        ui->Username_LE->setEnabled(false);
        ui->Name_LE->setEnabled(false);
        ui->Lastname_LE->setEnabled(false);
        ui->Phonenumber_LE->setEnabled(false);
        ui->Address_LE->setEnabled(false);
        ui->Credit_LE->setEnabled(false);
        ui->Debt_LE->setEnabled(false);
        ui->Customerid_L->setEnabled(false);
        edit_mode_on = false;

        Customer *customer = new Customer(this);
        if (username != ui->Username_LE->text()) customer->updateUsername(ui->Username_LE->text(), customer_id);
        if (first_name != ui->Name_LE->text()) customer->updateFirstName(ui->Name_LE->text(), customer_id);
        if (last_name != ui->Lastname_LE->text()) customer->updateLastName(ui->Lastname_LE->text(), customer_id);
        if (phone_number != ui->Phonenumber_LE->text()) customer->updatePhoneNumber(ui->Phonenumber_LE->text(), customer_id);
        if (address != ui->Address_LE->text()) customer->updateAddress(ui->Address_LE->text(), customer_id);
        if (credit != ui->Credit_LE->text().toDouble()) customer->updateCredit(ui->Credit_LE->text().toDouble(), customer_id);
        if (debt != ui->Debt_LE->text().toDouble()) customer->updateDebt(ui->Debt_LE->text().toDouble(), customer_id);
        QMessageBox::information(nullptr, "Update Customer", "Updated!");
    }
}


void Showcustomer::on_Delete_PB_clicked() {
    QSqlQuery q(QSqlDatabase::database("customer"));
    q.prepare("DELETE FROM Customers WHERE id = :id");
    q.bindValue(":id", customer_id);
    if (!q.exec()) qDebug() << "Failed to delete customer: " << q.lastError().text();
    else {
        qDebug() << "Customer deleted successfully";
        QMessageBox::information(nullptr, "Delete Customer", "Deleted!");
        close();
    }
}


void Showcustomer::on_Add_PB_clicked() {
    Customer *customer = new Customer(this);
    customer->writeData(ui->Name_LE->text(), ui->Lastname_LE->text(), ui->Phonenumber_LE->text(), ui->Address_LE->text(), ui->Credit_LE->text().toDouble(), ui->Debt_LE->text().toDouble(), ui->Username_LE->text(), ui->Password_LE->text());
}


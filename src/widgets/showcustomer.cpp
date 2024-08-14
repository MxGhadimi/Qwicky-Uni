#include "showcustomer.h"
#include "ui_showcustomer.h"

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
    if (customer.readData(input_customer_id)) {
        customer_id = input_customer_id;
        ui->Username_LE->setText(customer.getUsername());
        ui->Name_LE->setText(customer.getFirstName());
        ui->Lastname_LE->setText(customer.getLastName());
        ui->Phonenumber_LE->setText(customer.getPhoneNumber());
        ui->Address_LE->setText(customer.getAddress());
        ui->Credit_LE->setText(QString::number(customer.getCredit()));
        ui->Debt_LE->setText(QString::number(customer.getDebt()));
        ui->Customerid_L->setText("#" + QString::number(customer_id));
        show();
    }
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

        bool updated = true;
        if (customer.getUsername() != ui->Username_LE->text()) {
            if (!customer.updateUsername(ui->Username_LE->text(), customer_id)) updated = false;
        }
        if (customer.getFirstName() != ui->Name_LE->text()) {
            if (!customer.updateFirstName(ui->Name_LE->text(), customer_id)) updated = false;
        }
        if (customer.getLastName() != ui->Lastname_LE->text()) {
            if (!customer.updateLastName(ui->Lastname_LE->text(), customer_id)) updated = false;
        }
        if (customer.getPhoneNumber() != ui->Phonenumber_LE->text()) {
            if (!customer.updatePhoneNumber(ui->Phonenumber_LE->text(), customer_id)) updated = false;
        }
        if (customer.getAddress() != ui->Address_LE->text()) {
            if (!customer.updateAddress(ui->Address_LE->text(), customer_id)) updated = false;
        }
        if (customer.getCredit() != ui->Credit_LE->text().toDouble()) {
            if (!customer.updateCredit(ui->Credit_LE->text().toDouble(), customer_id)) updated = false;
        }
        if (customer.getDebt() != ui->Debt_LE->text().toDouble()) {
            if (!customer.updateDebt(ui->Debt_LE->text().toDouble(), customer_id)) updated = false;
        }
        if (updated) QMessageBox::information(nullptr, "Update Customer", "Updated!");
    }
}

void Showcustomer::on_Add_PB_clicked() {
    if (customer.writeData(ui->Name_LE->text(), ui->Lastname_LE->text(), ui->Phonenumber_LE->text(), ui->Address_LE->text(), ui->Credit_LE->text().toDouble(), ui->Debt_LE->text().toDouble(), ui->Username_LE->text(), ui->Password_LE->text())) {
        QMessageBox::information(nullptr, "Add Customer", "Added!");
    }
    else qDebug() << "Failed to add Customer (on_Delete_PB_clicked)";
}

void Showcustomer::on_Delete_PB_clicked() {
    if (customer.deleteCustomer(customer_id)) {
        QMessageBox::information(nullptr, "Delete Customer", "Deleted!");
        close();
    }
    else qDebug() << "Failed to delete Customer (on_Delete_PB_clicked)";
}


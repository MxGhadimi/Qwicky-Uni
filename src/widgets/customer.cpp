#include "customer.h"
#include "ui_customer.h"

Customer::Customer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Customer)
{
    ui->setupUi(this);
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "customer");
    QString dbpath = QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/admin.db";
    database.setDatabaseName(dbpath);
    if (!database.open()) qDebug() << "Failed to open database" << database.lastError().text();
}

Customer::~Customer()
{
    delete ui;
}

void Customer::writeData(QString input_first_name, QString input_last_name, QString input_phone_number, QString input_address, double input_credit, double input_debt, QString input_username, QString input_password, int input_customer_id) {
    customer_id = input_customer_id;
    QSqlQuery q(QSqlDatabase::database("customer"));
    q.prepare("INSERT INTO Customers (first_name, last_name, phone_number, address, debt, credit, username, password) VALUES (:first_name, :last_name, :phone_number, :address, :debt, :credit, :username, :password)");
    q.bindValue(":first_name", input_first_name);
    q.bindValue(":last_name", input_last_name);
    q.bindValue(":phone_number", input_phone_number);
    q.bindValue(":address", input_address);
    q.bindValue(":debt", input_debt);
    q.bindValue(":credit", input_credit);
    q.bindValue(":username", input_username);
    q.bindValue(":password", input_password);
    if (!q.exec()) qDebug() << "Failed to insert Customer: " << q.lastError().text();
}

void Customer::readData(int input_customer_id) {
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
    }
    else qDebug() << "No rows found in the table";
}
/*
void Customer::showData() {
    ui->FirstName_L->setText(first_name);
    ui->LastName_L->setText(last_name);
    ui->PhoneNumber_L->setText(phone_number);
    ui->Address_TE->setText(address);
    ui->Credit_L->setText("$" + QString::number(credit));
    ui->Debt_L->setText("$" + QString::number(debt));
    ui->Username_L->setText(username);
    ui->Password_L->setText(password);
}
*/

void Customer::updateFirstName(QString input_first_name, int customer_id) {
    QSqlQuery q(QSqlDatabase::database("customer"));
    q.prepare("UPDATE Customers SET first_name = :first_name WHERE id = :id");
    q.bindValue(":first_name", input_first_name);
    q.bindValue(":id", customer_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

void Customer::updateLastName(QString input_last_name, int customer_id) {
    QSqlQuery q(QSqlDatabase::database("customer"));
    q.prepare("UPDATE Customers SET last_name = :last_name WHERE id = :id");
    q.bindValue(":last_name", input_last_name);
    q.bindValue(":id", customer_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

void Customer::updatePhoneNumber(QString input_phone_number, int customer_id) {
    QSqlQuery q(QSqlDatabase::database("customer"));
    q.prepare("UPDATE Customers SET phone_number = :phone_number WHERE id = :id");
    q.bindValue(":phone_number", input_phone_number);
    q.bindValue(":id", customer_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

void Customer::updateAddress(QString input_address, int customer_id) {
    QSqlQuery q(QSqlDatabase::database("customer"));
    q.prepare("UPDATE Customers SET address = :address WHERE id = :id");
    q.bindValue(":address", input_address);
    q.bindValue(":id", customer_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

void Customer::updateCredit(double input_credit, int customer_id) {
    QSqlQuery q(QSqlDatabase::database("customer"));
    q.prepare("UPDATE Customers SET credit = :credit WHERE id = :id");
    q.bindValue(":credit", input_credit);
    q.bindValue(":id", customer_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

void Customer::updateDebt(double input_debt, int customer_id) {
    QSqlQuery q(QSqlDatabase::database("customer"));
    q.prepare("UPDATE Customers SET debt = :debt WHERE id = :id");
    q.bindValue(":debt", input_debt);
    q.bindValue(":id", customer_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

#include "orderitems.h"
#include "ui_orderitems.h"

OrderItems::OrderItems(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrderItems)
{
    ui->setupUi(this);
    setFixedSize(290, 20);
}

OrderItems::~OrderItems()
{
    delete ui;
}

bool OrderItems::readData(int input_orderitem_id) {
    QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(item_db);
    q.prepare("SELECT item_id, amount FROM OrderItems WHERE orderitem_id = :orderitem_id");
    q.bindValue(":orderitem_id", input_orderitem_id);

    if (q.exec()) {
        while (q.next()) {
            item_id = q.value("item_id").toInt();
            amount = q.value("amount").toInt();

            QSqlQuery q2(item_db);
            q2.prepare("SELECT name, price FROM Items WHERE item_id = :item_id");
            q2.bindValue(":item_id", item_id);

            if (!q2.exec()) {
                qDebug() << "Error executing query(Order items readData2): " << q2.lastError().text();
                return false;
            }

            if (q2.next()) {
                name = q2.value("name").toString();
                price = q2.value("price").toDouble();
                total_price = price * amount;

                ui->Items_L->setText(name);
                ui->Qty_L->setText(QString::number(amount));
                ui->Price_L->setText(QString::number(total_price, 'f', 2));
                return true;
            }
            else {
                qDebug() << "No item found with item_id " << item_id;
                return false;
            }
        }
    }
    else {
        qDebug() << "Error executing query(Order items readData1): " << q.lastError().text();
        return false;
    }
}

bool OrderItems::showTMPData(int input_amount, int input_item_id) {
    QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(item_db);
    q.prepare("SELECT * FROM Items WHERE item_id = ?");
    q.bindValue(0, input_item_id);
    if (q.exec()) {
        q.next();
        name = q.value("name").toString();
        price = q.value("price").toDouble();
        total_price = price * input_amount;
        amount = input_amount;
        return true;
    }
    else {
        qDebug() << "Error executing query";
        return false;
    }
}

void OrderItems::updateAmount(int input_amount) {
    ui->Qty_L->setText(QString::number(input_amount));
    total_price = price * input_amount;
    ui->Price_L->setText("$" + QString::number(total_price, 'f', 2));
    amount = input_amount;
}

void OrderItems::showData() {
    ui->Items_L->setText(name);
    ui->Qty_L->setText(QString::number(amount));
    ui->Price_L->setText("$" + QString::number(total_price, 'f', 2));
}

double OrderItems::getTotalPrice() {
    return total_price;
}

int OrderItems::getAmount() {
    return amount;
}


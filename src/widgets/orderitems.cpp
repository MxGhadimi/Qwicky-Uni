#include "orderitems.h"
#include "ui_orderitems.h"

OrderItems::OrderItems(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrderItems)
{
    ui->setupUi(this);
}

OrderItems::~OrderItems()
{
    delete ui;
}

void OrderItems::readData(int input_orderitem_id) {
    QSqlDatabase db = QSqlDatabase::database("admin-items");
    if (!db.isOpen()) {
        qDebug() << "Database connection failed.";
        return;
    }

    QSqlQuery q(db);
    q.prepare("SELECT item_id, amount FROM OrderItems WHERE orderitem_id = :orderitem_id");
    q.bindValue(":orderitem_id", input_orderitem_id);

    if (q.exec()) {
        while (q.next()) {
            item_id = q.value("item_id").toInt();
            amount = q.value("amount").toInt();

            QSqlQuery q2(db);
            q2.prepare("SELECT name, price FROM Items WHERE item_id = :item_id");
            q2.bindValue(":item_id", item_id);

            if (!q2.exec()) {
                qDebug() << "Error executing query(Order items readData2): " << q2.lastError().text();
                return;
            }

            if (q2.next()) {
                name = q2.value("name").toString();
                price = q2.value("price").toDouble();
                total_price = price * amount;

                ui->Items_L->setText(name);
                ui->Qty_L->setText(QString::number(amount));
                ui->Price_L->setText(QString::number(total_price, 'f', 2));
            }
            else qDebug() << "No item found with item_id " << item_id;
        }
    }
    else qDebug() << "Error executing query(Order items readData1): " << q.lastError().text();
}

void OrderItems::showTMPData(int input_amount, int input_item_id) {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT * FROM Items WHERE item_id = ?");
    q.bindValue(0, input_item_id);
    if (q.exec()) {
        q.next();
        name = q.value("name").toString();
        price = q.value("price").toDouble();
        total_price = price * input_amount;
        amount = input_amount;
    }
    else qDebug() << "Error executing query";
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


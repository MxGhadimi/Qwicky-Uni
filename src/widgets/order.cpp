#include "order.h"
#include "ui_order.h"

Order::Order(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Order)
{
    ui->setupUi(this);
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "items");
    QString dbpath = QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/items.db";
    database.setDatabaseName(dbpath);
    if (!database.open()) qDebug() << "Failed to open database" << database.lastError().text();

    QSqlDatabase database2 = QSqlDatabase::addDatabase("QSQLITE", "admin");
    QString dbpath2 = QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/admin.db";
    database2.setDatabaseName(dbpath2);
    if (!database2.open()) qDebug() << "Failed to open database" << database2.lastError().text();
}

Order::~Order()
{
    delete ui;
}

void Order::writeData(int customer_id, const QString &table, const QString &order_type, const QString &selected_items_str) {
    QSqlQuery q(QSqlDatabase::database("admin"));
    q.prepare("INSERT INTO Orders (order_id, customer_id, table, order_type) VALUES (NULL, :customer_id, :table, :order_type)");
    q.bindValue(":customer_id", customer_id);
    q.bindValue(":table", table);
    q.bindValue(":order_type", order_type);
    if (!q.exec()) qDebug() << "Failed to insert into Orders table: " << q.lastError().text() << customer_id << table << order_type;
    else {
        int order_id = q.lastInsertId().toInt();
        QStringList itemsList = selected_items_str.split(", ");
        for (const QString &item : itemsList) {
            QStringList part = item.split(" - ");
            if (part.size() == 2) {
                int item_id = part[0].toInt();
                int amount = part[1].toInt();

                QSqlQuery q2(QSqlDatabase::database("order"));
                q2.prepare("INSERT INTO OrderItems (order_id, item_id, amount) VALUES (:order_id, :item_id, :amount)");
                q2.bindValue(":order_id", order_id);
                q2.bindValue(":item_id", item_id);
                q2.bindValue(":amount", amount);
                if (!q2.exec()) qDebug() << "Failed to insert into OrderItems table: " << q2.lastError().text();
            }
        }
    }
}

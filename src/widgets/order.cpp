#include "order.h"
#include "ui_order.h"

Order::Order(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Order)
{
    ui->setupUi(this);

    total_price = 0;

    scrollWidget = new QWidget(this);
    verticalLayout = new QVBoxLayout(scrollWidget);
    verticalLayout->setSpacing(5);
    verticalLayout->setAlignment(Qt::AlignTop);
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setMinimumWidth(ui->scrollArea->width());
    scrollArea->setMinimumHeight(ui->scrollArea->height());
    ui->scrollArea->setWidget(scrollArea);
}

Order::~Order()
{
    delete ui;
}

void Order::writeData(int customer_id, const QString &table, const QString &order_type, const QString &selected_items_str) {
    QString last_order_id;
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT MAX(order_id) FROM Orders");
    q.exec();
    if (q.first()) last_order_id = q.value(0).toString();

    QString left_part = last_order_id.left(6);
    QString today_str = QDate::currentDate().toString("yyMMdd");

    if (left_part == today_str) {
        QString right_part = last_order_id.right(last_order_id.length() - 6);
        order_id = (left_part + QString::number(right_part.toInt() + 1)).toInt();
    }
    else {
        left_part = today_str;
        QString right_part = "1";
        order_id = (left_part + right_part).toInt();
    }

    q.prepare("INSERT INTO Orders (order_id, customer_id, [table], order_type) VALUES (:order_id, :customer_id, :table, :order_type)");
    q.bindValue(":order_id", order_id);
    q.bindValue(":customer_id", customer_id);
    q.bindValue(":table", table.isEmpty()? "TA" : table);
    q.bindValue(":order_type", order_type);
    if (q.exec()) {
        QStringList itemsList = selected_items_str.split(", ");
        for (const QString &item : itemsList) {
            QStringList part = item.split(" - ");
            if (part.size() == 2) {
                int item_id = part[0].toInt();
                int amount = part[1].toInt();

                QSqlQuery q2(QSqlDatabase::database("admin-items"));
                q2.prepare("INSERT INTO OrderItems (order_id, item_id, amount) VALUES (:order_id, :item_id, :amount)");
                q2.bindValue(":order_id", order_id);
                q2.bindValue(":item_id", item_id);
                q2.bindValue(":amount", amount);
                if (!q2.exec()) qDebug() << "Failed to insert into OrderItems table: " << q2.lastError().text();
            }
        }
    }
    else qDebug() << "Failed to insert into Orders table: " << q.lastError().text() << customer_id << table << order_type;
}

void Order::readData(int input_item_id) {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT * FROM Orders WHERE order_id = :order_id");
    q.bindValue(":order_id", input_item_id);
    if (q.exec()) {
        if (q.next()) {
            order_id = q.value("order_id").toInt();
            customer_id = q.value("customer_id").toString();
            table = q.value("table").toString();
            order_type = q.value("order_type").toString();
            date = q.value("date").toString();
            time = q.value("time").toString();
            pay_status = q.value("pay_status").toString();
        }
    }
    else qDebug() << "Error executing query(Order readData1): " << q.lastError().text();

    QSqlQuery q2(QSqlDatabase::database("admin"));
    q2.prepare("SELECT first_name, last_name FROM Customers WHERE id = :id");
    q2.bindValue(":id", customer_id);
    if (q2.exec()) {
        if (q2.next()) name = q2.value("first_name").toString() + " " + q2.value("last_name").toString();
    }
    else qDebug() << "Error executing query(Order readData2): " << q2.lastError().text();
}

void Order::showData() {
    ui->Table_L->setText(table);
    ui->Customerinfo_PB->setText(name);
    ui->Orderid_PB->setText("#" + QString::number(order_id));
    ui->Orderstatus_L->setText(order_type);

    total_price = 0;
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT orderitem_id FROM OrderItems WHERE order_id = :order_id");
    q.bindValue(":order_id", order_id);
    if (q.exec()) {
        while(q.next()) {
            int orderitem_id = q.value("orderitem_id").toInt();
            OrderItems *orderitems = new OrderItems(this);
            orderitems->readData(orderitem_id);
            orderitems->showData();
            total_price += orderitems->getPrice();
            orderitems->setMinimumSize(290, 20);
            orderitems->setMaximumSize(290, 20);
            verticalLayout->addWidget(orderitems);
        }
    }
    else qDebug() << "Error executing query (Order showData)";
    ui->Total_L_2->setText("$" + QString::number(total_price, 'f', 2));
}

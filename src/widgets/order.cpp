#include "order.h"
#include "ui_order.h"
#include "Showorder.h"

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

void Order::writeData(int customer_id, const QString &table, const QString &order_type, const QString &selected_items_str, const QString &date_str, const QString &time_str) {
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

    q.prepare("INSERT INTO Orders (order_id, customer_id, [table], order_type, date, time, pay_status) VALUES (:order_id, :customer_id, :table, :order_type, :date, :time, :pay_status)");
    q.bindValue(":order_id", order_id);
    q.bindValue(":customer_id", customer_id);
    q.bindValue(":table", table.isEmpty()? "TA" : table);
    q.bindValue(":order_type", order_type);
    q.bindValue(":date", date_str);
    q.bindValue(":time", time_str);
    q.bindValue(":pay_status", pay_status);
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
                if (!q2.exec()) qDebug() << "Failed to insert into OrderItems (Orders writeData2): " << q2.lastError().text();
            }
        }
    }
    else qDebug() << "Failed to insert into Orders (Orders writeData1): " << q.lastError().text();

    QSqlQuery q3(QSqlDatabase::database("admin-items"));
    q3.prepare("INSERT INTO Tabletime (table_name, date, time, order_id) VALUES (:table_name, :date, :time, :order_id)");
    q3.bindValue(":table_name", table);
    q3.bindValue(":date", date_str);
    q3.bindValue(":time", time_str);
    q3.bindValue(":order_id", order_id);
    if (!q3.exec()) qDebug() << "Failed to insert into Tabletime (Orders writeData3): " << q3.lastError().text();
}

void Order::readData(int input_order_id) {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT * FROM Orders WHERE order_id = :order_id");
    q.bindValue(":order_id", input_order_id);
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
    ui->dateEdit->setDate(QDate::fromString(date, "yyyy-MM-dd"));
    ui->timeEdit->setTime(QTime::fromString(time));
    if ("Payed" == pay_status) {
        ui->Paystatus_CB->setChecked(true);
        ui->Paystatus_CB->setStyleSheet("QCheckBox { background: rgb(144, 238, 144); color: rgb(31, 48, 58); border: none; border-radius: 6px; font: 600 10pt 'Segoe UI'; padding-right: 6px; } QCheckBox::indicator { background: transparent; border: none; width: 16px; height: 16px; } QCheckBox::indicator:unchecked { image: url(:/icons/images/icons/timer.png); } QCheckBox::indicator:checked { image: url(:/icons/images/icons/check.png); }");
        ui->Paystatus_CB->setText(pay_status);
    }
    else {
        ui->Paystatus_CB->setChecked(false);
        ui->Paystatus_CB->setStyleSheet("QCheckBox { background: rgb(255, 204, 153); color: rgb(31, 48, 58); border: none; border-radius: 6px; font: 600 10pt 'Segoe UI'; padding-right: 6px; } QCheckBox::indicator { background: transparent; border: none; width: 16px; height: 16px; } QCheckBox::indicator:unchecked { image: url(:/icons/images/icons/timer.png); } QCheckBox::indicator:checked { image: url(:/icons/images/icons/check.png); }");
        ui->Paystatus_CB->setText("Pending");
    }

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
            total_price += orderitems->getTotalPrice();
            orderitems->setMinimumSize(290, 20);
            orderitems->setMaximumSize(290, 20);
            verticalLayout->addWidget(orderitems);
        }
    }
    else qDebug() << "Error executing query (Order showData)";
    ui->Total_L_2->setText("$" + QString::number(total_price, 'f', 2));
}

void Order::on_Paystatus_CB_stateChanged(int arg1) {
    if (Qt::Checked == arg1) {
        ui->Paystatus_CB->setStyleSheet("QCheckBox { background: rgb(144, 238, 144); color: rgb(31, 48, 58); border: none; border-radius: 6px; font: 600 10pt 'Segoe UI'; padding-right: 6px; } QCheckBox::indicator { background: transparent; border: none; width: 16px; height: 16px; } QCheckBox::indicator:unchecked { image: url(:/icons/images/icons/timer.png); } QCheckBox::indicator:checked { image: url(:/icons/images/icons/check.png); }");
        ui->Paystatus_CB->setText("Payed");
        QSqlQuery q(QSqlDatabase::database("admin-items"));
        q.prepare("UPDATE Orders SET pay_status = 'Payed' WHERE order_id = :order_id");
        q.bindValue(":order_id", order_id);
        if (!q.exec()) qDebug() << "Failed to execute query (Order Paystatus changed1): " << q.lastError().text();
    }
    else {
        ui->Paystatus_CB->setStyleSheet("QCheckBox { background: rgb(255, 204, 153); color: rgb(31, 48, 58); border: none; border-radius: 6px; font: 600 10pt 'Segoe UI'; padding-right: 6px; } QCheckBox::indicator { background: transparent; border: none; width: 16px; height: 16px; } QCheckBox::indicator:unchecked { image: url(:/icons/images/icons/timer.png); } QCheckBox::indicator:checked { image: url(:/icons/images/icons/check.png); }");
        ui->Paystatus_CB->setText("Pending");
        QSqlQuery q(QSqlDatabase::database("admin-items"));
        q.prepare("UPDATE Orders SET pay_status = 'Pending' WHERE order_id = :order_id");
        q.bindValue(":order_id", order_id);
        if (!q.exec()) qDebug() << "Failed to execute query (Order Paystatus changed2): " << q.lastError().text();
    }
}

void Order::on_Orderid_PB_clicked() {
    Showorder *showorder = new Showorder(nullptr);
    pay_status = ui->Paystatus_CB->text();
    showorder->showData(order_id);
    showorder->show();
    connect(showorder, &QObject::destroyed, showorder, &QObject::deleteLater);
}


void Order::updateItems(const QString &selected_items_str, int order_id) {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("DELETE FROM OrderItems WHERE order_id = :order_id");
    q.bindValue(":order_id", order_id);
    if(q.exec()) {
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
                if (!q2.exec()) qDebug() << "Failed to insert into OrderItems (Order updateItems2): " << q2.lastError().text();
            }
        }
    }
    else qDebug() << "Failed to delete from OrderItems (Order updateItems1): " << q.lastError().text();
}

void Order::updateDate(const QString &date_str, int order_id) {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("UPDATE Orders SET date = :date WHERE order_id = :order_id");
    q.bindValue(":date", date_str);
    q.bindValue(":order_id", order_id);
    if (!q.exec()) qDebug() << "Failed to update date in Orders (Order updateDate1): " << q.lastError().text();

    QSqlQuery q2(QSqlDatabase::database("admin-items"));
    q2.prepare("UPDATE Tabletime SET date = :date WHERE order_id = :order_id");
    q2.bindValue(":date", date_str);
    q2.bindValue(":order_id", order_id);
    if (!q2.exec()) qDebug() << "Failed to update date in Tabletime (Order updateDate2): " << q2.lastError().text();
}

void Order::updateTime(const QString &time_str, int order_id) {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("UPDATE Orders SET time = :time WHERE order_id = :order_id");
    q.bindValue(":time", time_str);
    q.bindValue(":order_id", order_id);
    if (!q.exec()) qDebug() << "Failed to update time in Orders (Order updateTime1): " << q.lastError().text();

    QSqlQuery q2(QSqlDatabase::database("admin-items"));
    q2.prepare("UPDATE Tabletime SET time = :time WHERE order_id = :order_id");
    q2.bindValue(":time", time_str);
    q2.bindValue(":order_id", order_id);
    if (!q2.exec()) qDebug() << "Failed to update time in Tabletime (Order updateTime2): " << q2.lastError().text();
}

void Order::updateTable(const QString &table_str, int order_id) {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("UPDATE Orders SET [table] = :table WHERE order_id = :order_id");
    q.bindValue(":table", table_str);
    q.bindValue(":order_id", order_id);
    if (!q.exec()) qDebug() << "Failed to update table in Orders (Order updateTable): " << q.lastError().text();

    QSqlQuery q2(QSqlDatabase::database("admin-items"));
    q2.prepare("UPDATE Tabletime SET table_name = :table_name WHERE order_id = :order_id");
    q2.bindValue(":table_name", table_str);
    q2.bindValue(":order_id", order_id);
    if (!q2.exec()) qDebug() << "Failed to insert into Tabletime (Order updateTable2): " << q2.lastError().text();
}

void Order::updateOrderType(const QString &order_type, int order_id) {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("UPDATE Orders SET order_type = :order_type WHERE order_id = :order_id");
    q.bindValue(":order_type", order_type);
    q.bindValue(":order_id", order_id);
    if (!q.exec()) qDebug() << "Failed to update table in Orders (Order updateOrderType): " << q.lastError().text();
}

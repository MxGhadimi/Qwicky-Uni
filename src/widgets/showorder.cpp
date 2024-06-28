#include "showorder.h"
#include "ui_showorder.h"

Showorder::Showorder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Showorder)
{
    ui->setupUi(this);
    setFixedSize(311, 438);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    ui->Table_PB->setEnabled(false);
    ui->Orderstatus_C->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    ui->timeEdit->setEnabled(false);
    ui->Orderstatus_C->setFixedSize(85,25);

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

    scrollWidget_2 = new QWidget(this);
    gridLayout = new QGridLayout(scrollWidget_2);
    gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->scrollArea_4->setWidgetResizable(true);
    ui->scrollArea_4->setWidget(scrollWidget_2);

    scrollWidget_3 = new QWidget(this);
    gridLayout_3 = new QGridLayout(scrollWidget_3);
    gridLayout_3->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->scrollArea_5->setWidgetResizable(true);
    ui->scrollArea_5->setWidget(scrollWidget_3);
}

Showorder::~Showorder()
{
    delete ui;
}

void Showorder::showData(int input_order_id) {
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

    ui->Customerinfo_PB->setText(name);
    ui->Table_PB->setText(table);
    int index = ui->Orderstatus_C->findText(order_type);
    if (index != -1) ui->Orderstatus_C->setCurrentIndex(index);
    else qDebug() << "order_type not found in Orderstatus_C: " << order_type;
    ui->dateEdit->setDate(QDate::fromString(date, "yyyy-MM-dd"));
    ui->timeEdit->setTime(QTime::fromString(time));
    ui->Orderid_L->setText("#" + QString::number(order_id));
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

    QSqlQuery q3(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT orderitem_id, item_id, amount FROM OrderItems WHERE order_id = :order_id");
    q.bindValue(":order_id", order_id);
    if (q.exec()) {
        while(q.next()) {
            int orderitem_id = q.value("orderitem_id").toInt();
            int item_id = q.value("item_id").toInt();
            int amount = q.value("amount").toInt();
            OrderItems *orderitems = new OrderItems(this);
            orderitems->readData(orderitem_id);
            orderitems->showData();
            total_price += orderitems->getTotalPrice();
            orderitems->setMinimumSize(290, 20);
            orderitems->setMaximumSize(290, 20);
            verticalLayout->addWidget(orderitems);
            selectedItems[item_id] = orderitems;
        }
    }
    else qDebug() << "Error executing query (Order showData)";
    ui->Total_L_2->setText("$" + QString::number(total_price, 'f', 2));

    show();
}

void Showorder::on_Paystatus_CB_stateChanged(int arg1) {
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

void Showorder::on_Edit_PB_clicked() {
    static bool edit_mode_on = false;
    if (!edit_mode_on) {
        setFixedSize(1124, 650);
        ui->Edit_PB->setText("Done");
        ui->Table_PB->setEnabled(true);
        ui->Orderstatus_C->setEnabled(true);
        ui->dateEdit->setEnabled(true);
        ui->timeEdit->setEnabled(true);
        ui->dateEdit->setDisplayFormat("yyyy-MM-dd");
        showItems();
        edit_mode_on = true;
    }
    else {
        ui->Edit_PB->setText("Edit");
        ui->Table_PB->setEnabled(false);
        ui->Orderstatus_C->setEnabled(false);
        ui->dateEdit->setEnabled(false);
        ui->timeEdit->setEnabled(false);
        ui->dateEdit->setDisplayFormat("ddd, yyyy MMMM dd");

        QString selected_items_str;
        for (auto i = selectedItems.begin(); i != selectedItems.end(); i++) {
            selected_items_str += QString::number(i.key()) + " - " + QString::number(i.value()->getAmount()) + ", ";
        }
        if (!selected_items_str.isEmpty()) selected_items_str.chop(2);

        QDate date = ui->dateEdit->date();
        QString date_str = date.toString("yyyy-MM-dd");
        QTime time = ui->timeEdit->time();
        QString time_str = time.toString("HH:mm");

        Order *order = new Order(this);
        order->updateItems(selected_items_str, order_id);
        order->updateDate(date_str, order_id);
        order->updateTime(time_str, order_id);
        order->updateTable(ui->Table_PB->text(), order_id);
        order->updateOrderType(ui->Orderstatus_C->currentText(), order_id);
        QMessageBox::information(nullptr, "Update Order", "Updated!");
        edit_mode_on = false;
    }
}

void Showorder::showItems() {
    ui->Search_LE->setPlaceholderText("Search for an item...");
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT * FROM Items");
    if (!q.exec()) qDebug() << "Error executing query";

    int row = 0, column = 0;
    while(q.next()) {
        int item_id = q.value("item_id").toInt();
        Item *item = new Item(this);
        item->readData(item_id);
        item->showData();
        int amount = 0;
        if (selectedItems.contains(item_id)) amount = selectedItems[item_id]->getAmount();
        item->setAmountText(amount);
        itemAmounts[item_id] = amount;
        item->showAmount();
        item->setMinimumSize(245, 285);
        item->setMaximumSize(250, 290);
        connect(item, &Item::amountChanged, this, &Showorder::updateItemAmount);

        gridLayout->setVerticalSpacing(3);
        gridLayout->setHorizontalSpacing(3);

        gridLayout->addWidget(item, row, column);
        if (++column >= 3) {
            column = 0;
            row++;
        }
    }
}

void Showorder::updateItemAmount(int item_id, int amount) {
    itemAmounts[item_id] = amount;
    if (selectedItems.contains(item_id)) {
        if (amount == 0) {
            delete selectedItems[item_id];
            selectedItems.remove(item_id);
        }
        else selectedItems[item_id]->updateAmount(amount);
    }
    else {
        OrderItems *orderitems = new OrderItems(this);
        orderitems->showTMPData(amount, item_id);
        orderitems->showData();
        orderitems->setMinimumSize(290, 20);
        orderitems->setMaximumSize(290, 20);
        verticalLayout->addWidget(orderitems);
        selectedItems[item_id] = orderitems;
    }
    total = 0.0;
    for (auto i = selectedItems.begin(); i != selectedItems.end(); i++) {
        total += i.value()->getTotalPrice();
    }

    ui->Total_L_2->setText("$" + QString::number(total, 'f', 2));
}

void Showorder::on_Search_LE_textChanged(const QString &arg1) {
    QLayoutItem *item;
    while ((item = gridLayout->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT * FROM Items WHERE name LIKE :search OR description LIKE :search");
    q.bindValue(":search", "%" + arg1 + "%");
    if (!q.exec()) qDebug() << "Error executing query";

    int row = 0, column = 0;
    while(q.next()) {
        int item_id = q.value("item_id").toInt();
        Item *item = new Item(this);
        item->readData(item_id);
        item->showData();
        if (itemAmounts.contains(item_id)) item->setAmountText(itemAmounts[item_id]);
        else item->setAmountText(0);
        item->showAmount();
        item->setMinimumSize(250, 290);
        item->setMaximumSize(250, 290);

        connect(item, &Item::amountChanged, this, &Showorder::updateItemAmount);

        gridLayout->setVerticalSpacing(3);
        gridLayout->setHorizontalSpacing(3);

        gridLayout->addWidget(item, row, column);
        if (++column >= 3) {
            column = 0;
            row++;
        }
    }
}


void Showorder::on_back_PB_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Orderinfo_QW);
    setFixedSize(1124, 650);
    showItems();
    ui->Search_LE->show();
    ui->Searchlogo_L->show();
}

void Showorder::on_Table_PB_clicked() {
    setFixedSize(311, 438);
    ui->stackedWidget->setCurrentWidget(ui->Table_QW);
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    QDate date = ui->dateEdit->date();
    QString date_str = date.toString("yyyy-MM-dd");
    QTime time = ui->timeEdit->time();
    QString time_str = time.toString("HH:mm");

    q.prepare("SELECT * FROM Tables WHERE table_name NOT IN (SELECT table_name FROM Tabletime WHERE date = :date AND time = :time)");
    q.bindValue(":date", date_str);
    q.bindValue(":time", time_str);
    if (!q.exec()) qDebug() << "Error executing query: " << q.lastError().text();

    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    int row = 0, column = 0;
    while(q.next()) {
        QString table_name = q.value("table_name").toString();
        QPushButton *table_pb = new QPushButton(this);
        table_pb->setText(table_name);

        table_pb->setMinimumSize(240, 40);
        table_pb->setMaximumSize(240, 40);
        table_pb->setStyleSheet("QPushButton { background-color: rgb(6, 106, 110); border: none; border-radius: 5px; padding-left: 10px; font: 600 15pt; } QPushButton:hover { background-color: rgb(7, 132, 136); } QPushButton::pressed { background-color: rgb(5, 97, 100); }");
        gridLayout_3->setHorizontalSpacing(5);

        gridLayout_3->addWidget(table_pb, row, column);
        if (++column >= 1) {
            column = 0;
            row++;
        }
        connect(table_pb, &QPushButton::clicked, this, [this, table_name]() {
            ui->Table_PB->setText(table_name);
            ui->stackedWidget->setCurrentWidget(ui->Orderinfo_QW);
        });
    }
}

void Showorder::on_Delete_PB_clicked() {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("DELETE FROM Tabletime WHERE order_id = :order_id");
    q.bindValue(":order_id", order_id);
    if (q.exec()) {
        q.prepare("DELETE FROM OrderItems WHERE order_id = :order_id");
        q.bindValue(":order_id", order_id);
        if (q.exec()) {
            q.prepare("DELETE FROM Orders WHERE order_id = :order_id");
            q.bindValue(":order_id", order_id);
            if (q.exec()) {
                QMessageBox::information(nullptr, "Delete Order", "Deleted!");
                close();
            }
            else qDebug() << "Failed to delete from Orders (Order deleteOrder3): " << q.lastError().text();
        }
        else qDebug() << "Failed to delete from OrderItems (Order deleteOrder2): " << q.lastError().text();
    }
    else  qDebug() << "Failed to delete from Tabletime (Order deleteOrder1): " << q.lastError().text();
}


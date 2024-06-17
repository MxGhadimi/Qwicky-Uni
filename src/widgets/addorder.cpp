#include "addorder.h"
#include "ui_addorder.h"
#include <QButtonGroup>
#include "item.h"
#include "showselected.h"
#include "order.h"

Addorder::Addorder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Addorder)
{
    ui->setupUi(this);
    setWindowTitle("Add Order");
    setFixedHeight(435);
    setFixedWidth(320);

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "addorder");
    QString dbpath = QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/admin.db";
    database.setDatabaseName(dbpath);
    if (!database.open()) qDebug() << "Failed to open database" << database.lastError().text();

    guests = 0;
    order_type = "Dine In";
    ui->Guestnumber_LE->setEnabled(false);
    ui->Table_LE->setEnabled(false);

    // to prevent memory leak
    scrollWidget = new QWidget(this);
    gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollWidget);

    scrollWidget_2 = new QWidget(this);
    gridLayout_2 = new QGridLayout(scrollWidget_2);
    gridLayout_2->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->scrollArea_2->setWidgetResizable(true);
    ui->scrollArea_2->setWidget(scrollWidget_2);

    scrollWidget_3 = new QWidget(this);
    verticalLayout = new QVBoxLayout(scrollWidget_3);
    verticalLayout->setSpacing(5);
    verticalLayout->setAlignment(Qt::AlignTop);
    ui->scrollArea_3->setWidgetResizable(true);
    ui->scrollArea_3->setWidget(scrollWidget_3);
    scrollWidget_3->setMinimumWidth(ui->scrollArea_3->width());
    scrollWidget_3->setMinimumHeight(ui->scrollArea_3->height());
}

Addorder::~Addorder()
{
    delete ui;
}

void Addorder::on_Choosetable_PB_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Tables_QW);
    static QRegularExpression number("\\d+");
    QRegularExpressionMatch match = number.match(ui->Guestnumber_LE->text());
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    if (match.hasMatch()) {
        int capacity = match.captured(0).toInt();
        q.prepare("SELECT * FROM Tables WHERE capacity = ?");
        q.bindValue(0, capacity);
        if (!q.exec()) qDebug() << "Error executing query: " << q.lastError().text();
    }
    else qDebug() << "Invalid capacity";

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
        gridLayout->setHorizontalSpacing(5);

        gridLayout->addWidget(table_pb, row, column);
        if (++column >= 1) {
            column = 0;
            row++;
        }
        connect(table_pb, &QPushButton::clicked, this, [this, table_name]() {
            ui->Table_LE->setText(table_name);
            ui->stackedWidget->setCurrentWidget(ui->Neworder_QW);
        });
    }
}

void Addorder::on_Takeaway_RB_clicked() {
    this->setFixedHeight(285);
    ui->Continueorder_PB->move(50, 235);
    ui->Guestnumber_L->hide();
    ui->Guestnumber_LE->hide();
    ui->Addperson_PB->hide();
    ui->RemovePerson_PB->hide();
    order_type = "Takeaway";
}


void Addorder::on_Dinein_RB_clicked() {
    ui->Info_L->show();
    ui->Continueorder_PB->move(50, 380);
    setFixedHeight(435);
    ui->Guestnumber_L->show();
    ui->Guestnumber_LE->show();
    ui->Addperson_PB->show();
    ui->RemovePerson_PB->show();
    order_type = "Dine In";
}

void Addorder::on_Addperson_PB_clicked() {
    ++guests;
    if (1 == guests) ui->Guestnumber_LE->setText(QString::number(guests) + " Person");
    else ui->Guestnumber_LE->setText(QString::number(guests) + " Persons");
}

void Addorder::on_RemovePerson_PB_clicked() {
    if (0 == guests) return;
    --guests;
    if (0 == guests) ui -> Guestnumber_LE->clear();
    else if (1 == guests) ui->Guestnumber_LE->setText(QString::number(guests) + " Person");
    else ui->Guestnumber_LE->setText(QString::number(guests) + " Persons");
}

void Addorder::on_Continueorder_PB_clicked() {
    customer_id = -1;

    QString input_info = ui->Info_LE->text();
    QSqlQuery q(QSqlDatabase::database("addorder"));
    if (input_info.toInt()) {
        q.prepare("SELECT id FROM Customers WHERE id = :id");
        q.bindValue(":id", input_info.toInt());
    }
    else {
        q.prepare("SELECT id FROM Customers WHERE first_name || ' ' || last_name = :info");
        q.bindValue(":info", input_info);
    }

    if (q.exec()) {
        if (q.next()) customer_id = q.value(0).toInt();
        else qDebug() << "No customer found with the given information.";
    }
    else qDebug() << "Query execution failed: " << q.lastError().text();

    if (-1 == customer_id) QMessageBox::critical(this, "UserInfo", "no user with this information was found.");
    else {
        ui->stackedWidget->setCurrentWidget(ui->Items_QW);
        setFixedHeight(650);
        setFixedWidth(1104);
        showItems();
    }
}

void Addorder::showItems() {
    ui->Search_LE_2->setPlaceholderText("Search for an item...");
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT * FROM Items");
    if (!q.exec()) qDebug() << "Error executing query";

    int row = 0, column = 0;
    while(q.next()) {
        int item_id = q.value("item_id").toInt();
        Item *item = new Item(this);
        item->readData(item_id);
        item->showData();
        item->showAmount();
        item->setMinimumSize(245, 285);
        item->setMaximumSize(250, 290);
        connect(item, &Item::amountChanged, this, &Addorder::updateItemAmount);

        gridLayout_2->setVerticalSpacing(3);
        gridLayout_2->setHorizontalSpacing(3);

        gridLayout_2->addWidget(item, row, column);
        if (++column >= 3) {
            column = 0;
            row++;
        }
    }
}

void Addorder::on_deleteamount_PB_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Neworder_QW);
}

void Addorder::on_Search_LE_2_textChanged(const QString &arg1) {
    QLayoutItem *item;
    while ((item = gridLayout_2->takeAt(0))) {
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
        if (itemAmounts.contains(item_id)) item->setAmountText(QString::number(itemAmounts[item_id]));
        else item->setAmountText("0");
        item->showAmount();
        item->setMinimumSize(250, 290);
        item->setMaximumSize(250, 290);

        connect(item, &Item::amountChanged, this, &Addorder::updateItemAmount);

        gridLayout_2->setVerticalSpacing(3);
        gridLayout_2->setHorizontalSpacing(3);

        gridLayout_2->addWidget(item, row, column);
        if (++column >= 3) {
            column = 0;
            row++;
        }
    }
}

void Addorder::updateItemAmount(int item_id, int amount) {
    itemAmounts[item_id] = amount;
    if (selectedItems.contains(item_id)) {
        if (amount == 0) {
            delete selectedItems[item_id];
            selectedItems.remove(item_id);
        }
        else selectedItems[item_id]->updateAmount(amount);
    }
    else {
        QSqlQuery q(QSqlDatabase::database("admin-items"));
        q.prepare("SELECT * FROM Items WHERE item_id = ?");
        q.bindValue(0, item_id);
        if (!q.exec()) qDebug() << "Error executing query";
        q.next();

        ShowSelected *selectedItem = new ShowSelected(this);
        selectedItem->showData(q.value("image").toByteArray(), q.value("name").toString(), q.value("price").toString(), amount, item_id);
        selectedItem->setMinimumSize(290, 69);
        selectedItem->setMaximumSize(290, 69);
        verticalLayout->addWidget(selectedItem);
        selectedItems[item_id] = selectedItem;
    }
    total = 0.0;
    for (auto i = selectedItems.begin(); i != selectedItems.end(); i++) {
        total += i.value()->getTotal();
    }
    ui->Total_L_2->setText("$" + QString::number(total, 'f', 2));
}

void Addorder::on_Additems_PB_clicked() {
    QString selected_items_str;
    for (auto i = selectedItems.begin(); i != selectedItems.end(); i++) {
        selected_items_str += QString::number(i.key()) + " - " + QString::number(i.value()->getAmount()) + ", ";
    }
    if (!selected_items_str.isEmpty()) {
        selected_items_str.chop(2);
    }

    Order *order = new Order(this);
    order->writeData(customer_id, ui->Table_LE->text(), order_type, selected_items_str);
    QMessageBox::information(this, "Add New Order", "Added");
    closeUI();
}

void Addorder::closeUI() {
    ui->Guestnumber_LE->clear();
    ui->Table_LE->clear();
    ui->Info_LE->clear();
    ui->Search_LE_2->clear();
    ui->Total_L_2->clear();

    guests = 0;
    order_type = "Dine In";
    customer_id = -1;
    itemAmounts.clear();
    selectedItems.clear();
    total = 0.0;

    QLayoutItem *item;
    while ((item = verticalLayout->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    close();
    setFixedHeight(435);
    setFixedWidth(320);
    ui->stackedWidget->setCurrentWidget(ui->Neworder_QW);
}

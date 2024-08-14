#include "admindashboard.h"
#include "ui_admindashboard.h"

#include "databasemanager.h"

AdminDashboard::AdminDashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminDashboard)
{
    ui->setupUi(this);
    setWindowTitle("Qwicky");
    ui -> stackedWidget -> setCurrentWidget(ui->Dashboard_QW);

    on_Dashboard_PB_clicked();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AdminDashboard::updateDate);
    timer->start(1000);
    ui->dateEdit_3->setDate(QDate::currentDate());
}

AdminDashboard::~AdminDashboard() {
    delete ui;
}

void AdminDashboard::updateDate() {
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
}

// ================ Dashboard ================

void AdminDashboard::on_Dashboard_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: rgb(255, 137, 64);}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Dashboard_QW);

    ui->Dashboard_PB->setStyleSheet(clickedstyle);
    ui->Customer_PB->setStyleSheet(defaultstyle);
    ui->Reservations_PB->setStyleSheet(defaultstyle);
    ui->Menu_PB->setStyleSheet(defaultstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
    ui->Orders_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);

    QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(item_db);
    q.prepare("SELECT COUNT(*) FROM Orders");
    if (!q.exec()) qDebug() << "Error executing query";
    if (q.next()) ui->Totalordernumber_L->setText(QString::number(q.value(0).toInt()));

    int count = 0;
    q.prepare("SELECT order_id FROM Orders");
    if (!q.exec()) qDebug() << "Error executing query";
    while (q.next()) {
        QString orderId = q.value(0).toString();
        if (orderId.left(6) == QDate::currentDate().toString("yyMMdd")) count++;
    }
    ui->Newordernumber_L->setText(QString::number(count));

    QSqlDatabase admin_db = DatabaseManager::getInstance().getAdminDatabase();
    QSqlQuery q3(admin_db);
    q3.prepare("SELECT COUNT(*) FROM Customers");
    if (!q3.exec()) qDebug() << "Error executing query";
    if (q3.next()) ui->Totalcustomersnumber_L->setText(QString::number(q3.value(0).toInt()));

    ui->dateEdit_3->setDate(QDate::currentDate());

}

void AdminDashboard::on_Neworder_PB_clicked() {
    emit showAddorderPage();
}

// ================ Menu Items ================

void AdminDashboard::on_Menu_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Menu_QW);

    ui->Menu_PB->setStyleSheet(clickedstyle);
    ui->Customer_PB->setStyleSheet(defaultstyle);
    ui->Dashboard_PB->setStyleSheet(defaultstyle);
    ui->Reservations_PB->setStyleSheet(defaultstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
    ui->Orders_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);
    showTodayMenu();

    ui->Menusearch_LE->setPlaceholderText("Search for an item...");
}

void AdminDashboard::showMenu() {
    QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(item_db);
    q.prepare("SELECT * FROM Items");
    if (!q.exec()) qDebug() << "Error executing query";

    QWidget *scrollWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    int row = 0, column = 0;
    while(q.next()) {
        int item_id = q.value("item_id").toInt();
        Item *item = new Item(this);
        if (item->readData(item_id)) {
            item->showData();
            gridLayout->setVerticalSpacing(5);
            gridLayout->setHorizontalSpacing(5);

            gridLayout->addWidget(item, row, column);
            if (++column >= 4) {
                column = 0;
                row++;
            }
        }
    }
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollWidget);

    ui->gridLayout->addWidget(ui->scrollArea);
    connect(ui->scrollArea, &QScrollArea::destroyed, scrollWidget, &QObject::deleteLater);
}

void AdminDashboard::showTodayMenu() {
    QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(item_db);
    QString currentDay = QDate::currentDate().toString("dddd");
    q.prepare("SELECT * FROM Items WHERE days LIKE :search");
    q.bindValue(":search", "%" + currentDay + "%");
    if (!q.exec()) qDebug() << "Error executing query";

    QWidget *scrollWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    int row = 0, column = 0;
    while(q.next()) {
        int item_id = q.value("item_id").toInt();
        Item *item = new Item(this);
        if (item->readData(item_id)) {
            item->showData();
            gridLayout->setVerticalSpacing(5);
            gridLayout->setHorizontalSpacing(5);

            gridLayout->addWidget(item, row, column);
            if (++column >= 4) {
                column = 0;
                row++;
            }
        }
    }
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollWidget);

    ui->gridLayout->addWidget(ui->scrollArea);
    connect(ui->scrollArea, &QScrollArea::destroyed, scrollWidget, &QObject::deleteLater);
}

void AdminDashboard::on_Menusearch_LE_textChanged(const QString &arg1) {
    QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(item_db);
    q.prepare("SELECT * FROM Items WHERE name LIKE :search OR description LIKE :search");
    q.bindValue(":search", "%" + arg1 + "%");
    if (!q.exec()) qDebug() << "Error executing query";

    QWidget *scrollWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    int row = 0, column = 0;
    while(q.next()) {
        int item_id = q.value("item_id").toInt();
        Item *item = new Item(this);
        if (item->readData(item_id)) {
            item->showData();
            gridLayout->setVerticalSpacing(5);
            gridLayout->setHorizontalSpacing(5);

            gridLayout->addWidget(item, row, column);
            if (++column >= 4) {
                column = 0;
                row++;
            }
        }
    }
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollWidget);

    ui->gridLayout->addWidget(ui->scrollArea);
    connect(ui->scrollArea, &QScrollArea::destroyed, scrollWidget, &QObject::deleteLater);
}

void AdminDashboard::on_Additem_PB_clicked() {
    emit showAdditemPage();
}

void AdminDashboard::on_dateEdit_3_userDateChanged(const QDate &date) {
    QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(item_db);
    q.prepare("SELECT * FROM Items WHERE days LIKE :search");
    q.bindValue(":search", "%" + date.toString("dddd") + "%");
    if (!q.exec()) qDebug() << "Error executing query";

    QWidget *scrollWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    int row = 0, column = 0;
    while(q.next()) {
        int item_id = q.value("item_id").toInt();
        Item *item = new Item(this);
        if (item->readData(item_id)) {
            item->showData();
            gridLayout->setVerticalSpacing(5);
            gridLayout->setHorizontalSpacing(5);

            gridLayout->addWidget(item, row, column);
            if (++column >= 4) {
                column = 0;
                row++;
            }
        }
    }
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollWidget);

    ui->gridLayout->addWidget(ui->scrollArea);
    connect(ui->scrollArea, &QScrollArea::destroyed, scrollWidget, &QObject::deleteLater);
}

void AdminDashboard::on_Category_C_currentTextChanged(const QString &arg1) {
    if ("All" == arg1) showMenu();
    else {
        QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
        QSqlQuery q(item_db);
        q.prepare("SELECT * FROM Items WHERE category LIKE :search");
        q.bindValue(":search", "%" + arg1 + "%");
        if (!q.exec()) qDebug() << "Error executing query";

        QWidget *scrollWidget = new QWidget(this);
        QGridLayout *gridLayout = new QGridLayout(scrollWidget);
        gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        int row = 0, column = 0;
        while(q.next()) {
            int item_id = q.value("item_id").toInt();
            Item *item = new Item(this);
            if (item->readData(item_id)) {
                item->showData();
                gridLayout->setVerticalSpacing(5);
                gridLayout->setHorizontalSpacing(5);

                gridLayout->addWidget(item, row, column);
                if (++column >= 4) {
                    column = 0;
                    row++;
                }
            }
        }
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(scrollWidget);

        ui->gridLayout->addWidget(ui->scrollArea);
        connect(ui->scrollArea, &QScrollArea::destroyed, scrollWidget, &QObject::deleteLater);
    }
}

// ================ Orders ================

void AdminDashboard::on_Orders_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Orders_QW);

    ui->Orders_PB->setStyleSheet(clickedstyle);
    ui->Customer_PB->setStyleSheet(defaultstyle);
    ui->Dashboard_PB->setStyleSheet(defaultstyle);
    ui->Menu_PB->setStyleSheet(defaultstyle);
    ui->Reservations_PB->setStyleSheet(defaultstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);

    ui->Searchorder_L->setPlaceholderText("Search for an order...");
    showOrders();
}

void AdminDashboard::showOrders() {
    QWidget *scrollWidget_3 = new QWidget(this);
    QGridLayout *gridLayout_3 = new QGridLayout(scrollWidget_3);
    gridLayout_3->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->scrollArea_3->setWidgetResizable(true);
    ui->scrollArea_3->setWidget(scrollWidget_3);
    gridLayout_3->setVerticalSpacing(5);
    gridLayout_3->setHorizontalSpacing(5);

    QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(item_db);
    q.prepare("SELECT order_id FROM Orders");
    if (q.exec()) {
        if (q.last()) {
            int row = 0, column = 0;
            do {
                int order_id = q.value("order_id").toInt();
                Order *order = new Order(this);
                if (order->readData(order_id)) {
                    order->showData();

                    gridLayout_3->addWidget(order, row, column);
                    if (++column >= 3) {
                        column = 0;
                        row++;
                    }
                }
            } while(q.previous());
        }
    }
    else qDebug() << "Error executing query (AdminDashboard showOrders)";

    ui->gridLayout_3->addWidget(ui->scrollArea_3);
}

void AdminDashboard::on_Searchorder_L_textChanged(const QString &arg1) {
    QWidget *scrollWidget_3 = new QWidget(this);
    QGridLayout *gridLayout_3 = new QGridLayout(scrollWidget_3);
    gridLayout_3->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->scrollArea_3->setWidgetResizable(true);
    ui->scrollArea_3->setWidget(scrollWidget_3);
    gridLayout_3->setVerticalSpacing(5);
    gridLayout_3->setHorizontalSpacing(5);

    QSqlDatabase item_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(item_db);
    q.prepare("SELECT * FROM Orders WHERE order_id LIKE :search OR customer_id LIKE :search OR [table] LIKE :search OR pay_status LIKE :search OR date LIKE :search");
    q.bindValue(":search", "%" + arg1 + "%");
    if (q.exec()) {
        if (q.last()) {
            int row = 0, column = 0;
            do {
                int order_id = q.value("order_id").toInt();
                Order *order = new Order(this);
                if (order->readData(order_id)) {
                    order->showData();

                    gridLayout_3->addWidget(order, row, column);
                    if (++column >= 3) {
                        column = 0;
                        row++;
                    }
                }
            } while(q.previous());
        }
    }
    else qDebug() << "Error executing query (AdminDashboard showOrders search)";

    ui->gridLayout_3->addWidget(ui->scrollArea_3);
}

void AdminDashboard::on_Neworder_PB_2_clicked() {
    emit showAddorderPage();
}

// ================ Customers ================

void AdminDashboard::on_Customer_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Customer_QW);

    ui->Customer_PB->setStyleSheet(clickedstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
    ui->Dashboard_PB->setStyleSheet(defaultstyle);
    ui->Menu_PB->setStyleSheet(defaultstyle);
    ui->Reservations_PB->setStyleSheet(defaultstyle);
    ui->Orders_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);

    ui->Search_LE->setPlaceholderText("Search for a Customer...");
    showCustomers();
}

void AdminDashboard::showCustomers() {
    QSqlDatabase admin_db = DatabaseManager::getInstance().getAdminDatabase();
    QSqlQuery q(admin_db);
    q.prepare("SELECT * FROM Customers");
    if (!q.exec()) qDebug() << "Error executing query";

    QWidget *scrollWidget = new QWidget(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout(scrollWidget);
    verticalLayout->setAlignment(Qt::AlignTop);

    while(q.next()) {
        int customer_id = q.value("id").toInt();
        Customer *customer = new Customer(this);
        customer->readData(customer_id);
        customer->showData();
        customer->setMinimumSize(980, 25);
        customer->setMaximumSize(980, 25);

        verticalLayout->addWidget(customer);
    }
    ui->scrollArea_2->setWidgetResizable(true);
    ui->scrollArea_2->setWidget(scrollWidget);
}

void AdminDashboard::on_Search_LE_textChanged(const QString &arg1) {
    QSqlDatabase admin_db = DatabaseManager::getInstance().getAdminDatabase();
    QSqlQuery q(admin_db);
    q.prepare("SELECT * FROM Customers WHERE first_name LIKE :search OR last_name LIKE :search OR username LIKE :search OR phone_number LIKE :search OR id LIKE :id");
    q.bindValue(":search", "%" + arg1 + "%");
    q.bindValue(":id", "%" + arg1 + "%");
    if (!q.exec()) qDebug() << "Error executing query";

    QWidget *scrollWidget = new QWidget(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout(scrollWidget);
    verticalLayout->setAlignment(Qt::AlignTop);

    while(q.next()) {
        int customer_id = q.value("id").toInt();
        Customer *customer = new Customer(this);
        customer->readData(customer_id);
        customer->showData();
        customer->setMinimumSize(980, 25);
        customer->setMaximumSize(980, 25);

        verticalLayout->addWidget(customer);
    }
    ui->scrollArea_2->setWidgetResizable(true);
    ui->scrollArea_2->setWidget(scrollWidget);
}

void AdminDashboard::on_Newcustomer_PB_clicked() {
    Showcustomer *showcustomer = new Showcustomer(nullptr);
    showcustomer->addCustomer();
    showcustomer->show();
}

// ================ Others ================

void AdminDashboard::on_Reservations_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Reservations_QW);

    ui->Reservations_PB->setStyleSheet(clickedstyle);
    ui->Customer_PB->setStyleSheet(defaultstyle);
    ui->Dashboard_PB->setStyleSheet(defaultstyle);
    ui->Menu_PB->setStyleSheet(defaultstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
    ui->Orders_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);
}

void AdminDashboard::on_Tabels_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Tables_QW);

    ui->Tabels_PB->setStyleSheet(clickedstyle);
    ui->Customer_PB->setStyleSheet(defaultstyle);
    ui->Dashboard_PB->setStyleSheet(defaultstyle);
    ui->Menu_PB->setStyleSheet(defaultstyle);
    ui->Reservations_PB->setStyleSheet(defaultstyle);
    ui->Orders_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);
}

void AdminDashboard::on_Settings_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Settings_QW);

    ui->Settings_PB->setStyleSheet(clickedstyle);
    ui->Dashboard_PB->setStyleSheet(defaultstyle);
    ui->Menu_PB->setStyleSheet(defaultstyle);
    ui->Reservations_PB->setStyleSheet(defaultstyle);
    ui->Orders_PB->setStyleSheet(defaultstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
}

void AdminDashboard::on_Quit_PB_clicked() {
    QMessageBox confirm;
    confirm.setText("Are you sure you want to log out?");
    confirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirm.setDefaultButton(QMessageBox::No);

    if (QMessageBox::Yes == confirm.exec()) {
        QFile file(QCoreApplication::applicationDirPath() + QDir::separator() + "data/usersdata/login.txt");
        if (file.exists() && !file.remove()) qDebug() << "Failed to delete file: " << file.errorString();
        this->close();
        emit showMainWindowPage();
    }
}

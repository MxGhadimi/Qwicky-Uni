#include "admindashboard.h"
#include "ui_admindashboard.h"

AdminDashboard::AdminDashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminDashboard)
{
    ui->setupUi(this);
    setWindowTitle("Qwicky");
    ui -> stackedWidget -> setCurrentWidget(ui->Dashboard_QW);

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "admin-items");
    QString dbpath = QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/items.db";
    database.setDatabaseName(dbpath);
    if (!database.open()) qDebug() << "Failed to open database" << database.lastError().text();


    QSqlDatabase database2 = QSqlDatabase::addDatabase("QSQLITE", "admin");
    QString dbpath2 = QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/admin.db";
    database2.setDatabaseName(dbpath2);
    if (!database2.open()) qDebug() << "Failed to open database" << database2.lastError().text();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AdminDashboard::updateDate);
    timer->start(1000);

    scrollWidget_3 = new QWidget(this);
    gridLayout_3 = new QGridLayout(scrollWidget_3);
    gridLayout_3->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->scrollArea_3->setWidgetResizable(true);
    ui->scrollArea_3->setWidget(scrollWidget_3);

    gridLayout_3->setVerticalSpacing(5);
    gridLayout_3->setHorizontalSpacing(5);
}

AdminDashboard::~AdminDashboard() {
    QSqlDatabase database = QSqlDatabase::database("admin-items");
    if (database.isOpen()) database.close();
    QSqlDatabase::removeDatabase("admin-items");
    delete ui;
}

void AdminDashboard::updateDate() {
    ui->dateEdit->setDate(QDate::currentDate());
}

void AdminDashboard::on_Dashboard_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: rgb(255, 137, 64);}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Dashboard_QW);

    ui->Dashboard_PB->setStyleSheet(clickedstyle);
    ui->Reservations_PB->setStyleSheet(defaultstyle);
    ui->Menu_PB->setStyleSheet(defaultstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
    ui->Orders_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);
}

void AdminDashboard::on_Menu_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Menu_QW);

    ui->Menu_PB->setStyleSheet(clickedstyle);
    ui->Dashboard_PB->setStyleSheet(defaultstyle);
    ui->Reservations_PB->setStyleSheet(defaultstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
    ui->Orders_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);
    showMenu();

    ui->Menusearch_LE->setPlaceholderText("Search for an item...");
}

void AdminDashboard::on_Reservations_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Reservations_QW);

    ui->Reservations_PB->setStyleSheet(clickedstyle);
    ui->Dashboard_PB->setStyleSheet(defaultstyle);
    ui->Menu_PB->setStyleSheet(defaultstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
    ui->Orders_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);
}

void AdminDashboard::on_Orders_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Orders_QW);

    ui->Orders_PB->setStyleSheet(clickedstyle);
    ui->Dashboard_PB->setStyleSheet(defaultstyle);
    ui->Menu_PB->setStyleSheet(defaultstyle);
    ui->Reservations_PB->setStyleSheet(defaultstyle);
    ui->Tabels_PB->setStyleSheet(defaultstyle);
    ui->Settings_PB->setStyleSheet(defaultstyle);

    showOrders();
}


void AdminDashboard::on_Tabels_PB_clicked() {
    const QString defaultstyle = "QPushButton {font: 700 12pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: none;} QPushButton:hover {background-color: rgb(255, 215, 147);} QPushButton:pressed {background-color: orange;}";
    const QString clickedstyle = "QPushButton {font: 700 11pt \"Segoe UI\";color: rgb(31, 48, 58);text-align: left;padding: 10px 20px;background-color: rgb(255, 137, 64);}";
    ui -> stackedWidget -> setCurrentWidget(ui->Tables_QW);

    ui->Tabels_PB->setStyleSheet(clickedstyle);
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

void AdminDashboard::on_Additem_PB_clicked() {
    emit showAdditemPage();
}

void AdminDashboard::showMenu() {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT * FROM Items");
    if (!q.exec()) qDebug() << "Error executing query";

    QWidget *scrollWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    int row = 0, column = 0;
    while(q.next()) {
        int item_id = q.value("item_id").toInt();
        Item *item = new Item(this);
        item->readData(item_id);
        item->showData();
        item->setMinimumSize(250, 290);
        item->setMaximumSize(250, 290);
        gridLayout->setVerticalSpacing(5);
        gridLayout->setHorizontalSpacing(5);

        gridLayout->addWidget(item, row, column);
        if (++column >= 3) {
            column = 0;
            row++;
        }
    }
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollWidget);

    ui->gridLayout->addWidget(ui->scrollArea);
    connect(ui->scrollArea, &QScrollArea::destroyed, scrollWidget, &QObject::deleteLater);
}

void AdminDashboard::on_Menusearch_LE_textChanged(const QString &arg1) {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
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
        item->readData(item_id);
        item->showData();
        item->setMinimumSize(250, 290);
        item->setMaximumSize(250, 290);
        gridLayout->setVerticalSpacing(5);
        gridLayout->setHorizontalSpacing(5);

        gridLayout->addWidget(item, row, column);
        if (++column >= 3) {
            column = 0;
            row++;
        }
    }
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollWidget);

    ui->gridLayout->addWidget(ui->scrollArea);
    connect(ui->scrollArea, &QScrollArea::destroyed, scrollWidget, &QObject::deleteLater);
}

void AdminDashboard::on_Neworder_PB_clicked() {
    emit showAddorderPage();
}

void AdminDashboard::showOrders() {
    QSqlQuery q(QSqlDatabase::database("admin-items"));
    q.prepare("SELECT order_id FROM Orders");
    if (q.exec()) {
        q.last();
        int row = 0, column = 0;
        do {
            int order_id = q.value("order_id").toInt();
            Order *order = new Order(this);
            order->readData(order_id);
            order->showData();
            order->setMinimumSize(315, 355);
            order->setMaximumSize(315, 355);

            gridLayout_3->addWidget(order, row, column);
            if (++column >= 3) {
                column = 0;
                row++;
            }
        } while(q.previous());
    }
    else qDebug() << "Error executing query (AdminDashboard showOrders)";

    ui->gridLayout_3->addWidget(ui->scrollArea_3);
}


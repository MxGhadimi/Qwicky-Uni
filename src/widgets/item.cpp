#include "item.h"
#include "ui_item.h"
#include "showitem.h"

Item::Item(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Item)
{
    ui->setupUi(this);
    setFixedSize(250, 290);

    ui->Description_TE->setReadOnly(true);
    ui->Description_TE->setContextMenuPolicy(Qt::NoContextMenu);
    ui->Amount_L->hide();
    ui->Addamount_PB->hide();
    ui->Removeamount_PB->hide();
    ui->Amount_L->setEnabled(false);
    amount = 0;
}

Item::~Item()
{
    delete ui;
}

bool Item::writeData(QByteArray input_image, const QString &input_name, const QString &input_description, const QString &input_price, const QString &input_days, const QString &input_category, int input_item_id) {
    item_id = input_item_id;
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("INSERT INTO Items (image, name, description, price, days, category) VALUES (:image, :name, :description, :price, :days, :category)");
    q.bindValue(":image", input_image);
    q.bindValue(":name", input_name);
    q.bindValue(":description", input_description);
    q.bindValue(":price", input_price.trimmed());
    q.bindValue(":days", input_days);
    q.bindValue(":category", input_category);
    if (q.exec()) return true;
    else {
        qDebug() << "Failed to insert item: " << q.lastError().text();
        return false;
    }
}

bool Item::readData(int input_item_id) {
    item_id = input_item_id;
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("SELECT * FROM Items WHERE item_id = :item_id");
    q.bindValue(":item_id", input_item_id);
    if (!q.exec()) {
        qDebug() << "Error executing query (setData1): " << q.lastError().text();
        return false;
    }

    if (q.next()) {
        image = q.value("image").toByteArray();
        name = q.value("name").toString();
        setWindowTitle(name);
        description = q.value("description").toString();
        price = q.value("price").toString();
        days = q.value("days").toString();
        category = q.value("category").toString();
        return true;
    }
    else {
        qDebug() << "No rows found in the table (Item readData2)";
        return false;
    }
}

void Item::showData() {
    QImage img;
    img.loadFromData(image);
    ui->Image_L->setPixmap(QPixmap::fromImage(img));
    ui->Image_L->setScaledContents(true);
    ui->Name_PB->setText(name);
    ui->Description_TE->setText(description);
    ui->Price_L->setText("$" + price);
}

void Item::on_Name_PB_clicked() {
    Showitem *showitem = new Showitem(this);
    showitem->showData(item_id);
    connect(showitem, &QObject::destroyed, showitem, &QObject::deleteLater);
    showitem->show();
}

bool Item::updateName(const QString &input_name, int item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("UPDATE Items SET name = :name WHERE item_id = :item_id");
    q.bindValue(":name", input_name);
    q.bindValue(":item_id", item_id);
    return q.exec();
}

bool Item::updateDays(const QString &input_days, int item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("UPDATE Items SET days = :days WHERE item_id = :item_id");
    q.bindValue(":days", input_days);
    q.bindValue(":item_id", item_id);
    return q.exec();
}

bool Item::updatePrice(const QString &input_price, int item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("UPDATE Items SET price = :price WHERE item_id = :item_id");
    q.bindValue(":price", input_price);
    q.bindValue(":item_id", item_id);
    return q.exec();
}

bool Item::updateDescription(const QString &input_Description, int item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("UPDATE Items SET description = :description WHERE item_id = :item_id");
    q.bindValue(":description", input_Description);
    q.bindValue(":item_id", item_id);
    return q.exec();
}

bool Item::updateCategory(const QString &input_category, int item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("UPDATE Items SET category = :category WHERE item_id = :item_id");
    q.bindValue(":category", input_category);
    q.bindValue(":item_id", item_id);
    return q.exec();
}

void Item::showAmount() {
    ui->Amount_L->show();
    ui->Addamount_PB->show();
    ui->Removeamount_PB->show();
}

void Item::setAmountText(int input_amount) {
    amount = input_amount;
    ui->Amount_L->setText(QString::number(amount));
}

void Item::on_Addamount_PB_clicked() {
    ui->Amount_L->setText(QString::number(++amount));
    emit amountChanged(item_id, amount);
}

void Item::on_Removeamount_PB_clicked() {
    if (0 == amount) return;
    else ui->Amount_L->setText(QString::number(--amount));
    emit amountChanged(item_id, amount);
}

int Item::getMaxItemID() const {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.exec("SELECT MAX(item_id) FROM Items");
    if (q.next()) return q.value(0).toInt();
    else {
        qDebug() << "Failed to get max item_id" << q.lastError().text();
        return 0;
    }
}

QString Item::getName() const {
    return name;
}

QString Item::getDescription() const {
    return description;
}

QString Item::getPrice() const {
    return price;
}

QString Item::getDays() const {
    return days;
}

QString Item::getCategory() const {
    return category;
}

QByteArray Item::getImage() const {
    return image;
}

bool Item::deleteItem(int input_item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("DELETE FROM Items WHERE item_id = :item_id");
    q.bindValue(":item_id", input_item_id);
    if (q.exec()) {
        Ingredient ingredient;
        if (ingredient.deleteIngredient(input_item_id)) return true;
        else return false;
    }
    else {
        qDebug() << "Failed to delete item: " << q.lastError().text();
        return false;
    }
}

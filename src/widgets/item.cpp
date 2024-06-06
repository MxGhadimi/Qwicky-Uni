#include "item.h"
#include "ui_item.h"


Item::Item(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Item)
{
    ui->setupUi(this);
    ui->Description_TE->setReadOnly(true);
    ui->Description_TE->setContextMenuPolicy(Qt::NoContextMenu);
}

Item::~Item()
{
    delete ui;
}

void Item::setData(QByteArray input_image, QString input_name, QString input_description, QString input_price, QString input_days, QString input_category, int input_item_id) {
    item_id = input_item_id;
    QSqlQuery q;
    q.prepare("INSERT INTO Items (image, name, description, price, days, category) VALUES (:image, :name, :description, :price, :days, :category)");
    q.bindValue(":image", input_image);
    q.bindValue(":name", input_name);
    q.bindValue(":description", input_description);
    q.bindValue(":price", input_price.trimmed());
    q.bindValue(":days", input_days);
    q.bindValue(":category", input_category);
    if (!q.exec()) qDebug() << "Failed to insert Food: " << q.lastError().text();
}


void Item::getData(int input_item_id) {
    item_id = input_item_id;
    QSqlQuery q;
    q.prepare("SELECT * FROM Items WHERE item_id = :item_id");
    q.bindValue(":item_id", item_id);
    if (!q.exec()) qDebug() << "Error executing query: " << q.lastError().text();

    if (q.next()) {
        image = q.value("image").toByteArray();
        name = q.value("name").toString();
        description = q.value("description").toString();
        price = q.value("price").toString();
    }
    else qDebug() << "No rows found in the table";
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
    showitem->setData(item_id);
    connect(showitem, &QObject::destroyed, showitem, &QObject::deleteLater);
    showitem->show();
}

void Item::updateName(QString input_name, int item_id) {
    QSqlQuery q;
    q.prepare("UPDATE Items SET name = :name WHERE item_id = :item_id");
    q.bindValue(":name", input_name);
    q.bindValue(":item_id", item_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

void Item::updateDays(QString input_days, int item_id) {
    QSqlQuery q;
    q.prepare("UPDATE Items SET days = :days WHERE item_id = :item_id");
    q.bindValue(":days", input_days);
    q.bindValue(":item_id", item_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

void Item::updatePrice(QString input_price, int item_id) {
    QSqlQuery q;
    q.prepare("UPDATE Items SET price = :price WHERE item_id = :item_id");
    q.bindValue(":price", input_price);
    q.bindValue(":item_id", item_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

void Item::updateDescription(QString input_Description, int item_id) {
    QSqlQuery q;
    q.prepare("UPDATE Items SET description = :description WHERE item_id = :item_id");
    q.bindValue(":description", input_Description);
    q.bindValue(":item_id", item_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

void Item::updateCategory(QString input_category, int item_id) {
    QSqlQuery q;
    q.prepare("UPDATE Items SET category = :category WHERE item_id = :item_id");
    q.bindValue(":category", input_category);
    q.bindValue(":item_id", item_id);
    if (!q.exec()) qDebug() << "Failed to update";
}

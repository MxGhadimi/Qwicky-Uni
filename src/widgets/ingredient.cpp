#include "ingredient.h"
#include "ui_ingredient.h"

Ingredient::Ingredient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ingredient)
{
    ui->setupUi(this);
}

Ingredient::~Ingredient()
{
    delete ui;
}

bool Ingredient::writeData(const QString &input_ingredients, int input_item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    QStringList ingredientsList = input_ingredients.split(", ");
    for (const QString &ingredient : ingredientsList) {
        QStringList part = ingredient.split(" - ");
        if (part.size() == 2) {
            QString ingredient_name = part[0];
            QString amount = part[1];
            q.prepare("INSERT INTO Ingredients (item_id, ingredient_name, amount) VALUES (:item_id, :ingredient_name, :amount)");
            q.bindValue(":item_id", input_item_id);
            q.bindValue(":ingredient_name", ingredient_name);
            q.bindValue(":amount", amount);
            if (!q.exec()) {
                qDebug() << "Failed to insert into Ingredients table: " << q.lastError().text();
                return false;
            }
        }
    }
    all_ingredients = input_ingredients;
    item_id = input_item_id;
    return true;
}

bool Ingredient::readData(int input_item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("SELECT * FROM Ingredients WHERE item_id = :item_id");
    q.bindValue(":item_id", input_item_id);
    if (!q.exec()) {
        qDebug() << "Error executing query(setData2): " << q.lastError().text();
        return false;
    }
    QString ingredients;
    while (q.next()) {
        QString ingredient = q.value("ingredient_name").toString();
        QString amount = q.value("amount").toString();
        if (!ingredients.isEmpty()) ingredients += ", " + ingredient + " - " + amount;
        else ingredients = ingredient + " - " + amount;
    }
    all_ingredients = ingredients;
    return true;
}

QString Ingredient::getAllIngredients() {
    return all_ingredients;
}

bool Ingredient::updateIngredient(const QString &input_ingredients, int input_item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("DELETE FROM Ingredients WHERE item_id = :item_id");
    q.bindValue(":item_id", input_item_id);
    if (!q.exec()) {
        qDebug() << "Failed to delete ingredients: " << q.lastError().text();
        return false;
    }

    QStringList ingredient_list = input_ingredients.split(", ");
    for (const QString &ingredient : ingredient_list) {
        QStringList part = ingredient.split(" - ");
        if (part.size() == 2) {
            QString name = part[0];
            QString amount = part[1];

            q.prepare("INSERT INTO Ingredients (item_id, ingredient_name, amount) VALUES (:item_id, :name, :amount)");
            q.bindValue(":item_id", input_item_id);
            q.bindValue(":name", name);
            q.bindValue(":amount", amount);
            if (!q.exec()) {
                qDebug() << "Failed to insert ingredient: " << q.lastError().text();
                return false;
            }
        }
    }
    return true;
}

bool Ingredient::deleteIngredient(int input_item_id) {
    QSqlDatabase items_db = DatabaseManager::getInstance().getItemsDatabase();
    QSqlQuery q(items_db);
    q.prepare("DELETE FROM Ingredients WHERE item_id = :item_id");
    q.bindValue(":item_id", input_item_id);
    if (q.exec()) return true;
    else {
        qDebug() << "Failed to delete ingredients: " << q.lastError().text();
        return false;
    }
}

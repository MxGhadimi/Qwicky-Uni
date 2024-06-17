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

void Ingredient::setData(const QString &input_ingredients, int input_item_id) {
    QSqlQuery q;
    QStringList ingredientsList = input_ingredients.split(", ");
    for (const QString &ingredient : ingredientsList) {
        QStringList parted = ingredient.split(" - ");
        if (parted.size() == 2) {
            QString ingredient_name = parted[0];
            QString amount = parted[1];
            q.prepare("INSERT INTO Ingredients (item_id, ingredient_name, amount) VALUES (:item_id, :ingredient_name, :amount)");
            q.bindValue(":item_id", input_item_id);
            q.bindValue(":ingredient_name", ingredient_name);
            q.bindValue(":amount", amount);
            if (!q.exec()) qDebug() << "Failed to insert into Ingredients table: " << q.lastError().text();
        }
    }
}

void Ingredient::updateIngredient(const QString &input_ingredients, int input_item_id) {
    QSqlQuery q;
    q.prepare("DELETE FROM Ingredients WHERE item_id = :item_id");
    q.bindValue(":item_id", input_item_id);
    if (!q.exec()) {
        qDebug() << "Failed to delete ingredients: " << q.lastError().text();
        return;
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
                return;
            }
        }
    }
}


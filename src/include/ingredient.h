#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QWidget>
#include "commonincludes.h"
#include "item.h"

namespace Ui {
class Ingredient;
}

class Ingredient : public QWidget
{
    Q_OBJECT

public:
    explicit Ingredient(QWidget *parent = nullptr);
    ~Ingredient();
    void writeData(const QString &input_ingredients, int input_item_id);
    void updateIngredient(const QString &input_ingredients, int input_item_id);


private:
    Ui::Ingredient *ui;
    QString all_ingredients;
    int item_id;
};

#endif // INGREDIENT_H

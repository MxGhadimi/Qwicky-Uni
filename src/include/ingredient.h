#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QWidget>
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QtUiTools/QUiLoader>
#include <QMessageBox>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include <QSqlError>
#include <QCheckBox>
#include <QMainWindow>
#include <QFileDialog>
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
    void setData(const QString &input_ingredients, int input_item_id);
    void getData(int input_item_id);
    void updateIngredient(const QString &input_ingredients, int input_item_id);


private:
    Ui::Ingredient *ui;
};

#endif // INGREDIENT_H

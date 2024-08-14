#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QWidget>
#include "commonincludes.h"
#include "item.h"

namespace Ui {
class Ingredient;
}

/**
 * @class Ingredient
 * @brief A class representing the ingredients in the Qwicky application.
 * @details This class provides methods to manage ingredient data, including writing, reading, updating, and deleting ingredients.
 */
class Ingredient : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Ingredient class.
     * @param parent The parent widget.
     */
    explicit Ingredient(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Ingredient class.
     */
    ~Ingredient();

    /**
     * @brief Writes ingredient data to the database.
     * @param input_ingredients The ingredients to be written.
     * @param input_item_id The ID of the item associated with the ingredients.
     * @return True if the operation is successful, false otherwise.
     */
    bool writeData(const QString &input_ingredients, int input_item_id);

    /**
     * @brief Reads ingredient data from the database.
     * @param input_item_id The ID of the item associated with the ingredients.
     * @return True if the operation is successful, false otherwise.
     */
    bool readData(int input_item_id);

    /**
     * @brief Retrieves all ingredients.
     * @return A string containing all ingredients.
     */
    QString getAllIngredients();

    /**
     * @brief Updates an ingredient in the database.
     * @param input_ingredients The new ingredients to be updated.
     * @param input_item_id The ID of the item associated with the ingredients.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateIngredient(const QString &input_ingredients, int input_item_id);

    /**
     * @brief Deletes an ingredient from the database.
     * @param input_item_id The ID of the item associated with the ingredients.
     * @return True if the operation is successful, false otherwise.
     */
    bool deleteIngredient(int input_item_id);

private:
    Ui::Ingredient *ui; ///< Pointer to UI components.
    QString all_ingredients; ///< String containing all ingredients.
    int item_id; ///< ID of the item associated with the ingredients.
};

#endif // INGREDIENT_H

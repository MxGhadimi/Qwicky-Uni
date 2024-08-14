#ifndef SHOWITEM_H
#define SHOWITEM_H

#include <QWidget>
#include "commonincludes.h"
#include "item.h"
#include "ingredient.h"

namespace Ui {
class Showitem;
}

/**
 * @class Showitem
 * @brief A class representing an Item display in the Qwicky application.
 * @details This class provides methods to manage item data, including displaying, editing and deleting an item.
 */
class Showitem : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Showitem class.
     * @param parent The parent widget.
     * @details Initializes the UI components and sets up the layout.
     */
    explicit Showitem(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Showitem class.
     * @details Deletes the UI components to free resources.
     */
    ~Showitem();

    /**
     * @brief Shows item data.
     * @param item_id The ID of the item to be displayed.
     * @details Retrieves and displays the item details from the database.
     */
    void showData(int item_id);

signals:
    /**
     * @brief Signal emitted when the item is updated.
     * @details Notifies other parts of the application that the item has been updated.
     */
    void updatedItem();

private slots:
    /**
     * @brief Slot triggered when the "Edit" button is clicked.
     * @details Adjusts UI layout for editing mode.
     */
    void on_Edit_PB_clicked();

    /**
     * @brief Slot triggered when the amount is entered.
     * @details adds ingredient (name and amount) to the item.
     */
    void on_AmountEnter();

    /**
     * @brief Slot triggered when the "Delete Amount" button is clicked.
     * @details Deletes the last added ingredient from the item.
     */
    void on_deleteamount_PB_clicked();

    /**
     * @brief Slot triggered when the "Edit Image" button is clicked.
     * @details opens a new window to select a new image for the item.
     */
    void on_Editimage_PB_clicked();

    /**
     * @brief Slot triggered when the "Delete" button is clicked.
     * @details Deletes the item from the database.
     */
    void on_Delete_PB_clicked();

private:
    Ui::Showitem *ui; ///< Pointer to UI components.
    int item_id; ///< ID of the item.
    QByteArray image_data; ///< Image data of the item.
    QCheckBox *checkBoxes; ///< Checkboxes for ingredients.
    Item item; ///< Item object.
    Ingredient ingredient; ///< Ingredient object.
    QString all_ingredients; ///< All ingredients as a string.
};

#endif // SHOWITEM_H

#ifndef ADDITEM_H
#define ADDITEM_H

#include <QWidget>
#include "commonincludes.h"
#include "item.h"
#include "ingredient.h"

namespace Ui {
class Additem;
}

/**
 * @class Additem
 * @brief A class representing the Add Item (& Ingredient) in the Qwicky application.
 * @details This class provides methods to manage adding new items, including handling image uploads, ingredient lists, and saving item data.
 */
class Additem : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Additem class.
     * @param parent The parent widget.
     */
    explicit Additem(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Additem class.
     */
    ~Additem();

signals:
    /**
     * @brief Signal emitted when a new item is successfully inserted into the database.
     */
    void itemInserted();

private slots:
    /**
     * @brief Slot triggered when the "Add Image" button is clicked.
     * @details Opens a file dialog to select an image file and displays it in the UI.
     */
    void on_Addimage_PB_clicked();

    /**
     * @brief Slot triggered when the "Add Item" button is clicked.
     * @details Collects all input data from UI elements and saves it to the database.
     */
    void on_Additem_PB_clicked();

    /**
     * @brief Slot triggered when Enter key is pressed in Amount Line Edit.
     * @details Adds ingredient and amount to list displayed in UI.
     */
    void on_AmountEnter();

    /**
     * @brief Slot triggered when Delete Amount button is clicked.
     * @details Removes last ingredient from list displayed in UI.
     */
    void on_deleteamount_PB_clicked();

    /**
     * @brief Clears all UI elements after adding an item or closing dialog.
     */
    void clearUI();

    /**
     * @brief closeEvent handler to clear UI before closing dialog.
     * @param event Close event object.
     */
    void closeEvent(QCloseEvent *event);

private:
    Ui::Additem *ui; ///< Pointer to UI components.
    QByteArray image_data; ///< Data of uploaded image.
    QString all_ingredients; ///< List of ingredients added by user.
    QString days; ///< List of days selected by user (e.g., Monday, Tuesday).
};

#endif // ADDITEM_H

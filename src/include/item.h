#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include "commonincludes.h"

namespace Ui {
class Item;
}

/**
 * @class Item
 * @brief A class representing an item in the Qwicky application.
 * @details This class provides methods to manage item data, including reading, writing, updating, and deleting items.
 */
class Item : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Item class.
     * @param parent The parent widget.
     */
    explicit Item(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Item class.
     */
    ~Item();

    /**
     * @brief Reads item data from the database.
     * @param input_item_id The ID of the item to be read.
     * @return True if the operation is successful, false otherwise.
     */
    bool readData(int input_item_id);

    /**
     * @brief Writes item data to the database.
     * @param input_image The image of the item.
     * @param input_name The name of the item.
     * @param input_description The description of the item.
     * @param input_price The price of the item.
     * @param input_days The days associated with the item.
     * @param input_category The category of the item.
     * @param input_item_id The ID of the item.
     * @return True if the operation is successful, false otherwise.
     */
    bool writeData(QByteArray input_image, const QString &input_name, const QString &input_description, const QString &input_price, const QString &input_days, const QString &input_category, int input_item_id);

    /**
     * @brief Displays the item data.
     */
    void showData();

    /**
     * @brief Shows the amount of the item.
     */
    void showAmount();

    /**
     * @brief Sets the amount text for the item.
     * @param input_amount The amount to be set.
     */
    void setAmountText(int input_amount);

    /**
     * @brief Gets the maximum item ID.
     * @return The maximum item ID.
     */
    int getMaxItemID() const;

    /**
     * @brief Gets the name of the item.
     * @return The name of the item.
     */
    QString getName() const;

    /**
     * @brief Gets the description of the item.
     * @return The description of the item.
     */
    QString getDescription() const;

    /**
     * @brief Gets the price of the item.
     * @return The price of the item.
     */
    QString getPrice() const;

    /**
     * @brief Gets the days associated with the item.
     * @return The days associated with the item.
     */
    QString getDays() const;

    /**
     * @brief Gets the category of the item.
     * @return The category of the item.
     */
    QString getCategory() const;

    /**
     * @brief Gets the image of the item.
     * @return The image of the item.
     */
    QByteArray getImage() const;

    /**
     * @brief Updates the name of the item.
     * @param input_name The new name of the item.
     * @param item_id The ID of the item.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateName(const QString &input_name, int item_id);

    /**
     * @brief Updates the days associated with the item.
     * @param input_days The new days associated with the item.
     * @param item_id The ID of the item.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateDays(const QString &input_days, int item_id);

    /**
     * @brief Updates the price of the item.
     * @param input_price The new price of the item.
     * @param item_id The ID of the item.
     * @return True if the operation is successful, false otherwise.
     */
    bool updatePrice(const QString &input_price, int item_id);

    /**
     * @brief Updates the category of the item.
     * @param input_category The new category of the item.
     * @param item_id The ID of the item.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateCategory(const QString &input_category, int item_id);

    /**
     * @brief Updates the description of the item.
     * @param input_Description The new description of the item.
     * @param item_id The ID of the item.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateDescription(const QString &input_Description, int item_id);

    /**
     * @brief Deletes an item from the database.
     * @param input_item_id The ID of the item to be deleted.
     * @return True if the operation is successful, false otherwise.
     */
    bool deleteItem(int input_item_id);

signals:
    /**
     * @brief Signal emitted when the amount of an item changes.
     * @param item_id The ID of the item.
     * @param amount The new amount of the item.
     */
    void amountChanged(int item_id, int amount);

private slots:
    /**
     * @brief Slot triggered when the "Name" button is clicked.
     * @details Shows the item details using Showitem class ui.
     */
    void on_Name_PB_clicked();

    /**
     * @brief Slot triggered when the "Add Amount(+ icon)" button is clicked.
     * @details Increments the amount of the item.
     */
    void on_Addamount_PB_clicked();

    /**
     * @brief Slot triggered when the "Remove Amount(- icon)" button is clicked.
     * @details Decrements the amount of the item.
     */
    void on_Removeamount_PB_clicked();

private:
    Ui::Item *ui; ///< Pointer to UI components.
    int item_id; ///< ID of the item.
    QByteArray image; ///< Image of the item.
    QString name; ///< Name of the item.
    QString description; ///< Description of the item.
    QString price; ///< Price of the item.
    QString days; ///< Days associated with the item.
    QString category; ///< Category of the item.
    int amount; ///< Amount of the item.
};

#endif // ITEM_H

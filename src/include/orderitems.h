#ifndef ORDERITEMS_H
#define ORDERITEMS_H

#include <QWidget>
#include "commonincludes.h"

namespace Ui {
class OrderItems;
}

/**
 * @class OrderItems
 * @brief A class representing order items in the Qwicky application.
 * @details This class provides methods to manage the itmes of the order, including reading, displaying, and updating order items.
 */
class OrderItems : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the OrderItems class.
     * @param parent The parent widget.
     */
    explicit OrderItems(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the OrderItems class.
     */
    ~OrderItems();

    /**
     * @brief Reads items data from the database.
     * @param input_orderitem_id The ID of the order item to be read.
     * @return True if the operation is successful, false otherwise.
     */
    bool readData(int input_orderitem_id);

    /**
     * @brief Reads the price of an order item.
     * @return The price of the order item.
     */
    double readPrice();

    /**
     * @brief Reads the name, price and total (based on amount) of the order.
     * @param input_amount The amount of the order item.
     * @param input_item_id The ID of the order item.
     * @return True if the operation is successful, false otherwise.
     */
    bool showTMPData(int input_amount, int input_item_id);

    /**
     * @brief Displays the order item data on ui.
     */
    void showData();

    /**
     * @brief Gets the total price of the order items.
     * @return The total price of the order items.
     */
    double getTotalPrice();

    /**
     * @brief Gets the amount of the order item.
     * @return The amount of the order item.
     */
    int getAmount();

    /**
     * @brief Updates the amount of the order item.
     * @param amount The new amount of the order item.
     */
    void updateAmount(int amount);

private:
    Ui::OrderItems *ui; ///< Pointer to UI components.
    QString name; ///< Name of the order item.
    int item_id; ///< ID of the order item.
    int amount; ///< Amount of the order item.
    double total_price; ///< Total price of the order items.
    double price; ///< Price of the order item.
};

#endif // ORDERITEMS_H

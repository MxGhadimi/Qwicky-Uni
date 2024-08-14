#ifndef ORDER_H
#define ORDER_H

#include <QWidget>
#include "commonincludes.h"
#include "orderitems.h"
#include "showcustomer.h"
#include "databasemanager.h"

namespace Ui {
class Order;
}

/**
 * @class Order
 * @brief A class representing an order in the Qwicky application.
 * @details This class provides methods to manage order data, including Deleting, Adding, updating, and displaying orders.
 */
class Order : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Order class.
     * @param parent The parent widget.
     */
    explicit Order(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Order class.
     */
    ~Order();

    /**
     * @brief Writes order data to the database.
     * @param customer_id The ID of the customer.
     * @param table The table number.
     * @param order_type The type of order(dine in/takeaway).
     * @param selected_items_str The selected items as a string.
     * @param date_str The date of the order.
     * @param time_str The time of the order.
     * @return True if the operation is successful, false otherwise.
     */
    bool writeData(int customer_id, const QString &table, const QString &order_type, const QString &selected_items_str, const QString &date_str, const QString &time_str);

    /**
     * @brief Reads order data from the database.
     * @param input_item_id The ID of the item to be read.
     * @return True if the operation is successful, false otherwise.
     */
    bool readData(int input_item_id);

    /**
     * @brief Displays the order data.
     */
    void showData();

    /**
     * @brief Gets the order ID.
     * @return The order ID.
     */
    int getOrderID() const;

    /**
     * @brief Gets the customer ID.
     * @return The customer ID.
     */
    int getCustomerID() const;

    /**
     * @brief Gets the table number.
     * @return The table number.
     */
    QString getTable() const;

    /**
     * @brief Gets the order type.
     * @return The order type.
     */
    QString getOrderType() const;

    /**
     * @brief Gets the date of the order.
     * @return The date of the order.
     */
    QString getDate() const;

    /**
     * @brief Gets the time of the order.
     * @return The time of the order.
     */
    QString getTime() const;

    /**
     * @brief Gets the pay status of the order.
     * @return The pay status of the order.
     */
    QString getPayStatus() const;

    /**
     * @brief Gets the name associated with the order.
     * @return The name associated with the order.
     */
    QString getName() const;

    /**
     * @brief Gets the total price of the order.
     * @return The total price of the order.
     */
    double getTotalPrice() const;

    /**
     * @brief Updates the selected items in the order.
     * @param selected_items_str The new items as a string.
     * @param order_id The ID of the order.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateItems(const QString &selected_items_str, int order_id);

    /**
     * @brief Updates the date of the order.
     * @param date_str The new date of the order.
     * @param order_id The ID of the order.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateDate(const QString &date_str, int order_id);

    /**
     * @brief Updates the time of the order.
     * @param time_str The new time of the order.
     * @param order_id The ID of the order.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateTime(const QString &time_str, int order_id);

    /**
     * @brief Updates the table number of the order.
     * @param table_str The new table number.
     * @param order_id The ID of the order.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateTable(const QString &table_str, int order_id);

    /**
     * @brief Updates the order type (+ if takeaway change the tale to "TA").
     * @param order_type The new order type.
     * @param order_id The ID of the order.
     * @return True if the operation is successful, false otherwise.
     */
    bool updateOrderType(const QString &order_type, int order_id);

private slots:
    /**
     * @brief Slot triggered when the pay status combo box state changes.
     * @param arg1 The new state.
     * @details changes the Paystatus to "Payed" or "Pending"
     */
    void on_Paystatus_CB_stateChanged(int arg1);

    /**
     * @brief Shows the Showorder class ui when the order ID button is clicked.
     * @details for deleting or editing the order
     */
    void on_Orderid_PB_clicked();

    /**
     * @brief Shows the Showcustomer class ui when the customer info button is clicked.
     */
    void on_Customerinfo_PB_clicked();

private:
    Ui::Order *ui; ///< Pointer to UI components.
    QVBoxLayout *verticalLayout; ///< Vertical layout.
    QWidget *scrollWidget; ///< Scroll widget.
    int order_id; ///< ID of the order.
    int customer_id; ///< ID of the customer.
    QString table; ///< Table number.
    QString order_type; ///< Order type.
    QString date; ///< Date of the order.
    QString time; ///< Time of the order.
    QString pay_status; ///< Pay status of the order.
    QString name; ///< Name associated with the order.
    double total_price; ///< Total price of the order.
};

#endif // ORDER_H

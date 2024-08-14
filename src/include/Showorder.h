#ifndef SHOWORDER_H
#define SHOWORDER_H

#include <QWidget>
#include "commonincludes.h"
#include "orderitems.h"
#include "addorder.h"
#include "item.h"
#include "order.h"

namespace Ui {
class Showorder;
}

/**
 * @class Showorder
 * @brief A class representing an Order display in the Qwicky application.
 * @details This class provides methods to manage order data, including displaying, editing, and deleting an order.
 */
class Showorder : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Showorder class.
     * @param parent The parent widget.
     * @details Initializes the UI components and sets up the layout.
     */
    explicit Showorder(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Showorder class.
     * @details Deletes the UI components to free resources.
     */
    ~Showorder();

    /**
     * @brief Shows order data.
     * @param input_order_id The ID of the order to be displayed.
     * @details Retrieves and displays the order details from the database.
     */
    void showData(int input_order_id);

private slots:
    /**
     * @brief Slot triggered when the "Edit" button is clicked.
     * @details Adjusts UI layout for editing mode.
     */
    void on_Edit_PB_clicked();

    /**
     * @brief Slot triggered when the pay status combo box state changes.
     * @param arg1 The new state.
     * @details Updates the pay status in the database based on user selection.
     */
    void on_Paystatus_CB_stateChanged(int arg1);

    /**
     * @brief Shows the items in the order.
     * @details Retrieves and displays all items associated with the current order.
     */
    void showItems();

    /**
     * @brief Updates the amount of an item in the order.
     * @param item_id The ID of the item.
     * @param amount The new amount of the item.
     * @details Reflects changes in UI elements displaying total cost as well as individual item amounts.
     */
    void updateItemAmount(int item_id, int amount);

    /**
     * @brief Slot triggered when the search line edit text changes.
     * @param arg1 The new text.
     * @details Updates item list based on search query entered by user.
     */
    void on_Search_LE_textChanged(const QString &arg1);

    /**
     * @brief Slot triggered when the back button is clicked.
     * @details Navigates back to previous screen (Order Info).
     */
    void on_back_PB_clicked();

    /**
     * @brief Slot triggered when the table button is clicked.
     * @details Displays available tables based on current date and time selection.
     */
    void on_Table_PB_clicked();

    /**
     * @brief Slot triggered when the delete button is clicked.
     * @details Deletes an order from database along with its associated items and table reservations if any exists respectively then closes window after confirmation message displayed successfully deleted otherwise logs error messages accordingly if failed during execution process steps involved therein respectively too!
      */
    void on_Delete_PB_clicked();

    /**
       *@brief Slot triggered when customer info button clicked
       *@details Opens new window displaying customer information corresponding current selected customer ID respectively too!
        */
    void on_Customerinfo_PB_clicked();

private:
    Ui::Showorder *ui; ///< Pointer to UI components.

    QVBoxLayout *verticalLayout; ///< Vertical layout used within first scroll area widget.
    QWidget *scrollWidget; ///< Scroll widget used within first scroll area widget.
    QGridLayout *gridLayout; ///< Grid layout used within first scroll area widget.
    QGridLayout *gridLayout_3; ///< Second grid layout used within second scroll area widget.
    QWidget *scrollWidget_2; ///< Second scroll widget used within second scroll area widget.
    QWidget *scrollWidget_3; ///< Third scroll widget used within third scroll area widget.

    Order order; ///< Order object representing current displayed order details respectively too!
    int order_id; ///< ID representing current displayed order respectively too!
    double total_price; ///< Total price calculated summing up prices multiplied quantities respective items added cart list respectively too!
    QMap<int,int> itemAmounts; ///< Map storing amounts corresponding each selected item's ID respectively too!
    QMap<int ,OrderItems*> selectedItems; ///< Map storing pointers towards OrderItems objects representing each selected Item respectively too!
    double total; ///< Total cost calculated summing up prices multiplied quantities respective items added cart list respectively too!
};

#endif // SHOWORDER_H

#ifndef ADDORDER_H
#define ADDORDER_H

#include <QWidget>
#include "commonincludes.h"
#include "showselected.h"
#include "item.h"
#include "order.h"

namespace Ui {
class Addorder;
}

/**
 * @class Addorder
 * @brief A class representing the Add Order in the Qwicky application.
 * @details This class provides methods to manage adding new orders, including handling different types of orders (Dine In, Takeaway), selecting and filtering(by the selected time and capacity) tables, and managing item selection.
 */
class Addorder : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Addorder class.
     * @param parent The parent widget.
     */
    explicit Addorder(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Addorder class.
     */
    ~Addorder();

    /**
     * @brief Displays available items based on current date.
     */
    void showItems();

private slots:
    /**
     * @brief Slot triggered when Choose Table (right arrow) button is clicked.
     * @details Shows available tables based on guest number and date/time selection.
     */
    void on_Choosetable_PB_clicked();

    /**
     * @brief Slot triggered when "Takeaway" radio button is clicked.
     * @details Adjusts UI layout for Takeaway orders.
     */
    void on_Takeaway_RB_clicked();

    /**
     * @brief Slot triggered when "Dine In" radio button is clicked.
     * @details Adjusts UI layout for Dine In orders.
     */
    void on_Dinein_RB_clicked();

    /**
     * @brief Slot triggered when "Continue Order" button is clicked.
     * @details Proceeds to item selection after validating customer information and table choice (if applicable) shows the items based on the availibilty in the chosen date.
     */
    void on_Continueorder_PB_clicked();

    /**
     * @brief Slot triggered when "Add Person" button is clicked.
     * @details Increments guest count and updates display accordingly.
     */
    void on_Addperson_PB_clicked();

    /**
     * @brief Slot triggered when "Remove Person" button is clicked.
     * @details Decrements guest count and updates display accordingly.
     */
    void on_RemovePerson_PB_clicked();

    /**
     * @brief Slot triggered when "Back" button is clicked.
     * @details Navigates back to previous screen (New Order).
     */
    void on_Back_PB_clicked();

    /**
     * @brief Slot triggered when "Add Items" button is clicked.
     * @details Finalizes order by saving selected items into database with corresponding details like customer ID, table name (if applicable), order type, etc.
     */
    void on_Additems_PB_clicked();

    /**
     * @brief Search between the Items and display the matching Items when the text changes in Search Line Edit widget.
     * @param arg1 New text entered into Search Line Edit widget.
     * @details Updates item list based on search query entered by user.
     */
    void on_Search_LE_2_textChanged(const QString &arg1);

    /**
     * @brief Updates amount of an item in the selected items list.
      *@param item_id ID of the item whose amount needs updating.
      *@param amount New amount value for that item.
      *@details Reflects changes in UI elements displaying total cost as well as individual item amounts.
      */
    void updateItemAmount(int item_id, int amount);

    /**
      *@brief Clears all UI elements after adding an order or closing dialog.
      *@details Resets all fields back to their initial state before closing this dialog window.
      */
    void closeUI();

private:
    Ui::Addorder *ui; ///< Pointer to UI components.

    QWidget *scrollWidget;
    QWidget *scrollWidget_2;
    QWidget *scrollWidget_3;

    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;

    QCheckBox *checkBox; ///< Check box used internally.
    QString table_name; ///< Name of chosen table (if applicable).
    QString all_orders; ///< variable storing all orders data temporarily during processing steps

    QMap<int,int> itemAmounts; ///< Map storing amounts corresponding each selected item's ID
    QMap<int ,ShowSelected*> selectedItems; ///< Map storing pointers towards ShowSelected objects representing each selected Item

    int guests; ///< Number representing number guests attending order
    int customer_id; ///< ID representing customer placing order
    QString order_type; ///< Type representing type whether dine-in takeaway etc
    QString selected_items_str; ///< String containing concatenated string representation all selected items along their respective quantities
    double total; ///< Total cost calculated summing up prices multiplied quantities respective items added cart list
};

#endif // ADDORDER_H

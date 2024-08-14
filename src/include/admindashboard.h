#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QMainWindow>
#include "commonincludes.h"
#include "item.h"
#include "order.h"
#include "showcustomer.h"
#include "customer.h"

namespace Ui {
class AdminDashboard;
}

/**
 * @class AdminDashboard
 * @brief The main administrative dashboard for the Qwicky application.
 * @details This class manages the UI and functionality of the admin dashboard, including navigation, managing items, orders and customers and displaying there info.
 */
class AdminDashboard : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the AdminDashboard class.
     * @param parent The parent widget.
     */
    explicit AdminDashboard(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the AdminDashboard class.
     */
    ~AdminDashboard();

public slots:
    /**
     * @brief Displays the menu items.
     */
    void showMenu();

    /**
     * @brief Displays the orders.
     */
    void showOrders();

    /**
     * @brief Displays the customers.
     */
    void showCustomers();

signals:
    /**
     * @brief Signal to show the Additem page.
     */
    void showAdditemPage();

    /**
     * @brief Signal to show the Addorder page.
     */
    void showAddorderPage();

    /**
     * @brief Signal to show the MainWindow page.
     */
    void showMainWindowPage();

private slots:
    /**
     * @brief Updates the date displayed in the UI.
     */
    void updateDate();

    // Menu
    /**
     * @brief sets the current page to Dashboard widget when the Dashboard button is clicked.
     */
    void on_Dashboard_PB_clicked();

    /**
     * @brief Slot triggered when the New Order button is clicked to send the showAddorderPage signal.
     */
    void on_Neworder_PB_clicked();

    // Menu
    /**
     * @brief Displays the menu items for the current day.
     */
    void showTodayMenu();

    /**
     * @brief sets the current page to Menu widget when the Menu button is clicked.
     */
    void on_Menu_PB_clicked();

    /**
     * @brief Search between the menu Items and display the matching Items when the menu search text changes.
     * @param arg1 The new search text.
     */
    void on_Menusearch_LE_textChanged(const QString &arg1);

    /**
     * @brief Slot triggered when the Add Item button is clicked to send the showAdditemPage signal.
     */
    void on_Additem_PB_clicked();

    /**
     * @brief Display the available items in the selected date when the date edit widget's user date changes.
     * @param date The new date.
     */
    void on_dateEdit_3_userDateChanged(const QDate &date);

    /**
     * @brief Display the items in the chosen category when the category combo box's current text changes.
     * @param arg1 The new category text.
     */
    void on_Category_C_currentTextChanged(const QString &arg1);

    // Orders
    /**
     * @brief Sets the current page to Order widget when the Orders button is clicked.
     */
    void on_Orders_PB_clicked();

    /**
     * @brief Slot triggered when the Add Order button is clicked to send the showAddorderPage signal.
     */
    void on_Neworder_PB_2_clicked();

    /**
     * @brief Search between the Orders and display the matching Orders when the order search text changes.
     * @param arg1 The new search text.
     */
    void on_Searchorder_L_textChanged(const QString &arg1);

    // Customers
    /**
     * @brief Sets the current page to Customer widget when the Customers button is clicked.
     */
    void on_Customer_PB_clicked();

    /**
     * @brief Slot triggered when the New Customer button is clicked to show the Showcustomer ui.
     */
    void on_Newcustomer_PB_clicked();

    /**
     * @brief Search between the Customers and display the matching Customers when the customer search text changes.
     * @param arg1 The new search text.
     */
    void on_Search_LE_textChanged(const QString &arg1);

    // Other
    /**
     * @brief Sets the current page to Reservations widget when the Reservations button is clicked.
     */
    void on_Reservations_PB_clicked();

    /**
     * @brief sets the current page to Tables widget when the Tables button is clicked.
     */
    void on_Tabels_PB_clicked();

    /**
     * @brief sets the current page to Settings widget when the Settings button is clicked.
     */
    void on_Settings_PB_clicked();

    /**
     * @brief sets the current page to Quit widget when the Quit button is clicked.
     */
    void on_Quit_PB_clicked();

private:
    Ui::AdminDashboard *ui; ///< Pointer to the UI component
};

#endif // ADMINDASHBOARD_H

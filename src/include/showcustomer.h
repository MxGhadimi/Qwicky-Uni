#ifndef SHOWCUSTOMER_H
#define SHOWCUSTOMER_H

#include <QWidget>
#include "commonincludes.h"
#include "customer.h"

namespace Ui {
class Showcustomer;
}

/**
 * @class Showcustomer
 * @brief A class representing a Customer display in the Qwicky application.
 * @details This class provides methods to manage customer data, including displaying, adding, editing and deleting an customer.
 */
class Showcustomer : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Showcustomer class.
     * @param parent The parent widget.
     */
    explicit Showcustomer(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Showcustomer class.
     */
    ~Showcustomer();

    /**
     * @brief Shows customer data.
     * @param input_customer_id The ID of the customer to be displayed.
     */
    void showData(int input_customer_id);

    /**
     * @brief Adds a new customer.
     * @details Adjusts UI layout for adding new customer.
     */
    void addCustomer();

private slots:
    /**
     * @brief Slot triggered when the "Add" button is clicked.
     * @details Adds a new customer to the database.
     */
    void on_Add_PB_clicked();

    /**
     * @brief Slot triggered when the "Edit" button is clicked.
     * @details Adjusts UI layout for editing mode.
     */
    void on_Edit_PB_clicked();

    /**
     * @brief Slot triggered when the "Delete" button is clicked.
     * @details Deletes the customer from the database.
     */
    void on_Delete_PB_clicked();

private:
    Ui::Showcustomer *ui; ///< Pointer to UI components.
    int customer_id; ///< ID of the customer.
    Customer customer; ///< Customer object.
};

#endif // SHOWCUSTOMER_H

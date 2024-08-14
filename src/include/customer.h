#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include "commonincludes.h"

namespace Ui {
class Customer;
}

/**
 * @class Customer
 * @brief A class representing a customer in the Qwicky application.
 * @details This class provides methods to manage customer data, including writing, reading, updating, and deleting customer information.
 */
class Customer : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Customer class.
     * @param parent The parent widget.
     */
    explicit Customer(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Customer class.
     */
    ~Customer();

    /**
     * @brief Writes new customer data to the database.
     * @param input_first_name The first name of the customer.
     * @param input_last_name The last name of the customer.
     * @param input_phone_number The phone number of the customer.
     * @param input_address The address of the customer.
     * @param input_credit The credit amount for the customer.
     * @param input_debt The debt amount for the customer.
     * @param input_username The username chosen by or assigned to the customer.
     * @param input_password The password chosen by or assigned to the customer.
     * @return True if data is successfully written; false otherwise.
     */
    bool writeData(QString input_first_name, QString input_last_name, QString input_phone_number, QString input_address, double input_credit, double input_debt, QString input_username, QString input_password);

    /**
     * @brief Reads existing customer data from the database based on a given ID.
     * @param input_customer_id The ID of the customer to read data for.
     * @return True if data is successfully read; false otherwise.
     */
    bool readData(int input_customer_id);

    /**
     * @brief Displays the customer data in UI elements.
     */
    void showData();

    /**
     * @brief Gets the ID of this customer instance.
     * @return The ID of this customer instance.
     */
    int getCustomerID() const;

    /**
     * @brief Gets first name associated with this customer instance.
     * @return First name associated with this customer instance.
     */
    QString getFirstName() const;

    /**
     * @brief Gets last name associated with this customer instance.
     * @return Last name associated with this customer instance.
     */
    QString getLastName() const;

    /**
     * @brief Gets phone number associated with this customer instance.
     * @return Phone number associated with this customer instance.
     */
    QString getPhoneNumber() const;

    /**
     * @brief Gets address associated with this customer instance.
     * @return Address associated with this customer instance.
     */
    QString getAddress() const;

    /**
     * @brief Gets credit amount associated with this customer instance.
     * @return Credit amount associated with this customer instance.
     */
    double getCredit() const;

    /**
     * @brief Gets debt amount associated with this customer instance.
     * @return Debt amount associated with this customer instance.
     */
    double getDebt() const;

    /**
     * @brief Gets username chosen by or assigned to this customer instance.
     * @return Username chosen by or assigned to this customer instance.
     */
    QString getUsername() const;

    /**
     * @brief Gets password chosen by or assigned to this customer instance.
     * @return Password chosen by or assigned to this customer instance.
     */
    QString getPassword() const;

    /**
     * @brief Updates first name in database for a given ID.
      *@param input_first_name New first name value.
      *@param customer_id ID of the customer whose first name needs updating.
      *@return True if update operation is successful; false otherwise.
      */
    bool updateFirstName(QString input_first_name,int customer_id);

    /**
      *@brief Updates last name in database for a given ID.
      *@param input_last_name New last name value.
      *@param customer_id ID of the customer whose last name needs updating.
      *@return True if update operation is successful; false otherwise.
      */
    bool updateLastName(QString input_last_name,int customer_id);

    /**
      *@brief Updates phone number in database for a given ID.
      *@param input_phone_number New phone number value.
      *@param customer_id ID of the customer whose phone number needs updating.
      *@return True if update operation is successful; false otherwise.
      */
    bool updatePhoneNumber(QString input_phone_number,int customer_id);

    /**
      *@brief Updates address in database for a given ID.
      *@param input_address New address value.
      *@param customer_id ID of the customer whose address needs updating.
      *@return True if update operation is successful; false otherwise.
      */
    bool updateAddress(QString input_address,int customer_id);

    /**
      *@brief Updates credit amount in database for a given ID.
      *@param input_credit New credit amount value.
      *@param customer_id ID of the customer whose credit amount needs updating.
      *@return True if update operation is successful; false otherwise.
      */
    bool updateCredit(double input_credit,int customer_id);

    /**
      *@brief Updates debt amount in database for a given ID.
      *@param input_debt New debt amount value.
      *@param customer_id ID of the customer whose debt amount needs updating.
      *@return True if update operation is successful; false otherwise.
      */
    bool updateDebt(double input_debt,int customer_id);

    /**
      *@brief Updates username in database for a given ID.
      *@param input_username New username value.
      *@param customer_id ID of the customer whose username needs updating.
      *@return True if update operation is successful; false otherwise.
      */
    bool updateUsername(const QString &input_username,int customer_id);

    /**
      *@brief Deletes existing record from database based on provided ID.
       *@param input_customer_id ID corresponding to record that should be deleted from Customers table
       *@return True upon successful deletion; False otherwise
       */
    bool deleteCustomer(int input_customer_id);

private slots:
    /**
    * Shows the Showcustoemr class ui when Edit button clicked
    */
    void on_Edit_PB_clicked();

    /**
    * Delets the custoemr from database.
    */
    void on_Delete_PB_clicked();

private:
    Ui::Customer *ui; ///< Pointer to the UI component

    QString first_name; ///< First name attribute
    QString last_name; ///< Last name attribute
    QString phone_number; ///< Phone Number attribute
    QString address; ///< Address attribute
    double credit; ///< Credit Attribute
    double debt; ///< Debt Attribute
    QString username; ///< Username Attribute
    QString password; ///< Password Attribute
    int customer_id; ///< Customer ID Attribute

};

#endif // CUSTOMER_H

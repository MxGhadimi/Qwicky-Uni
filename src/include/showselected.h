#ifndef SHOWSELECTED_H
#define SHOWSELECTED_H

#include <QWidget>
#include "commonincludes.h"

namespace Ui {
class ShowSelected;
}

/**
 * @class ShowSelected
 * @brief A class representing a selected Item display in the Qwicky application.
 * @details This class provides methods to manage selected item data, including displaying and updating selected item information.
 */
class ShowSelected : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the ShowSelected class.
     * @param parent The parent widget.
     */
    explicit ShowSelected(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the ShowSelected class.
     */
    ~ShowSelected();

    /**
     * @brief Shows selected item data.
     * @param input_image The image of the item.
     * @param input_name The name of the item.
     * @param input_price The price of the item.
     * @param input_amount The amount of the item.
     * @param input_item_id The ID of the item.
     */
    void showData(QByteArray input_image, const QString &input_name, const QString &input_price, int input_amount, int input_item_id);

    /**
     * @brief Gets the amount of the selected item.
     * @return The amount of the selected item.
     */
    int getAmount();

    /**
     * @brief Gets the total price of the selected item.
     * @return The total price of the selected item.
     */
    double getTotal();

    /**
     * @brief Updates the amount of the selected item.
     * @param input_amount The new amount of the selected item.
     */
    void updateAmount(int input_amount);

private:
    Ui::ShowSelected *ui; ///< Pointer to UI components.
    QString price; ///< Price of the selected item.
    int amount; ///< Amount of the selected item.
};

#endif // SHOWSELECTED_H

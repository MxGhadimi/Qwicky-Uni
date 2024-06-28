#ifndef ORDERITEMS_H
#define ORDERITEMS_H

#include <QWidget>
#include "commonincludes.h"

namespace Ui {
class OrderItems;
}

class OrderItems : public QWidget
{
    Q_OBJECT

public:
    explicit OrderItems(QWidget *parent = nullptr);
    ~OrderItems();
    void readData(int input_orderitem_id);
    void showTMPData(int input_amount, int input_item_id);
    void showData();
    double getTotalPrice();
    void updateAmount(int amount);
    int getAmount();
    double readPrice();

private:
    Ui::OrderItems *ui;
    QString name;
    int item_id;
    int amount;
    double total_price;
    double price;
};

#endif // ORDERITEMS_H

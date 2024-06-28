#ifndef ORDER_H
#define ORDER_H

#include <QWidget>
#include "commonincludes.h"
#include "orderitems.h"

namespace Ui {
class Order;
}

class Order : public QWidget
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = nullptr);
    ~Order();
    void writeData(int customer_id, const QString &table, const QString &order_type, const QString &selected_items_str, const QString &date_str, const QString &time_str);
    void writeOrderItems(const QString &selected_items_str, int order_id);
    void readData(int input_item_id);
    void showData();
    void updateItems(const QString &selected_items_str, int order_id);
    void updateDate(const QString &date_str, int order_id);
    void updateTime(const QString &time_str, int order_id);
    void updateTable(const QString &table_str, int order_id);
    void updateOrderType(const QString &order_type, int order_id);

private slots:
    void on_Paystatus_CB_stateChanged(int arg1);
    void on_Orderid_PB_clicked();

private:
    Ui::Order *ui;
    QVBoxLayout *verticalLayout;
    QWidget *scrollWidget;
    int order_id;
    QString customer_id;
    QString table;
    QString order_type;
    QString date;
    QString time;
    QString pay_status;
    QString name;
    double total_price;
};

#endif // ORDER_H

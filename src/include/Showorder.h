#ifndef Showorder_H
#define Showorder_H

#include <QWidget>
#include "commonincludes.h"
#include "orderitems.h"
#include "addorder.h"
#include "item.h"
#include "order.h"

namespace Ui {
class Showorder;
}

class Showorder : public QWidget
{
    Q_OBJECT

public:
    explicit Showorder(QWidget *parent = nullptr);
    ~Showorder();
    void showData(int order_id);

private slots:

    void on_Edit_PB_clicked();
    void on_Paystatus_CB_stateChanged(int arg1);
    void showItems();
    void updateItemAmount(int item_id, int amount);

    void on_Search_LE_textChanged(const QString &arg1);

    void on_back_PB_clicked();

    void on_Table_PB_clicked();

    void on_Delete_PB_clicked();

private:
    Ui::Showorder *ui;
    QVBoxLayout *verticalLayout;
    QWidget *scrollWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QWidget *scrollWidget_2;
    QWidget *scrollWidget_3;
    int order_id;
    QString customer_id;
    QString table;
    QString order_type;
    QString date;
    QString time;
    QString pay_status;
    QString name;
    double total_price;
    QMap<int, int> itemAmounts;
    QMap<int, OrderItems*> selectedItems;
    double total;
};

#endif // Showorder_H

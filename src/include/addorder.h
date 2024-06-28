#ifndef ADDORDER_H
#define ADDORDER_H

#include <QWidget>
#include "commonincludes.h"
#include "showselected.h"

namespace Ui {
class Addorder;
}

class Addorder : public QWidget
{
    Q_OBJECT

public:
    explicit Addorder(QWidget *parent = nullptr);
    ~Addorder();
    void showItems();

private slots:
    void on_Choosetable_PB_clicked();
    void on_Takeaway_RB_clicked();
    void on_Dinein_RB_clicked();
    void on_Continueorder_PB_clicked();
    void on_Addperson_PB_clicked();
    void on_RemovePerson_PB_clicked();
    void on_Back_PB_clicked();
    void on_Additems_PB_clicked();
    void on_Search_LE_2_textChanged(const QString &arg1);
    void updateItemAmount(int item_id, int amount);
    void closeUI();

private:
    Ui::Addorder *ui;
    QWidget *scrollWidget;
    QWidget *scrollWidget_2;
    QWidget *scrollWidget_3;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QString table_name;
    QString all_orders;
    QMap<int, int> itemAmounts;
    QMap<int, ShowSelected*> selectedItems;
    int guests;
    int customer_id;
    QString order_type;
    QString selected_items_str;
    double total;
};

#endif // ADDORDER_H

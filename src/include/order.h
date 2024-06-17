#ifndef ORDER_H
#define ORDER_H

#include <QWidget>
#include <QFile>
#include <QDir>
#include <QtUiTools/QUiLoader>
#include <QMessageBox>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include <QSqlError>
#include <QCheckBox>
#include <QMainWindow>
#include <QFileDialog>
#include <QGridLayout>
#include <QScrollArea>
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
    void writeData(int customer_id, const QString &table, const QString &order_type, const QString &selected_items_str);
    void writeOrderItems(const QString &selected_items_str, int order_id);
    void readData(int input_item_id);
    void showData();

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

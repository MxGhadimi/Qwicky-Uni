#ifndef ORDERITEMS_H
#define ORDERITEMS_H

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

namespace Ui {
class OrderItems;
}

class OrderItems : public QWidget
{
    Q_OBJECT

public:
    explicit OrderItems(QWidget *parent = nullptr);
    ~OrderItems();
    void writeData();
    void readData(int input_orderitem_id);
    void showData();
    double getPrice();

private:
    Ui::OrderItems *ui;
    QString name;
    int item_id;
    int amount;
    double total_price;
};

#endif // ORDERITEMS_H

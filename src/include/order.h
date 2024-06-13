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

private:
    Ui::Order *ui;
};

#endif // ORDER_H

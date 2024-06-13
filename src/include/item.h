#ifndef ITEM_H
#define ITEM_H

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

#include "showitem.h"

namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT

public:
    explicit Item(QWidget *parent = nullptr);
    ~Item();
    void readData(int input_item_id);
    void writeData(QByteArray input_image, const QString &input_name, const QString &input_description, const QString &input_price, const QString &input_days, const QString &input_category, int input_item_id0);
    void updateName(const QString &input_name, int item_id);
    void updateDays(const QString &input_name, int item_id);
    void updatePrice(const QString &input_price, int item_id);
    void updateCategory(const QString &input_category, int item_id);
    void updateDescription(const QString &input_Description, int item_id);
    void showData();
    void showAmount();
    void setAmountText(const QString &text);

signals:
    void amountChanged(int item_id, int amount);

private slots:
    void on_Name_PB_clicked();

    void on_Addamount_PB_clicked();

    void on_Removeamount_PB_clicked();

private:
    Ui::Item *ui;
    int item_id;
    QByteArray image;
    QString name;
    QString description;
    QString price;
    QCheckBox *Check_CB;
    int amount;
};

#endif // ITEM_H

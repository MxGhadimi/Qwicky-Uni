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
    void getData(int input_item_id);
    void setData(QByteArray input_image, QString input_name, QString input_description, QString input_price, QString input_days, QString input_category, int input_item_id0);
    void updateName(QString input_name, int item_id);
    void updateDays(QString input_name, int item_id);
    void updatePrice(QString input_price, int item_id);
    void updateCategory(QString input_category, int item_id);
    void updateDescription(QString input_Description, int item_id);
    void showData();

private slots:

    void on_Name_PB_clicked();

private:
    Ui::Item *ui;
    int item_id;
    QByteArray image;
    QString name;
    QString description;
    QString price;
};

#endif // ITEM_H

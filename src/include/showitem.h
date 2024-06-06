#ifndef SHOWITEM_H
#define SHOWITEM_H

#include <QWidget>
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
#include <QTimer>
#include "item.h"
#include "ingredient.h"

namespace Ui {
class Showitem;
}

class Showitem : public QWidget
{
    Q_OBJECT

public:
    explicit Showitem(QWidget *parent = nullptr);
    ~Showitem();
    void showData(int item);
    void setData(int item);

signals:
    void updatedItem();

private slots:
    void on_Edit_PB_clicked();
    void on_AmountEnter();
    void on_deleteamount_PB_clicked();
    void on_Editimage_PB_clicked();
    void on_Delete_PB_clicked();

private:
    Ui::Showitem *ui;
    int item_id;
    QByteArray image_data;
    QCheckBox *checkBoxes;
    QString all_ingredients;

    QByteArray image;
    QString name;
    QString description;
    QString price;
    QString days;
    QString category;
};

#endif // SHOWITEM_H

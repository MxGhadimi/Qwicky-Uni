#ifndef ADDITEM_H
#define ADDITEM_H

#include "item.h"
#include "ingredient.h"

#include <QWidget>
#include <QSqlDatabase>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QTextCursor>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include <QSqlError>
#include <QEvent>
#include <QCloseEvent>

namespace Ui {
class Additem;
}

class Additem : public QWidget
{
    Q_OBJECT

public:
    explicit Additem(QWidget *parent = nullptr);
    ~Additem();

signals:
    void itemInserted();

private slots:
    void on_Addimage_PB_clicked();
    void on_Additem_PB_clicked();
    void on_AmountEnter();
    void on_deleteamount_PB_clicked();
    void clearUI();
    void closeEvent(QCloseEvent *event);

private:
    Ui::Additem *ui;
    QByteArray image_data;
    QString all_ingredients;
    QString days;
};

#endif // ADDITEM_H

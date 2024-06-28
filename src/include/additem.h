#ifndef ADDITEM_H
#define ADDITEM_H

#include <QWidget>
#include "commonincludes.h"
#include "item.h"
#include "ingredient.h"

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

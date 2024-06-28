#ifndef SHOWSELECTED_H
#define SHOWSELECTED_H

#include <QWidget>
#include "commonincludes.h"

namespace Ui {
class ShowSelected;
}

class ShowSelected : public QWidget
{
    Q_OBJECT

public:
    explicit ShowSelected(QWidget *parent = nullptr);
    ~ShowSelected();
    void showData(QByteArray input_image, const QString &input_name, const QString &input_price, int input_amount, int input_item_id);
    void updateAmount(int input_amount);
    int getAmount();
    double getTotal();

private:
    Ui::ShowSelected *ui;
    QString price;
    int amount;
};

#endif // SHOWSELECTED_H

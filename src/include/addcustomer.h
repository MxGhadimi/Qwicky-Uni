#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include <QWidget>

namespace Ui {
class Addcustomer;
}

class Addcustomer : public QWidget
{
    Q_OBJECT

public:
    explicit Addcustomer(QWidget *parent = nullptr);
    ~Addcustomer();

private:
    Ui::Addcustomer *ui;
};

#endif // ADDCUSTOMER_H

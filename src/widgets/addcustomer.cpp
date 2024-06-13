#include "addcustomer.h"
#include "ui_addcustomer.h"

Addcustomer::Addcustomer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Addcustomer)
{
    ui->setupUi(this);
}

Addcustomer::~Addcustomer()
{
    delete ui;
}

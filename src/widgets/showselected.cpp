#include "showselected.h"
#include "ui_showselected.h"

ShowSelected::ShowSelected(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShowSelected)
{
    ui->setupUi(this);
}

ShowSelected::~ShowSelected()
{
    delete ui;
}

void ShowSelected::showData(QByteArray input_image, const QString &input_name, const QString &input_price, int input_amount, int input_item_id) {
    QImage img;
    img.loadFromData(input_image);
    ui->Image_L->setPixmap(QPixmap::fromImage(img));
    ui->Image_L->setScaledContents(true);
    ui->Name_PB->setText(input_name);
    price = input_price;
    ui->Price_L->setText("$" + price);
    ui->Amount_L->setText(QString::number(input_amount));
    ui->Total_L->setText("$" + QString::number((price.toDouble()) * input_amount, 'f', 2));
    amount = input_amount;
}

void ShowSelected::updateAmount(int input_amount) {
    ui->Amount_L->setText(QString::number(input_amount));
    ui->Total_L->setText("$" + QString::number((price.toDouble()) * input_amount, 'f', 2));
    amount = input_amount;
}

int ShowSelected::getAmount() {
    return amount;
}

double ShowSelected::getTotal() {
    return ui->Total_L->text().remove(0, 1).toDouble();
}

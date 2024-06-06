#include "customerdashboard.h"
#include "ui_customerdashboard.h"

customerdashboard::customerdashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::customerdashboard)
{
    ui->setupUi(this);
    setWindowTitle("Qwicky");
}

customerdashboard::~customerdashboard()
{
    delete ui;
}

#include "additem.h"
#include "ui_additem.h"


Additem::Additem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Additem)
{
    ui->setupUi(this);
    setWindowTitle("Add Item");
    setFixedSize(380, 545);

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    QString dbpath = QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/items.db";
    database.setDatabaseName(dbpath);
    if (!database.open()) qDebug() << "Failed to open database" << database.lastError().text();

    ui->Showingredies_TE->setReadOnly(true);
    connect(ui->Amount_LE, &QLineEdit::returnPressed, this, &Additem::on_AmountEnter);
}

Additem::~Additem()
{
    delete ui;
}

void Additem::on_Addimage_PB_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Choose Image", "", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QFile::ReadOnly)) {
            image_data = file.readAll();
            file.close();

            QPixmap p;
            p.loadFromData(image_data);
            ui->Image_L->setPixmap(p);
            ui->Image_L->setScaledContents(true);
            ui->Addimage_PB->setStyleSheet("QPushButton { background-color: rgb(255, 137, 64); border: none; border-radius: 6px; padding-bottom: 5px; padding-left: 0.5px; padding-top: 3px; image: url(:/icons/images/icons/edit.png); font: 600 15pt \"Segoe UI\"; position: absolute; top: 12px; left: 228px; width: 25px; height: 25px; } QPushButton:hover { background-color: rgb(255, 215, 147); } QPushButton::pressed { background-color: rgb(255, 85, 0); }");
            ui->Addimage_PB->setGeometry(228, 12, 25, 25);
            //ui->Addimage_PB->setBaseSize(228,12);
        }
    }
}

void Additem::on_Additem_PB_clicked() {
    QString name = ui->Name_LE->text();
    QString price = ui->Price_LE->text();
    QString description = ui->Description_TE->toPlainText();
    QString category = ui->Category_C->currentText();

    if (ui->Monday_CB->isChecked()) days += "Monday ";
    if (ui->Tuesday_CB->isChecked()) days += "Tuesday ";
    if (ui->Wednesday_CB->isChecked()) days += "Wednesday ";
    if (ui->Thursday_CB->isChecked()) days += "Thursday ";
    if (ui->Friday_CB->isChecked()) days += "Friday ";
    if (ui->Saturday_CB->isChecked()) days += "Saturday ";
    if (ui->Sunday_CB->isChecked()) days += "Sunday ";

    Item *item = new Item(this);
    Ingredient *ingredient = new Ingredient(this);

    int item_id;
    QSqlQuery q;
    q.exec("SELECT MAX(item_id) FROM Items");
    if (q.next()) {
        item_id = q.value(0).toInt() + 1;
        item->writeData(image_data, name, description, price, days, category, item_id);
        ingredient->writeData(all_ingredients, item_id);
        emit itemInserted();
        clearUI();
        QMessageBox::information(this, "Add New Item", "Added");
    }
    else qDebug() << "Failed to get max item_id" << q.lastError().text();
}


void Additem::on_AmountEnter() {
    QString ingredient = ui->Ingredients_LE->text();
    QString amount = ui->Amount_LE->text();

    if (!ingredient.isEmpty() && !amount.isEmpty()) {
        if (all_ingredients.isEmpty()) {
            all_ingredients = ingredient + " - " + amount;
        }
        else {
            all_ingredients += ", " + ingredient + " - " + amount;
        }
        ui->Showingredies_TE->setText(all_ingredients);
        ui->Ingredients_LE->clear();
        ui->Amount_LE->clear();
    }
}

void Additem::clearUI() {
    ui->Name_LE->clear();
    ui->Price_LE->clear();
    ui->Description_TE->clear();
    ui->Image_L->clear();
    ui->Showingredies_TE->clear();
    all_ingredients.clear();
    QCheckBox* checkboxes[] = {ui->Monday_CB, ui->Tuesday_CB, ui->Wednesday_CB, ui->Thursday_CB, ui->Friday_CB, ui->Saturday_CB, ui->Sunday_CB};
    for (int i = 0; i < 7; i++) {
        checkboxes[i]->setChecked(false);
    }
}

void Additem::on_deleteamount_PB_clicked() {
    if (!all_ingredients.isEmpty()) {
        QStringList ingredientList = all_ingredients.split(", ");
        ingredientList.removeLast();
        all_ingredients = ingredientList.join(", ");
        ui->Showingredies_TE->setText(all_ingredients);
    }
}

void Additem::closeEvent(QCloseEvent *event) {
    clearUI();
    image_data.clear();
    days.clear();
    all_ingredients.clear();
    event->accept();
}

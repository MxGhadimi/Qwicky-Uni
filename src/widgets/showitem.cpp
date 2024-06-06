#include "showitem.h"
#include "ui_showitem.h"

Showitem::Showitem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Showitem)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setStyleSheet("QMainWindow { background-color: white; }");
    setFixedSize(540, 310);
    connect(ui->Amount_LE, &QLineEdit::returnPressed, this, &Showitem::on_AmountEnter);
    ui->Ingredient_LE->setPlaceholderText("Ingredient");
    ui->Amount_LE->setPlaceholderText("Amount");
}

Showitem::~Showitem()
{
    delete ui;
}

void Showitem::setData(int input_item_id) {
    QSqlQuery q;
    q.prepare("SELECT * FROM Items WHERE item_id = :item_id");
    q.bindValue(":item_id", input_item_id);
    if (!q.exec()) qDebug() << "Error executing query (setData1): " << q.lastError().text();

    if (q.next()) {
        image = q.value("image").toByteArray();
        image_data = image;
        name = q.value("name").toString();
        setWindowTitle(name);
        description = q.value("description").toString();
        price = "$" + q.value("price").toString();
        days = q.value("days").toString();
        category = q.value("category").toString();
        int index = ui->Category_C->findText(category);
        if (index != -1) ui->Category_C->setCurrentIndex(index);
        else qDebug() << "Category not found in Category_C: " << category;
        ui->Name_TE->setReadOnly(true);
        ui->Description_TE->setReadOnly(true);
        ui->Price_TE->setReadOnly(true);
        ui->Category_C->setEnabled(false);

        ui->Name_TE->setText(name);
        ui->Price_TE->setText(price);
        ui->Description_TE->setText(description);
        QImage img;
        img.loadFromData(image);
        ui->Image_L->setPixmap(QPixmap::fromImage(img));
        ui->Image_L->setScaledContents(true);
        ui->Editimage_PB->hide();
        ui->Ingredient_LE->hide();
        ui->Amount_LE->hide();
        ui->deleteamount_PB->hide();

        QStringList daysList = days.split(" ");
        QCheckBox *checkBoxes[] = {ui->Monday_CB, ui->Tuesday_CB, ui->Wednesday_CB, ui->Thursday_CB, ui->Friday_CB, ui->Saturday_CB, ui->Sunday_CB};
        QString daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        for (int i = 0; i < 7; i++) {
            if (daysList.contains(daysOfWeek[i])) {
                checkBoxes[i]->setChecked(true);
            }
            checkBoxes[i]->setDisabled(true);
        }
    }
    else qDebug() << "No rows found in the table" << input_item_id;

    q.prepare("SELECT * FROM Ingredients WHERE item_id = :item_id");
    q.bindValue(":item_id", input_item_id);
    if (!q.exec()) qDebug() << "Error executing query(setData2): " << q.lastError().text();

    while (q.next()) {
        QString ingredient = q.value("ingredient_name").toString();
        QString amount = q.value("amount").toString();
        if (!all_ingredients.isEmpty()) all_ingredients += ", " + ingredient + " - " + amount;
        else all_ingredients = ingredient + " - " + amount;
    }

    ui->Ingredients_TE->setReadOnly(true);
    ui->Ingredients_TE->setText(all_ingredients);
    item_id = input_item_id;
    show();
}

void Showitem::on_Edit_PB_clicked() {
    static bool edit_mode_on = false;
    if (!edit_mode_on) {
        ui->Editimage_PB->show();
        ui->deleteamount_PB->show();
        ui->Amount_LE->show();
        ui->Ingredient_LE->show();

        ui->Edit_PB->setText("Done");
        ui->Name_TE->setReadOnly(false);
        ui->Description_TE->setReadOnly(false);
        ui->Price_TE->setReadOnly(false);
        ui->Category_C->setEnabled(true);
        ui->Ingredients_TE->setStyleSheet("QTextEdit { background-color: rgb(223, 229, 229); color: rgb(31, 48, 58); border-radius: 5px; border-width: 0.5px; border-style: solid; border-color: rgb(188, 193, 193); padding-left: 5px; padding-right: 35px; } QScrollBar:vertical { background: rgb(223, 229, 229); width: 4px; border-radius: 2px; padding-bottom: 5px; padding-top: 5px; } QScrollBar::handle:vertical { background: rgb(255, 137, 64); min-height: 3px; border-radius: 2px; } QScrollBar::add-line:vertical { background: rgb(223, 229, 229); } QScrollBar::sub-line:vertical { background: rgb(223, 229, 229); } QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: rgb(223, 229, 229); } QMenu { border: 1px solid white; border-radius: 5px; background-color: rgb(6, 106, 110); padding: 7px; color: white; } QMenu::item { padding: 4px; } QMenu::item:hover { border: none; outline: none; } QMenu::item:selected { background-color: rgb(255, 137, 64); border-radius: 5px; color: rgb(31, 48, 58); } QMenu::separator { height: 1px; background-color: white; }");

        QCheckBox *checkBoxes[] = {ui->Monday_CB, ui->Tuesday_CB, ui->Wednesday_CB, ui->Thursday_CB, ui->Friday_CB, ui->Saturday_CB, ui->Sunday_CB};
        for (int i = 0; i < 7; i++) {
            checkBoxes[i]->setDisabled(false);
        }
        edit_mode_on = true;
    }

    else {
        all_ingredients.clear();
        emit updatedItem();
        edit_mode_on = false;
        QString new_days;
        if (ui->Monday_CB->isChecked()) new_days += "Monday ";
        if (ui->Tuesday_CB->isChecked()) new_days += "Tuesday ";
        if (ui->Wednesday_CB->isChecked()) new_days += "Wednesday ";
        if (ui->Thursday_CB->isChecked()) new_days += "Thursday ";
        if (ui->Friday_CB->isChecked()) new_days += "Friday ";
        if (ui->Saturday_CB->isChecked()) new_days += "Saturday ";
        if (ui->Sunday_CB->isChecked()) new_days += "Sunday ";

        QString new_price = ui->Price_TE->toPlainText();
        if (new_price.startsWith("$")) new_price = new_price.mid(1);
        Item *item = new Item(this);
        Ingredient *ingredient = new Ingredient(this);
        if (new_days != days)                                       item->updateDays(new_days, item_id);
        if (ui->Name_TE->toPlainText() != name)                     item->updateName(ui->Name_TE->toPlainText(), item_id);
        if (new_price != price)                                     item->updatePrice(new_price, item_id);
        if (ui->Category_C->currentText() != category)              item->updateCategory(ui->Category_C->currentText(), item_id);
        if (ui->Description_TE->toPlainText() != description)       item->updateDescription(ui->Description_TE->toPlainText(), item_id);
        if (ui->Ingredients_TE->toPlainText() != all_ingredients)   ingredient->updateIngredient(ui->Ingredients_TE->toPlainText(), item_id);

        ui->Edit_PB->setText("Edit");
        ui->Editimage_PB->hide();
        ui->Amount_LE->hide();
        ui->deleteamount_PB->hide();
        ui->Ingredient_LE->hide();
        ui->Ingredients_TE->setStyleSheet("QTextEdit { color: rgb(31, 48, 58); background: rgb(255, 255, 255); border: none; } QScrollBar:vertical { background: rgb(255, 255, 255); width: 3px; border-radius: 2px; } QScrollBar::handle:vertical { background: rgb(255, 137, 64); min-height: 3px; border-radius: 2px; } QScrollBar::add-line:vertical { background: rgb(255, 255, 255); } QScrollBar::sub-line:vertical { background: rgb(255, 255, 255); } QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: rgb(255, 255, 255); } QMenu { border: 1px solid white; border-radius: 5px; background-color: rgb(6, 106, 110); padding: 7px; color: white; } QMenu::item { padding: 4px; } QMenu::item:hover { border: none; outline: none; } QMenu::item:selected { background-color: rgb(255, 137, 64); border-radius: 5px; color: rgb(31, 48, 58); } QMenu::separator { height: 1px; background-color: white; }");
        setData(item_id);
        QMessageBox::information(this, "Add New Item", "Added");
    }
}

void Showitem::on_AmountEnter() {
    QString ingredient = ui->Ingredient_LE->text();
    QString amount = ui->Amount_LE->text();

    if (!ingredient.isEmpty() && !amount.isEmpty()) {
        if (all_ingredients.isEmpty()) {
            all_ingredients = ingredient + " - " + amount;
        }
        else {
            all_ingredients += ", " + ingredient + " - " + amount;
        }
        ui->Ingredients_TE->setText(all_ingredients);
        ui->Ingredient_LE->clear();
        ui->Amount_LE->clear();
    }
}

void Showitem::on_deleteamount_PB_clicked() {
    if (!all_ingredients.isEmpty()) {
        QStringList ingredientList = all_ingredients.split(", ");
        ingredientList.removeLast();
        all_ingredients = ingredientList.join(", ");
        ui->Ingredients_TE->setText(all_ingredients);
    }
}

void Showitem::on_Editimage_PB_clicked() {
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
        }
    }
}

void Showitem::on_Delete_PB_clicked() {
    QSqlQuery q;
    q.prepare("DELETE FROM Items WHERE item_id = :item_id");
    q.bindValue(":item_id", item_id);
    if (!q.exec()) qDebug() << "Failed to delete item: " << q.lastError().text();

    q.prepare("DELETE FROM Ingredients WHERE item_id = :item_id");
    q.bindValue(":item_id", item_id);
    if (q.exec()) {
        emit updatedItem();
        QMessageBox::information(this, "Delete item", "Deleted");
    }
    else qDebug() << "Failed to delete ingredients: " << q.lastError().text();
    close();
}

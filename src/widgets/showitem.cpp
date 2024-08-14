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
    ui->Name_TE->setReadOnly(true);
    ui->Description_TE->setReadOnly(true);
    ui->Price_TE->setReadOnly(true);
    ui->Category_C->setEnabled(false);
    ui->Ingredients_TE->setReadOnly(true);
}

Showitem::~Showitem()
{
    delete ui;
}

void Showitem::showData(int input_item_id) {
    item_id = input_item_id;
    if (item.readData(item_id)) {
        int index = ui->Category_C->findText(item.getCategory());
        if (index != -1) ui->Category_C->setCurrentIndex(index);
        else qDebug() << "Category not found in Category_C: " << item.getCategory();

        ui->Name_TE->setText(item.getName());
        ui->Price_TE->setText("$" + item.getPrice());
        ui->Description_TE->setText(item.getDescription());
        QImage img;
        img.loadFromData(item.getImage());
        ui->Image_L->setPixmap(QPixmap::fromImage(img));
        ui->Image_L->setScaledContents(true);
        ui->Editimage_PB->hide();
        ui->Ingredient_LE->hide();
        ui->Amount_LE->hide();
        ui->deleteamount_PB->hide();

        QString days = item.getDays();
        QStringList daysList = days.split(" ");
        QCheckBox *checkBoxes[] = {ui->Monday_CB, ui->Tuesday_CB, ui->Wednesday_CB, ui->Thursday_CB, ui->Friday_CB, ui->Saturday_CB, ui->Sunday_CB};
        QString daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        for (int i = 0; i < 7; i++) {
            if (daysList.contains(daysOfWeek[i])) {
                checkBoxes[i]->setChecked(true);
            }
            checkBoxes[i]->setDisabled(true);
        }
        if (ingredient.readData(item_id)) {
            ui->Ingredients_TE->setText(ingredient.getAllIngredients());
            all_ingredients = ingredient.getAllIngredients();
        }
    }
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

        bool updated = true;
        if (new_days != item.getDays()) {
            if (!item.updateDays(new_days, item_id)) updated = false;
        }
        if (ui->Name_TE->toPlainText() != item.getName()) {
            if (!item.updateName(ui->Name_TE->toPlainText(), item_id)) updated = false;
        }
        if (new_price != item.getPrice()) {
            if (!item.updatePrice(new_price, item_id)) updated = false;
        }
        if (ui->Category_C->currentText() != item.getCategory()) {
            if (!item.updateCategory(ui->Category_C->currentText(), item_id)) updated = false;
        }
        if (ui->Description_TE->toPlainText() != item.getDescription()) {
            if (!item.updateDescription(ui->Description_TE->toPlainText(), item_id)) updated = false;
        }
        if (ui->Ingredients_TE->toPlainText() != ingredient.getAllIngredients()) {
            if (!ingredient.updateIngredient(ui->Ingredients_TE->toPlainText(), item_id)) updated = false;
        }

        if (updated) {
            ui->Edit_PB->setText("Edit");
            ui->Editimage_PB->hide();
            ui->Amount_LE->hide();
            ui->deleteamount_PB->hide();
            ui->Ingredient_LE->hide();
            ui->Ingredients_TE->setStyleSheet("QTextEdit { color: rgb(31, 48, 58); background: rgb(255, 255, 255); border: none; } QScrollBar:vertical { background: rgb(255, 255, 255); width: 3px; border-radius: 2px; } QScrollBar::handle:vertical { background: rgb(255, 137, 64); min-height: 3px; border-radius: 2px; } QScrollBar::add-line:vertical { background: rgb(255, 255, 255); } QScrollBar::sub-line:vertical { background: rgb(255, 255, 255); } QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: rgb(255, 255, 255); } QMenu { border: 1px solid white; border-radius: 5px; background-color: rgb(6, 106, 110); padding: 7px; color: white; } QMenu::item { padding: 4px; } QMenu::item:hover { border: none; outline: none; } QMenu::item:selected { background-color: rgb(255, 137, 64); border-radius: 5px; color: rgb(31, 48, 58); } QMenu::separator { height: 1px; background-color: white; }");
            showData(item_id);
            QMessageBox::information(this, "Update Item", "Updated!");
        }
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
        ui->Ingredients_TE->clear();
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
    if (item.deleteItem(item_id)) {
        QMessageBox::information(this, "Delete item", "Deleted!");
        emit updatedItem();
        close();
    }
}

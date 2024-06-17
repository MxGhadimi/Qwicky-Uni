#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Qwicky");
    QIcon icon(QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/images/icons/iconqwicky.png");
    QApplication::setWindowIcon(icon);
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "Admin");
    QString dbpath = QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/admin.db";
    database.setDatabaseName(dbpath);
    if (!database.open()) qDebug() << "Failed to open database" << database.lastError().text();

    QSqlDatabase database2 = QSqlDatabase::addDatabase("QSQLITE", "Items");
    QString dbpath2 = QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/items.db";
    database.setDatabaseName(dbpath2);
    if (!database.open()) qDebug() << "Failed to open database" << database.lastError().text();

    ui->Password_LE->setEchoMode(QLineEdit::Password);

    ui -> Strength_L -> setText(" ");
    ui -> Strength_PB -> setValue(0);
    connect(ui -> Password2_LE, &QLineEdit::textChanged, this, &MainWindow::checkPasswordStrength);

    QTimer::singleShot(0, this, &MainWindow::checkLoginFile);
}

MainWindow::~MainWindow() {
    delete ui;
}

//================ LogIn WIDGET ================//

void MainWindow::checkLoginFile() {
    file.setFileName(QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/usersdata/login.txt");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        int key = in.readLine().toInt();
        QString username = QString::fromStdString(ceasorDecrypt(in.readLine().toStdString(), key));
        QString password = QString::fromStdString(ceasorDecrypt(in.readLine().toStdString(), key));
        QString user_type = in.readLine();

        if (user_type == "admin") {
            hide();
            emit showAdminDashboardPage();
        }
        else if (user_type == "customer") {
            hide();
            emit showCustomerDashboardPage();
        }
    }
}

void MainWindow::on_Login_PB_clicked() {
    QString username = ui->Username_LE->text();
    QString password = ui->Password_LE->text();

    QSqlQuery q(QSqlDatabase::database("Login/Signup"));
    QString query = "SELECT 'admin' as user_type FROM Admins WHERE username = :username AND password = :password UNION SELECT 'customer' as user_type FROM Customers WHERE username = :username AND password = :password";
    if (!q.prepare(query)) qDebug() << "Error preparing query: " << q.lastError().text();
    q.bindValue(":username", username);
    q.bindValue(":password", password);
    if (!q.exec()) qDebug() << "Error Login in using username and password: " << q.lastError().text();

    if (q.next()) {
        QString user_type = q.value(0).toString();
        if (ui->Remember_CB->isChecked()) {
            int key = getRandomKey();
            if (file.open(QFile::WriteOnly | QFile::Text)) {
                QTextStream out (&file);
                out << key << "\n"
                    << QString::fromStdString(ceasorEncrypt(username.toStdString(), key)) << "\n"
                    << QString::fromStdString(ceasorEncrypt(password.toStdString(), key)) << "\n"
                    << user_type << "\n";
            }
            else qDebug() << "Failed to open file for writing.";
        }

        if (user_type == "admin") {
            hide();
            emit showAdminDashboardPage();
        }
        else if (user_type == "customer") {
            hide();
            emit showCustomerDashboardPage();
        }
    }
    else QMessageBox::warning(this, "Login", "Username/Password incorrect.\nTry Again.");
}

void MainWindow::on_SignUp_PB_clicked() {

    /* old method
    hide();
    signup = new Signup(this);
    signup -> show();
    */
    /* Using connect
    emit showSignUpPage();
    this->hide();
    */
    // using StackedWidget
    ui -> stackedWidget -> setCurrentWidget(ui->Signup_QW);
}

void MainWindow::on_ShowPass_PB_clicked() {
    if (ui->Password_LE->echoMode() == QLineEdit::Password) {
        ui->Password_LE->setEchoMode(QLineEdit::Normal);
                ui->ShowPass_PB->setIcon(QIcon(QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/images/icons/closedeye.png"));
    }
    else {
        ui->Password_LE->setEchoMode(QLineEdit::Password);
                ui->ShowPass_PB->setIcon(QIcon(QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/images/icons/openeye.png"));
    }
}

//================ SignUp WIDGET ================//

void MainWindow::on_SignUp2_PB_clicked() {
    QString name = ui->Name_LE->text();
    QString lastname = ui->Lastname_LE->text();
    QString phonenumber = ui->Phonenumber_LE->text();
    QString address = ui->Address_LE->text();
    QString username = ui->Username2_LE->text();
    QString password = ui->Password2_LE->text();

    if (!(username.isEmpty() || password.isEmpty())) {
        if (!(name.isEmpty() || lastname.isEmpty() || phonenumber.isEmpty() || address.isEmpty())) {
            if (insertData(name, lastname, phonenumber, address, username, password)) {
                QMessageBox::information(this, "Signup", "Success.");
                return;
            }
            else {
                QMessageBox::warning(this, "Signup", "Failed.");
                return;
            }
        }
        if (ui -> Strength_PB -> value() <= 2) {
            QMessageBox::warning(this, "Signup", "Password too weak.");
            return;
        }
        if (username.contains(" ") || password.contains(" ")) {
            QMessageBox::warning(this, "Signup", "Username/password cannot contain spaces.");
            return;
        }
        else {
            QString message = "";
            if (name.isEmpty()) message += "Name, ";
            if (lastname.isEmpty()) message += "Lastname, ";
            if (phonenumber.isEmpty()) message += "Phonenumber, ";
            if (address.isEmpty()) message += "Address";

            QMessageBox empty;
            empty.setText("Are you sure you want to leave these fields empty?");
            empty.setInformativeText(message);
            empty.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            empty.setDefaultButton(QMessageBox::No);

            if (empty.exec() == QMessageBox::No) {
                empty.close();

            }
            else {
                empty.close();
                if (insertData(name, lastname, phonenumber, address, username, password)) {
                    QMessageBox::information(this, "Signup", "Success.");
                }
                else {
                    QMessageBox::warning(this, "Signup", "Failed.");
                }
            }
        }
    }
    else QMessageBox::warning(this, "Signup", "Username and/or Password cannot be empty.");
}

bool MainWindow::insertData(const QString& name, const QString& lastName, const QString& phoneNumber, const QString& address, const QString& username, const QString& password) {
    QSqlQuery q(QSqlDatabase::database("Login/Signup"));
    q.prepare("INSERT INTO Customers (first_name, last_name, phone_number, address, username, password) VALUES (:name, :lastname, :phonenumber, :address, :username, :password)");
    q.bindValue(":name", name);
    q.bindValue(":lastname", lastName);
    q.bindValue(":phonenumber", phoneNumber.trimmed());
    q.bindValue(":address", address);
    q.bindValue(":username", username.trimmed());
    q.bindValue(":password", password.trimmed());

    if (!q.exec()) qDebug() << "Error Sign in up: " << q.lastError().text();
    return q.exec();
}

void MainWindow::on_Login2_PB_clicked() {
    QString username = ui->Username2_LE->text();
    QString password = ui->Password2_LE->text();

    QSqlQuery q(QSqlDatabase::database("Login/Signup"));
    q.prepare("SELECT 'admin' as user_type FROM Admins WHERE username = :username AND password = :password UNION SELECT 'customer' as user_type FROM Customers WHERE username = :username AND password = :password");
    q.bindValue(":username", username);
    q.bindValue(":password", password);
    if (!q.exec()) qDebug() << "Error Login in using username and password: " << q.lastError().text();

    if (q.next()) {
        QString user_type = q.value(0).toString();
        if (user_type == "admin") {
            emit showAdminDashboardPage();
            this->hide();
        }
        else if (user_type == "customer") {
            emit showCustomerDashboardPage();
            this->hide();
        }
    }
    else QMessageBox::warning(this, "Login", "Username/Password incorrect.\nTry Again.");
}

void MainWindow::on_ShowPass2_PB_clicked() {
    if (ui->Password2_LE->echoMode() == QLineEdit::Password) {
        ui->Password2_LE->setEchoMode(QLineEdit::Normal);
                ui->ShowPass2_PB->setIcon(QIcon(QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/images/icons/closedeye.png"));
    }
    else {
        ui->Password2_LE->setEchoMode(QLineEdit::Password);
        ui->ShowPass2_PB->setIcon(QIcon(QCoreApplication::applicationDirPath() + QDir::separator() + "../../data/images/icons/openeye.png"));
    }
}

void MainWindow::checkPasswordStrength (const QString &password) {
    if (password.isEmpty()) {
        ui -> Strength_L -> clear();
        ui -> Strength_PB -> setValue(0);
    }
    else {
        int strength = 0;
        if (password.length() >= 8) strength++;

        static QRegularExpression lowercaseRegex("[a-z]");
        if (lowercaseRegex.match(password).hasMatch()) strength++;
        static QRegularExpression uppercaseRegex("[A-Z]");
        if (uppercaseRegex.match(password).hasMatch()) strength++;
        static QRegularExpression digitRegex("[0-9]");
        if (digitRegex.match(password).hasMatch()) strength++;
        static QRegularExpression specialRegex("[^a-zA-Z0-9]");
        if (specialRegex.match(password).hasMatch()) strength++;

        ui -> Strength_PB -> setValue(strength);

        if (1 == strength || 2 == strength) {
            ui -> Strength_L -> setText("Weak");
            ui -> Strength_L -> setStyleSheet("color: rgb(255, 0, 0); font: 600 7pt \"Segoe UI\"; background: none;");
            ui -> Strength_PB -> setStyleSheet("QProgressBar::chunk { background-color: rgb(255, 0, 0); width: 14.5px; height: 4px; margin: 3px; }");
        }
        else if (2 == strength) {
            ui -> Strength_L -> setText("Weak");
            ui -> Strength_L -> setStyleSheet("color: rgb(255, 0, 0); font: 600 7pt \"Segoe UI\"; background: none;");
            ui -> Strength_PB -> setStyleSheet("QProgressBar::chunk { background-color: rgb(255, 0, 0); width: 14.5px; height: 4px; margin: 3px; }");
        }
        else if (3 == strength) {
            ui -> Strength_L -> setText("Medium");
            ui -> Strength_L -> setStyleSheet("color: rgb(255, 255, 0); font: 600 7pt \"Segoe UI\"; background: none;");
            ui -> Strength_PB -> setStyleSheet("QProgressBar::chunk { background-color: rgb(255, 255, 0); width: 14.5px; height: 4px; margin: 3px; }");
        }
        else if (4 == strength) {
            ui -> Strength_L -> setText("Medium");
            ui -> Strength_L -> setStyleSheet("color: rgb(255, 255, 0); font: 600 7pt \"Segoe UI\"; background: none;");
            ui -> Strength_PB -> setStyleSheet("QProgressBar::chunk { background-color: rgb(255, 255, 0); width: 14.5px; height: 4px; margin: 3px; }");
        }
        else {
            ui -> Strength_L -> setText("Strong");
            ui -> Strength_L -> setStyleSheet("color: rgb(0, 255, 0); font: 600 7pt \"Segoe UI\"; background: none;");
            ui -> Strength_PB -> setStyleSheet("QProgressBar::chunk { background-color: rgb(0, 255, 0); width: 14.5px; height: 4px; margin: 3px; }");
        }
    }
}

void MainWindow::on_Back_PB_clicked() {
    ui -> stackedWidget -> setCurrentWidget(ui->Login_QW);
}


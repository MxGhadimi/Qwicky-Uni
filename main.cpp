#include "mainwindow.h"
#include "customerdashboard.h"
#include "admindashboard.h"
#include "additem.h"
#include "showitem.h"
#include "addorder.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    int font_id = QFontDatabase::addApplicationFont(":fonts/Roboto-Regular.ttf");
    if (font_id != -1) {
        QFont font("Roboto");
        QApplication::setFont(font);
    }

    MainWindow mainWindow;
    //Signup signup;
    customerdashboard customerdashboard;
    AdminDashboard admindashboard;
    Additem additem;
    Showitem showitem;
    Addorder addorder;


    //QObject::connect(&mainWindow, &MainWindow::showSignUpPage, &signup, &Signup::show);
    //QObject::connect(&signup, &Signup::showMainWindowPage, &mainWindow, &MainWindow::show);
    QObject::connect(&mainWindow, &MainWindow::showCustomerDashboardPage, &customerdashboard, &customerdashboard::show);
    QObject::connect(&mainWindow, &MainWindow::showAdminDashboardPage, &admindashboard, &AdminDashboard::show);
    QObject::connect(&admindashboard, &AdminDashboard::showAdditemPage, &additem, &Additem::show);
    QObject::connect(&additem, &Additem::itemInserted, &admindashboard, &AdminDashboard::showMenu);
    QObject::connect(&showitem, &Showitem::updatedItem, &admindashboard, &AdminDashboard::showMenu);
    QObject::connect(&admindashboard, &AdminDashboard::showAddorderPage, &addorder, &Addorder::show);

    mainWindow.show();
    return a.exec();
}

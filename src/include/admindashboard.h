#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWidget>
#include <QSqlDatabase>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QTextCursor>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include <QSqlError>
#include <QScrollArea>
#include "item.h"


namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QMainWindow {
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

public slots:
    void showMenu();

signals:
    void showAdditemPage();
    void showAddorderPage();

private slots:
    void on_Dashboard_PB_clicked();
    void on_Menu_PB_clicked();
    void on_Reservations_PB_clicked();
    void on_Orders_PB_clicked();
    void on_Tabels_PB_clicked();
    void on_Settings_PB_clicked();

        // Menu
    void on_Additem_PB_clicked();

    void on_Search_LE_textChanged(const QString &arg1);

    void on_Neworder_PB_clicked();

private:
    Ui::AdminDashboard *ui;
};

#endif // ADMINDASHBOARD_H

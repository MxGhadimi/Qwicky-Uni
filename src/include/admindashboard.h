#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QMainWindow>
#include "commonincludes.h"
#include "item.h"
#include "order.h"

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
    void showOrders();

signals:
    void showAdditemPage();
    void showAddorderPage();

private slots:
        // utils
    void updateDate();

        // Menu
    void on_Dashboard_PB_clicked();
    void on_Menu_PB_clicked();
    void on_Reservations_PB_clicked();
    void on_Orders_PB_clicked();
    void on_Tabels_PB_clicked();
    void on_Settings_PB_clicked();

        // Items
    void on_Neworder_PB_clicked();
    void on_Additem_PB_clicked();
    // void showMenu();
    void on_Menusearch_LE_textChanged(const QString &arg1);

private:
    Ui::AdminDashboard *ui;
    QWidget *scrollWidget_3;
    QGridLayout *gridLayout_3;
};

#endif // ADMINDASHBOARD_H

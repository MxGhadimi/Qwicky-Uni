#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QIcon>
#include <QTimer>
#include <QSqlDatabase>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include <QSqlError>
#include <QRegularExpression>
#include "admindashboard.h"
#include "customerdashboard.h"
#include "Ceasor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void checkLoginFile();
    void on_Login_PB_clicked();
    void on_SignUp_PB_clicked();
    void on_Login2_PB_clicked();
    void on_SignUp2_PB_clicked();

    void on_ShowPass_PB_clicked();
    void on_ShowPass2_PB_clicked();
    void checkPasswordStrength(const QString &password);

    void on_Back_PB_clicked();
    bool insertData(const QString& name, const QString& lastName, const QString& phoneNumber, const QString& address, const QString& username, const QString& password);
    //void closeDatabaseConnection();

signals:
    //void showSignUpPage();
    void showCustomerDashboardPage();
    void showAdminDashboardPage();


private:
    Ui::MainWindow *ui;
    customerdashboard *cdashboard;
    AdminDashboard *adashboard;
    QFile file;

};
#endif // MAINWINDOW_H

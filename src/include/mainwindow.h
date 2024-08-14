#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "commonincludes.h"
#include "admindashboard.h"
#include "customerdashboard.h"
#include "Ceasor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The main window class for the Qwicky application.
 * @details This class manages the main window's UI and functionality, including login, signup, and navigation to other dashboards.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the MainWindow class.
     * @param parent The parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the MainWindow class.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Checks if a login file exists and logs in the user if it does.
     */
    void checkLoginFile();

    /**
     * @brief Slot triggered when the Login button is clicked.
     */
    void on_Login_PB_clicked();

    /**
     * @brief Sets the current page to Signup Page when the Signup button is clicked.
     */
    void on_SignUp_PB_clicked();

    /**
     * @brief Slot triggered when the Login button on the signup page is clicked.
     */
    void on_Login2_PB_clicked();

    /**
     * @brief Slot triggered when the Signup button on the signup page is clicked.
     */
    void on_SignUp2_PB_clicked();

    /**
     * @brief Shows/Hides the Password when the Eye button is clicked.
     */
    void on_ShowPass_PB_clicked();

    /**
     * @brief Shows/Hides the Password when the Eye button on the signup page is clicked.
     */
    void on_ShowPass2_PB_clicked();

    /**
     * @brief Checks the strength of the password entered in the signup page.
     * @param password The password to check.
     */
    void checkPasswordStrength(const QString &password);

    /**
     * @brief Sets the current page to Login page when the Back button is clicked.
     */
    void on_Back_PB_clicked();

    /**
     * @brief Inserts new user data into the database.
     * @param name The first name of the user.
     * @param lastName The last name of the user.
     * @param phoneNumber The phone number of the user.
     * @param address The address of the user.
     * @param username The username chosen by the user.
     * @param password The password chosen by the user.
     * @return True if data is successfully inserted; false otherwise.
     */
    bool insertData(const QString& name, const QString& lastName, const QString& phoneNumber, const QString& address, const QString& username, const QString& password);

signals:
    /**
     * @brief Signal to show the customerdashboard class ui.
     */
    void showCustomerDashboardPage();

    /**
     * @brief Signal to show the AdminDashboard class ui.
     */
    void showAdminDashboardPage();

private:
    Ui::MainWindow *ui; ///< Pointer to the UI component
    QFile file; ///< File object for handling login data
};

#endif // MAINWINDOW_H

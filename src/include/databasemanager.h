#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "commonincludes.h"

/**
 * @class DatabaseManager
 * @brief A singleton class responsible for managing database connections.
 * @details This class ensures that only one instance of the DatabaseManager exists throughout the program. It provides methods to get and manage different database connections.
 */
class DatabaseManager
{
public:
    /**
     * @brief Returns the singleton instance of the DatabaseManager class.
     * @return The singleton instance of the DatabaseManager class.
     */
    static DatabaseManager& getInstance() { //Singleton pattern ensures that only one instance of the DatabaseManager class exists throughout the program.
        static DatabaseManager instance;
        return instance;
    }

    /**
     * @brief Gets the admin database connection.
     * @return The admin database connection.
     */
    QSqlDatabase getAdminDatabase();

    /**
     * @brief Gets the items database connection.
     * @return The items database connection.
     */
    QSqlDatabase getItemsDatabase();

private:
    /**
     * @brief Private constructor to prevent instantiation from outside.
     */
    DatabaseManager() {}

    /**
     * @brief Destructor to close and remove all database connections.
     */
    ~DatabaseManager() {
        for (auto& database : databases) {
            if (database.isOpen()) database.close();
            QSqlDatabase::removeDatabase(database.connectionName());
        }
    }

    /**
     * @brief Gets a database connection by its connection name.
     * @param connectionName The name of the database connection to get.
     * @return The database connection associated with the given connection name.
     */
    QSqlDatabase getDatabase(const QString& connectionName);

    QMap<QString, QSqlDatabase> databases; ///< A map to store database connections by their names.

};

#endif // DATABASEMANAGER_H

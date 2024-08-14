#include "databasemanager.h"

QSqlDatabase DatabaseManager::getDatabase(const QString& connectionName) {
    if (databases.contains(connectionName)) return databases[connectionName];

    QSqlDatabase database = QSqlDatabase::contains(connectionName) ? QSqlDatabase::database(connectionName) : QSqlDatabase::addDatabase("QSQLITE", connectionName);
    QString dbpath;
    if (connectionName == "Admin") dbpath = QCoreApplication::applicationDirPath() + QDir::separator() + "data/admin.db";
    else if (connectionName == "Items") dbpath = QCoreApplication::applicationDirPath() + QDir::separator() + "data/items.db";

    database.setDatabaseName(dbpath);
    if (!database.open()) qDebug() << "Failed to open database" << database.lastError().text();

    databases[connectionName] = database;
    return database;
}

QSqlDatabase DatabaseManager::getItemsDatabase() {
    return getDatabase("Items");
}

QSqlDatabase DatabaseManager::getAdminDatabase() {
    return getDatabase("Admin");
}

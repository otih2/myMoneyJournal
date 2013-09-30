#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QFileDialog>
#include <iostream>
#include <QFile>

QVariant addAccount(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
    return q.lastInsertId();
}

void addBooking(QSqlQuery &q, const QString &description, const int &price)
{
    q.addBindValue(description);
    q.addBindValue(price);
    q.exec();
//    return q.lastInsertId();
}

QSqlError initDb()
{
    /*
    *   Initiates a database with the table ACCOUNTS and BOOKING.
    */
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //db connection name
    db.setHostName("127.0.0.1");
    db.setDatabaseName("db_norman");

    bool db_exist = QFile::exists("./db_norman");
    std::cout << "db_exist: " << db_exist << std::endl;

    //Open db
    if (!db.open()) return db.lastError();

    //Read-in the existing tables.
    if (db_exist){
        //     ??? In combination with tableView it parses from db2gui
        QStringList tables = db.tables();
        if (tables.contains("booking", Qt::CaseInsensitive) && tables.contains("accounts", Qt::CaseInsensitive))
            std::cout << "TABLES CONTAINS!!!!" << std::endl;
            return QSqlError();
    }


    //Create tables ACCOUNTS & BOOKING
    QSqlQuery q;
    if (!q.exec(QLatin1String("create table accounts(id integer primary key, name varchar)"))) //total for lbl?
        return q.lastError();
    if (!q.exec(QLatin1String("create table booking(id integer primary key, description varchar, price integer)")))
        return q.lastError();

//    Insert datas into table ACCOUNTS
//    if (!q.prepare(QLatin1String("insert into accounts(name) values(?)")))
//        return q.lastError();
//    addAccount(q, QLatin1String("norman"));
//    addAccount(q, QLatin1String("test"));

    //Insert datas into table BOOKING
//    if (!q.prepare(QLatin1String("insert into booking(description, price) values(?, ?)")))
//        return q.lastError();
//    addBooking(q, QLatin1String("Gehalt"), 750);
//    addBooking(q, QLatin1String("Food"), -10);

    return QSqlError();
}



#endif // INITDB_H

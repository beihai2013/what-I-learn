#ifndef SQLUTLS_H
#define SQLUTLS_H

#endif // SQLUTLS_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <string.h>

static bool initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("test");
    if (!db.open()) {
        return false;
    }
    
    // 创建数据表
    QSqlQuery q;
    // q.exec(QLatin1String("create table data(id integer primary key, name varchar, year integer, keyword1 varchar, keyword2 varchar, keyword3 varchar, keyword4 varchar, image longblob)"));
    
    
    return true;
}



#include "db_handler.h"
#include "db_struct.h"
#include <QtSql>

Db_handler::Db_handler(QString driver, QString host, QString dbName, QString user, QString passw)

{
    db = QSqlDatabase::addDatabase(driver);
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(passw);
    okOpen_h =db.open();
}

bool Db_handler::isOk() {
    return okOpen_h;
}

bool Db_handler::set_data(db_struct *table) {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a = QString("select %1 from %2;").arg(QString(table->t_fields))
                    .arg(QString(table->t_name));
        my.exec(a);
        while (my.next()) {
            for (int i = 0; i < table->t_count; ++i) {
                table->t_data->append(my.value(i).toString());
            }
        }
        return true;
    }
    return false;
}

bool Db_handler::resetData(db_struct *table) {
    if (okOpen_h) {
        delete table->t_data;
        set_data(table);
        return true;
    }
    return false;
}

QStringList Db_handler::get_item_info(QString a) {
    QSqlQuery my(db);
    QStringList answ;
    QString b = QString("select * from items where id='%1';").arg(a);
    my.exec(b);
    while (my.next()) {
        for (int i = 0; i < 3; ++i) {
            answ.append(my.value(i).toString());
        }
    }
    return answ;
}

QStringList Db_handler::get_job_info(QString a) {
    QSqlQuery my(db);
    QStringList answ;
    QString b = QString("select * from jobs where id='%1';").arg(a);
    my.exec(b);
    while (my.next()) {
        for (int i = 0; i < 3; ++i) {
            answ.append(my.value(i).toString());
        }
    }
    return answ;
}

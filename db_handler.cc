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
        if (my.next()) {
            table->t_data->clear();
            do {
                for (int i = 0; i < table->t_count; ++i) {
                    table->t_data->append(my.value(i).toString());
                }
            } while (my.next());
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

bool Db_handler::set_item_info(QStringList data) {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a = QString("select * from items where id='%1';").arg(data.at(0));
        my.exec(a);
        if (my.next()) {
            return false;
        } else {
            a = QString("insert into items values ('%1', '%2', '%3');").
                arg(data.at(0)).
                arg(data.at(1)).
                arg(data.at(2));
            my.exec(a);
            return true;
        }
    }
}

bool Db_handler::set_job_info(QStringList data) {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a = QString("select * from jobs where id='%1';").arg(data.at(0));
        my.exec(a);
        if (my.next()) {
            return false;
        } else {
            a = QString("insert into jobs values ('%1', '%2', '%3');").
                arg(data.at(0)).
                arg(data.at(1)).
                arg(data.at(2));
            my.exec(a);
            return true;
        }
    }
}

bool Db_handler::deleteItem(const QString &in) const {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a = QString("select * from items where id='%1';").arg(in);
        my.exec(a);
        if (my.next()) {
            a = QString("DELETE FROM items WHERE id='%1';").arg(in);
            my.exec(a);
            return true;
        } else {
            return false;
        }
    }
}

bool Db_handler::deleteJob(const QString &in) const {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a = QString("select * from items where id='%1';").arg(in);
        my.exec(a);
        if (my.next()) {
            a = QString("DELETE FROM jobs WHERE id='%1';").arg(in);
            my.exec(a);
            return true;
        } else {
            return false;
        }
    }
}

bool Db_handler::fillJobsTable(db_struct *data, QTableWidget *table) {
    table->clear();
    int size = data->t_data->size() / data->t_count;
    QTableWidgetItem *cell = nullptr;
    QStringList *list = data->t_data;
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"ID", "Name", "Type"});
    table->setRowCount(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 3; ++j) {
            cell = new QTableWidgetItem;
            cell->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            QString a = list->at((data->t_count)*i+j);
            cell->setText(a);
            table->setItem(i, j, cell);
        }
    }
    return true;
}

bool Db_handler::fillItemsTable(db_struct *data, QTableWidget *table) {
    table->clear();
    int size = data->t_data->size() / data->t_count;
    QTableWidgetItem *cell = nullptr;
    QStringList *list = data->t_data;
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"ID", "Name", "Description"});
    table->setRowCount(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 3; ++j) {
            cell = new QTableWidgetItem;
            cell->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            QString a = list->at((data->t_count)*i+j);
            cell->setText(a);
            table->setItem(i, j, cell);
        }
    }
    table->sortItems(0);
    return true;
}

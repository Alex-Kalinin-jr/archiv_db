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
        QString a = QString("DELETE FROM items WHERE id='%1';").arg(in);
        my.exec(a);
        a = QString("DELETE FROM item_job WHERE items='%1';").arg(in);
        my.exec(a);
    }
}

bool Db_handler::deleteJob(const QString &in) const {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a = QString("DELETE FROM jobs WHERE id='%1';").arg(in);
        my.exec(a);
        a = QString("DELETE FROM files WHERE job='%1';").arg(in);
        my.exec(a);
        a = QString("DELETE FROM item_job WHERE jobs='%1';").arg(in);
        return true;
    } else {
        return false;
    }
}

bool Db_handler::bindJobToItem(QString &item, QString &job) {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a = QString("select * from item_job where items='%1' and jobs='%2';")
                    .arg(item)
                    .arg(job);
        my.exec(a);
        if (my.next()) {
            return false;
        } else {
            a = QString("insert into item_job values ('%1', '%2');")
                    .arg(item)
                    .arg(job);
            my.exec(a);
            return true;
        }
    }
}

// unbinds certain job from certain item. DOES NOT REMOVE JOB NOR ITEM themselve
bool Db_handler::unbind_job_from_item(const QString &item, const QString &job) {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a = QString("delete from item_job where items='%1' and jobs='%2';")
                    .arg(item)
                    .arg(job);
        my.exec(a);
        return true;
    }
}

// binds list of files to certain job
bool Db_handler::set_files_info(QStringList *data, const QString &job) {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a;
        for (int i = 0; i < data->size(); ++i) {
            a = QString("select * from jobs where road='%1' and job='%2';")
                .arg(data->at(i))
                .arg(job);
            my.exec(a);
            if (!my.next()) {
                a = QString("insert into files values ('%1', '%2', '');")
                    .arg(job)
                    .arg(data->at(i));
                my.exec((a));
            }
        }
        return true;
    }
}

// unbinds certain file from certain job. DOES NOT REMOVE JOB
bool Db_handler::remove_file_from_job(QString &job, QString &file) {
    if (okOpen_h) {
        QSqlQuery my(db);
        QString a = QString("DELETE FROM files WHERE job='%1' and file='%2';")
                    .arg(job)
                    .arg(file);
        my.exec(a);
        return true;
    }
    return false;
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

bool Db_handler::fillItJRelationTable(db_struct *data, QTableWidget *table, QString str) {
    table->clear();
    int size = data->t_data->size() / data->t_count;
    QTableWidgetItem *cell = nullptr;
    QStringList *list = data->t_data;
    table->setColumnCount(data->t_count);
    table->setHorizontalHeaderLabels({"Item", "Job"});
    table->setRowCount(0);
    for (int i = 0; i < size; ++i) {
        if (list->at((data->t_count)*i) == str) {
            table->setRowCount(table->rowCount()+1);
            for (int j = 0; j < data->t_count; ++j) {
                cell = new QTableWidgetItem;
                cell->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                QString *a = new QString(list->at((data->t_count)*i+j));
                cell->setText(*a);
                table->setItem(table->rowCount()-1, j, cell);
            }
        }
    }
    table->sortItems(0);
    return true;
}


bool Db_handler::fillFilesTable(db_struct *data, QTableWidget *table, QString str) {
    table->clear();
    int size = data->t_data->size() / data->t_count;
    QTableWidgetItem *cell = nullptr;
    QStringList *list = data->t_data;
    table->setColumnCount(data->t_count);
    table->setHorizontalHeaderLabels({"Job", "File"});
    table->setRowCount(0);
    for (int i = 0; i < size; ++i) {
        if (list->at((data->t_count)*i) == str) {
            table->setRowCount(table->rowCount()+1);
            for (int j = 0; j < data->t_count; ++j) {
                cell = new QTableWidgetItem;
                cell->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                QString *a = new QString(list->at((data->t_count)*i+j));
                cell->setText(*a);
                table->setItem(table->rowCount()-1, j, cell);
            }
        }
    }
    table->sortItems(0);
    return true;
}

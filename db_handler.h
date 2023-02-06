#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <QSqlDatabase>
#include "db_struct.h"

class Db_handler : public QSqlDatabase
{
public:
    Db_handler(QString driver,
                           QString host,
                           QString dbName,
                           QString user,
                           QString passw);
    ~Db_handler();
    bool isOk();
    bool set_data(db_struct *table);
    bool resetData(db_struct *table);
    QStringList get_item_info(QString a);
    QStringList get_job_info(QString a);
    bool set_item_info(QStringList data);
    bool set_job_info(QStringList data);
    bool deleteItem(const QString &in) const;
    bool deleteJob(const QString &in) const;
    bool fillJobsTable(db_struct *data, QTableWidget *table);
    bool fillItemsTable(db_struct *data, QTableWidget *table);
private:
    QSqlDatabase db;
    bool okOpen_h;
};

#endif // DB_HANDLER_H

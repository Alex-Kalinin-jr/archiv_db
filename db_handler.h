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
private:
    QSqlDatabase db;
    bool okOpen_h;
};

#endif // DB_HANDLER_H

#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <QSqlDatabase>

class Db_handler : public QSqlDatabase
{
public:
    Db_handler();
    ~Db_handler();
    bool isOk();
    QString get_data();
private:
    QSqlDatabase db;
    bool okOpen_h;
};

#endif // DB_HANDLER_H

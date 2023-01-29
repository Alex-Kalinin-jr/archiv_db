#ifndef DB_STRUCT_H
#define DB_STRUCT_H
#include <QtWidgets>

class db_struct
{
public:
    explicit db_struct(const QString &name);
    ~db_struct();
    QStringList *t_fields;
    QStringList *t_data;
    QString t_name;
};

#endif // DB_STRUCT_H

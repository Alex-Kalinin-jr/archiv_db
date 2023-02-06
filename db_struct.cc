#include "db_struct.h"

#include <QtWidgets>

db_struct::db_struct(const QString &name, const QString &fields, int count)
    : t_name(name), t_data(new QStringList), t_fields(fields), t_count(count){};

db_struct::~db_struct() { delete t_data; }

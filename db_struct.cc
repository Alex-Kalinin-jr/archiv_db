#include "db_struct.h"
#include <QtWidgets>

db_struct::db_struct(const QString &name)
    : t_name(name), t_fields(new QStringList), t_data(new QStringList) {};

db_struct::~db_struct() {
    delete t_fields;
    delete t_data;
}

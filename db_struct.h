#ifndef DB_STRUCT_H
#define DB_STRUCT_H
#include <QtWidgets>

class db_struct {
 public:
  explicit db_struct(const QString &name, const QString &fields, int count);
  ~db_struct();
  QStringList *t_data;
  QString t_name;
  QString t_fields;
  int t_count;
};

#endif  // DB_STRUCT_H

#ifndef DATATABLE_H
#define DATATABLE_H

#include <QWidget>
#include <QtWidgets>

#include "db_struct.h"
#include "mainwindow.h"
class MainWindow;

class DataTable : public QWidget {
  Q_OBJECT
 public:
  explicit DataTable(QWidget *parent = nullptr, MainWindow *window = nullptr);
  QComboBox *d_type;
 signals:

 public slots:
  virtual void show_table(int);
  virtual void set_passport_data(int, int);
  virtual void on_reset_clicked();

 protected:
  QTableWidget *d_table;
  QVBoxLayout *d_layout;
  QLabel *d_title;
  MainWindow *d_window;
  QPushButton *d_reset;
};

class ItemJobsTable : public DataTable {
  Q_OBJECT
 public:
  ItemJobsTable(QWidget *parent, MainWindow *window, QString item_id);

 public slots:
  void set_passport_data(int, int);
  void on_reset_clicked();
  void show_table(int a);
  void on_d_append_clicked();
  void on_d_add_ok_clicked();
  void on_d_remove_clicked();

 protected:
 private:
  QPushButton *d_append;
  QPushButton *d_remove;
  QString d_item_id;

  // for jobs_adding_table
  QWidget *d_add_widget;
  QVBoxLayout *d_add_layout;
  QTableWidget *d_all_jobs_table;
  QPushButton *d_add_ok;
};

class FilesTable : public DataTable {
  Q_OBJECT
 public:
  explicit FilesTable(QWidget *parent, MainWindow *window, QString job_id);
 public slots:
  void set_passport_data(int, int){};
  void on_reset_clicked();
  void show_table(int a);
  void on_f_append_clicked();
  void on_f_remove_clicked();

 private:
  QString f_job_id;
  QPushButton *f_append;
  QPushButton *f_remove;
  QStringList *f_filenames;
};

#endif  // DATATABLE_H

#ifndef PASSPORT_H
#define PASSPORT_H

#include <QWidget>
#include <QtWidgets>

#include "datatable.h"
#include "mainwindow.h"
class MainWindow;
class ItemJobsTable;
class FilesTable;

class Passport : public QWidget {
  Q_OBJECT
 public:
  explicit Passport(QWidget *parent = nullptr, MainWindow *win = nullptr);
  void set_passport_data(QString data);
  void fillFields(QString a, int index);
  QComboBox *p_box;
  bool checkAnswer(QString, QString);
  void clearData();
  QString get_id();
 signals:

 public slots:
  // switches between item data(int=0) and job data(int=1)
  void change_type(int a);

  void on_add_button_clicked();
  void on_send_button_clicked();
  void on_del_button_clicked();
  void on_p_show_clicked();
  void on_p_show_files_clicked();

 private:
  QVBoxLayout *p_layout;
  QLabel *pl_name;
  QLabel *pl_id;
  QLabel *pl_description;
  QLabel *pl_title;
  QTextEdit *p_description;
  QLineEdit *p_id;
  QTextEdit *p_name;
  QComboBox *p_type;
  MainWindow *p_window;
  QHBoxLayout *p_layout_2;
  QPushButton *p_add;
  QPushButton *p_delete;  // чистить таблицу item_job
  QPushButton *p_show;
  QPushButton *p_show_files;

  // items - widget for adding item/job
  QWidget *p_add_widget = nullptr;
  QVBoxLayout *p_add_layout = nullptr;
  QPushButton *p_add_button = nullptr;
  QLineEdit *p_add_id = nullptr;
  QTextEdit *p_add_name = nullptr;
  QTextEdit *p_add_descr = nullptr;
  QComboBox *p_add_type = nullptr;
  // end of items for adding item/job

  // list of jobs for certain item
  ItemJobsTable *p_show_table;

  // list of files for certain job
  FilesTable *f_table;

  // items - widget for showing files;
  QWidget *p_files_widget;
  QVBoxLayout *p_files_layout;
  QTableWidget *p_files_table;
  QPushButton *p_files_add;
  QPushButton *p_files_del;
  // end of items for showing files;
};

#endif  // PASSPORT_H

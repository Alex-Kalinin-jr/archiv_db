#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtWidgets>

#include "datatable.h"
#include "db_handler.h"
#include "db_struct.h"
#include "passport.h"
class Passport;
class DataTable;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();
  ~MainWindow();
  void loadFile(const QString &fileName);
  db_struct *get_items();
  db_struct *get_jobs();
  db_struct *get_it_j();
  db_struct *get_files();
  Passport *get_passport();
  DataTable *get_datatable();

  Passport *passport;
  DataTable *dt;
  Db_handler *handler;

 protected:
 private slots:
  bool on_search_clicked();
  void takeActInDb();

 private:
  QString p_curFile;
  QGridLayout *layer_1_1;
  QTableWidget *itemTable;
  bool itemShow = false;
  db_struct *it_struct;
  db_struct *j_struct;
  db_struct *it_j_struct;
  db_struct *f_struct;
};
#endif  // MAINWINDOW_H

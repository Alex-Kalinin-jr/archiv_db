
#include "mainwindow.h"

#include <QFileDialog>
#include <QFormLayout>
#include <QTableWidget>
#include <QtSql>
#include <QtWidgets>

#include "datatable.h"
#include "passport.h"

//#include <QByteArray>

MainWindow::~MainWindow() {}

bool MainWindow::on_search_clicked() {
  QFileDialog dialog(this);
  dialog.setWindowModality(Qt::WindowModal);
  dialog.setAcceptMode(QFileDialog::AcceptOpen);
  if (dialog.exec() != QFileDialog::Accepted) {
    return false;
  } else {
    takeActInDb();
    return true;
  }
}

void MainWindow::takeActInDb() {
  p_curFile = QFileDialog::getOpenFileName(this);
  if (!p_curFile.isEmpty()) return;
  return;
}

MainWindow::MainWindow() {
  handler = new Db_handler("QMYSQL", "localhost", "work_db", "root", "Df8a9c");
  if (handler->isOk()) {
    it_struct = new db_struct("items", "id, name, description", 3);
    j_struct = new db_struct("jobs", "id, job, type", 3);
    it_j_struct = new db_struct("item_job", "items, jobs", 2);
    f_struct = new db_struct("files", "job, file", 2);
    handler->set_data(it_struct);
    handler->set_data(j_struct);
    handler->set_data(it_j_struct);
    handler->set_data(f_struct);
  }

  // make central widget of the window be layout
  QWidget *center_1 = new QWidget();
  layer_1_1 = new QGridLayout(center_1);
  setCentralWidget(center_1);

  passport = new Passport(nullptr, this);
  layer_1_1->addWidget(passport, 0, 0, 3, 1);

  dt = new DataTable(nullptr, this);
  layer_1_1->addWidget(dt, 0, 1, 3, 2);
  dt->show_table(0);

  setLayout(layer_1_1);
}

db_struct *MainWindow::get_items() { return it_struct; }

db_struct *MainWindow::get_jobs() { return j_struct; }

db_struct *MainWindow::get_it_j() { return it_j_struct; }

db_struct *MainWindow::get_files() { return f_struct; }

Passport *MainWindow::get_passport() { return passport; }

DataTable *MainWindow::get_datatable() { return dt; }

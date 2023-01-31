#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include "db_handler.h"
#include "db_struct.h"
#include "passport.h"
#include "datatable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void loadFile(const QString &fileName);
    db_struct * get_items();
    db_struct * get_jobs();
    Passport * get_passport();
    DataTable * get_datatable();



    Db_handler *handler;

protected:
//    void closeEvent(QCloseEvent *event) override;

private slots:
    bool on_search_clicked();
    void takeActInDb();


private:
    QString p_curFile;
    QGridLayout *layer_1_1;
    QTableWidget *itemTable;
    bool itemShow = false;
    db_struct * it_struct;
    db_struct *j_struct;
    Passport *passport;
    DataTable *dt;
};
#endif // MAINWINDOW_H

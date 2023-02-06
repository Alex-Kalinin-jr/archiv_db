#ifndef DATATABLE_H
#define DATATABLE_H

#include <QWidget>
#include <QtWidgets>
#include "db_struct.h"
#include "mainwindow.h"
class MainWindow;

class DataTable : public QWidget
{
    Q_OBJECT
public:
    explicit DataTable(QWidget *parent = nullptr, MainWindow *window = nullptr);
    QComboBox *d_type;
    virtual bool showData(db_struct *data);
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
protected:
    bool showData(db_struct *);

private:
    QPushButton *d_append;
    QPushButton *d_remove;
    QString d_item_id;
    QPushButton *d_add_ok;

};


#endif // DATATABLE_H

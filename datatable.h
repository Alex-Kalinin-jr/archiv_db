#ifndef DATATABLE_H
#define DATATABLE_H

#include <QWidget>
#include <QtWidgets>
#include "db_struct.h"
#include "mainwindow.h"

class DataTable : public QWidget
{
    Q_OBJECT
public:
    explicit DataTable(QWidget *parent = nullptr, MainWindow *window = nullptr);

signals:

private slots:
    void show_table(int);
    void set_passport_data();

private:
    QTableWidget *d_table;
    QComboBox *d_type;
    QVBoxLayout *d_layout;
    QLabel *d_title;
    MainWindow *d_window;
    bool showData(db_struct *data);

};

#endif // DATATABLE_H

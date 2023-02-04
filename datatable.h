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
signals:

public slots:
    void show_table(int);
    void set_passport_data(int, int);

private:
    QTableWidget *d_table;

    QVBoxLayout *d_layout;
    QLabel *d_title;
    MainWindow *d_window;
    bool showData(db_struct *data);

};

#endif // DATATABLE_H

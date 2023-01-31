#include "datatable.h"
#include "mainwindow.h"
#include <QtWidgets>

DataTable::DataTable(QWidget *parent, MainWindow *window)
    : QWidget(parent), d_window(window)
{
    d_title = new QLabel();
    d_title->setText("Item");
    d_title->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    d_layout = new QVBoxLayout(this);
    d_table = new QTableWidget();
    d_type = new QComboBox();
    d_type->insertItems(0, {"Item", "Job"});
    d_layout->addWidget(d_title);
    d_layout->addWidget(d_table);
    d_layout->addWidget(d_type);
    connect(d_type, SIGNAL(currentIndexChanged(int)), this, SLOT(show_table(int)));
//    connect(d_table, SIGNAL(cellClicked(int,int)), this, SLOT(set_passport_data(int, int)));
}

bool DataTable::showData(db_struct *data)
{
    d_table->clear();
    d_table->setColumnCount(2);
    int size = data->t_data->size() / data->t_count;
    d_table->setRowCount(size);
    int c = 0;
    QTableWidgetItem *cell = nullptr;
    QStringList *b = data->t_data;
    for (int i = 0; i < size; ++i) {
        c += 1;
        for (int j = 0; j < 2; ++j) {
            cell = new QTableWidgetItem;
            cell->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            QString a = b->at((data->t_count)*i+j);
            cell->setText(a);
            d_table->setItem(i, j, cell);
        }
    }
}

void DataTable::show_table(int a)
{
    if (d_window != nullptr) {
        if (a == 0) {
            d_title->setText("Items");
            showData(d_window->get_items());
        } else if (a == 1) {
            d_title->setText("Jobs");
            showData(d_window->get_jobs());
        }
    }
}

//void DataTable::set_passport_data(int row, int col) {
//    QString buff = d_table->item(0, col)->text();
//    int indicator = d_type->currentIndex();
//    window->get_passport()->func

//}

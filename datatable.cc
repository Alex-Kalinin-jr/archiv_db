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
    d_type->setVisible(false); // this button is a mistake of architecture
    d_type->insertItems(0, {"Item", "Job"});
    d_reset = new QPushButton();
    d_reset->setText("Reset");
    d_layout->addWidget(d_title);
    d_layout->addWidget(d_table);
    d_layout->addWidget(d_type);
    d_layout->addWidget(d_reset);

    connect(d_type, SIGNAL(currentIndexChanged(int)), this, SLOT(show_table(int)));
    connect(d_table, SIGNAL(cellClicked(int,int)), this, SLOT(set_passport_data(int, int)));
    connect(d_reset, SIGNAL(clicked(bool)), this, SLOT(on_reset_clicked()));

}

//bool DataTable::showData(db_struct *data)
//{
//    d_table->clear();
//    d_table->setColumnCount(2);
//    int size = data->t_data->size() / data->t_count;
//    d_table->setRowCount(size);
//    QTableWidgetItem *cell = nullptr;
//    QStringList *b = data->t_data;
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < 2; ++j) {
//            cell = new QTableWidgetItem;
//            cell->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
//            QString a = b->at((data->t_count)*i+j);
//            cell->setText(a);
//            d_table->setItem(i, j, cell);
//        }
//    }
//}

void DataTable::show_table(int a)
{
    if (a == 0) {
        d_title->setText("Items");
        d_window->handler->fillItemsTable(d_window->get_items(), d_table);
    } else if (a == 1) {
        d_title->setText("Jobs");
        d_window->handler->fillJobsTable(d_window->get_jobs(), d_table);
    }
    if (d_window->passport->p_box->currentIndex() != a)
        d_window->passport->p_box->setCurrentIndex(a);
}

void DataTable::set_passport_data(int row, int col) {
    QString buff = d_table->item(row, 0)->text();
    int indicator = d_type->currentIndex();
    d_window->get_passport()->fillFields(buff, indicator);
}


void DataTable::on_reset_clicked() {
    d_window->handler->set_data(d_window->get_items());
    d_window->handler->set_data(d_window->get_jobs());
    d_table->clear();
    show_table(d_type->currentIndex());
}


ItemJobsTable::ItemJobsTable(QWidget *parent, MainWindow *window, QString item_id)
        : DataTable(parent, window), d_item_id(item_id) {
    d_title->setText("Jobs for current item");

    d_append = new QPushButton();
    d_append->setText("Add");
    d_layout->addWidget(d_append);
    connect(d_append, SIGNAL(clicked(bool)), this, SLOT(on_d_append_clicked()));

    d_remove = new QPushButton();
    d_remove->setText("Delete");
    d_layout->addWidget(d_remove);

    // this button is for new addjobtable
    d_add_ok = new QPushButton();
    d_add_ok->setText("Add");
    d_add_ok->setVisible(false);
}

void ItemJobsTable::set_passport_data(int, int) {}

void ItemJobsTable::on_reset_clicked() {
    d_window->handler->set_data(d_window->get_it_j());
    d_table->clear();
    show_table(0);
}

void ItemJobsTable::show_table(int a) {
    showData(d_window->get_it_j());
}

bool ItemJobsTable::showData(db_struct *data) {
    d_table->clear();
    d_table->setColumnCount(1);
    d_table->setRowCount(0);
    int size = data->t_data->size();
    QTableWidgetItem *cell = nullptr;
    QStringList *b = data->t_data;
    for (int i = 0; i < size; i += 2) {
        if (b->at(i) == d_item_id) {
            cell = new QTableWidgetItem;
            cell->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            d_table->setRowCount(d_table->rowCount()+1);
            cell->setText(b->at(i+1));
            d_table->setItem(d_table->rowCount()-1, 0, cell);
        }
    }
}

void ItemJobsTable::on_d_append_clicked() {
    QWidget d_add_widget;
    QVBoxLayout d_add_layout(&d_add_widget);
    QTableWidget d_all_jobs_table;

    d_add_layout.addWidget((d_add_ok));
}

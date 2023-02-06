#include "datatable.h"
#include "mainwindow.h"
#include <QtWidgets>

DataTable::DataTable(QWidget *parent, MainWindow *window)
    : QWidget(parent), d_window(window)
{
    // this button is a mistake of architecture
    d_type = new QComboBox();
    d_type->setVisible(false);
    d_type->insertItems(0, {"Item", "Job"});
    // end of button


    d_title = new QLabel();
    d_title->setText("Item");
    d_title->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    d_layout = new QVBoxLayout(this);
    d_table = new QTableWidget();
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
    connect(this->d_remove, SIGNAL(clicked(bool)), this, SLOT(on_d_remove_clicked()));

// table for adding jobs to item
    d_add_widget = new QWidget();
    d_add_widget->setWindowModality(Qt::ApplicationModal);
    d_add_layout = new QVBoxLayout(d_add_widget);

    d_all_jobs_table = new QTableWidget;
    d_add_layout->addWidget(d_all_jobs_table);
    d_window->handler->fillJobsTable(d_window->get_jobs(), d_all_jobs_table);

    d_add_ok = new QPushButton();
    d_add_ok->setText("Add");
    d_add_layout->addWidget((d_add_ok));
    connect(this->d_add_ok, SIGNAL(clicked(bool)), this, SLOT(on_d_add_ok_clicked()));
// end of table
}

void ItemJobsTable::set_passport_data(int, int) {}

void ItemJobsTable::on_reset_clicked() {
    d_window->handler->set_data(d_window->get_it_j());
    show_table(0);
}

void ItemJobsTable::show_table(int a) {
    d_window->handler->fillItJRelationTable(d_window->get_it_j(), d_table, d_item_id);
}

void ItemJobsTable::on_d_append_clicked() {

    d_add_widget->show();
}

void ItemJobsTable::on_d_add_ok_clicked() {
    int a = d_all_jobs_table->currentRow();
    QString cur_id = d_window->passport->get_id();
    QString cur_job = d_all_jobs_table->item(a, 0)->text();
    d_window->handler->bindJobToItem(cur_id, cur_job);
}

void ItemJobsTable::on_d_remove_clicked() {
    QString cur_id = d_window->passport->get_id();
    QString cur_job = d_table->item(d_table->currentRow(), 1)->text();
    d_window->handler->deleteItemJob(cur_id, cur_job);
    on_reset_clicked();
}




FilesTable::FilesTable(QWidget *parent, MainWindow *window, QString job_id)
        : DataTable(parent, window), f_job_id(job_id) {
    f_filenames = new QStringList;
    d_title->setText("Files for current job");

    f_append = new QPushButton();
    f_append->setText("Add");
    d_layout->addWidget(f_append);
    connect(f_append, SIGNAL(clicked(bool)), this, SLOT(on_f_append_clicked()));

    f_remove = new QPushButton();
    f_remove->setText("Delete");
    d_layout->addWidget(f_remove);
    connect(this->f_remove, SIGNAL(clicked(bool)), this, SLOT(on_f_remove_clicked()));
}

void FilesTable::show_table(int a) {
    d_window->handler->fillFilesTable(d_window->get_files(), d_table, f_job_id);
}

void FilesTable::on_reset_clicked() {
    d_window->handler->set_data(d_window->get_files());
    show_table(0);
}

void FilesTable::on_f_append_clicked() {
        QFileDialog *dialog = new QFileDialog(this);
        dialog->setFileMode(QFileDialog::ExistingFiles);
        dialog->setViewMode(QFileDialog::Detail);
        *f_filenames = dialog->getOpenFileNames();
        delete dialog;
        if (!(f_filenames->isEmpty())) {
            d_window->handler->set_files_info(f_filenames, d_window->passport->get_id());
        }
}

void FilesTable::on_f_remove_clicked() {
    QString removed_road = d_table->item(d_table->currentRow(), 1)->text();
    QString job = d_table->item(d_table->currentRow(), 0)->text();
    d_window->handler->remove_file_from_job(job, removed_road);
}

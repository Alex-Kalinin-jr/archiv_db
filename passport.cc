#include "passport.h"
#include "db_handler.h"
#include <QtWidgets>

Passport::Passport(QWidget *parent, MainWindow *win) : QWidget(parent), p_window(win)
{

    p_layout = new QVBoxLayout(this);
    pl_name = new QLabel;
    pl_id = new QLabel;
    pl_description = new QLabel;
    pl_title = new QLabel;

    p_id = new QLineEdit();
    p_id->setReadOnly(true);
    p_name = new QTextEdit();
    p_name->setReadOnly(true);
    p_description = new QTextEdit();
    p_type = new QComboBox();
    p_type->setEditable(false);

    p_layout_2 = new QHBoxLayout();
    p_add = new QPushButton();
    p_delete = new QPushButton();
    p_add_button = new QPushButton();


   pl_title->setText("Item");
   pl_title->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
   p_layout->addWidget(pl_title);

   pl_id->setAlignment((Qt::AlignLeft|Qt::AlignVCenter));
   pl_id->setText("ID:");
   p_layout->addWidget(pl_id);

   p_id->setAlignment((Qt::AlignHCenter|Qt::AlignVCenter));
   p_id->setText("");
   p_layout->addWidget(p_id);

    pl_name->setAlignment((Qt::AlignLeft|Qt::AlignVCenter));
    pl_name->setText("Name:");
    p_layout->addWidget(pl_name);

    p_name->setAlignment((Qt::AlignLeft|Qt::AlignTop));
    p_name->setText("");
    p_layout->addWidget(p_name);

    pl_description->setAlignment((Qt::AlignLeft|Qt::AlignVCenter));
    pl_description->setText("Description:");
    p_layout->addWidget(pl_description);

    p_description->setAlignment((Qt::AlignLeft|Qt::AlignTop));
    p_description->setText("");
    p_layout->addWidget(p_description);

    p_type->insertItems(0, {"prepare", "main", "after"});
    p_layout->addWidget(p_type);
    p_type->setVisible(false);

    p_box = new QComboBox();
    p_box->insertItems(0, {"items", "jobs"});
    p_layout->addWidget(p_box);
    connect(p_box, SIGNAL(currentIndexChanged(int)), this, SLOT(change_type(int)));


    p_layout->addLayout(p_layout_2);

    p_add->setText("Add new");
    p_layout_2->addWidget(p_add);
    connect(p_add, SIGNAL(clicked(bool)), this, SLOT(on_add_button_clicked()));

    p_delete->setText("Delete");
    p_layout_2->addWidget(p_delete);
    connect(p_delete, SIGNAL(clicked(bool)), this, SLOT(on_del_button_clicked()));

    p_show = new QPushButton();
    p_show->setText("show jobs");
    p_layout_2->addWidget(p_show);
    connect(p_show, SIGNAL(clicked()), this, SLOT(on_p_show_clicked()));
}

void Passport::change_type(int a)
{
    if (a == 1) {
        pl_title->setText("Job");
        pl_description->setText("Type:");
        p_description->setVisible(false);
        p_type->setVisible(true);
    } else if (a == 0) {
        pl_title->setText("Item");
        pl_description->setText("Description:");
        p_type->setVisible(false);
        p_description->setVisible(true);
    }
    clearData();
    if (p_window->dt->d_type->currentIndex() != a)
        p_window->dt->d_type->setCurrentIndex(a);
}
void Passport::fillFields(QString a, int index) {
    QStringList buff;
    if (index == 0) {
        buff = p_window->handler->get_item_info(a);
    } else if (index == 1) {
        buff = p_window->handler->get_job_info(a);
    }
    p_id->setText(buff.at(0));
    p_name->setText(buff.at(1));
    if (index == 0) {
        p_description->setText(buff.at(2));
    } else if (index == 1) {
        p_type->setCurrentIndex(buff.at(2).toInt());
    }
}


void Passport::on_add_button_clicked() {
    p_add_widget = new QWidget();
    p_add_layout = new QVBoxLayout(p_add_widget);

    QLabel *label_id = new QLabel(p_add_widget);
    label_id->setText("ID:");
    p_add_id = new QLineEdit(p_add_widget);
    p_add_layout->addWidget(label_id);
    p_add_layout->addWidget(p_add_id);

    QLabel *label_name = new QLabel(p_add_widget);
    label_name->setText("Name:");
    p_add_name = new QTextEdit(p_add_widget);
    p_add_layout->addWidget(label_name);
    p_add_layout->addWidget(p_add_name);
    QLabel *label_descr = new QLabel(p_add_widget);
    if (this->p_box->currentIndex() == 0) {
        label_descr->setText("Description");
        p_add_layout->addWidget(label_descr);
        p_add_descr = new QTextEdit(p_add_widget);
        p_add_layout->addWidget(p_add_descr);
    } else if (this->p_box->currentIndex() == 1) {
        label_descr->setText("type");
        p_add_layout->addWidget(label_descr);
        p_add_type = new QComboBox(p_add_widget);
        p_add_type->insertItems(0, {"prepare", "main", "after"});
        p_add_layout->addWidget(p_add_type);
    }
    p_add_button->setText("send to server");
    p_add_layout->addWidget(p_add_button);
    connect(p_add_button, SIGNAL(clicked(bool)), this, SLOT(on_send_button_clicked()));
    p_add_widget->show();
}

void Passport::on_send_button_clicked() {
    int indicator = this->p_box->currentIndex();
    QStringList sended;
    sended<<p_add_id->text()<<p_add_name->toPlainText();
    if (indicator == 0) {
        sended<<p_add_descr->toPlainText();
    } else if (indicator == 1) {
        sended<<QString::number(p_add_type->currentIndex());
    }

    if (indicator == 0) {
        this->p_window->handler->set_item_info(sended);
    } else if (indicator == 1) {
        this->p_window->handler->set_job_info(sended);
    }
}

void Passport::on_del_button_clicked() {
    if (checkAnswer("Are yo sure?", "You are going to delete record from database")) {
        QString deleted = p_id->text();
        if (p_box->currentIndex() == 0) {
            p_window->handler->deleteItem(deleted);
        } else if (p_box->currentIndex() == 1) {
            p_window->handler->deleteJob(deleted);
        }

        // here
    } else {
        pl_title->setText("Not permitted");
    }
}

bool Passport::checkAnswer(QString a, QString b) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, a, b, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        return 1;
    } else {
        return 0;
    }
}

void Passport::clearData() {
    p_id->setText("");
    p_name->setText("");
    p_description->setText("");
    p_type->setCurrentIndex(0);
}

void Passport::on_p_show_clicked() {
    p_show_table = new ItemJobsTable(nullptr, p_window, p_id->text());
    p_show_table->show_table(0);
    p_show_table->show();
}

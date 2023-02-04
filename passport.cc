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
    p_description = new QTextEdit();
    p_id = new QLineEdit();
    p_id->setReadOnly(true);
    p_name = new QTextEdit();
    p_name->setReadOnly(true);
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
}
void Passport::fillFields(QString a, int index) {
    p_box->setCurrentIndex(index);
    //    change_type(index);
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
    p_add_widget->show();
}


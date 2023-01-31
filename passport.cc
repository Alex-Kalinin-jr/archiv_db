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
    p_name = new QTextEdit();
    p_type = new QComboBox();

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

    QComboBox *a = new QComboBox();
    a->insertItems(0, {"items", "jobs"});
    p_layout->addWidget(a);
    connect(a, SIGNAL(currentIndexChanged(int)), this, SLOT(change_type(int)));
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
    change_type(index);
    QStringList buff;
    if (index == 0) {
        buff = p_window->handler->get_item_info(a);
    } else if (index == 1) {
        buff = p_window->handler->get_job_info(a);
    }
    pl_id->setText(buff.at(0));
    pl_name->setText(buff.at(1));
    if (index == 0) {
        pl_description->setText(buff.at(2));
    } else if (index == 1) {
        p_type->setCurrentIndex(buff.at(2).toInt());
    }
}


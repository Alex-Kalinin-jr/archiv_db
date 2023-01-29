#include "db_handler.h"

Db_handler::Db_handler()

{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("shop_db");
    db.setUserName("root");
    db.setPassword("Df8a9c");
    okOpen_h =db.open();
}

bool Db_handler::isOk() {
    return okOpen_h;
}


//    if (ok) {
//        QSqlQuery my(db);
//        if (my.exec("select max(price) from shop;")) {
//            my.next();
//            QString answ = my.value(0).toString();
//            ui->label->setText(answ);
//        } else {
//            ui->label->setText(my.lastError().text());
//        }
//    } else {
//        ui->label->setText("fail");
//    }

#ifndef PASSPORT_H
#define PASSPORT_H

#include <QWidget>
#include <QtWidgets>
#include "mainwindow.h"
#include "datatable.h"
class MainWindow;
class ItemJobsTable;

class Passport : public QWidget
{
    Q_OBJECT
public:
    explicit Passport(QWidget *parent = nullptr, MainWindow *win = nullptr);
    void set_passport_data(QString data);
    void fillFields(QString a, int index);
    QComboBox *p_box;
    bool checkAnswer(QString, QString);
    void clearData();
signals:

public slots:
    void change_type(int a);
    void on_add_button_clicked();
    void on_send_button_clicked();
    void on_del_button_clicked();
    void on_p_show_clicked();

private:
    QVBoxLayout *p_layout;
    QLabel *pl_name;
    QLabel *pl_id;
    QLabel *pl_description;
    QLabel *pl_title;
    QTextEdit *p_description;
    QLineEdit *p_id;
    QTextEdit *p_name;
    QComboBox *p_type;
    MainWindow *p_window;
    QHBoxLayout *p_layout_2;
    QPushButton *p_add;
    QPushButton *p_delete;
    QPushButton *p_show;

    QWidget *p_add_widget = nullptr;
    QVBoxLayout *p_add_layout = nullptr;
    QPushButton *p_add_button = nullptr;
    QLineEdit *p_add_id = nullptr;
    QTextEdit *p_add_name = nullptr;
    QTextEdit *p_add_descr = nullptr;
    QComboBox *p_add_type = nullptr;

    ItemJobsTable *p_show_table;




};

#endif // PASSPORT_H

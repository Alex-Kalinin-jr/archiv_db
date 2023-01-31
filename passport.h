#ifndef PASSPORT_H
#define PASSPORT_H

#include <QWidget>
#include <QtWidgets>
#include "mainwindow.h"
class MainWindow;
class Passport : public QWidget
{
    Q_OBJECT
public:
    explicit Passport(QWidget *parent = nullptr, MainWindow *win = nullptr);
    void set_passport_data(QString data);
    void fillFields(QString a, int index);
signals:

private slots:
    void change_type(int a);

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
    QComboBox *p_box;
};

#endif // PASSPORT_H

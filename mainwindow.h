#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include "db_handler.h"
#include "db_struct.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    void loadFile(const QString &fileName);

protected:
//    void closeEvent(QCloseEvent *event) override;

private slots:
    bool on_search_clicked();
    void takeActInDb();
//    void newFile();
//    void open();
//    bool save();
//    bool saveAs();
//    void about();
//    void documentWasModified();
//#ifndef QT_NO_SESSIONMANAGER
//    void commitData(QSessionManager &);
//#endif

private:
//    void createActions();
//    void createStatusBar();
//    void readSettings();
//    void writeSettings();
//    bool maybeSave();
//    bool saveFile(const QString &fileName);
//    void setCurrentFile(const QString &fileName);
//    QString strippedName(const QString &fullFileName);

//    QPlainTextEdit *textEdit;
    QString p_curFile;
    db_struct * it_struct;
    db_struct *j_struct;
    Db_handler *handler;
};
#endif // MAINWINDOW_H

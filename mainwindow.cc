
#include <QtSql>
#include "mainwindow.h"

#include <QtWidgets>
#include <QFormLayout>
#include <QFileDialog>
#include <QTableWidget>
#include "passport.h"
#include "datatable.h"

//#include <QByteArray>


MainWindow::~MainWindow() {}

bool MainWindow::on_search_clicked()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (dialog.exec() != QFileDialog::Accepted) {
        return false;
    } else {
        takeActInDb();
        return true;
    }
}

void MainWindow::takeActInDb() {
    p_curFile = QFileDialog::getOpenFileName(this);
    if (!p_curFile.isEmpty())
        return;
    return;
}


MainWindow::MainWindow()
{
    handler = new Db_handler("QMYSQL", "localhost", "work_db", "root", "Df8a9c");
    if (handler->isOk()) {
        it_struct = new db_struct("items", "id, name, description", 3);
        j_struct = new db_struct("jobs", "id, job, type", 3);
        handler->set_data(it_struct);
        handler->set_data(j_struct);
    }

    // make central widget of the window be layout
    QWidget *center_1 = new QWidget();
    layer_1_1 = new QGridLayout(center_1);
    setCentralWidget(center_1);

    passport = new Passport();
    layer_1_1->addWidget(passport, 0, 0, 3, 1);

    dt = new DataTable(nullptr, this);
    layer_1_1->addWidget(dt, 0, 1, 3, 1);

    setLayout(layer_1_1);

}

db_struct *MainWindow::get_items() {
    return it_struct;
}

db_struct *MainWindow::get_jobs() {
    return j_struct;
}

Passport * MainWindow::get_passport() {
    return passport;
}

DataTable * MainWindow::get_datatable() {
    return dt;
}




















//resize(800, 600);
//setWindowTitle("db_program_test - [*]");
//setCentralWidget(textEdit);
//createActions();
//createStatusBar();
//readSettings();
//connect(textEdit->document(), &QTextDocument::contentsChanged,
//        this, &MainWindow::documentWasModified);
//#ifndef QT_NO_SESSIONMANAGER
//connect(qApp, &QGuiApplication::commitDataRequest, this, &MainWindow::commitData);
//#endif
//setCurrentFile(QString());
//setUnifiedTitleAndToolBarOnMac(true);



//    QMenu *file = menuBar()->addMenu("&File");
//    auto *quit = new QAction("&Quit", this);
//    auto *save = new QAction ("&Save", this);
//    file->addAction(save);
//    file->addAction(quit);
//    connect(quit, &QAction::triggered, qApp, QApplication::quit);
//    QToolBar *tool = addToolBar("&New");
//    auto *new_win = new QAction("&New", this);
//    tool->addAction(new_win);
//    connect(new_win, &QAction::triggered, this, SLOT(new_wind()));































//void MainWindow::closeEvent(QCloseEvent *event) {
//    if (maybeSave()) {
//        writeSettings();
//        event->accept();
//    } else {
//        event->ignore();
//    }
//}

//void MainWindow::newFile() {
//    if (maybeSave()) {
//        textEdit->clear();
//        setCurrentFile(QString());
//    }
//}

//void MainWindow::open() {
//    if (maybeSave()) {
//        QString filename = QFileDialog::getOpenFileName(this);
//        if (!filename.isEmpty())
//            loadFile(filename);
//    }
//}

//bool MainWindow::save() {
//    if (curFile.isEmpty()) {
//        return saveAs();
//    } else {
//        return saveFile(curFile);
//    }
//}

//bool MainWindow::saveAs() {
//    QFileDialog dialog(this);
//    dialog.setWindowModality(Qt::WindowModal);
//    dialog.setAcceptMode(QFileDialog::AcceptSave);
//    if (dialog.exec() != QFileDialog::Accepted) {
//        return false;
//    } else {
//        return saveFile(dialog.selectedFiles().first());
//    }

//}

//void MainWindow::about() {
//    QMessageBox::about(this, "about", "educational program");
//}

//void MainWindow::documentWasModified() {
//    setWindowModified(textEdit->document()->isModified());
//}

//void MainWindow::createActions() {
//    QMenu *fileMenu = menuBar()->addMenu("&File");
//    QToolBar *fileToolBar = addToolBar("&File");

//    QAction *newAct = new QAction("&New", this);
//    newAct->setShortcuts(QKeySequence::New);
//    newAct->setStatusTip("create a new file");
//    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
//    fileMenu->addAction(newAct);
//    fileToolBar->addAction(newAct);

//    QAction *openAct = new QAction("&Open", this);
//    openAct->setShortcuts(QKeySequence::Open);
//    openAct->setStatusTip("open a file");
//    connect(openAct, &QAction::triggered, this, &MainWindow::open);
//    fileMenu->addAction(openAct);
//    fileToolBar->addAction(openAct);

//    QAction *saveAct = new QAction("&Save", this);
//    saveAct->setShortcuts(QKeySequence::Save);
//    saveAct->setStatusTip("save a file");
//    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
//    fileMenu->addAction(saveAct);
//    fileToolBar->addAction(saveAct);

//    QAction *saveAsAct = new QAction("&SaveAs", this);
//    saveAsAct->setShortcuts(QKeySequence::SaveAs);
//    saveAsAct->setStatusTip("save a file under diff name");
//    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);
//    fileMenu->addAction(saveAsAct);
//    fileToolBar->addAction(saveAsAct);
//}

//void MainWindow::createStatusBar()
//{
//    statusBar()->showMessage(tr("Ready"));
//}

//void MainWindow::readSettings() {
//    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
//    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
//    if (geometry.isEmpty()) {
//        const QRect availableGeometry = screen()->availableGeometry();
//        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
//        move((availableGeometry.width() - width()) / 2,
//             (availableGeometry.height() - height()) /2);
//    } else {
//        restoreGeometry(geometry);
//    }
//}

//void MainWindow::writeSettings() {
//    QSettings settings(QCoreApplication::organizationName(),
//                       QCoreApplication::applicationName());
//    settings.setValue("geometry", saveGeometry());
//}

//bool MainWindow::maybeSave() {
//    if (!textEdit->document()->isModified())
//        return true;
//    const QMessageBox::StandardButton ret
//            = QMessageBox::warning(this, "Application", "do u want to save?",
//                                   QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
//    switch(ret) {
//        case QMessageBox::Save:
//            return save();
//        case QMessageBox::Cancel:
//            return false;
//        default:
//            break;
//    }
//    return true;
//}

//void MainWindow::loadFile(const QString &fileName) {
//    QFile file(fileName);
//    if(!file.open(QFile::ReadOnly | QFile::Text)) {
//        QMessageBox::warning(this, "app",
//                QString("cannot read fie %1:/n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
//        return;
//    }
//    QTextStream in(&file);
//#ifndef QT_NO_CURSOR
//    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
//#endif
//    textEdit->setPlainText(in.readAll());
//#ifndef QT_NO_CURSOR
//    QGuiApplication::restoreOverrideCursor();
//#endif
//    setCurrentFile(fileName);
//    statusBar()->showMessage("loaded"), 2000;
//}

//bool MainWindow::saveFile(const QString &filename) {
//    QString errorMessage;
//    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
//    QSaveFile file(filename);
//    if (file.open(QFile::WriteOnly|QFile::Text)) {
//        QTextStream out(&file);
//        out<<textEdit->toPlainText();
//        if (!file.commit()) {
//            errorMessage = QString("Cannot write %1:\n%2.")
//                           .arg(QDir::toNativeSeparators(filename), file.errorString());
//        }
//    } else {
//        errorMessage = QString("cannot open %1 for writing:\n%2").
//                       arg(QDir::toNativeSeparators(filename), file.errorString());
//    }
//    QGuiApplication::restoreOverrideCursor();

//    if (!errorMessage.isEmpty()) {
//        QMessageBox::warning(this, "app", errorMessage);
//        return false;
//    }
//    setCurrentFile(filename);
//    statusBar()->showMessage("file saved", 2000);
//    return true;
//}

//void MainWindow::setCurrentFile(const QString &fileName) {
//    curFile = fileName;
//    textEdit->document()->setModified(false);
//    setWindowModified(false);
//    QString shownName = curFile;
//    if (curFile.isEmpty())
//        shownName = "untitled.txt";
//    setWindowFilePath(shownName);
//}

//QString MainWindow::strippedName(const QString &fullFileName) {
//    return QFileInfo(fullFileName).fileName();
//}

//#ifndef QT_NO_SESSIONMANAGER
//void MainWindow::commitData(QSessionManager &manager) {
//    if (manager.allowsInteraction()) {
//        if (!maybeSave()) {
//            manager.cancel();
//        } else {
//            if (textEdit->document()->isModified())
//                save();
//        }
//    }
//}
//#endif


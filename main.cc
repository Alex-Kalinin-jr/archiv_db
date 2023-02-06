#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  //    Q_INIT_RESOURCE(application);
  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("my_org");
  QCoreApplication::setApplicationName("my_app");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);
  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::applicationName());
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", "the file to open");
  parser.process(app);
  MainWindow w;
  //    if (!parser.positionalArguments().isEmpty()) {
  //        w.loadFile(parser.positionalArguments().first());
  //    }
  w.show();
  return app.exec();
}

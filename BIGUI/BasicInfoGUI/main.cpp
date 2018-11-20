#include "bidialog.h"
#include <QApplication>
#include "qdir.h"

#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>

int main(int argc, char *argv[])
{
    std::unique_ptr<g3::LogWorker> logworker{ g3::LogWorker::createLogWorker() };
    QString logDir = QDir::homePath() + "/StudentPassing/Logs";
    auto defaultHandler = logworker->addDefaultLogger(argv[0], logDir.toStdString());
    g3::initializeLogging(logworker.get());

    LOG(INFO) << "Launching Qt GUI app node for StudentPassing";
    QApplication a(argc, argv);
    BIDialog w;
    w.show();

    return a.exec();
}

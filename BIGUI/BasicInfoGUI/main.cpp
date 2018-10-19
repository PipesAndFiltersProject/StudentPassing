#include "bidialog.h"
#include <QApplication>

#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>

int main(int argc, char *argv[])
{
    std::unique_ptr<g3::LogWorker> logworker{ g3::LogWorker::createLogWorker() };
    auto defaultHandler = logworker->addDefaultLogger(argv[0], "./");
    g3::initializeLogging(logworker.get());

    LOG(INFO) << "Launching Qt GUI app node for StudentPassing";
    QApplication a(argc, argv);
    BIDialog w;
    w.show();

    return a.exec();
}

#include "bidialog.h"
#include "ui_bidialog.h"
#include "qdir.h"
#include "qmessagebox.h"

#include <g3log/g3log.hpp>

#include <OHARBaseLayer/ProcessorNode.h>

#include <OHARStudentLayer/PlainStudentFileHandler.h>
#include <OHARStudentLayer/StudentNetOutputHandler.h>
#include <OHARStudentLayer/StudentDataItem.h>


BIDialog::BIDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BIDialog),
    node(nullptr)
{
    ui->setupUi(this);

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    connect(ui->pingButton, SIGNAL(clicked()), this, SLOT(onPingButtonClicked()));
    connect(ui->addStudentButton, SIGNAL(clicked()), this, SLOT(onAddStudentButtonClicked()));
    connect(ui->readfileButton, SIGNAL(clicked()), this, SLOT(onReadFileButtonClicked()));

    if (QApplication::arguments().count() > 1) {
        config = QApplication::arguments().at(1);
    }
    //TODO: modify UI element names based on configuration.

    node = new OHARBase::ProcessorNode("BasicInfo", this);
    using namespace OHARStudent;
    node->addHandler(new PlainStudentFileHandler(*node));
    node->addHandler(new StudentNetOutputHandler(*node));
}

BIDialog::~BIDialog()
{
    delete ui;
    delete node;
}


void BIDialog::onStartButtonClicked()
{
    LOG(INFO) << "Start/stop button clicked.";
    if (!node->isRunning()) {
        if (configureNode())
        {
            LOG(INFO) << "***** Configured, starting the node";
            showMessage("Node configured, starting the node.");
            node->start();
        } else {
            LOG(INFO) << "Configuration failed, cannot start node.";
            showMessage("Node configuration failed, cannot start node.");
            QMessageBox box;
            box.setText("Create configuration file for the node first!");
            box.exec();
        }


    } else {
        LOG(INFO) << "***** Stopping the node";
        node->stop();
        showMessage("Node stopped");
    }
}


void BIDialog::onPingButtonClicked()
{
    showMessage("Sending ping");
    LOG(INFO) << "***** Ping button clicked";
    node->handleCommand("ping");
}

void BIDialog::onReadFileButtonClicked()
{
    //TODO: get data file name from node configuration.
    QString dataFile = QDir::homePath() + "/StudentPassing/basic-student-info.txt";
    showMessage("Reading data from " + dataFile);
    node->handleCommand("readfile");
}

void BIDialog::onShutdownButtonClicked()
{

}

void BIDialog::onAddStudentButtonClicked()
{
     LOG(INFO) << "***** Add student button clicked";
    QString id = ui->studentId->text();
    if (id.length() > 0)
    {
        QString name = ui->studentName->text();
        if (name.length() > 0)
        {
            QString studyProgram = ui->studyProgram->text();
            if (studyProgram.length() > 0)
            {
                //TODO: set proper student data items based on configuration.
                LOG(INFO) << "Creating a data Package to send...";
                OHARBase::Package p;
                p.setType((OHARBase::Package::Data));
                LOG(INFO) << "Creating a student object...";
                std::shared_ptr<OHARStudent::StudentDataItem> student(new OHARStudent::StudentDataItem());
                student->setId(id.toStdString());
                student->setName(name.toStdString());
                student->setStudyProgram(studyProgram.toStdString());
                LOG(INFO) << "Handing over the student to the Package...";
                p.setDataItem(student.get());
                LOG(INFO) << "Telling node to pass to handlers";
                node->passToHandlers(p);
            }
        }
    }
}

bool BIDialog::configureNode()
{
    if (config.length() > 0) {
        QString configFile = QDir::homePath() + "/StudentPassing/" + config + ".txt";
        showMessage("Reading configuration from " + configFile);
        return node->configure(configFile.toStdString());
    } else {
        showMessage("No configuration file name in startup parameters!");
        return false;
    }
}


void BIDialog::NodeEventHappened(EventType /*event*/, const std::string & message)
{
    showMessage(QString::fromStdString(message));
    refreshUI();
}

void BIDialog::showMessage(const QString & message)
{
    ui->logView->appendPlainText(message);
}

void BIDialog::refreshUI()
{
    if (node->isRunning()) {
        ui->pingButton->setDisabled(false);
        ui->readfileButton->setDisabled(false);
        ui->shutdownButton->setDisabled(false);
        ui->addStudentButton->setDisabled(false);
        ui->startButton->setText("&Stop");
    } else {
        ui->pingButton->setDisabled(true);
        ui->readfileButton->setDisabled(true);
        ui->shutdownButton->setDisabled(true);
        ui->addStudentButton->setDisabled(true);
        ui->startButton->setText("&Start");
    }
}

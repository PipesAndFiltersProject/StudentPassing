#include "bidialog.h"
#include "ui_bidialog.h"
#include "qdir.h"
#include "qmessagebox.h"

#include <g3log/g3log.hpp>

#include <OHARBaseLayer/ProcessorNode.h>

#include <OHARStudentLayer/PlainStudentFileHandler.h>
#include <OHARStudentLayer/StudentNetInputHandler.h>
#include <OHARStudentLayer/StudentNetOutputHandler.h>
#include <OHARStudentLayer/StudentHandler.h>
#include <OHARStudentLayer/GradingHandler.h>
#include <OHARStudentLayer/StudentWriterHandler.h>
#include <OHARStudentLayer/StudentDataItem.h>


BIDialog::BIDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BIDialog),
    node(nullptr)
{
    ui->setupUi(this);

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    connect(ui->pingButton, SIGNAL(clicked()), this, SLOT(onPingButtonClicked()));
    connect(ui->addStudentButton, SIGNAL(clicked()), this, SLOT(onAddDataButtonClicked()));
    connect(ui->readfileButton, SIGNAL(clicked()), this, SLOT(onReadFileButtonClicked()));

    if (QApplication::arguments().count() > 1) {
        config = QApplication::arguments().at(1);
    }
    //TODO: modify UI element names based on configuration.

    configureApp();
}

BIDialog::~BIDialog()
{
    delete ui;
    delete node;
}


bool BIDialog::configureApp()
{
    bool success = false;

    node = new OHARBase::ProcessorNode(config.toStdString(), this);
    using namespace OHARStudent;
    if (config =="BasicInfoConfig") {
        node->addHandler(new PlainStudentFileHandler(*node));
        node->addHandler(new StudentNetOutputHandler(*node));
        success = true;
    } else if (config == "ExerciseInfoConfig") {
        node->addHandler(new StudentNetInputHandler());
        node->addHandler(new StudentHandler(*node));
        node->addHandler(new StudentNetOutputHandler(*node));
        success = true;
    } else if (config == "ExamInfoConfig") {
        node->addHandler(new StudentNetInputHandler());
        node->addHandler(new StudentHandler(*node));
        node->addHandler(new StudentNetOutputHandler(*node));
        success = true;
    } else if (config == "ProjectInfoConfig") {
        node->addHandler(new StudentNetInputHandler());
        node->addHandler(new StudentHandler(*node));
        node->addHandler(new GradingHandler(*node));
        node->addHandler(new StudentWriterHandler(*node));
        success = true;
    } else {
        delete node;
        node = nullptr;
        showMessage("Unknown configuration, cannot configure node!");
        QMessageBox box;
        box.setText("Use a configuration file for the node!");
        box.exec();
    }
    return success;
}

void BIDialog::onStartButtonClicked()
{
    LOG(INFO) << "Start/stop button clicked.";
    if (node != nullptr) {
        if (!node->isRunning()) {
            showMessage("Starting the node.");
            node->start();
        } else {
            showMessage("Stopping the node...");
            node->stop();
            showMessage("Node stopped");
        }
    }
}


void BIDialog::onPingButtonClicked()
{
    showMessage("Sending ping");
    node->handleCommand("ping");
}

void BIDialog::onReadFileButtonClicked()
{
    showMessage("Start reading data from dataFile");
    node->handleCommand("readfile");
}

void BIDialog::onShutdownButtonClicked()
{

}

void BIDialog::onAddDataButtonClicked()
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
                //TODO: create a json object, not a student object.
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
    LOG(INFO) << "User message: " << message.toStdString();
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

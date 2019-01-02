#include "bidialog.h"
#include "ui_bidialog.h"
#include "qdir.h"
#include "qmessagebox.h"

#include <string>

#include <g3log/g3log.hpp>

#include <OHARBaseLayer/ProcessorNode.h>

#include <OHARStudentLayer/PlainStudentFileHandler.h>
#include <OHARStudentLayer/StudentInputHandler.h>
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

    configureApp();
}

BIDialog::~BIDialog()
{
    delete ui;
    delete node;
}


void BIDialog::configureApp()
{
    node = new OHARBase::ProcessorNode(config.toStdString(), this);
    if (configureNode()) {
        setWindowTitle(config);
        //TODO: modify UI element names based on configuration.
        if (config =="BasicInfoConfig") {
            // labels in .ui file are for Basic config, no need to change anything here.
        } else {
            ui->label3rdItem->hide();
            ui->studyProgram->hide();
            if (config == "ExerciseInfoConfig") {
                ui->label2ndItem->setText("Exercise points, comma separated:");
            } else if (config == "ExamInfoConfig") {
                ui->label2ndItem->setText("Exam points (one number):");
            } else if (config == "ProjectInfoConfig") {
                ui->label2ndItem->setText("Project points (one number):");
            }
        }

    } else {
        delete node;
        node = nullptr;
        this->setWindowTitle("No configuration provided");
        showMessage("Unknown configuration, cannot configure node!");
        QMessageBox box;
        box.setText("Use a configuration file for the node. See user guide for details.");
        box.exec();
    }
    refreshUI();
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
    LOG(INFO) << "***** Add data button clicked";
    QString id = ui->studentId->text();
    if (id.length() > 0)
    {
        QString element2ndText = ui->edit2nd->text();
        if (element2ndText.length() > 0)
        {
            QString studyProgram = ui->studyProgram->text();
            if (studyProgram.length() > 0)
            {
                LOG(INFO) << "Creating a data Package to send...";
                OHARBase::Package p;
                p.setType((OHARBase::Package::Data));
                LOG(INFO) << "Creating a json student structure with proper elements...";
                std::string json("{ \"id\" : \"");
                json += id.toStdString() + "\", ";
                if (config =="BasicInfoConfig") {
                    json += " \"name\" : \"" + element2ndText.toStdString() + "\",";
                    json += " \"studyprogram\" : \"" + studyProgram.toStdString() + "\"";
                } else if (config == "ExerciseInfoConfig") {
                    json += "\"exercisepoints\" : [" + element2ndText.toStdString() + "]";
                } else if (config == "ExamInfoConfig") {
                    json += "\"exampoints\" : " + element2ndText.toStdString();
                } else if (config == "ProjectInfoConfig") {
                    json += "\"courseprojectpoints\" : " + element2ndText.toStdString();
                }
                json += " }";
                LOG(INFO) << "JSON data is: " + json;
                LOG(INFO) << "Handing over the json data string to the Package...";
                p.setData(json);

/*
 {
   "id" : 12345,
   "name" : "Test Student",
   "studyprogram" : "TOL",
   "exampoints" : 15,
   "exercisepoints" : 8,
   "courseprojectpoints" : 16,
   "grade" : 3
}
 */
                LOG(INFO) << "Telling node to pass to handlers";
                node->passToHandlers(p);
            }
        }
    }
}

bool BIDialog::configureNode()
{
    bool success = false;
    if (config.length() > 0) {
        QString configFile = QDir::homePath() + "/StudentPassing/" + config + ".txt";
        showMessage("Reading configuration from " + configFile);
        if (node->configure(configFile.toStdString())) {
            using namespace OHARStudent;
            if (config =="BasicInfoConfig") { // First node
                node->addHandler(new PlainStudentFileHandler(*node));
                node->addHandler(new StudentInputHandler());
                node->addHandler(new StudentNetOutputHandler(*node));
                success = true;
            } else if (config == "ExerciseInfoConfig") { // middle node
                node->addHandler(new StudentInputHandler());
                node->addHandler(new StudentHandler(*node));
                node->addHandler(new StudentNetOutputHandler(*node));
                success = true;
            } else if (config == "ExamInfoConfig") { // middle node
                node->addHandler(new StudentInputHandler());
                node->addHandler(new StudentHandler(*node));
                node->addHandler(new StudentNetOutputHandler(*node));
                success = true;
            } else if (config == "ProjectInfoConfig") { // last node
                node->addHandler(new StudentInputHandler());
                node->addHandler(new StudentHandler(*node));
                node->addHandler(new GradingHandler(*node));
                node->addHandler(new StudentWriterHandler(*node));
                success = true;
            }
        }
    } else {
        showMessage("No configuration file name in startup parameters!");
    }
    return success;
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
    if (node) {
        ui->startButton->setDisabled(false);
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
    } else {
        ui->startButton->setDisabled(true);
    }
}

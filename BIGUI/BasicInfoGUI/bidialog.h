#ifndef BIDIALOG_H
#define BIDIALOG_H

#include <QDialog>
#include <string>

#include <OHARBaseLayer/ProcessorNodeObserver.h>

namespace Ui {
class BIDialog;
}

namespace OHARBase {
class ProcessorNode;
}

class BIDialog : public QDialog, public OHARBase::ProcessorNodeObserver
{
    Q_OBJECT

public:
    explicit BIDialog(QWidget *parent = nullptr);
    ~BIDialog();

    void NodeEventHappened(EventType e, const std::string & message);

private:
    bool configureNode();

    void showMessage(const QString & message);

    void refreshUI();

private slots:
    void onStartButtonClicked();
    void onPingButtonClicked();
    void onReadFileButtonClicked();
    void onShutdownButtonClicked();
    void onAddStudentButtonClicked();

private:
    Ui::BIDialog *ui;
    OHARBase::ProcessorNode * node;
};

#endif // BIDIALOG_H

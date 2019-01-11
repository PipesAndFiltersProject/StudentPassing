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
    void configureApp();
    bool configureNode();

    void showMessage(const QString & message);

    void refreshUI();

    void doShutdown();

private slots:
    void onStartButtonClicked();
    void onPingButtonClicked();
    void onAddDataButtonClicked();
    void onReadFileButtonClicked();
    void onShutdownButtonClicked();
    void handleNodeEvent(EventType e, QString message);

private:
    Ui::BIDialog *ui;
    OHARBase::ProcessorNode * node;
    QString config;
};

#endif // BIDIALOG_H

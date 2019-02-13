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

Q_DECLARE_METATYPE(OHARBase::ProcessorNodeObserver::EventType)

class BIDialog : public QDialog, public OHARBase::ProcessorNodeObserver
{
    Q_OBJECT

public:
    explicit BIDialog(QWidget *parent = nullptr);
    virtual ~BIDialog() override;

    /** Implements the ProcessorNodeObserver interface. */
    void NodeEventHappened(OHARBase::ProcessorNodeObserver::EventType e, const std::string & message) override;

signals:
    void nodeEvent(OHARBase::ProcessorNodeObserver::EventType e, QString message);

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
    void handleNodeEvent(OHARBase::ProcessorNodeObserver::EventType e, QString message);

private:
    Ui::BIDialog *ui;
    /** The processor node this GUI is running. */
    OHARBase::ProcessorNode * node;
    /** The name of the configuration this node is running. */
    QString config;
};

#endif // BIDIALOG_H

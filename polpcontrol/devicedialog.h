#ifndef DEVICEDIALOG_H
#define DEVICEDIALOG_H

#include <QDialog>
#include <plugins.h>

namespace Ui {
class DeviceDialog;
}

class DeviceDialog : public QDialog
{
    Q_OBJECT
    explicit DeviceDialog(QWidget *parent = 0);
public:
    ~DeviceDialog();
    static QString getDeviceID(Device*, QWidget *parent, bool *ok, QString *title);
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DeviceDialog *ui;
    bool isAccepted;
};

#endif // DEVICEDIALOG_H

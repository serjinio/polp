#include "devicedialog.h"
#include "ui_devicedialog.h"

#include <QStringListModel>
#include "plugins.h"
#include <QPushButton>

static DeviceDialog* dialog;

DeviceDialog::DeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceDialog)
{
    ui->setupUi(this);
}

DeviceDialog::~DeviceDialog()
{
    delete ui;
}

QString DeviceDialog::getDeviceID(Device *dev , QWidget* parent, bool*ok, QString *title){
    if(dialog==NULL)
        dialog = new DeviceDialog();
    dialog->setParent(0);
    dialog->setModal(true);
    QStringListModel model(dialog->ui->listView);
    model.setStringList(dev->devices());
    dialog->ui->listView->setModel(&model);
    dialog->ui->lineEdit->setText(*(title));
    if(model.stringList().empty()){
        dialog->ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }else{
        dialog->ui->listView->selectionModel()->select(model.index(0,0),QItemSelectionModel::Select);
    }
    dialog->exec();
    QString res;
    if(dialog->isAccepted){
        res = model.stringList().at(dialog->ui->listView->selectionModel()->selectedIndexes().at(0).row());
        *(title)=dialog->ui->lineEdit->text();
    }
    *(ok) = dialog->isAccepted;
    return res;
}

void DeviceDialog::on_buttonBox_accepted()
{
    isAccepted= true;
    close();
}

void DeviceDialog::on_buttonBox_rejected(){
    isAccepted = false;
    close();
}

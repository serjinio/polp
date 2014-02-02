#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "project.h"
#include "pluginmanager.h"
#include "projectmanager.h"
#include "devicedialog.h"

#include <QProgressBar>
#include <QSignalMapper>
#include <QThread>
#include <QInputDialog>
#include<QDialog>
#include <QComboBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow){
    currentData = NULL;
    ui->setupUi(this);
    ui->projectView->setModel(new ProjectModel(ui->projectView));
    connect(ui->projectView->selectionModel(),
          SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
          this, SLOT(handleSelectionChanged(QItemSelection)));
    ui->leftsplitter->setStretchFactor(0, 0);
    ui->leftsplitter->setStretchFactor(1, 1);
    ui->viewsplitter->setStretchFactor(0, 1);
    ui->viewsplitter->setStretchFactor(1, 0);
    ui->analesersplitter->setStretchFactor(0, 1);
    ui->analesersplitter->setStretchFactor(1, 0);
    ui->toolsplitter->setStretchFactor(0, 1);
    ui->toolsplitter->setStretchFactor(1, 0);
    loadViews();
    loadAnalysers();
    loadSimulations();
    loadDevices();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionOpen_triggered(){
}



void MainWindow::loadViews(){
    QSignalMapper* mapper = new QSignalMapper(this);
    QList<View*> views = PluginManager::instance()->views().values();
    Q_FOREACH(View* view, views){
        ui->viewstackedWidget->addWidget(view->viewPane());
        QAction* action = new QAction(view->title(),this);
        ui->menuView->addAction(action);
        connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
        mapper->setMapping(action,view->title());
    }
    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(view_selected(QString)));
    view_selected("Simple view");
}

void MainWindow::loadAnalysers(){
    //TODO:://loadAnalysers
    analyserBox = new QComboBox(ui->mainToolBar);
    QList<Analyser*> analysers = PluginManager::instance()->analysers().values();
    Q_FOREACH(Analyser* analyser, analysers){
        QVariant v = qVariantFromValue((void*)analyser);
        analyserBox->addItem(analyser->title(),v);
        if(analyser->controlPane()!=NULL){
            ui->analyserstackedWidget->addWidget(analyser->controlPane());
        }
    }
    connect(analyserBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onAnalyserBoxIndexChanged(int)));
    ui->mainToolBar->addWidget(analyserBox);
    analyserBox->setCurrentIndex(0);
    onAnalyserBoxIndexChanged(0);
}

void MainWindow::loadSimulations(){
    QSignalMapper* mapper = new QSignalMapper(this);
    QList<Simulation*> simulations = PluginManager::instance()->simulations();
    Q_FOREACH(Simulation* sim, simulations){
        QAction* action = new QAction(sim->title(),this);
        ui->menuSimulation->addAction(action);
        connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
        mapper->setMapping(action,sim->title());
    }
    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(simulation_add(QString)));
}

void MainWindow::loadDevices(){
    QSignalMapper* mapper = new QSignalMapper(this);
    QList<Device*> devices = PluginManager::instance()->devices();
    Q_FOREACH(Device* dev,devices){
        QAction* action = new QAction(dev->deviceClass(),this);
        ui->menuDevice->addAction(action);
        connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
        mapper->setMapping(action,dev->deviceClass());
    }
    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(device_add(QString)));
}

void MainWindow::displayData(Data *data){
    if(data!=NULL){
        if(currentView->setData(data)){
            QMessageBox::information(this,"Error",currentView->error());
        }
    }
}

void MainWindow::analyse(){
    QList<Data*> datalist;
    Q_FOREACH(const QModelIndex &index, ui->projectView->selectionModel()->selectedIndexes()){
        ProjectItem* item = (ProjectItem*)(ui->projectView->model()->data(index,Qt::UserRole).value<void*>());
        item->analyser = currentAnalyser;
        datalist.append(item->data);
    }
    if(datalist.size()==1){
       currentData = currentAnalyser->analyse(datalist.at(0));
    }else if (datalist.size()>1){
       currentData = currentAnalyser->analyse(datalist);
    }
    displayData(currentData);
}

void MainWindow::view_selected(QString viewtitle){
    currentView = PluginManager::instance()->findView(viewtitle);
    Q_FOREACH(const QModelIndex &index, ui->projectView->selectionModel()->selectedIndexes()){
        ProjectItem* item = (ProjectItem*)(ui->projectView->model()->data(index,Qt::UserRole).value<void*>());
        item->view = currentView;
    }
    displayData(currentData);
    ui->viewstackedWidget->setCurrentWidget(currentView->viewPane());
}

void MainWindow::simulation_add(QString simulationtitle){
    Simulation* sim = PluginManager::instance()->findSimulation(simulationtitle);
    bool ok = 0;
    QString text(sim->title());
     text = QInputDialog::getText(this,"New Simulation","Simulation name",QLineEdit::Normal,text, &ok);
    if(ok){
        Data2D* data = new Data2D(ProjectManager::instance()->currentProject());
        data->setParameter("title",text);
        sim->predefineDataParametres(data);
        ProjectManager::instance()->currentProject()->addItem(data,sim);
    }
}

void MainWindow::device_add(QString devicetitle){
    Device* dev = PluginManager::instance()->findDevice(devicetitle);
    bool ok = 0;
    QString text(dev->deviceClass());
    QString devid = DeviceDialog::getDeviceID(dev,this,&ok,&text);
    if(ok){
        Data2D* data = new Data2D(ProjectManager::instance()->currentProject());
        data->setParameter("title",text);
        data->setParameter("deviceID",devid);
        ProjectManager::instance()->currentProject()->addItem(data,dev);
    }
}

void MainWindow::handleSelectionChanged(QItemSelection item){
    //SET Contron pane here:
    analyse();
}

void MainWindow::onAnalyserBoxIndexChanged(int i){
    currentAnalyser = (Analyser*)analyserBox->currentData().value<void*>();
    if(currentAnalyser->controlPane()==NULL){
        ui->analyserstackedWidget->hide();
    }else{
        ui->analyserstackedWidget->show();
        ui->analyserstackedWidget->setCurrentWidget(currentAnalyser->controlPane());
    }
    analyse();
}

void MainWindow::on_actionNew_triggered(){
    ProjectManager::instance()->newProject();
}

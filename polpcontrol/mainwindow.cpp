#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "project.h"
#include "pluginmanager.h"

#include <QProgressBar>
#include <QSignalMapper>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->projectView->setModel(new ProjectModel(this));
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
    ui->viewstackedWidget->setCurrentWidget(PluginManager::instance()->findView("Simple view")->viewPane());
}

void MainWindow::loadAnalysers(){

}

void MainWindow::loadSimulations(){
    QSignalMapper* mapper = new QSignalMapper(this);

}

void MainWindow::loadDevices(){

}

void MainWindow::view_selected(QString viewtitle){
    View * view = PluginManager::instance()->findView(viewtitle);
    //TODO:: view->setData();
    //TODO:: projectitem.view = view
    ui->viewstackedWidget->setCurrentWidget(view->viewPane());
}

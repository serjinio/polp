#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "project.h"
#include "pluginmanager.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionOpen_triggered(){
    qDebug("test");
    startTimer(2000);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    QApplication::alert(this);
    QApplication::beep();
    killTimer(event->timerId());
}

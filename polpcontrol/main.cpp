#include "mainwindow.h"
#include <QApplication>
#include "pluginmanager.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    PluginManager::instance()->loadPlugins();
    MainWindow w;

    w.show();
    return a.exec();
}

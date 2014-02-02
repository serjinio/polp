#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "plugins.h"

class PluginManager
{
private:
    PluginManager();
public:
    static PluginManager* instance();

    void loadPlugins();
    QMap<QString, View *> views();
    QMap<QString, Analyser*> analysers();
    QMap<QString, Tool *> tools();

    QList<FileFormat*> fileFormats();
    QList<Device*> devices();
    QList<Simulation *> simulations();

    View *findView(QString key);
    Simulation * findSimulation(QString title);
    Device *findDevice(QString title);

private:
    void loadPlugin(QObject* plugin);

    QMap<QString, View*> _views;
    QMap<QString, Analyser*> _analysers;
    QMap<QString, Tool*> _tools;

    QList<FileFormat*> _fileFormats;
    QList<Device*> _devices;
    QList<Simulation*> _simulations;

};


#endif // PLUGINMANAGER_H

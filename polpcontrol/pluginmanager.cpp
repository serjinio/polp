#include "pluginmanager.h"
#include <QDir>
#include <QPluginLoader>
#include <QApplication>
#include <simplesim.h>
#include <simpledevice.h>
#include "simpleview.h"
#include "simpleanalyser.h"

static PluginManager* manager = NULL;

PluginManager::PluginManager(){
}

PluginManager* PluginManager::instance(){
    if(manager == NULL){
        manager = new PluginManager;
    }
    return manager;
}

void PluginManager::loadPlugins(){
    loadPlugin(new SimpleView);
    loadPlugin(new SimpleAnalyser);
    loadPlugin(new SimpleSim);
    loadPlugin(new SimpleDevice);
    QDir pluginsDir = QDir(qApp->applicationDirPath());
        qDebug("%s", pluginsDir.absolutePath().toLocal8Bit().data());
    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
            pluginsDir.cdUp();
    #elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
    #endif
        pluginsDir.cd("plugins");
        QStringList filelist = pluginsDir.entryList(QDir::Files);
        Q_FOREACH (QString fileName, filelist) {
                qDebug("%s",fileName.toLocal8Bit().data());
                QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
                QObject *plugin = loader.instance();
                if (plugin) {
                       PluginCollection *tmp =  qobject_cast<PluginCollection *>(plugin);
                       if(tmp){
                            QList<QObject*> plugins  = tmp->plugins();
                            Q_FOREACH(QObject* plg,plugins){
                                loadPlugin(plg);
                            }
                       }else{
                           loadPlugin(plugin);
                       }
                }else{
                    qDebug("Failed to load %s",fileName.toLocal8Bit().data());
                }
        }
}

QMap<QString, View *> PluginManager::views(){
    return _views;
}

QMap<QString, Analyser *> PluginManager::analysers(){
    return _analysers;
}

QMap<QString, Tool *> PluginManager::tools(){
    return _tools;
}

QList<FileFormat *> PluginManager::fileFormats(){
    return _fileFormats;
}

QList<Device *> PluginManager::devices(){
    return _devices;
}

QList<Simulation *> PluginManager::simulations(){
    return _simulations;
}

View *PluginManager::findView(QString key){
    if(_views.contains(key)){
        return _views.value(key);
    }
    return _views.value("Simple view");
}

Simulation *PluginManager::findSimulation(QString title){
    Q_FOREACH(Simulation * sim, _simulations){
        if(title == sim->title())
            return sim;
    }
    qDebug("ERROR:: PluginManager :: Simulation not found");
    return NULL;
}

Device *PluginManager::findDevice(QString title){
Q_FOREACH(Device * dev, _devices){
    if(title == dev->deviceClass())
        return dev;
}
qDebug("ERROR:: PluginManager :: Device not found");
return NULL;
}

void PluginManager::loadPlugin(QObject *plugin){
    if(qobject_cast<View*>(plugin)!=NULL){
        View* o = qobject_cast<View*>(plugin);
        QString key = o->title();
        _views.insert(key,o);
    }else if(qobject_cast<Tool*>(plugin)!=NULL){
        Tool* o = qobject_cast<Tool*>(plugin);
        QString key = o->title();
        _tools.insert(key,o);
    }
    else if(qobject_cast<Analyser*>(plugin)!=NULL){
        Analyser* o = qobject_cast<Analyser*>(plugin);
        QString key = o->title();
        _analysers.insert(key,o);
    }
    else if(qobject_cast<Simulation*>(plugin)!=NULL){
        _simulations.append(qobject_cast<Simulation*>(plugin));
    }
    else if(qobject_cast<FileFormat*>(plugin)!=NULL){
        _fileFormats.append(qobject_cast<FileFormat*>(plugin));
    }else if(qobject_cast<Device*>(plugin)!=NULL){
        _devices.append(qobject_cast<Device*>(plugin));
    }else{
        qDebug("Unknown plugin class");
    }
}

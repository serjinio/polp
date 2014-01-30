#include "project.h"
#include "pluginmanager.h"

Project::Project(QObject *parent) :
    QObject(parent)
{
}

void Project::addItem(Data *data, Simulation *sim){
    SimulationProjectItem * item = new SimulationProjectItem;
    item->data = data;
    item->simulation = sim;
    item->view = PluginManager::instance()->findView(sim->preferedView());
    _items.append(item);
    _status = Unsaved;
    emit projectChanged();
}

void Project::addItem(Data *data, Device *dev){
    DeviceProjectItem * item = new DeviceProjectItem;
    item->data = data;
    item->device = dev;
    item->view = PluginManager::instance()->findView(dev->preferedView());
    _items.append(item);
    _status = Unsaved;
    emit projectChanged();
}

void Project::addItem(Data *data,QString preferedview){
    ProjectItem * item = new ProjectItem;
    item->data = data;
    item->view = PluginManager::instance()->findView(preferedview);
    _items.append(item);
    _status = Unsaved;
    emit projectChanged();
}

void Project::removeItem(ProjectItem *item){
    _items.removeOne(item);
    _status = Unsaved;
    emit projectChanged();
}


ProjectItem::ProjectItem(QObject *parent):QObject(parent){
   analyser =NULL;
   data = NULL;
   view =NULL;
}

void ProjectItem::itemSelected(){

}

QWidget *ProjectItem::control()
{
    return NULL;
}


SimulationProjectItem::SimulationProjectItem(QObject *parent):ProjectItem(parent){
    simulation=NULL;
}

void SimulationProjectItem::itemSelected(){
    //TODO::
}

QWidget *SimulationProjectItem::control() //TODO::
{
    return NULL;
}


DeviceProjectItem::DeviceProjectItem(QObject *parent):ProjectItem(parent){
    device = NULL;
}

void DeviceProjectItem::itemSelected(){
    if(device!=NULL)
        device->loadData(data);
}

QWidget *DeviceProjectItem::control(){
    if(device!=NULL){
        return device->controlPane();
    }
}



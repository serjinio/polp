#include "project.h"
#include "pluginmanager.h"
#include "projectmanager.h"

Project::Project(QObject *parent) :
    QObject(parent)
{
}

QList<ProjectItem *> Project::items(){
    return _items;
}

void Project::addItem(Data *data, Simulation *sim){
    SimulationProjectItem * item = new SimulationProjectItem(this);
    item->title = data->parameter("title").toString();
    item->data = data;
    item->simulation = sim;
    item->view = PluginManager::instance()->findView(sim->preferedView());
    _items.append(item);
    _status = Unsaved;
    emit projectChanged();
}

void Project::addItem(Data *data, Device *dev){
    DeviceProjectItem * item = new DeviceProjectItem(this);
    item->data = data;
    item->device = dev;
    item->title = data->parameter("title").toString();
    item->view = PluginManager::instance()->findView(dev->preferedView());
    _items.append(item);
    _status = Unsaved;
    emit projectChanged();
}

void Project::addItem(Data *data,QString preferedview){
    ProjectItem * item = new ProjectItem(this);
    item->data = data;
    item->title = data->parameter("title").toString();
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

ProjectItem::~ProjectItem(){
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

QWidget *SimulationProjectItem::control() {//TODO::
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


ProjectModel::ProjectModel(QObject *parent):QAbstractListModel(parent){

    connect(ProjectManager::instance(),SIGNAL(projectChanged()),this,SLOT(onProjectChanged()));
}

ProjectModel::~ProjectModel(){
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
            return QVariant();
    if ( role == Qt::DisplayRole ) {
        Project* project = ProjectManager::instance()->currentProject();
        return project->items().at(index.row())->title;
    } if(role ==Qt::UserRole){
        Project* project = ProjectManager::instance()->currentProject();
        QVariant v;
        v.setValue<void*>(project->items().at(index.row()));
        return v;
    }
    return QVariant();
}

QVariant ProjectModel::headerData(int selection, Qt::Orientation orientation, int role) const{
    return "Project";
}

int ProjectModel::rowCount(const QModelIndex &parent) const{
    Project* project = ProjectManager::instance()->currentProject();  
    return project->items().size();
}

bool ProjectModel::insertRows(int position, int rows, const QModelIndex &parent){
    return false; //TODO::
}

bool ProjectModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    Project* project = ProjectManager::instance()->currentProject();
    if(project!=NULL){
        for(int row = 0; row < rows; ++row){
            project->removeItem(project->items().at(position));
        }
     }
        endRemoveRows();
        return true;
}

bool ProjectModel::setData(const QModelIndex &index, const QVariant &value, int role){
    return false; //TODO::
}

Qt::ItemFlags ProjectModel::flags(const QModelIndex &index) const{
    if(!index.isValid())
            return Qt::ItemIsEditable;
    return QAbstractListModel::flags(index) |  Qt::ItemIsSelectable;
}

void ProjectModel::onProjectChanged(){
    QModelIndex _left = createIndex(0,0);
    QModelIndex _right = createIndex(ProjectManager::instance()->currentProject()->items().size()-1,0);
    emit dataChanged(_left,_right);
}



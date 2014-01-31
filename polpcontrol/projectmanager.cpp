#include "projectmanager.h"

static ProjectManager* manager=NULL;

ProjectManager::ProjectManager(QObject *parent) :QObject(parent){
    _currentProject=NULL;
    newProject();
}

ProjectManager* ProjectManager::instance(){
    if(manager == NULL){
        manager = new ProjectManager();
    }
    return manager;
}

void ProjectManager::loadFromFile(QString file){
    //TODO:: implement loadFromFile
    qDebug("Not implemented ProjectManager::loadFromFile");
}

Project *ProjectManager::currentProject(){
    return _currentProject;
}

Project *ProjectManager::newProject(){
    //TODO:: Add checking for need of saving
    // Save project
    if(_currentProject!=NULL){
        delete _currentProject;
    }
    _currentProject = new Project();
    connect(_currentProject,SIGNAL(projectChanged()),this,SLOT(onProjectChanged()));
    _currentProject->filename = "untitled";
    emit projectChanged();
    return _currentProject;
}

void ProjectManager::saveCurrentProject(){
    //TODO:: implement loadFromFile
    qDebug("Not implemented ProjectManager::saveCurrentProject");
}

void ProjectManager::onProjectChanged(){
    emit projectChanged();
}

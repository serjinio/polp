#include "projectmanager.h"

static ProjectManager* manager=NULL;

ProjectManager::ProjectManager() {
    _currentProject = 0;
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
    _currentProject = new Project();
    return _currentProject;
}

void ProjectManager::saveCurrentProject(){
    //TODO:: implement loadFromFile
    qDebug("Not implemented ProjectManager::saveCurrentProject");
}

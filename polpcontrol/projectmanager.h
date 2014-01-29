#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H


#include "project.h"

class ProjectManager {
private:
     ProjectManager();
public:
     static ProjectManager *instance();
     void loadFromFile(QString file);
     Project* currentProject();
     Project* newProject();
     void saveCurrentProject();
private:
     Project* _currentProject;
};

#endif // PROJECTMANAGER_H

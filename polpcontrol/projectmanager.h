#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H


#include "project.h"

class ProjectManager :public QObject {
    Q_OBJECT
private:
     ProjectManager(QObject *parent=0);
public:
     static ProjectManager *instance();
     void loadFromFile(QString file);
     Project* currentProject();
     Project* newProject();
     void saveCurrentProject();
private:
     Project* _currentProject;

public:
signals:
     void projectChanged();

private slots:
     void onProjectChanged();
};

#endif // PROJECTMANAGER_H

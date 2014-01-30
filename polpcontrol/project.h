#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include "plugins.h"
#include "data.h"

class ProjectItem : public QObject{
public:
    explicit ProjectItem(QObject *parent = 0);
    QString title;
    Data* data;
    View* view;
    Analyser* analyser;
    virtual void itemSelected();
    virtual QWidget* control();
};

class SimulationProjectItem :public ProjectItem{
public:
    explicit SimulationProjectItem(QObject *parent = 0);
    Simulation* simulation;
    virtual void itemSelected();
    virtual QWidget* control();
};

class DeviceProjectItem :public ProjectItem{
public:
    explicit DeviceProjectItem(QObject *parent = 0);
    Device* device;
    virtual void itemSelected();
    virtual QWidget* control();
};


class Project : public QObject
{
    Q_OBJECT
    friend class ProjectManager;
public:
    explicit Project(QObject *parent = 0);
    QList<ProjectItem*> items();
    enum Status{
      Saved,
      Unsaved
    };

    void addItem(Data* data, Simulation *sim);
    void addItem(Data* data, Device *dev);
    void addItem(Data* data, QString preferedview);
    void removeItem(ProjectItem* item);
    Status status();

signals:
    void projectChanged();
public slots:

private:
    QString filename;
    QList<ProjectItem*> _items;
    Status _status;
};

#endif // PROJECT_H

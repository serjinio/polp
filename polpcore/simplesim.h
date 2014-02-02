#ifndef SIMPLESIM_H
#define SIMPLESIM_H

#include <QObject>
#include "plugins.h"

class SimpleSim : public QObject, public Simulation
{
    Q_OBJECT
    Q_INTERFACES(Simulation)
public:
    explicit SimpleSim(QObject *parent = 0);
    virtual QString title();
    virtual Data *simulate(Data* data);
    virtual QString preferedView();
    virtual void predefineDataParametres(Data* data);
signals:

public slots:

};

#endif // SIMPLESIM_H

#include "simplesim.h"

SimpleSim::SimpleSim(QObject *parent) :
    QObject(parent)
{
}

QString SimpleSim::preferedView()
{
    return "";
}

void SimpleSim::predefineDataParametres(Data *data){
    Data2D * d = (Data2D*)data;
    data->setParameter("sim_A",5);
    data->setParameter("sim_B",10);
    for(int i=0; i<100;i++){
        d->addPoint("test",i,i*i);
    }
}

Data *SimpleSim::simulate(Data *data){

    return data;
}

QString SimpleSim::title()
{
    return "Simple Sim";
}

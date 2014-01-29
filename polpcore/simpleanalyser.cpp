#include "simpleanalyser.h"

SimpleAnalyser::SimpleAnalyser(QObject *parent) :QObject(parent){
    data = new Data2D(this);
}

QString SimpleAnalyser::title(){
    return "<None>";
}

QWidget *SimpleAnalyser::controlPane(){
    return NULL;
}

Data *SimpleAnalyser::analyse(Data *data){
    return data;
}

Data *SimpleAnalyser::analyse(QList<Data *> dataset){
    if(dataset.isEmpty())
        return data;
    return dataset.at(0);
}

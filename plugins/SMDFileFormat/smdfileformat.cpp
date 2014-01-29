#include "smdfileformat.h"

SMDFileFormat::SMDFileFormat(QObject *parent):QObject(parent){
}

QString SMDFileFormat::extension(){
    return "smd";
}

QString SMDFileFormat::description(){
    return "smd";
}

int SMDFileFormat::loadData(Data *data){
// if !qobject_cast<Data2D*>(data) else error "Wrong data format"
// create file to open data.parameter("filename")
// if QVariant not QString error "wronf file name"
// open file , read file ,fill data2d obj(curve1 = real , curve=image),
//
// use startEdit(), addPoint(), setParameter(), stopEdit()


}

int SMDFileFormat::saveData(Data *data){
// if !qobject_cast<Data2D*>(data) else error "Wrong data format"
    // create file to open data.parameter("filename")
    // if QVariant not QString error "wronf file name"
    //  take first two curves from data2D(error if no 2curves)

}

QString SMDFileFormat::error(){
    return error_message;
}

QString SMDFileFormat::preferedView(){
    return "NMRView";
}

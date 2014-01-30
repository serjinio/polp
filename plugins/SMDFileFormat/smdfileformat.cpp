#include "smdfileformat.h"

#include <QTextStream>
#include <qfile.h>

SMDFileFormat::SMDFileFormat(QObject *parent):QObject(parent){
}

QString SMDFileFormat::extension(){
    return "smd";
}

QString SMDFileFormat::description(){
<<<<<<< HEAD
    return "Reads from and writes data in .smd format.";
=======
    //TODo:: add description
    return "smd";
>>>>>>> mev/master
}

int SMDFileFormat::loadData(Data *data){

    Data2D *data2d =  qobject_cast<Data2D*>(data);
    if (data2d == NULL) {
        this->error_message = "Error! Invalid data object provided.";
        return -1;
    }

    QString filename = data2d->parameter("filename").toString();
    if (validateFilename(filename) != 0) {
        return -1;
    }

    QFile file(filename);
    QTextStream inputDataStream(&file);

    QMap<QString, QString> headerParams = parseSMDHeader(inputDataStream);
    if (hasError()) {
        return -1;
    }

    QMap<QString, QVector<double> > dataPoints = parseSMDDataStream(inputDataStream);
    if (hasError()) {
        return -1;
    }

// if !qobject_cast<Data2D*>(data) else error "Wrong data format"
// create file to open data.parameter("filename")
// if QVariant not QString error "wronf file name"
// open file , read file ,fill data2d obj(curve1 = real , curve=image),
//
// use startEdit(), addPoint(), setParameter(), stopEdit()

    return 0;
}

int SMDFileFormat::saveData(Data *data){
// if !qobject_cast<Data2D*>(data) else error "Wrong data format"
    // create file to open data.parameter("filename")
    // if QVariant not QString error "wronf file name"
    //  take first two curves from data2D(error if no 2curves)

    return 0;
}

QString SMDFileFormat::error(){
    return error_message;
}

QString SMDFileFormat::preferedView(){
    return "NMRView";
}

QMap<QString, QString> SMDFileFormat::parseSMDHeader(QTextStream& stream)
{
    QMap<QString, QString> headerData;

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        if (line.isNull() || line.startsWith("#")) { // end of header
            break;
        }

        QStringList lstLine = line.split("=");
        if (lstLine.length() != 2) {
            this->error_message = "Invalid SMD header found.";
        }

        headerData.insert(lstLine.at(0), lstLine.at(1));
    }

    return headerData;
}

QMap<QString, QVector<double> > SMDFileFormat::parseSMDDataStream(QTextStream& stream)
{

}

int SMDFileFormat::validateFilename(QString filename)
{
    if (filename == NULL || filename.isEmpty()) {
        this->error_message = "'filename' parameter cannot be empty!";
        return -1;
    }

    QFile file(filename);
    if (!file.exists() || !file.isReadable()) {
        this->error_message = "Cannot open provided input file: " + filename;
        return -1;
    }

    return 0;
}

bool SMDFileFormat::hasError()
{
    if (!error_message.isNull()) {
        return true;
    } else {
        return false;
    }
}


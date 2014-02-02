#include "smdfileformat.h"

#include <QTextStream>
#include <qfile.h>

#include <qdebug.h>


SMDFileFormat::SMDFileFormat(QObject *parent):QObject(parent){
}

QString SMDFileFormat::extension(){
    return "*.smd";
}

QString SMDFileFormat::description(){
    return "Reads from and writes data in .smd format.";
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

    QMap<QString, QVariant> headerParams = parseSMDHeader(inputDataStream);
    if (hasError()) {
        return -1;
    }

    QMap<QString, QVector<double> > dataPoints = parseSMDDataStream(inputDataStream);
    if (hasError()) {
        return -1;
    }

    int length = headerParams["point"].toInt();
    int dwell = headerParams["dwell"].toDouble();
    QVector<double> time = makeTimeVector(dwell, length);

    // Populate output data object

    QVector<double> reals = dataPoints["real"];
    QVector<double> imags = dataPoints["imag"];

    data2d->startEdit();
    for (int i = 0; i < time.length(); i++) {
        data2d->addPoint("real", time[i], reals[i]);
        data2d->addPoint("imag", time[i], imags[i]);
    }

    for (QMap<QString, QVariant>::iterator it = headerParams.begin(); it != headerParams.end(); it++) {
        data2d->setParameter(it.key(), it.value());
    }
    data2d->stopEdit();

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

QMap<QString, QVariant> SMDFileFormat::parseSMDHeader(QTextStream& stream)
{
    QMap<QString, QVariant> headerData;

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        if (line.isNull() || line.startsWith("#")) { // end of header
            break;
        }

        QStringList lstLine = line.split("=");
        if (lstLine.length() != 2) {
            this->error_message = "Invalid SMD header found.";
            return headerData;
        }

        QString key = lstLine.at(0);
        QString rawValue = lstLine.at(1);

        qDebug() << "processing key: " << key << "; will convert: " << rawValue << " to double.";
        bool isConverted = false;
        double doubleValue = rawValue.toDouble(&isConverted);
        if (!isConverted) {
            this->error_message = "Cannot parse header data. It seems to be invalid!";
            return headerData;
        }

        headerData.insert(key, doubleValue);
    }

    return headerData;
}

QMap<QString, QVector<double> > SMDFileFormat::parseSMDDataStream(QTextStream& stream)
{
    QMap<QString, QVector<double> > pointsData;
    QVector<double> reals;
    QVector<double> imags;

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        if (line.isNull()) { // end of header
            break;
        }
        if (line.trimmed() == "") {
            continue; // skip empty lines
        }

        line = line.trimmed();
        qDebug() << "will parse the line: " << line;
        QStringList lstLine = line.split(" ");
        if (lstLine.length() != 2) {
            this->error_message = "Invalid data found.";
            return pointsData;
        }

        bool isConverted = false;

        double re = lstLine[0].toDouble(&isConverted);
        if (!isConverted) {
            this->error_message = "Invalid data point found: '" + lstLine[0] + "'.";
            return pointsData;
        }

        double im = lstLine[1].toDouble(&isConverted);
        if (!isConverted) {
            this->error_message = "Invalid data point found: '" + lstLine[1] + "'.";
            return pointsData;
        }

        reals.append(re);
        imags.append(im);
    }

    pointsData.insert("real", reals);
    pointsData.insert("imag", imags);
    qDebug() << "reals vector length: " << reals.length();
    qDebug() << "imags vector length: " << imags.length();

    return pointsData;
}

QVector<double> SMDFileFormat::makeTimeVector(int length, double dwell)
{
    QVector<double> time;
    double currentTime = 0.0;

    for (int i = 0; i < length; i++) {
        time.append(currentTime);
        currentTime += dwell;
    }

    return time;
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


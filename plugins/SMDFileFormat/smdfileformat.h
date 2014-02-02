#ifndef SMDFILEFORMAT_H
#define SMDFILEFORMAT_H

#include "smdfileformat_global.h"

#include "plugins.h"

#include <QTextStream>

class SMDFILEFORMATSHARED_EXPORT SMDFileFormat: public QObject , public FileFormat{
    Q_OBJECT
    Q_INTERFACES(FileFormat)
    Q_PLUGIN_METADATA(IID "SMDFileFormat.Plugin")
public:
    explicit SMDFileFormat(QObject *parent = 0);
    virtual QString extension();
    virtual QString description();
    virtual int loadData(Data* data);
    virtual int saveData(Data* data);
    virtual QString error();
    virtual QString preferedView();
protected:
    QTextStream getInputDataStream(QString filename);

    QMap<QString, QVariant> parseSMDHeader(QTextStream&);
    QMap<QString, QVector<double> > parseSMDDataStream(QTextStream&);
    QVector<double> makeTimeVector(int length, double dwell);

    int validateFilename(QString filename);
    bool hasError();
private:
    QString error_message;
};

#endif // SMDFILEFORMAT_H

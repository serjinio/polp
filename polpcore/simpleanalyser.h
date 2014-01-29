#ifndef SIMPLEANALYSER_H
#define SIMPLEANALYSER_H

#include <QObject>

#include "plugins.h"

class SimpleAnalyser : public QObject, public Analyser
{
    Q_OBJECT
    Q_INTERFACES(Analyser)
public:
    explicit SimpleAnalyser(QObject *parent = 0);

    virtual QString title();
    virtual QWidget * controlPane();
    virtual Data *analyse(Data* data);
    virtual Data *analyse(QList<Data*> dataset);
signals:

public slots:

private:
    Data2D* data;
};

#endif // SIMPLEANALYSER_H

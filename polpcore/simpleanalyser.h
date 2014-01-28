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

signals:

public slots:

};

#endif // SIMPLEANALYSER_H

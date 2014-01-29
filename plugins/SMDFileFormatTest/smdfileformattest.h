#ifndef SMDFILEFORMATTEST_H
#define SMDFILEFORMATTEST_H

#include <QObject>

class SMDFileFormatTest : public QObject
{
    Q_OBJECT
private slots:
    void testParseSMDHeader();
};

#endif // SMDFILEFORMATTEST_H

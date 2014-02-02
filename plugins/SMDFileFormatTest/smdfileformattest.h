#ifndef SMDFILEFORMATTEST_H
#define SMDFILEFORMATTEST_H

#include <QObject>
#include <smdfileformat.h>

class SMDFileFormatUT : public SMDFileFormat
{
    friend class SMDFileFormatTest;

    Q_OBJECT
};

class SMDFileFormatTest : public QObject
{
    Q_OBJECT
private slots:
    void testParseSMDHeader();
    void testParseSMDDataStream();

public:
};

#endif // SMDFILEFORMATTEST_H

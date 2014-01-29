#ifndef SMDFILEFORMATTEST_H
#define SMDFILEFORMATTEST_H

#include <QObject>

class SMDFileFormatTest : public QObject
{
    Q_OBJECT
public:
    explicit SMDFileFormatTest(QObject *parent = 0);

signals:

public slots:
    void testPaseSMDHeader();
};

#endif // SMDFILEFORMATTEST_H

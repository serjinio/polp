#include <iostream>
#include <QtTest/QtTest>
#include <qdebug.h>

#include "smdfileformattest.h"

#include "smdfileformat.h"

using namespace std;

QTEST_MAIN(SMDFileFormatTest)


void SMDFileFormatTest::testParseSMDHeader()
{
    SMDFileFormatUT smdFile;

    QString sampleKeys = "key1 = value1\n";
    sampleKeys += "key2   =   value2\n";
    sampleKeys += "# header finish";

    QTextStream stream(&sampleKeys);

    QMap<QString, QString> res = smdFile.parseSMDHeader(stream);

    /*qDebug() << "parameters map printout:";
    for (QMap<QString, QString>::iterator it = res.begin(); it != res.end(); ++it) {
        qDebug() << it.key() << ": " << it.value();
    }*/

    QCOMPARE(res["key1"], QString("value1"));
    QCOMPARE(res["key2"], QString("value3"));
}




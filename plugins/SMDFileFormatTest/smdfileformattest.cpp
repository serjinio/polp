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

    QString sampleKeys = "point=4096\n";
    sampleKeys += "dw=1.000000\n";
    sampleKeys += "# header finish";

    QTextStream stream(&sampleKeys);

    QMap<QString, QVariant> res = smdFile.parseSMDHeader(stream);
    if (smdFile.hasError()) {
        qDebug() << smdFile.error();
        QFAIL("Header parsing failed.");
    }

    qDebug() << "parameters map printout:";
    for (QMap<QString, QVariant>::iterator it = res.begin(); it != res.end(); ++it) {
        qDebug() << it.key() << ": " << it.value();
    }

    QCOMPARE(res["point"].toString(), QString("4096"));
    QCOMPARE(res["dw"].toString(), QString("1"));
}

void SMDFileFormatTest::testParseSMDDataStream()
{
    SMDFileFormatUT smdFile;

    QString sampleData = "0.070000003325 0.004000000190 \n";
    sampleData += "0.104000004940 0.004000000190\n";

    QTextStream stream(&sampleData);

    QMap<QString, QVector<double> > res = smdFile.parseSMDDataStream(stream);
    if (smdFile.hasError()) {
        qDebug() << smdFile.error();
        QFAIL("Error parsing data stream.");
    }

    QVector<double> reals = res["real"];
    QVector<double> imags = res["imag"];


    qDebug() << "reals print out: ";
    qDebug() << "reals vector length: " << reals.length();
    for (QVector<double>::iterator it = reals.begin(); it != reals.end(); ++it) {
        qDebug() << *it;
    }

    QCOMPARE(reals[0], 0.07);
    QCOMPARE(reals[1], 0.104);
}


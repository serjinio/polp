#include "smdfileformattest.h"

#include "smdfileformat.h"

#include <QtTest/QtTest>



SMDFileFormatTest::SMDFileFormatTest(QObject *parent)
{

}

void SMDFileFormatTest::testPaseSMDHeader()
{
    QCOMPARE("ok", "ok");
}

QTEST_MAIN(SMDFileFormatTest)

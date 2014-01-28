#include "mainwindow.h"
#include <QApplication>
#include "data.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    new Data2D();
    MainWindow w;
    w.show();
    return a.exec();
}

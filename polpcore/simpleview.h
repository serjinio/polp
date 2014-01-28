#ifndef SIMPLEVIEW_H
#define SIMPLEVIEW_H

#include <QObject>
#include <plugins.h>

class SimpleView : public QObject, public View
{
    Q_OBJECT
    Q_INTERFACES(View)
public:
    explicit SimpleView(QObject *parent = 0);

signals:

public slots:

};

#endif // SIMPLEVIEW_H

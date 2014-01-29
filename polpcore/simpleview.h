#ifndef SIMPLEVIEW_H
#define SIMPLEVIEW_H

#include <QObject>
#include <plugins.h>

namespace Ui {
class SimpleViewForm;
}

class SimpleView : public QWidget, public View
{
    Q_OBJECT
    Q_INTERFACES(View)
public:
    explicit SimpleView(QWidget *parent = 0);
    ~SimpleView();
    virtual QString title();
    virtual QWidget * viewPane();
    virtual int setData(Data* data);
    virtual QString error();
signals:

public slots:

private:
    QString error_message;
    Ui::SimpleViewForm* ui;
};

#endif // SIMPLEVIEW_H

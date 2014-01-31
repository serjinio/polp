#ifndef SIMULATIONCONTROLPANE_H
#define SIMULATIONCONTROLPANE_H

#include <QWidget>

namespace Ui {
class SimulationControlPane;
}

class SimulationControlPane : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationControlPane(QWidget *parent = 0);
    ~SimulationControlPane();

private:
    Ui::SimulationControlPane *ui;
};

#endif // SIMULATIONCONTROLPANE_H

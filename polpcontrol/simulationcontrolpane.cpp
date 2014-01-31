#include "simulationcontrolpane.h"
#include "ui_simulationcontrolpane.h"

SimulationControlPane::SimulationControlPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationControlPane)
{
    ui->setupUi(this);
}

SimulationControlPane::~SimulationControlPane()
{
    delete ui;
}

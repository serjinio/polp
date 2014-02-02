#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QItemSelection>
#include <QMainWindow>
#include <plugins.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    QComboBox * analyserBox;
    Analyser * currentAnalyser;
    View * currentView;
    Data * currentData;

    void loadViews();
    void loadAnalysers();
    void loadSimulations();
    void loadDevices();
    void displayData(Data* data);
    void analyse();

private slots:
    void view_selected(QString viewtitle);
    void simulation_add(QString simulationtitle);
    void device_add(QString devicetitle);
    void handleSelectionChanged(QItemSelection item);
    void onAnalyserBoxIndexChanged(int index);
};

#endif // MAINWINDOW_H

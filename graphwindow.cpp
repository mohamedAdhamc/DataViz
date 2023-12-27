#include "graphwindow.h"
#include "ui_graphwindow.h"

// Initialising the static variable
int GraphWindow::FigureCounter=0;

GraphWindow::GraphWindow(DataSet *DataSet,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);

    // Increment the figure counter:
    FigureCounter++;

    // Create the XY graph (setting te paramters of the dataset graph):
    SetGraphSetting(DataSet);

    // Setting the paramters of the figure:
    SetFigureSetting();

    // Setting the title of the figure
    this->setWindowTitle("Figure "+QString::number(FigureCounter));


}

GraphWindow::~GraphWindow()
{ // Called when the window of the figure is closed
    delete ui;
}

void GraphWindow::SetGraphSetting(DataSet *DataSet)
{ // Sets up the curve and plots it

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->addData(DataSet);
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(0)->setName(DataSet->getName());
    ui->customPlot->graph(0)->rescaleAxes();

}

void GraphWindow::SetFigureSetting()
{ // Sets up the properties of the figure (that contains the curve)

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

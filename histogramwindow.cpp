#include "histogramwindow.h"
#include "ui_histogramwindow.h"
#include <iostream>
#include <vector>

// Initialising the static variable
int HistogramWindow::FigureCounter=0;

HistogramWindow::HistogramWindow(DataSet *DataSet,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistogramWindow)
{
    ui->setupUi(this);

    // Install an event filter on CustomWidget
    ui->customPlot->installEventFilter(this);

    // Increment the figure counter:
    FigureCounter++;

    // Create the XY Histogram (setting te paramters of the dataset Histogram):
    SetHistogramSetting(DataSet);

    // Setting the paramters of the figure:
    SetFigureSetting();

    // Setting the title of the figure
    this->setWindowTitle("Figure "+QString::number(FigureCounter));
}

HistogramWindow::~HistogramWindow()
{ // Called when the window of the figure is closed
    delete ui;
}

void HistogramWindow::SetHistogramSetting(DataSet *DataSet)
{ // Sets up the curve and plots it
    std::cout << "histogram method called" << std::endl;
    ui->customPlot->addGraph();
    ui->customPlot->graph()->addData(DataSet);
    ui->customPlot->graph()->setPen(QPen(Qt::blue));
    ui->customPlot->graph()->setName(DataSet->getName());
    ui->customPlot->graph()->rescaleAxes();
}

void HistogramWindow::SetFigureSetting()
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

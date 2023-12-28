#include "histogramwindow.h"
#include "ui_histogramwindow.h"
#include "gsl/gsl_histogram.h"
#include <vector>

// Initialising the static variable
int HistogramWindow::FigureCounter=0;

HistogramWindow::HistogramWindow(DataSet *DataSet,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistogramWindow)
{
    ui->setupUi(this);

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
    const int kHistogramBinNumber= 10; // Number of bins in the histogram
    gsl_histogram * h = gsl_histogram_alloc (kHistogramBinNumber); // Creating an empty histogram with 10 bins
    double *val = DataSet->getPoint(0);
    double max_y = *(++val), min_y = max_y;
    double values[DataSet->Size()];
    double keys[DataSet->Size()];

    for (int i=0; i<DataSet->Size(); i++) {
        double* ValuePtr = DataSet->getPoint(i);
        double x_value= *(ValuePtr);
        double y_value= *(++ValuePtr);
        keys[i] = x_value;
        values[i] = y_value;
        if (y_value > max_y) max_y = y_value;
        if (y_value < min_y) min_y = y_value;
    }

    gsl_histogram_set_ranges_uniform(h, min_y, max_y); // Sets the limits of the histogram
    for (int i=0;i<DataSet->Size();i++) gsl_histogram_increment(h,values[i]); // Populating the histogram with data

    for (int i=0; i<kHistogramBinNumber;i++) qDebug() << gsl_histogram_get(h,i);
    QCPBars *barChart = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    for (int i=0; i< kHistogramBinNumber; i++) {
        barChart->addData(i, gsl_histogram_get(h,i));
    }

    barChart->setPen(QPen(Qt::blue));  // Set bar outline color
    barChart->setBrush(QBrush(Qt::blue));  // Set bar fill color

    ui->customPlot->rescaleAxes();
}

void HistogramWindow::SetFigureSetting()
{ // Sets up the properties of the figure (that contains the curve)

    // ui->customPlot->legend->setVisible(true);
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    ui->customPlot->xAxis->setLabel("bin");
    ui->customPlot->yAxis->setLabel("freq");
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

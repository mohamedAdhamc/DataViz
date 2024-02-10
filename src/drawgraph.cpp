#include "drawgraph.h"
#include "ui_drawgraph.h"
#include "parentwindow.h"
#include "datasetwindow.h"

DrawGraph::DrawGraph(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DrawGraph)
{
	ui->setupUi(this);

	// Create the XY graph (setting te paramters of the dataset graph):
	setGraphSettings();

	// Setting the paramters of the figure:
	SetFigureSetting();

	// Setting the title of the figure
	this->setWindowTitle("Figure "+QString::number(DataSet::datasets.size()+1));

	//connect clicked signal
	connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));

	setMinimumSize(300, 300);

}

DrawGraph::~DrawGraph()
{
	delete ui;
}

void DrawGraph::setGraphSettings()
{
	ui->customPlot->addGraph();
	//we are supposed to add data but we don't have none yet
	ui->customPlot->graph()->setPen(QPen(Qt::blue));
	ui->customPlot->graph()->setName("New Dataset" + DataSet::datasets.size()+1);
	ui->customPlot->graph()->rescaleAxes();
}

void DrawGraph::SetFigureSetting()
{ // Sets up the properties of the figure (that contains the curve)
	ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
	ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
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

void DrawGraph::clickedGraph(QMouseEvent *event)
{
	if (draw){
		QPoint point = event->pos();
		addPoint(ui->customPlot->xAxis->pixelToCoord(point.x()), ui->customPlot->yAxis->pixelToCoord(point.y()));
		plot();
	}
}

void DrawGraph::plot()
{
	ui->customPlot->graph(0)->setData(xpoints, ypoints);
	ui->customPlot->replot();
	ui->customPlot->update();
}

void DrawGraph::addPoint(double x, double y)
{
	xpoints.append(x);
	ypoints.append(y);
}

void DrawGraph::on_pushButton_clicked()
{
	//make a new file with the point and ask for name

	// Get the file location and name from the user
	QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", QDir::homePath(), "Text Files (*.txt)");

	// If the user cancels the file dialog, filePath will be empty
	if (filePath.isEmpty()) {
		qDebug() << "User canceled the operation.";
		return;
	}

	// Open the file for writing
	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Error opening the file for writing.";
		return;
	}

	// Write x and y values to the file
	QTextStream out(&file);
	for (int i = 0; i < qMin(xpoints.size(), ypoints.size()); ++i) {
		out << xpoints.at(i) << " " << ypoints.at(i) << "\n";
	}
	// Close the file
	file.close();

	qDebug() << "File saved successfully at:" << filePath;
	//make the dataset with the file

	// Creating a new dataset in the app:
	DataSet* AddedDataSet= new DataSet(filePath);
	if (AddedDataSet->IsDataSetValid) // Making sure the dataset is only dealt with if it was loaded succsessfully
	{

	ParentWindow::AllDataSets.push_back(AddedDataSet); // Addding a pointer to the new dataset so that it can be accessed by the rest of the app

	// Creat a subWindow for the loaded DataSet:
	ParentWindow::AddedDataSetWindow=new DataSetWindow(AddedDataSet,this);
	ParentWindow::subWindow=ParentWindow::WindowsManager->addSubWindow(ParentWindow::AddedDataSetWindow);
	ParentWindow::AddedDataSetWindow->show(); // showing the new dataset window to the user (when it is added for the first time)



	// To enable the ParentWindow to plot the dataset when the user clicks on XYPlot option in the context menu
	// of an already displayed DataSetWidnow
	connect(ParentWindow::AddedDataSetWindow,SIGNAL(Plot_XYPlot_SIGNAL(DataSet*)), ParentWindow::parentWindow, SLOT(GraphWindowToBePlotted(DataSet*)));
	connect(ParentWindow::AddedDataSetWindow,SIGNAL(Plot_Histogram_SIGNAL(DataSet*)),ParentWindow::parentWindow, SLOT(HistogramWindowToBePlotted(DataSet*)));
	}


}


void DrawGraph::on_checkBox_toggled(bool checked)
{
	draw = checked;
}


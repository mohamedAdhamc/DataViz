#include "parentwindow.h"
#include "ui_parentwindow.h"
#include <iostream>
#include <datasetsviewer.h>
#include <drawgraph.h>

//static member init
DataSet* ParentWindow::AddedDataSet=nullptr; // Temporary variable for dataset (usally has the latest added dataset)
DataSetWindow* ParentWindow::AddedDataSetWindow=nullptr;// Temporary variable for datasetwindow (usually has the latest created datasetwidnow)
QMdiSubWindow* ParentWindow::subWindow=nullptr;
QList<DataSet*> ParentWindow::AllDataSets;
QMdiArea* ParentWindow::WindowsManager = nullptr;
ParentWindow* ParentWindow::parentWindow = nullptr;

//class methods

ParentWindow::ParentWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::ParentWindow)
{
	ui->setupUi(this);
    Function_dlg=new FunctionDialog(this, &AllDataSets);
	connect(Function_dlg,SIGNAL(Plot_Function_SIGNAL(DataSet*)),this,SLOT(GraphWindowToBePlotted(DataSet*)));

	setCentralWidget(ui->WindowsManager);

	WindowsManager = ui->WindowsManager;

	parentWindow = this;
}

ParentWindow::~ParentWindow()
{ // This block is called when the app is closing (to clean up all memory allocation used when tha app started)
    delete AddedDataSetWindow;
    delete subWindow;
    delete AddedDataSet;
    delete ui;
}



void ParentWindow::on_actionLoad_Dataset_triggered()
{ // This block is called when the user triggers Load action to load a file


    // Opening a file dialog
    QString curPath=QDir::currentPath(); // Directs the "open file" to the current directory
    QString FileName=QFileDialog::getOpenFileName(this,tr("Open file"),curPath,tr("Text files (*.txt);;Images (*.png *.xpm *.jpg);;All files(*.*)"));


    if (FileName.isEmpty())
        return; //If no file is selected don't do anything further

    // Creating a new dataset in the app:
    AddedDataSet= new DataSet(FileName);
    if (AddedDataSet->IsDataSetValid) // Making sure the dataset is only dealt with if it was loaded succsessfully
    {

    AllDataSets.push_back(AddedDataSet); // Addding a pointer to the new dataset so that it can be accessed by the rest of the app

    // Creat a subWindow for the loaded DataSet:
    AddedDataSetWindow=new DataSetWindow(AddedDataSet,this);
    subWindow=ui->WindowsManager->addSubWindow(AddedDataSetWindow);
    AddedDataSetWindow->show(); // showing the new dataset window to the user (when it is added for the first time)



    // To enable the ParentWindow to plot the dataset when the user clicks on XYPlot option in the context menu
    // of an already displayed DataSetWidnow
    connect(AddedDataSetWindow,SIGNAL(Plot_XYPlot_SIGNAL(DataSet*)),this,SLOT(GraphWindowToBePlotted(DataSet*)));
    connect(AddedDataSetWindow,SIGNAL(Plot_Histogram_SIGNAL(DataSet*)),this,SLOT(HistogramWindowToBePlotted(DataSet*)));
    }


	//add the dataset to the toolbar

}

void ParentWindow::on_actionShow_DataSets_triggered()
{
	std::cout<<"testyoooo"<<Qt::endl;
	// Creat a subWindow :
	DatasetsViewer* ds=new DatasetsViewer(this);
	subWindow=ui->WindowsManager->addSubWindow(ds);
	ds->show(); // showing the new dataset window to the user (when it is added for the first time)
	connect(ds,SIGNAL(Plot_XYPlot_SIGNAL_Multiple(std::vector<DataSet*>)),this,SLOT(GraphWindowToBePlotted(std::vector<DataSet*>)));
}

void ParentWindow::on_actionDraw_Dataset_triggered()
{
	//make a new draw graph plot
	DrawGraph* addedDrawGraph = new DrawGraph(this);
	subWindow=ui->WindowsManager->addSubWindow(addedDrawGraph);
	addedDrawGraph->show();
}

void ParentWindow::GraphWindowToBePlotted(DataSet *ptr)
{ // This function is a slot that is called when the parentwindow is to plot a dataset in from a datasetwindow
	GraphWindow *AddedGraphWindow=new GraphWindow(ptr,this);
    subWindow=ui->WindowsManager->addSubWindow(AddedGraphWindow);
	AddedGraphWindow->show();
}

void ParentWindow::GraphWindowToBePlotted(std::vector<DataSet *> DataSet)
{
	GraphWindow *AddedGraphWindow=new GraphWindow(DataSet,this);
	subWindow=ui->WindowsManager->addSubWindow(AddedGraphWindow);
	AddedGraphWindow->show();
}

void ParentWindow::HistogramWindowToBePlotted(DataSet *ptr)
{ // This function is a slot that is called when the parentwindow is to plot a dataset in from a datasetwindow
    HistogramWindow *AddedHistogramWindow=new HistogramWindow(ptr,this);
    subWindow=ui->WindowsManager->addSubWindow(AddedHistogramWindow);
    AddedHistogramWindow->show();
}


void ParentWindow::on_actionAbout_triggered()
{ // This function is called when the user clicks on "About" option under "About" menu
    AboutDialog* About_dlg=new AboutDialog(this);
    About_dlg->exec();
    delete About_dlg;
}


void ParentWindow::on_actionHelp_triggered()
{// This function is called when the user clicks on "Help" option under "Help" menu
    HelpDialog* Help_dlg=new HelpDialog(this);
	Help_dlg->show();
}

void ParentWindow::on_actionFunction_triggered()
{// This function is called when the user clicks on "Function" option under "Analysis" menu
    Function_dlg->exec();
}


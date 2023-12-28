#include "graphwindow.h"
#include "ui_graphwindow.h"
#include <iostream>
#include <vector>

// Initialising the static variable
int GraphWindow::FigureCounter=0;

GraphWindow::GraphWindow(DataSet *DataSet,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);

	// Install an event filter on CustomWidget
	ui->customPlot->installEventFilter(this);

    // Increment the figure counter:
    FigureCounter++;

    // Create the XY graph (setting te paramters of the dataset graph):
    SetGraphSetting(DataSet);

    // Setting the paramters of the figure:
    SetFigureSetting();

    // Setting the title of the figure
    this->setWindowTitle("Figure "+QString::number(FigureCounter));

	// Constructing the context menu so it is ready to be called whenever
	ConstructContextMenu(ContextMenu);

	// connecting actions to responses via signal-slot mechanism:
	{
		//color change actions
		connect(changeColorRed, &QAction::triggered, this, [this]() {
			changeGraphColor(0, Qt::red);
		});
		connect(changeColorGreen, &QAction::triggered, this, [this]() {
			changeGraphColor(0, Qt::green);
		});
		connect(changeColorBlack, &QAction::triggered, this, [this]() {
			changeGraphColor(0, Qt::black);
		});
		connect(changeColorYellow, &QAction::triggered, this, [this]() {
			changeGraphColor(0, Qt::yellow);
		});
	}

	{
		//width change actions
		connect(changeWidth10, &QAction::triggered, this, [this]() {
			changeGraphLineWidth(0, 1);
		});
		connect(changeWidth3, &QAction::triggered, this, [this]() {
			changeGraphLineWidth(0, 3);
		});
		connect(changeWidth5, &QAction::triggered, this, [this]() {
			changeGraphLineWidth(0, 5);
		});
		connect(changeWidth10, &QAction::triggered, this, [this]() {
			changeGraphLineWidth(0, 10);
		});

	}

	{
		//line style change actions
		connect(lineStyleNone, &QAction::triggered, this, [this]() {
			changeGraphStyle(0, QCPGraph::lsNone);
		});
		connect(lineStyleLine, &QAction::triggered, this, [this]() {
			changeGraphStyle(0, QCPGraph::lsLine);
		});
		connect(lineStyleStepLeft, &QAction::triggered, this, [this]() {
			changeGraphStyle(0, QCPGraph::lsStepLeft);
		});
		connect(lineStyleStepCenter, &QAction::triggered, this, [this]() {
			changeGraphStyle(0, QCPGraph::lsStepCenter);
		});
		connect(lineStyleImpulse, &QAction::triggered, this, [this]() {
			changeGraphStyle(0, QCPGraph::lsImpulse);
		});
	}

}

GraphWindow::GraphWindow(std::vector<DataSet *>DataSet,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);

    // Install an event filter on CustomWidget
    ui->customPlot->installEventFilter(this);

    // Increment the figure counter:
    FigureCounter += DataSet.size();

    // Create the XY graph (setting te paramters of the dataset graph):
    SetGraphVectorSetting(DataSet);

    // Setting the paramters of the figure:
    SetFigureSetting();

    // Setting the title of the figure
    this->setWindowTitle("Figure "+QString::number(FigureCounter));

    // Constructing the context menu so it is ready to be called whenever
    ConstructContextMenu(ContextMenu);

    // connecting actions to responses via signal-slot mechanism:
    {
        //color change actions
        connect(changeColorRed, &QAction::triggered, this, [this]() {
            changeGraphColor(0, Qt::red);
        });
        connect(changeColorGreen, &QAction::triggered, this, [this]() {
            changeGraphColor(0, Qt::green);
        });
        connect(changeColorBlack, &QAction::triggered, this, [this]() {
            changeGraphColor(0, Qt::black);
        });
        connect(changeColorYellow, &QAction::triggered, this, [this]() {
            changeGraphColor(0, Qt::yellow);
        });
    }

    {
        //width change actions
        connect(changeWidth10, &QAction::triggered, this, [this]() {
            changeGraphLineWidth(0, 1);
        });
        connect(changeWidth3, &QAction::triggered, this, [this]() {
            changeGraphLineWidth(0, 3);
        });
        connect(changeWidth5, &QAction::triggered, this, [this]() {
            changeGraphLineWidth(0, 5);
        });
        connect(changeWidth10, &QAction::triggered, this, [this]() {
            changeGraphLineWidth(0, 10);
        });

    }

    {
        //line style change actions
        connect(lineStyleNone, &QAction::triggered, this, [this]() {
            changeGraphStyle(0, QCPGraph::lsNone);
        });
        connect(lineStyleLine, &QAction::triggered, this, [this]() {
            changeGraphStyle(0, QCPGraph::lsLine);
        });
        connect(lineStyleStepLeft, &QAction::triggered, this, [this]() {
            changeGraphStyle(0, QCPGraph::lsStepLeft);
        });
        connect(lineStyleStepCenter, &QAction::triggered, this, [this]() {
            changeGraphStyle(0, QCPGraph::lsStepCenter);
        });
        connect(lineStyleImpulse, &QAction::triggered, this, [this]() {
            changeGraphStyle(0, QCPGraph::lsImpulse);
        });
    }

}

GraphWindow::~GraphWindow()
{ // Called when the window of the figure is closed
    delete ui;
	delete ContextMenu;
	delete colorGrpah1;
	delete widthGrpah1;
	delete styleGrpah1;
}

void GraphWindow::SetGraphSetting(DataSet *DataSet)
{ // Sets up the curve and plots it

    ui->customPlot->addGraph();
    ui->customPlot->graph()->addData(DataSet);
    ui->customPlot->graph()->setPen(QPen(Qt::blue));
    ui->customPlot->graph()->setName(DataSet->getName());
    ui->customPlot->graph()->rescaleAxes();
}

void GraphWindow::SetGraphVectorSetting(std::vector<DataSet *>DataSet)
{ // Draw multiple datasets on the same graph
    std::vector<QPen> colours = {QPen(Qt::blue),QPen(Qt::red),QPen(Qt::yellow),QPen(Qt::black),QPen(Qt::green),QPen(Qt::magenta),QPen(Qt::cyan)};
    for (unsigned long i=0; i<DataSet.size(); i++) {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->addData(DataSet[i]);
        ui->customPlot->graph()->setPen(colours[i%colours.size()]);
        ui->customPlot->graph()->setName(DataSet[i]->getName());
        ui->customPlot->graph()->rescaleAxes();
    }
}

void GraphWindow::contextMenuEvent(QContextMenuEvent *event)
{
	std::cout<<__PRETTY_FUNCTION__<<std::endl;
// This function is called when the user right-clicks on the datasetwindow
	ContextMenu->popup(event->globalPos()); // displaying the menu where the user clicks
}

void GraphWindow::ConstructContextMenu(QMenu *)
{
// This function is called in the constructor to build the context menu so that it does not need to be built everytime from scratch
//	Graph1SubMenu->addAction(changeColor); // Add the action to the menu
	colorGrpah1->addAction(changeColorRed);
	colorGrpah1->addAction(changeColorBlack);
	colorGrpah1->addAction(changeColorGreen);
	colorGrpah1->addAction(changeColorYellow);

	widthGrpah1->addAction(changeWidth1);
	widthGrpah1->addAction(changeWidth3);
	widthGrpah1->addAction(changeWidth5);
	widthGrpah1->addAction(changeWidth10);

	styleGrpah1->addAction(lineStyleNone);
	styleGrpah1->addAction(lineStyleLine);
	styleGrpah1->addAction(lineStyleStepLeft);
	styleGrpah1->addAction(lineStyleStepCenter);
	styleGrpah1->addAction(lineStyleImpulse);


	Graph1SubMenu->addMenu(colorGrpah1);
	Graph1SubMenu->addMenu(styleGrpah1);
	Graph1SubMenu->addMenu(widthGrpah1);
	ContextMenu->addMenu(Graph1SubMenu); // Add the submenus to the main menu
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

void GraphWindow::changeGraphColor(int graphIndex, Qt::GlobalColor color){
	QPen pen = ui->customPlot->graph(graphIndex)->pen();
	pen.setColor(color);
	ui->customPlot->graph(graphIndex)->setPen(pen);
	ui->customPlot->replot();
}

void GraphWindow::changeGraphLineWidth(int graphIndex, int width)
{
	QPen pen = ui->customPlot->graph(graphIndex)->pen();
	pen.setWidth(width);
	ui->customPlot->graph(graphIndex)->setPen(pen);
	ui->customPlot->replot();
}

void GraphWindow::changeGraphStyle(int graphIndex, QCPGraph::LineStyle lineStyle)
{
	ui->customPlot->graph(graphIndex)->setLineStyle(lineStyle);
	ui->customPlot->replot();
}

bool GraphWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == ui->customPlot && event->type() == QEvent::ContextMenu) {
		return true;
	 }
	return QDialog::eventFilter(obj, event);;
}

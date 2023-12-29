#include "datasetsviewer.h"
#include <QVBoxLayout>
#include <iostream>
#include <QContextMenuEvent>
#include <parentwindow.h>
#include <vector>

QStandardItemModel* DatasetsViewer::model = new QStandardItemModel();


DatasetsViewer::DatasetsViewer(QWidget *parent)
	: QDialog{parent}
{

	QVBoxLayout* mainVBox = new QVBoxLayout(this);

	// Create a model for the list view
	//QStandardItemModel *model = new QStandardItemModel(this);

	// Set headers for the columns
	model->setHorizontalHeaderLabels({"Dataset Name", "Comment"});

	//add any new model data
	for (int i=0; i<DataSet::datasets.size(); i++) {
		if ((i+1) <= model->rowCount())
			continue;
		// Add data
		QStandardItem *itemName = new QStandardItem(DataSet::datasets[i]->getName());
		QStandardItem *itemComment = new QStandardItem();

		// Make the comment item editable
		itemComment->setFlags(itemComment->flags() | Qt::ItemIsEditable);
		itemName->setFlags(itemName->flags() & ~Qt::ItemIsEditable);
		QList<QStandardItem *> itemo ;
		itemo << itemName << itemComment;

		model->appendRow(itemo);
	}

	// Create the table view
	tableView = new QTableView;
	tableView->setModel(model);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::MultiSelection);

	mainVBox->addWidget(tableView);
	setLayout(mainVBox);


	//create menu
	ContextMenu->addAction(plotSelectedAction);
	//connect plotSelectedAction
	connect(plotSelectedAction,SIGNAL(triggered()),this,SLOT(DataSetToBePlotted()));

}

DatasetsViewer::~DatasetsViewer()
{
	//save the items in static var for later reuse
}

void DatasetsViewer::contextMenuEvent(QContextMenuEvent *event)
{
	ContextMenu->popup(event->globalPos()); // displaying the menu where the user clicks
}

void DatasetsViewer::DataSetToBePlotted()
{
	//get selected datasets
	QModelIndexList selectedIndexes = tableView->selectionModel()->selectedRows();
	QList<int> selectedRows;
	for (const QModelIndex &index : selectedIndexes) {
		selectedRows.append(index.row());
	}
	//now that we know selected rows construct the dataset vector
	std::vector<DataSet*> ds;
	for (int i: selectedRows)
		ds.push_back(DataSet::datasets[i]);
	emit Plot_XYPlot_SIGNAL_Multiple(ds);
}

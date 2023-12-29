#include "datasetsviewer.h"
#include <QTableView>
#include <QVBoxLayout>
#include <dataset.h>

QStandardItemModel* DatasetsViewer::model = new QStandardItemModel();


DatasetsViewer::DatasetsViewer(QWidget *parent)
	: QDialog{parent}
{

	QVBoxLayout* mainVBox = new QVBoxLayout(this);

	// Create a model for the list view
//	QStandardItemModel *model = new QStandardItemModel(this);

	// Set headers for the columns
	model->setHorizontalHeaderLabels({"Dataset Name", "Comment"});

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
	QTableView *tableView = new QTableView;
	tableView->setModel(model);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::MultiSelection);

	mainVBox->addWidget(tableView);
	setLayout(mainVBox);
}

DatasetsViewer::~DatasetsViewer()
{
	//save the items in static var for later reuse
}

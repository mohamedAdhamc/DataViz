#ifndef DATASETSVIEWER_H
#define DATASETSVIEWER_H

#include <QWidget>
#include <QDialog>
#include <QStandardItem>
#include <QMenu>
#include <QTableView>
#include <dataset.h>

class DatasetsViewer : public QDialog
{
	Q_OBJECT
public:
	explicit DatasetsViewer(QWidget *parent = nullptr);
	~DatasetsViewer();

	static QStandardItemModel *model;

private:
	QTableView *tableView;
	QList<QStandardItem *> items;
	QMenu *ContextMenu=new QMenu(this);
	QAction* plotSelectedAction=new QAction("plot selected datasets", this);

	void contextMenuEvent(QContextMenuEvent *event);

public slots:
	void DataSetToBePlotted();

signals:
	void Plot_XYPlot_SIGNAL_Multiple(std::vector<DataSet *> ptr); // A signal to tell the parent window that the user wants this DataSet to be plot
};

#endif // DATASETSVIEWER_H

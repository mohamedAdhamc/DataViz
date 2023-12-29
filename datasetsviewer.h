#ifndef DATASETSVIEWER_H
#define DATASETSVIEWER_H

#include <QWidget>
#include <QDialog>
#include <QStandardItem>

class DatasetsViewer : public QDialog
{
	Q_OBJECT
public:
	explicit DatasetsViewer(QWidget *parent = nullptr);
	~DatasetsViewer();

	static QStandardItemModel *model;

private:
	QList<QStandardItem *> items;

signals:

};

#endif // DATASETSVIEWER_H

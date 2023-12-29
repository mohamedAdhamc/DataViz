#ifndef CUSTOMITEMMODEL_H
#define CUSTOMITEMMODEL_H

#include <QWidget>

class CustomItemModel : public QStandardItemModel
{
public:
	CustomItemModel(QObject *parent = nullptr) : QStandardItemModel(parent) {}

	Qt::ItemFlags flags(const QModelIndex &index) const override
	{
		Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);

		if (index.column() == 1) // Make only the second column editable
			return defaultFlags | Qt::ItemIsEditable;

		return defaultFlags;
	}
};

#endif // CUSTOMITEMMODEL_H

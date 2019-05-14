#include "ShapeListModel.h"

ShapeListModel::ShapeListModel(const vector_t* list)
    : list{list} { }

int ShapeListModel::rowCount(const QModelIndex &) const
{
	return static_cast<int>(list->size());
}

QVariant ShapeListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || index.row() < 0)
		return QVariant{};
	
	if (index.row() >= static_cast<int>(list->size()))
		return "None";
	
	const Shape* s = (*list)[static_cast<size_t>(index.row())];
	
	switch (role) {
	case Qt::DisplayRole:
		return QString{"ID: %1; Type: %2"}.arg(s->getID()).arg(SHAPE_NAMES[s->getType()]);
		
	default:
		return QVariant{};
	}
}

void ShapeListModel::itemsChanged()
{
	this->endResetModel();
}


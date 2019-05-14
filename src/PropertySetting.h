#ifndef PROPERTYDELEGATE_H
#define PROPERTYDELEGATE_H

#include <QStyledItemDelegate>

// user interface delegate on the side --


class PropertySettings : public QStyledItemDelegate
{
	Q_OBJECT

public:

    PropertySettings(QObject* parent = nullptr);


	QWidget *createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	void setEditorData(QWidget* editor, const QModelIndex& index) const override;

	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

	void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	
private:
	Q_SIGNAL void valueChanged(QWidget*) const;
};
#endif // PROPERTYDELEGATE_H

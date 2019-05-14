#include "PropertySetting.h"

#include "FontComboBox.h"
#include "ItemProperty.h"

#include <QComboBox>
#include <QFontComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTreeWidget>

PropertySettings::PropertySettings(QObject *parent)
    : QStyledItemDelegate{parent}
{
	connect(this, &PropertySettings::valueChanged, this, &PropertySettings::commitData);
}


QWidget* createComboBox(QWidget* parent, const QStringList &source) {
	QComboBox* editor = new QComboBox{parent};
	editor->insertItems(0, source);
	editor->setEditable(false);
	return editor;
}

QWidget* PropertySettings::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex& index) const
{
	if (index.column() == 0) {
		return nullptr;
	}
	
	auto* tree = dynamic_cast<QTreeWidget*>(parent->parent());
	auto* item = tree->currentItem();
	int type = item->type();
	
	switch (type) {
	case PropInt: {
		auto *editor = new QSpinBox(parent);
		editor->setFrame(false);
		editor->setRange(0, 2000);
		return editor;
	}
	case PropString: {
		auto* editor = new QLineEdit(parent);
		return editor;
	}
	case PropAlignment:
		return createComboBox(parent, ALIGNMENT_NAMES.values());
	case PropBrushStyle:
		return createComboBox(parent, BRUSH_STYLE_NAMES.values());
	case PropColor:
		return createComboBox(parent, COLOR_NAMES.keys());
	case PropFont:
		return new QFontComboBox{parent};
	case PropFontSize:
        return new FontComboBox{parent};
	case PropFontStyle:
		return createComboBox(parent, FONT_STYLE_NAMES.values());
	case PropFontWeight:
		return createComboBox(parent, FONT_WEIGHT_NAMES.values());
	case PropPenStyle:
		return createComboBox(parent, PEN_STYLE_NAMES.values());
	case PropPenCapStyle:
		return createComboBox(parent, PEN_CAP_STYLE_NAMES.values());
	case PropPenJoinStyle:
		return createComboBox(parent, PEN_JOIN_STYLE_NAMES.values());
	}
	
	return nullptr;
}

#define TRY_CAST(type, var) auto* var = dynamic_cast<type*>(editor)

void PropertySettings::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (TRY_CAST(QFontComboBox, fontBox)) {
		QString value = index.model()->data(index, Qt::EditRole).toString();
		
		fontBox->setCurrentFont(QFont{value});
		connect(fontBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, std::bind(&PropertySettings::valueChanged, this, editor));
	}
	else if (TRY_CAST(QComboBox, comboBox)) {
		QString value = index.model()->data(index, Qt::EditRole).toString();
		
		comboBox->setCurrentText(value);
		connect(comboBox, &QComboBox::currentTextChanged, this, std::bind(&PropertySettings::valueChanged, this, editor));
	}
	else if (TRY_CAST(QSpinBox, spinBox)) {
		int value = index.model()->data(index, Qt::EditRole).toInt();
		
		spinBox->setValue(value);
		connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, std::bind(&PropertySettings::valueChanged, this, editor));
	}
	else if (TRY_CAST(QLineEdit, line)) {
		QString value = index.model()->data(index, Qt::EditRole).toString();
		
		line->setText(value);
		connect(line, &QLineEdit::textChanged, this, std::bind(&PropertySettings::valueChanged, this, editor));
	}
}

void PropertySettings::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (TRY_CAST(FontComboBox, sizeBox)) {
		int value = sizeBox->value();
		
		model->setData(index, value, Qt::EditRole);
	}
	if (TRY_CAST(QComboBox, comboBox)) {
		QString value = comboBox->currentText();
		
		model->setData(index, value, Qt::EditRole);
	}
	else if (TRY_CAST(QSpinBox, spinBox)) {
		spinBox->interpretText();
		int value = spinBox->value();
		
		model->setData(index, value, Qt::EditRole);
	}
	else if (TRY_CAST(QLineEdit, line)) {
		QString value = line->text();
		
		model->setData(index, value, Qt::EditRole);
	}
}

#undef TRY_CAST

void PropertySettings::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex&) const
{
	editor->setGeometry(option.rect);
}


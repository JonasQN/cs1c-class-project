#include "FontComboBox.h"

#include <QRegExp>

FontComboBox::FontComboBox(QWidget* parent)
    : QComboBox{parent}
{
	setEditable(true);
	for (int i = 6; i < 16; ++i) {
		addItem(QString{"%1"}.arg(i));
	}
	for (int i = 16; i < 29; i += 2) {
		addItem(QString{"%1"}.arg(i));
	}
	for (int i = 32; i < 59; i += 4) {
		addItem(QString{"%1"}.arg(i));
	}
	for (int i = 54; i < 73; i += 6) {
		addItem(QString{"%1"}.arg(i));
	}
	for (int i = 80; i < 97; i += 8) {
		addItem(QString{"%1"}.arg(i));
	}
	
    connect(this, &QComboBox::editTextChanged, this, &FontComboBox::validate);
}

void FontComboBox::validate()
{
	QString str = currentText();
	str.replace(QRegExp{"[^0-9]"}, "");
	setEditText(str);
	int index = findText(currentText());
	if (index >= 0) {
		setCurrentIndex(index);
	}
}

int FontComboBox::value()
{
	validate();
	return currentText().toInt();
}


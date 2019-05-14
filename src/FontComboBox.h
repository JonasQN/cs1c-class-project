#ifndef FONTSIZECOMBOBOX_H
#define FONTSIZECOMBOBOX_H

#include <QComboBox>

class FontComboBox : public QComboBox
{
	Q_OBJECT
	
public:
    FontComboBox(QWidget* parent = nullptr);
	
	void validate();
	int value();
};

#endif // FONTSIZECOMBOBOX_H

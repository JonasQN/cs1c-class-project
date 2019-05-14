#ifndef POSBUTTON_H
#define POSBUTTON_H

#include <QPushButton>
#include <QWidget>

namespace Ui {
class ItemButton;
}


class ItemButton : public QWidget
{
	Q_OBJECT
	
public:

	explicit ItemButton(const QList<QPair<QIcon, QString>> &buttons, QWidget *parent = nullptr);


	~ItemButton();
	
	QPushButton* button(int i);
	
signals:

	void clicked(int i);
	
private:
	QVector<QPushButton*> buttons;
	Ui::ItemButton *ui;
};

#endif // POSBUTTON_H

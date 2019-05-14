#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include <QDialog>

namespace Ui {
class DetailView;
}

class DetailView : public QDialog
{
	Q_OBJECT
	
public:

	explicit DetailView(const QString &text, QWidget *parent = nullptr);

	~DetailView();
	
private:
	Ui::DetailView *ui;
};

#endif // DETAILVIEW_H

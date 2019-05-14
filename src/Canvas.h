#ifndef CANVAS_H
#define CANVAS_H

#include "Storage.h"

#include <QWidget>

class Canvas : public QWidget
{
	Q_OBJECT

public:

	explicit Canvas(QWidget *parent = nullptr);

	void set_storage(const vector_t* vec);
	
signals:
	
public slots:

	void setSelected(int);
	
protected:

    void mousePressEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

	
private:
    const QImage target;
    int selection;
	const vector_t* shapes;


};

#endif // CANVAS_H

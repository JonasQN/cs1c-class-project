#include "Canvas.h"

#include "MainWindow.h"

#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), shapes{nullptr}, target{":/icons/target_small.png"}, selection{-1}
{
	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);
}

void Canvas::set_storage(const vector_t* vec)
{
	shapes = vec;
}

void Canvas::setSelected(int i)
{
	selection = i;
	update();
}

void Canvas::paintEvent(QPaintEvent */*event*/)
{
	static QPoint offset{target.size().width() / 2, target.size().height() / 2};
	if (shapes) {
		for (const Shape* shape : *shapes) {
			shape->draw(this);
		}
		
		if (selection >= 0 && selection < shapes->size()) {
			Shape* s = (*shapes)[selection];
			QPainter paint{this};
			QPen outline;
			outline.setStyle(Qt::DotLine);
			paint.setPen(outline);
			paint.drawRect(s->getRect().marginsAdded(QMargins{2, 2, 2, 2}));
			paint.drawImage(s->getPos() - offset, target);
		}
	}
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	if (event->button() & Qt::LeftButton) {
		dynamic_cast<MainWindow*>(window())->onCanvasClick(event->x(), event->y());
	}
}


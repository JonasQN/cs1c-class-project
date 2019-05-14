#include "Line.h"

#include <algorithm>

static QPoint center(QPoint &A, QPoint &B, const QPoint &offset)
{
	QPoint center = (A + offset + B + offset) / 2;
	A += offset - center;
	B += offset - center;
	return center;
}

Line::Line(const QPoint &a, const QPoint &b, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{QPoint{}, brush, pen, id}, startPoint{a}, endPoint{b}
{
	setPos(center(startPoint, endPoint, getPos()));
}

Line::Line(Line &&move) noexcept
    : Shape{id_t(-1)}
{
	swap(move);
	std::swap(startPoint, move.startPoint);
	std::swap(endPoint, move.endPoint);
}

Line::~Line() = default;

Line& Line::operator=(Line &&other) noexcept
{
	Line move{std::move(other)};
	swap(move);
	std::swap(startPoint, move.startPoint);
	std::swap(endPoint, move.endPoint);
	return *this;
}

void Line::draw(QPaintDevice* device) const
{
	auto paint = getPainter(device);
	
	paint->drawLine(startPoint, endPoint);
}

ShapeType Line::getType() const
{ return LineType; }

double Line::getPerimeter() const
{ return -1; }

double Line::getArea() const
{ return -1; }

QRect Line::getRect() const
{
	QRect rect{QPoint{std::min(startPoint.x(), endPoint.x()), std::min(startPoint.y(), endPoint.y())},
	           QPoint{std::max(startPoint.x(), endPoint.x()), std::max(startPoint.y(), endPoint.y())}};
	rect.moveCenter(getPos());
	return rect;
}

QPoint Line::getStart() const
{ return startPoint + getPos(); }

QPoint Line::getEnd() const
{ return endPoint + getPos(); }

void Line::setStart(const QPoint &start)
{
	startPoint = start - getPos();
	setPos(center(startPoint, endPoint, getPos()));
}

void Line::setEnd(const QPoint &end)
{
	endPoint = end - getPos();
	setPos(center(startPoint, endPoint, getPos()));
}


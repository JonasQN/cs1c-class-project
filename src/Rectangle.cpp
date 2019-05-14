#include "Rectangle.h"

#include <algorithm>

Rectangle::Rectangle(int width, int height, const QPoint& pos, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{pos, brush, pen, id}, w{width}, h{height}
{ }

Rectangle::Rectangle(const QRect &rect, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{rect.center(), brush, pen, id}, w{rect.width()}, h{rect.height()}
{ }

Rectangle::Rectangle(Rectangle &&move) noexcept
    : Shape{id_t(-1)}, w{0}, h{0}
{
	swap(move);
	std::swap(w, move.w);
	std::swap(h, move.h);
}

Rectangle::Rectangle(id_t id)
    : Shape{id}, w{0}, h{0}
{ }

Rectangle::~Rectangle() = default;

Rectangle& Rectangle::operator=(Rectangle &&other) noexcept
{
	Rectangle move{std::move(other)};
	swap(move);
	std::swap(w, move.w);
	std::swap(h, move.h);
	return *this;
}

void Rectangle::draw(QPaintDevice* device) const
{
	auto paint = getPainter(device);
	QRect rect = getRect();
	rect.moveCenter(QPoint{});
	
	paint->drawRect(rect);
}

ShapeType Rectangle::getType() const
{ return RectangleType; }

double Rectangle::getPerimeter() const
{ return std::abs(2 * w) + std::abs(2 * h); }

double Rectangle::getArea() const
{ return std::abs(w * h); }

QRect Rectangle::getRect() const
{
	QRect rect{0, 0, w, h};
	rect.moveCenter(getPos());
	return rect;
}

int Rectangle::getWidth() const
{ return w; }

int Rectangle::getHeight() const
{ return h; }

void Rectangle::setWidth(int width)
{ w = width; }

void Rectangle::setHeight(int height)
{ h = height; }

void Rectangle::setRect(const QRect &rect)
{
	setPos(rect.center());
	w = rect.width();
	h = rect.height();
}


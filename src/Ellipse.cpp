#include "Ellipse.h"

#include <algorithm>
#include <cmath>

Ellipse::Ellipse(int width, int height, const QPoint& pos, const QBrush &brush, const QPen &pen, id_t id)
    : Rectangle{width, height, pos, brush, pen, id}
{ }

Ellipse::Ellipse(const QRect &rect, const QBrush &brush, const QPen &pen, id_t id)
    : Rectangle{rect, brush, pen, id}
{ }

Ellipse::Ellipse(Ellipse &&move) noexcept
    : Rectangle{id_t(-1)}
{
	swap(move);
	std::swap(w, move.w);
	std::swap(h, move.h);
}

Ellipse::~Ellipse() = default;

Ellipse& Ellipse::operator=(Ellipse &&other) noexcept
{
	Ellipse move{std::move(other)};
	swap(move);
	std::swap(w, move.w);
	std::swap(h, move.h);
	return *this;
}

void Ellipse::draw(QPaintDevice* device) const
{
	auto paint = getPainter(device);
	QRect rect = getRect();
	rect.moveCenter(QPoint{});
	
	paint->drawEllipse(rect);
}

ShapeType Ellipse::getType() const
{ return EllipseType; }

const double pi = std::acos(-1);
double Ellipse::getPerimeter() const
{
	// https://www.mathsisfun.com/geometry/ellipse-perimeter.html
	// Approximation 3
	
	double a = std::abs(w) / 2.0;
	double b = std::abs(h) / 2.0;
	
	double h = ((a - b) * (a - b)) / ((a + b) * (a + b));
	
	return pi * (a + b) * (1 + (3 * h) / (10 + std::sqrt(4 - 3 * h)));
}

double Ellipse::getArea() const
{
	double a = std::abs(w) / 2.0;
	double b = std::abs(h) / 2.0;
	
	return pi * a * b;
}


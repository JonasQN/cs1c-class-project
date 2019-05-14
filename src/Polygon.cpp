#include "Polygon.h"

#include <algorithm>
#include <cmath>
#include <utility>

Polygon::Polygon(std::vector<QPoint> points, const QBrush &brush, const QPen &pen, id_t id)
    : PolyLine{std::move(points), brush, pen, id}
{ }

Polygon::Polygon(Polygon &&move) noexcept
    : PolyLine{id_t(-1)}
{
	swap(move);
	std::swap(points, move.points);
}

Polygon::~Polygon() = default;

Polygon& Polygon::operator=(Polygon &&other) noexcept
{
	Polygon move{std::move(other)};
	swap(move);
	std::swap(points, move.points);
	return *this;
}

void Polygon::draw(QPaintDevice* device) const
{
	auto paint = getPainter(device);
	
	paint->drawPolygon(points.data(), points.size());
}

ShapeType Polygon::getType() const
{ return PolygonType; }

double Polygon::getPerimeter() const
{
	double perimeter = 0;
	
	for (auto it = points.begin(); it != points.end(); ++it) {
		const QPoint &start = *it;
		const QPoint &end = (it+1 != points.end() ? *(it+1) : points.front());
		QPoint dist = start - end;
		perimeter += std::sqrt(QPoint::dotProduct(dist, dist));
	}
	
	return perimeter;
}

double Polygon::getArea() const
{
	// https://brilliant.org/wiki/irregular-polygons/#area-coordinate-geometry
	double area = 0;
	
	for (auto it = points.begin(); it != points.end(); ++it) {
		const QPoint &start = *it;
		const QPoint &end = (it+1 != points.end() ? *(it+1) : points.front());
		area += (start.x() * end.y()) - (start.y() * end.x());
	}
	
	return area / 2;
}


#include "PolyLine.h"

#include <algorithm>
#include <utility>
#include <utility>

PolyLine::PolyLine(std::vector<QPoint> points, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{QPoint{}, brush, pen, id}, points{std::move(points)}
{
	setCenter();
}

PolyLine::PolyLine(PolyLine &&move) noexcept
    : Shape{id_t(-1)}
{
	swap(move);
	std::swap(points, move.points);
}

PolyLine::~PolyLine() = default;

PolyLine& PolyLine::operator=(PolyLine &&other) noexcept
{
	PolyLine move{std::move(other)};
	swap(move);
	std::swap(points, move.points);
	return *this;
}

void PolyLine::draw(QPaintDevice* device) const
{
	auto paint = getPainter(device);
	
	paint->drawPolyline(points.data(), points.size());
}

ShapeType PolyLine::getType() const
{ return PolylineType; }

double PolyLine::getPerimeter() const
{ return -1; }

double PolyLine::getArea() const
{ return -1; }

QRect PolyLine::getRect() const
{
	QPoint start = (points.empty() ? QPoint{} : points[0]) + getPos();
	QRect rect{start, start};
	for (auto p : points) {
		rect.setLeft(  std::min(p.x() + getPos().x(), rect.left()));
		rect.setRight( std::max(p.x() + getPos().x(), rect.right()));
		rect.setTop(   std::min(p.y() + getPos().y(), rect.top()));
		rect.setBottom(std::max(p.y() + getPos().y(), rect.bottom()));
	}
	return rect;
}

std::size_t PolyLine::getCount() const
{ return points.size(); }

QPoint PolyLine::getPoint(std::size_t i) const
{ return points[i] + getPos(); }

void PolyLine::setPoint(std::size_t i, const QPoint &point)
{
	points[i] = point - getPos();
	setCenter();
}

void PolyLine::insert(size_t before, const QPoint &point)
{
	points.insert(points.begin() + before, point - getPos());
	setCenter();
}

void PolyLine::pushPoint(const QPoint &point)
{
	points.push_back(point - getPos());
	setCenter();
}

void PolyLine::erase(size_t i)
{
	points.erase(points.begin() + i);
	setCenter();
}

void PolyLine::clearPoints()
{
	points.clear();
	setCenter();
}

PolyLine::PolyLine(id_t id)
    : Shape{id}
{ }

void PolyLine::setCenter()
{
	QPoint old = getPos();
	setPos(getRect().center());
	QPoint offset = old - getPos();
	
	for (auto& p : points) {
		p += offset;
	}
}


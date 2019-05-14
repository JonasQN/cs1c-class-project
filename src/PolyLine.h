#ifndef POLYLINE_H
#define POLYLINE_H

#include "Shape.h"

#include <vector>


class PolyLine : public Shape
{
public:

	PolyLine(std::vector<QPoint> points = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);


	PolyLine(PolyLine &&move) noexcept;


	~PolyLine() override;
	

	PolyLine& operator=(PolyLine &&move) noexcept;

    ShapeType getType() const override;


    double getPerimeter() const override;

    double getArea() const override;

    QRect getRect() const override;

    std::size_t getCount() const;

    QPoint getPoint(std::size_t i) const;

    void setPoint(std::size_t i, const QPoint &point);

	void draw(QPaintDevice* device) const override;
	
	void insert(size_t before, const QPoint &point);

	void pushPoint(const QPoint &point);

	void erase(size_t i);

	void clearPoints();
	
protected:
	PolyLine(id_t id);
	void setCenter();
	std::vector<QPoint> points;
};

#endif // POLYLINE_H

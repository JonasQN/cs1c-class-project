#ifndef POLYGON_H
#define POLYGON_H

#include "PolyLine.h"


class Polygon : public PolyLine
{
public:

	Polygon(std::vector<QPoint> points = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

	Polygon(Polygon &&move) noexcept;

	~Polygon() override;

    ShapeType getType() const override;

    double getPerimeter() const override;

    double getArea() const override;

	Polygon& operator=(Polygon &&move) noexcept;

	void draw(QPaintDevice* device) const override;

};

#endif // POLYGON_H

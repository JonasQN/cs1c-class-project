#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Rectangle.h"


class Ellipse : public Rectangle
{
public:

	Ellipse(int width = 0, int height = 0, const QPoint& pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

	Ellipse(const QRect &rect, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

    Ellipse(Ellipse &&move) noexcept;

	~Ellipse() override;

    ShapeType getType() const override;

    double getPerimeter() const override;

    double getArea() const override;
	
	Ellipse& operator=(Ellipse &&move) noexcept;

	void draw(QPaintDevice* device) const override;

};

#endif // ELLIPSE_H

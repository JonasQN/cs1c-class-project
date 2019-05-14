#ifndef LINE_H
#define LINE_H

#include "Shape.h"


class Line : public Shape
{
public:

    Line(const QPoint& startPoint = {}, const QPoint& endPoint = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);


	Line(Line &&move) noexcept;


	~Line() override;
	
    ShapeType getType() const override;


    double getPerimeter() const override;


    double getArea() const override;


    QRect getRect() const override;


    QPoint getStart() const;


    QPoint getEnd() const;


    void setStart(const QPoint&);


    void setEnd(const QPoint&);

	Line& operator=(Line &&move) noexcept;

	void draw(QPaintDevice* device) const override;
	


	
private:
    QPoint startPoint;
    QPoint endPoint;
};

#endif // LINE_H

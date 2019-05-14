#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"


class Rectangle : public Shape
{
protected:
    Rectangle(id_t id);
    int w{0}, h{0};

public:
    Rectangle(int width = 0, int height = 0, const QPoint& pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
    Rectangle(const QRect &rect, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
    Rectangle(Rectangle &&move) noexcept;
    ~Rectangle() override;

    ShapeType getType() const override;
    double getPerimeter() const override;
    double getArea() const override;
    QRect getRect() const override;
    int getWidth() const;
    int getHeight() const;

    void setWidth(int w);
    void setHeight(int h);
    void setRect(const QRect&);

    void draw(QPaintDevice* device) const override;
    Rectangle& operator=(Rectangle &&move) noexcept;
};

#endif // RECTANGLE_H

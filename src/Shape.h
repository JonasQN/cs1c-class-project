#ifndef SHAPE_H
#define SHAPE_H

#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QPoint>

#include <memory>


enum ShapeType {
	LineType,        /**< \var enum value LineType. */
	PolylineType,    /**< \var enum value PolylineType. */
	PolygonType,     /**< \var enum value PolygonType. */
	RectangleType,   /**< \var enum value RectangleType. */
	EllipseType,     /**< \var enum value EllipseType. */
	TextType         /**< \var enum value TextType. */
};


extern const QMap<QString, QColor> COLOR_NAMES;
extern const QMap<ShapeType, QString> SHAPE_NAMES;
extern const QMap<Qt::BrushStyle, QString> BRUSH_STYLE_NAMES;
extern const QMap<Qt::PenStyle, QString> PEN_STYLE_NAMES;
extern const QMap<Qt::PenCapStyle, QString> PEN_CAP_STYLE_NAMES;
extern const QMap<Qt::PenJoinStyle, QString> PEN_JOIN_STYLE_NAMES;


class Shape
{
public:

	using id_t = unsigned int;


	Shape(const QPoint &pos = {}, const QBrush &brush = {}, QPen pen = {}, id_t id = 0);


	Shape(const Shape&) = delete;


	virtual ~Shape();


	Shape& operator=(const Shape&) = delete;


	bool operator==(const Shape &other) const;


	bool operator<(const Shape &other) const;


    virtual ShapeType getType() const = 0;


    virtual double getPerimeter() const = 0;


    virtual double getArea() const = 0;


    virtual QRect getRect() const = 0;


    const QPoint& getPos() const;


    const QBrush& getBrush() const;


    const QPen& getPen() const;


    id_t getID() const;


    void setPos(int x, int y);

    void setPos(const QPoint& pos);


    void setBrush(const QBrush&);


    void setPen(const QPen&);

	virtual void draw(QPaintDevice* device) const = 0;

	void move(int dx, int dy);




	static bool hasFill(ShapeType);
protected:

	Shape(id_t id);


	void swap(Shape &other) noexcept;


	std::unique_ptr<QPainter> getPainter(QPaintDevice* device) const;

private:

	QPoint pos;

	QBrush brush;

	QPen pen;

	static QPen id_pen;
	static QFont id_font;


	id_t id{0};
};

#endif // SHAPE_H

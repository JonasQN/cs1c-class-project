#include "Shape.h"

#include <QMap>

#include <algorithm>
#include <utility>

static unsigned int shape_id = 0;

#define COLOR_DEF(name) {#name, QColor{Qt::name}}
const QMap<QString, QColor> COLOR_NAMES {
	COLOR_DEF(white),
	COLOR_DEF(black),
	COLOR_DEF(red),
	COLOR_DEF(green),
	COLOR_DEF(blue),
	COLOR_DEF(cyan),
	COLOR_DEF(magenta),
	COLOR_DEF(yellow),
	COLOR_DEF(gray),
};
#undef COLOR_DEF

const QMap<ShapeType, QString> SHAPE_NAMES {
	{LineType, "Line"},
	{PolylineType, "Polyline"},
	{PolygonType, "Polygon"},
	{RectangleType, "Rectangle"},
	{EllipseType, "Ellipse"},
	{TextType, "Text"}
};

#define STYLE_DEF(name) {Qt::name, #name}
const QMap<Qt::BrushStyle, QString> BRUSH_STYLE_NAMES {
	STYLE_DEF(NoBrush),
	STYLE_DEF(SolidPattern),
	STYLE_DEF(Dense1Pattern),
	STYLE_DEF(Dense2Pattern),
	STYLE_DEF(Dense3Pattern),
    STYLE_DEF(HorPattern),
    STYLE_DEF(VerPattern),
    STYLE_DEF(CrossPattern),
    STYLE_DEF(BDiagPattern),
    STYLE_DEF(FDiagPattern),
    STYLE_DEF(DiagCrossPattern),
};

const QMap<Qt::PenStyle, QString> PEN_STYLE_NAMES {
	STYLE_DEF(NoPen),
	STYLE_DEF(SolidLine),
	STYLE_DEF(DashLine),
	STYLE_DEF(DotLine),
	STYLE_DEF(DashDotLine),
};

const QMap<Qt::PenCapStyle, QString> PEN_CAP_STYLE_NAMES {
	STYLE_DEF(SquareCap),
	STYLE_DEF(FlatCap),
	STYLE_DEF(RoundCap),
};

const QMap<Qt::PenJoinStyle, QString> PEN_JOIN_STYLE_NAMES {
	STYLE_DEF(BevelJoin),
	STYLE_DEF(MiterJoin),
	STYLE_DEF(RoundJoin),
};
#undef STYLE_DEF

Shape::Shape(const QPoint& pos, const QBrush &brush, QPen pen, id_t id)
    : pos{pos}, brush{brush}, pen{std::move(pen)}, id{id}
{
	if (id == 0) {
		this->id = ++shape_id;
	}
	else if (id != id_t(-1) && id > shape_id) {
		shape_id = id;
	}
}

Shape::Shape(id_t id)
    : Shape{QPoint{}, QBrush{}, QPen{}, id}
{ }

Shape::~Shape() = default;

bool Shape::operator==(const Shape &other) const
{ return id == other.id; }

bool Shape::operator<(const Shape &other) const
{ return id < other.id; }

void Shape::move(int dx, int dy)
{
	pos.rx() += dx;
	pos.ry() += dy;
}

const QPoint& Shape::getPos() const
{ return pos; }

const QBrush& Shape::getBrush() const
{ return brush; }

const QPen& Shape::getPen() const
{ return pen; }

auto Shape::getID() const -> id_t
{ return id; }

void Shape::setPos(int x, int y)
{
	pos.setX(x);
	pos.setY(y);
}

void Shape::setPos(const QPoint& pos)
{ this->pos = pos; }

void Shape::setBrush(const QBrush& brush)
{ this->brush = brush; }

void Shape::setPen(const QPen& pen)
{ this->pen = pen; }

bool Shape::hasFill(ShapeType type)
{
	return    type != LineType
	       && type != PolylineType
	       && type != TextType;
}

void Shape::swap(Shape &other) noexcept
{
	std::swap(pos, other.pos);
	std::swap(brush, other.brush);
	std::swap(pen, other.pen);
	std::swap(id, other.id);
}

// TODO
QPen Shape::id_pen{};
QFont Shape::id_font{};

std::unique_ptr<QPainter> Shape::getPainter(QPaintDevice* device) const
{
	std::unique_ptr<QPainter> paint{new QPainter{device}};
	
	paint->setPen(id_pen);
	paint->setFont(id_font);
	paint->drawText(getRect().topLeft() - QPoint{0, 4}, QString("ID: %1").arg(getID()));
	paint->translate(pos);
	
	paint->setBrush(brush);
	paint->setPen(pen);
	
	return paint;
}


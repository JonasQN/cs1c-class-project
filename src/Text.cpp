#include "Text.h"

#include <QMap>

#include <algorithm>
#include <utility>

#define STYLE_DEF(name) {Qt::name, #name}
const QMap<Qt::AlignmentFlag, QString> ALIGNMENT_NAMES {
	STYLE_DEF(AlignLeft),
	STYLE_DEF(AlignRight),
	STYLE_DEF(AlignTop),
	STYLE_DEF(AlignBottom),
	STYLE_DEF(AlignCenter),
};
#undef STYLE_DEF

#define FONT_STYLE_DEF(name) {QFont::name, #name}
const QMap<QFont::Style, QString> FONT_STYLE_NAMES {
	FONT_STYLE_DEF(StyleNormal),
	FONT_STYLE_DEF(StyleItalic),
	FONT_STYLE_DEF(StyleOblique),
};
const QMap<QFont::Weight, QString> FONT_WEIGHT_NAMES {
	FONT_STYLE_DEF(Thin),
	FONT_STYLE_DEF(ExtraLight),
	FONT_STYLE_DEF(Light),
	FONT_STYLE_DEF(Normal),
	FONT_STYLE_DEF(Medium),
	FONT_STYLE_DEF(DemiBold),
	FONT_STYLE_DEF(Bold),
	FONT_STYLE_DEF(ExtraBold),
	FONT_STYLE_DEF(Black),
};
#undef FONT_STYLE_DEF

Text::Text(QString str, const QFont &font, int w, int h, Qt::AlignmentFlag align, const QPoint &pos, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{pos, brush, pen, id}, str{std::move(str)}, font{font}, w{w}, h{h}, align{align}
{ }

Text::Text(Text &&move) noexcept
    : Shape{id_t(-1)}
{
	swap(move);
	std::swap(str, move.str);
	std::swap(font, move.font);
	std::swap(w, move.w);
	std::swap(h, move.h);
	std::swap(align, move.align);
}

Text::~Text() = default;

Text& Text::operator=(Text &&other) noexcept
{
	Text move{std::move(other)};
	swap(move);
	std::swap(str, move.str);
	std::swap(font, move.font);
	std::swap(w, move.w);
	std::swap(h, move.h);
	std::swap(align, move.align);
	return *this;
}

void Text::draw(QPaintDevice* device) const
{
	auto paint = getPainter(device);
	QRect rect = getRect();
	rect.moveCenter(QPoint{});
	
	paint->setFont(font);
	
	paint->drawText(rect, align, str);
}

ShapeType Text::getType() const
{ return TextType; }

double Text::getPerimeter() const
{ return -1; }

double Text::getArea() const
{ return -1; }

const QString& Text::getString() const
{ return str; }

void Text::setString(QString string)
{ str = std::move(string); }

const QFont& Text::getFont() const
{ return font; }

void Text::setFont(QFont f)
{ font = std::move(f); }

QRect Text::getRect() const
{
	QFontMetrics fm{font};
	QSize size{((w < 0) ? (int)(fm.width(str) * 1.1) : w), ((h < 0) ? (int)(fm.height() * 1.1) : h)};
	QRect rect{QPoint{}, size};
	
	rect.moveCenter(getPos());
	
	return rect;
}

void Text::setRect(const QRect &rect)
{
	setPos(rect.center());
	w = rect.width();
	h = rect.height();
}

int Text::getWidth() const
{ return w; }

void Text::setWidth(int width)
{ w = width; }

int Text::getHeight() const
{ return h; }

void Text::setHeight(int height)
{ h = height; }

Qt::AlignmentFlag Text::getAlign() const
{ return align; }

void Text::setAlign(Qt::AlignmentFlag a)
{ align = a; }


#include "arrange.h"

std::ostream& operator<<(std::ostream& out, const QString &str)
{
	return out << str.toStdString();
}

std::ostream& operator<<(std::ostream& out, const vector_t &shapes)
{
	for (Shape* shape : shapes) {
		out << "ShapeId: " << shape->getID() << "\n";
		out << "ShapeType: " << SHAPE_NAMES[shape->getType()] << "\n";
		out << "ShapeDimensions: ";
		
#define TRY_CAST(type) auto* cast = dynamic_cast<type*>(shape)
		if (TRY_CAST(Line)) {
			QPoint A = cast->getStart();
			QPoint B = cast->getEnd();
			out << A.x() << ", " << A.y() << ", " << B.x() << ", " << B.y() << "\n";
		}
		else if (TRY_CAST(PolyLine)) {
			for (size_t i = 0, count = cast->getCount(); i < count; ++i) {
				QPoint p = cast->getPoint(i);
				out << p.x() << ", " << p.y();
				if (i != count - 1) {
					out << ", ";
				}
			}
			out << "\n";
		}
		else if (TRY_CAST(Ellipse)) {
			QRect rect = cast->getRect();
			out << rect.x() << ", " << rect.y() << ", " << (rect.width() / 2) << ", " << (rect.height() / 2) << "\n";
		}
		else if (TRY_CAST(Rectangle)) {
			QRect rect = cast->getRect();
			out << rect.x() << ", " << rect.y() << ", " << rect.width() << ", " << rect.height() << "\n";
		}
		else if (TRY_CAST(Text)) {
			QRect rect = cast->getRect();
			out << rect.x() << ", " << rect.y() << ", " << rect.width() << ", " << rect.height() << "\n";
		}
		
		if (shape->getType() != TextType)
		{
			const QPen &pen = shape->getPen();
			out << "PenColor: " << COLOR_NAMES.key(pen.color()) << "\n";
			out << "PenWidth: " << pen.width() << "\n";
			out << "PenStyle: " << PEN_STYLE_NAMES[pen.style()] << "\n";
			out << "PenCapStyle: " << PEN_CAP_STYLE_NAMES[pen.capStyle()] << "\n";
			out << "PenJoinStyle: " << PEN_JOIN_STYLE_NAMES[pen.joinStyle()] << "\n";
		}
		
		if (Shape::hasFill(shape->getType()))
		{
			const QBrush &brush = shape->getBrush();
			out << "BrushColor: " << COLOR_NAMES.key(brush.color()) << "\n";
			out << "BrushStyle: " << BRUSH_STYLE_NAMES[brush.style()] << "\n";
		}
		
		if (TRY_CAST(Text)) {
			const QFont &font = cast->getFont();
			out << "TextString: " << cast->getString() << "\n";
			out << "TextColor: " << COLOR_NAMES.key(cast->getPen().color()) << "\n";
			out << "TextAlignment: " << ALIGNMENT_NAMES[cast->getAlign()] << "\n";
			out << "TextPointSize: " << font.pointSize() << "\n";
			out << "TextFontFamily: " << font.family() << "\n";
			out << "TextFontStyle: " << FONT_STYLE_NAMES[font.style()] << "\n";
			out << "TextFontWeight: " << FONT_WEIGHT_NAMES[static_cast<QFont::Weight>(font.weight())] << "\n";
		}
#undef TRY_CAST
		out << "\n";
	}
	
	return out;
}

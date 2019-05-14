#include "saveFile.h"

#include <Qt>
#include <QPen>
#include <QColor>
#include <QFont>
#include <QMap>

Shape* ReadLine(std::ifstream&, int id);
Shape* ReadPolyLine( std::ifstream&, int id);
Shape* ReadPolygon(std::ifstream&, int id);
Shape* ReadRectangle(std::ifstream&, int id);
Shape* ReadSquare(std::ifstream&, int id);
Shape* ReadEllipse(std::ifstream&, int id);
Shape* ReadCircle(std::ifstream&, int id);
Shape* ReadText(std::ifstream&, int id);

Qt::GlobalColor  getColor(const std::string&);
Qt::PenStyle     getPenStyle(const std::string&);
Qt::PenCapStyle  getCapStyle(const std::string&);
Qt::PenJoinStyle getPenJoinStyle(const std::string&);
Qt::BrushStyle   getBrushStyle(const std::string&);
QFont::Weight    getFontWeight(const std::string&);

const QMap<ShapeNames, std::string> INPUT_SHAPE_NAMES {
	{LINE, "Line"},
	{POLYLINE, "Polyline"},
	{POLYGON, "Polygon"},
	{RECTANGLE, "Rectangle"},
	{SQUARE, "Square"},
	{ELLIPSE, "Ellipse"},
	{CIRCLE, "Circle"},
	{TEXT, "Text"},
};

cs1c::vector<Shape*> LoadShapeFile()
{

    std::ifstream inFile;
    inFile.open("myShapes.txt");

    cs1c::vector<Shape*> myShapes;
    int id;


    while(inFile)
    {
		std::string typeStr;
		ShapeNames type;
        // takes us to the first data point
//        std::cout << std::endl;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        inFile >> id;
//        std::cout << "ID " << id << std::endl;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
		inFile >> typeStr;
		type = INPUT_SHAPE_NAMES.key(typeStr);

		if(inFile.eof()) {
			break;
		}
        

        switch(type)
        {
        case LINE:
            // parse the line part of the file
            myShapes.push_back(ReadLine(inFile, id));
            break;
        case POLYLINE:
            myShapes.push_back(ReadPolyLine(inFile, id));
            break;
        case POLYGON:
            myShapes.push_back(ReadPolygon(inFile, id));
            break;
        case RECTANGLE:
            myShapes.push_back(ReadRectangle(inFile, id));
            break;
        case SQUARE:
             myShapes.push_back(ReadSquare(inFile, id));
            break;
        case ELLIPSE:
             myShapes.push_back(ReadEllipse(inFile, id));
            break;
        case CIRCLE:
            myShapes.push_back(ReadCircle(inFile, id));
            break;
        case TEXT:
            myShapes.push_back(ReadText(inFile, id));
            break;
        default:
            std::cout << "error";
//            std::cin.get();
        }
    }
    inFile.close();

    return myShapes;
}

Shape* ReadLine(std::ifstream &inFile, int id)
{
    int x, y, x2, y2, width;
    std::string color, style, cap, join;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> x2;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y2;

//    std::cout << "Points: " << x << ' ' << y << ' ' << x2 << ' ' << y2 << std::endl;
    QPoint front(x, y);
    QPoint end (x2, y2);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    QBrush brush(lineColor);
    QPen   pen(brush, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    Line *line = new Line(front, end, brush, pen, id);
    return line;
}

Shape* ReadPolyLine( std::ifstream& inFile, int id)
{
    int width;
    std::string color, style, cap, join;
	std::vector<QPoint> points;

	inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
	do {
		int x, y;
		inFile.get();
		inFile >> x;
		inFile.get();
		inFile >> y;
		points.emplace_back(x, y);
	}
	while (inFile.peek() == ',');

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    QBrush brush(lineColor);
    QPen   pen(brush, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    PolyLine *polyLine = new PolyLine(points, brush, pen, id);
    return polyLine;
}

Shape* ReadPolygon(std::ifstream& inFile, int id)
{
    int width;
    std::string color, style, cap, join, brushStyle, brushColor;
	std::vector<QPoint> points;

	inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
	do {
		int x, y;
		inFile.get();
		inFile >> x;
		inFile.get();
		inFile >> y;
		points.emplace_back(x, y);
	}
	while (inFile.peek() == ',');

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    Polygon *polygon = new Polygon(points, brush, pen, id);
    return polygon;
}

Shape* ReadRectangle(std::ifstream& inFile, int id)
{
    int x, y, width;
    int l, w;
    std::string color, style, cap, join, brushStyle, brushColor;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> l;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> w;

//    std::cout << " Length: " << l << " Width: " << w << std::endl;
    QPoint point(x, y);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

	Rectangle *rectangle = new Rectangle(QRect{point, QSize{l, w}}, brush, pen, id);
    return rectangle;
}

Shape* ReadSquare(std::ifstream& inFile, int id)
{
    int x, y, width;
    int l;
    std::string color, style, cap, join, brushStyle, brushColor;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> l;

//    std::cout << " Length: " << l << std::endl;
    QPoint point(x, y);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

	Rectangle* square = new Rectangle(QRect{point, QSize{l, l}}, brush, pen, id);
    return square;
}

Shape* ReadEllipse(std::ifstream& inFile, int id)
{
    int x, y, width;
    int a, b;
    std::string color, style, cap, join, brushStyle, brushColor;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> a;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> b;

//    std::cout << " Semi A: " << a << " Semi B: " << b << std::endl;
    QPoint point(x, y);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

	Ellipse *ellipse = new Ellipse(QRect{point, QSize{a, b} * 2}, brush, pen, id);
    return ellipse;
}

Shape* ReadCircle(std::ifstream& inFile, int id)
{
    int x, y, width;
    int r;
    std::string color, style, cap, join, brushStyle, brushColor;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> r;

//    std::cout << " Radius: " << r << std::endl;
    QPoint point(x + r, y + r);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    Ellipse *circle = new Ellipse(r * 2, r * 2, point, brush, pen, id);
    return circle;
}

Shape* ReadText(std::ifstream& inFile, int id)
{
    int x, y, pointSize;
    unsigned int l, w;
    std::string color, style, fontStyle, join, brushStyle, brushColor, textStr, textAlign, fontFam, weight;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> l;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> w;

//    std::cout << " Length: " << l << " Width: " << w << std::endl;
    QPoint point(x, y);

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, textStr);
    QString txtStr(textStr.c_str());
//    std::cout << "Text String: " << textStr << std::endl;

    // TEXT COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor textColor(getColor(color));

    // TEXT ALLIGN
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> textAlign;
//    std::cout << "Text Align: " << textAlign << std::endl;

    // TEXT POINT SIZE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> pointSize;
//    std::cout << "Point Size: " << pointSize << std::endl;

    // TEXT FONT FAMILY
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, fontFam);
    QString famStr(fontFam.c_str());

    // TEXT FONT STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, fontStyle);

    // TEXT WEIGHT
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, weight);

    QBrush brush(textColor);
    QPen   pen(textColor);
    QFont  font(famStr.trimmed(), pointSize, getFontWeight(weight), false);
    pen.setCapStyle(getCapStyle(fontStyle));



	Text *text = new Text(txtStr.trimmed(), font, l, w, ALIGNMENT_NAMES.key(QString::fromStdString(textAlign)), point, brush, pen, id);
	QRect rect = text->getRect();
	rect.moveTopLeft(point);
	text->setRect(rect);
    return text;
}

#if 0
ShapeId: 8
ShapeType: Text
ShapeDimensions: 250, 425, 500, 50
TextString: Class Project 2 - 2D Graphics Modeler
TextColor: blue
TextAlignment: AlignCenter
TextPointSize: 10
TextFontFamily: Comic Sans MS
TextFontStyle: FlatCap
TextFontWeight: Normal
#endif

Qt::GlobalColor getColor(const std::string& color)
{
    switch(color[1])
    {
    case 'w':
        return Qt::GlobalColor::white;
    case 'b':
        if(color[3] == 'u')
        {
            return Qt::GlobalColor::blue;
        }
        return Qt::black;
    case 'r':
        return Qt::GlobalColor::red;
    case 'd':
        switch(color[5])
        {
            case 'R':
                 return Qt::GlobalColor::darkRed;
            case 'G':
                if(color[7] == 'e')
                {
                    return Qt::GlobalColor::darkGreen;
                }
                else
                {
                    return Qt::GlobalColor::darkGray;
                }
          case 'B':
            return Qt::GlobalColor::darkBlue;
          case 'C':
            return Qt::GlobalColor::darkCyan;
         case 'M':
            return Qt::GlobalColor::darkMagenta;
         case 'Y':
            return Qt::GlobalColor::darkYellow;
        default:
            return Qt::GlobalColor::black;
        }
    case 'g':
        if(color[3] == 'e')
        {
            return Qt::GlobalColor::green;
        }
        else
        {
            return Qt::GlobalColor::gray;
        }
    case 'c':
        return Qt::GlobalColor::cyan;
    case 'm':
        return Qt::GlobalColor::magenta;
    case 'y':
        return Qt::GlobalColor::yellow;
    default:
        return Qt::GlobalColor::black;
    }
}

Qt::PenStyle getPenStyle(const std::string& style)
{
    if(style == " SolidLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::SolidLine;
    }
    else if(style == " DashLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::DashLine;
    }
    else if(style == " DotLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::DotLine;
    }
    else if(style == " DashDotLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::DashDotLine;
    }
    else if(style == " DashDotDotLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::DashDotDotLine;
    }
    else if(style == " CustomDashLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::CustomDashLine;
    }
    else
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::SolidLine;
    }
}

Qt::PenCapStyle getCapStyle(const std::string& capStyle)
{
    switch(capStyle[1])
    {
    case 'S':
//        std::cout << "Cap Style:" << capStyle << std::endl;
        return Qt::SquareCap;
    case 'F':
//         std::cout << "Cap Style:" << capStyle << std::endl;
        return Qt::FlatCap;
    case 'R':
//         std::cout << "Cap Style:" << capStyle << std::endl;
        return Qt::RoundCap;
    default:
//        std::cout << "Cap Style Sqaure Cap (Deafult)" << std::endl;
        return Qt::SquareCap;
    }
}

Qt::PenJoinStyle getPenJoinStyle(const std::string& joinStyle)
{
    switch(joinStyle[1])
    {
    case 'R':
//        std::cout << "Join Style:" << joinStyle << std::endl;
        return Qt::RoundJoin;
    case 'M':
//        std::cout << "Join Style:" << joinStyle << std::endl;
        return Qt::MiterJoin;
    default:
//        std::cout << "Join Style: BevelJoin (Default)" << std::endl;
        return Qt::BevelJoin;
    }
}

Qt::BrushStyle   getBrushStyle(const std::string& brushStyle)
{
    switch(brushStyle[1])
    {
    case 'S':
//        std::cout << "Brush Style:" << brushStyle << std::endl;
        return Qt::SolidPattern;
    case 'D' : switch(brushStyle[6])
               {
                case 1:
                    return Qt::Dense1Pattern;
               case 2:
                    return Qt::Dense2Pattern;
               case 3:
                    return Qt::Dense3Pattern;
               case 4:
                    return Qt::Dense4Pattern;
               case 5:
                    return Qt::Dense5Pattern;
               case 6:
                    return Qt::Dense6Pattern;
               case 7:
                    return Qt::Dense7Pattern;
               default:
                    return Qt::DiagCrossPattern;
               }
    case 'H' :
//        std::cout << "Brush Style:" << brushStyle << std::endl;
        return Qt::HorPattern;
    case 'V':
//        std::cout << "Brush Style:" << brushStyle << std::endl;
        return Qt::VerPattern;
    case 'C':
        return Qt::CrossPattern;
    case 'B':
        return Qt::BDiagPattern;
    case 'F':
//        std::cout << "Brush Style:" << brushStyle << std::endl;
        return Qt::FDiagPattern;
    default:
//        std::cout << "Brush Style: No Brush(Default)" << std::endl;
        return Qt::NoBrush;
    }
}

QFont::Weight getFontWeight(const std::string& fontWeight)
{
    switch(fontWeight[1])
    {
    case 'L':
        return QFont::Light;
    case 'N':
//        std::cout << "Font Weight:" << fontWeight << std::endl;
        return QFont::Normal;
    case 'D':
        return QFont::DemiBold;
    case 'B':
        if(fontWeight[2] == 'o')
        {
            return QFont::Bold;
        }
        else
        {
            return QFont::Black;
        }
   default:
//        std::cout << "Font Weight: Normal (Default)" << std::endl;
        return QFont::Normal;
    }
}


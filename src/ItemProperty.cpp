#include "ItemProperty.h"

#include "MainWindow.h"
#include "ItemButton.h"
#include "Shapes.h"

using namespace std::placeholders;

/******************************************************************************
 * 
 * Shape specialization
 * 
 *****************************************************************************/

ItemProperty<Shape>::ItemProperty(QTreeWidgetItem* parent, Shape& s)
    : QTreeWidgetItem(parent, PropNone),
      name{QString("ID: %1; Type: %2").arg(s.getID()).arg(SHAPE_NAMES[s.getType()])}
{
	new ItemProperty<QPoint>(
	            this,
	            "Position",
	            std::bind(&Shape::getPos, &s),
	            [&s](QPoint p) { s.setPos(p); }
	);
	if (s.getType() != TextType) {
		new ItemProperty<QPen>(
			this,
			"Line",
			std::bind(&Shape::getPen, &s),
			std::bind(&Shape::setPen, &s, _1)
		);
	}
	if (Shape::hasFill(s.getType())) {
		new ItemProperty<QBrush>(
			this,
			"Fill",
			std::bind(&Shape::getBrush, &s),
			std::bind(&Shape::setBrush, &s, _1)
		);
	}
	
#define TRY_CAST(type, var) auto* var = dynamic_cast<type*>(&s)
	
	if (TRY_CAST(Ellipse, ellipse)) {
		new ItemProperty<QRect>(this,
		                        "Ellipse",
		                        std::bind(&Ellipse::getRect, ellipse),
		                        std::bind(&Ellipse::setRect, ellipse, _1)
		);
	}
	else if (TRY_CAST(Line, line)) {
		new ItemProperty<Line>(this, *line);
	}
	else if (TRY_CAST(Polygon, poly)) {
		new ItemProperty<Polygon>(this, *poly);
	}
	else if (TRY_CAST(PolyLine, poly)) {
		new ItemProperty<PolyLine>(this, *poly);
	}
	else if (TRY_CAST(Rectangle, rect)) {
		new ItemProperty<QRect>(this,
		                        "Rectangle",
		                        std::bind(&Rectangle::getRect, rect),
		                        std::bind(&Rectangle::setRect, rect, _1)
		);
	}
	else if (TRY_CAST(Text, text)) {
		new ItemProperty<Text>(this, *text);
	}
#undef TRY_CAST
	
	treeWidget()->setCurrentItem(this);
}

/******************************************************************************
 * 
 * Line specialization
 * 
 *****************************************************************************/

ItemProperty<Line>::ItemProperty(QTreeWidgetItem* parent, Line& line)
    : QTreeWidgetItem(parent, PropNone), name{"Line"}
{
	new ItemProperty<QPoint>(
	            this,
	            "Start",
	            std::bind(&Line::getStart, &line),
	            std::bind(&Line::setStart, &line, _1)
	);
	new ItemProperty<QPoint>(
	            this,
	            "End",
	            std::bind(&Line::getEnd, &line),
	            std::bind(&Line::setEnd, &line, _1)
	);
}

/******************************************************************************
 * 
 * Polygon specialization
 * 
 *****************************************************************************/

ItemProperty<Polygon>::ItemProperty(QTreeWidgetItem* parent, Polygon& poly)
    : QTreeWidgetItem(parent, PropNone), name{"Polygon"}
{
	
	new ItemProperty<QList<QPoint>>(
	            this,
	            "Vertices",
	            std::bind(&Polygon::getCount, &poly),
	            std::bind(&Polygon::getPoint, &poly, _1),
	            std::bind(&Polygon::setPoint, &poly, _1, _2),
	            std::bind(&Polygon::insert, &poly, _1, _2),
	            std::bind(&Polygon::erase, &poly, _1)
	);
}

/******************************************************************************
 * 
 * PolyLine specialization
 * 
 *****************************************************************************/

ItemProperty<PolyLine>::ItemProperty(QTreeWidgetItem* parent, PolyLine& poly)
    : QTreeWidgetItem(parent, PropNone), name{"PolyLine"}
{
	
	new ItemProperty<QList<QPoint>>(
	            this,
	            "Vertices",
	            std::bind(&PolyLine::getCount, &poly),
	            std::bind(&PolyLine::getPoint, &poly, _1),
	            std::bind(&PolyLine::setPoint, &poly, _1, _2),
	            std::bind(&PolyLine::insert, &poly, _1, _2),
	            std::bind(&PolyLine::erase, &poly, _1)
	);
}

/******************************************************************************
 * 
 * Text specialization
 * 
 *****************************************************************************/

ItemProperty<Text>::ItemProperty(QTreeWidgetItem* parent, Text& text)
    : QTreeWidgetItem(parent, PropNone), name{"Text"}
{
	new ItemProperty<QString>(
	            this,
	            "Text",
	            std::bind(&Text::getString, &text),
	            std::bind(&Text::setString, &text, _1),
	            PropString
	);
	new ItemProperty<QString>(
	            this,
	            "Color",
	            ([&text]() { return COLOR_NAMES.key(text.getPen().color()); }),
	            ([&text](QString s) { QPen p = text.getPen(); p.setColor(COLOR_NAMES[s]); text.setPen(p); }),
	            PropColor
	);
	new ItemProperty<QFont>(
	            this,
	            "Font",
	            std::bind(&Text::getFont, &text),
	            std::bind(&Text::setFont, &text, _1)
	);
	new ItemProperty<QRect>(
	            this,
	            "Box",
	            std::bind(&Text::getRect, &text),
	            std::bind(&Text::setRect, &text, _1)
	);
	new ItemProperty<QString>(
	            this,
	            "Alignment",
	            ([&text]() { return ALIGNMENT_NAMES[text.getAlign()]; }),
	            ([&text](QString s) { text.setAlign(ALIGNMENT_NAMES.key(s)); }),
	            PropAlignment
	);
}

/******************************************************************************
 * 
 * QPoint specialization
 * 
 *****************************************************************************/

void Disconnect(MainWindow* window, QTreeWidget* tree)
{
	QObject::disconnect(window, &MainWindow::onCanvasClick, nullptr, nullptr);
	QObject::disconnect(tree, &QTreeWidget::currentItemChanged, nullptr, nullptr);
	window->SetCanvasCursor(Qt::ArrowCursor);
	window->SetStatusText("");
}

MainWindow* GetWindow(QTreeWidgetItem* item)
{
	auto* window = item->treeWidget()->window();
	auto* main = dynamic_cast<MainWindow*>(window);
	if (!main) {
		main = dynamic_cast<MainWindow*>(window->parent());
	}
	assert(main);
	return main;
}

ItemProperty<QPoint>::ItemProperty(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new ItemProperty<int>(
	            this,
	            "X",
	            [this]() -> int { return getter().x(); },
	            [this](int x) { setter(QPoint{x, getter().y()}); }
	);
	new ItemProperty<int>(
	            this,
	            "Y",
	            [this]() -> int { return getter().y(); },
	            [this](int y) { setter(QPoint{getter().x(), y}); }
	);
	
	auto* window = GetWindow(this);
	
	auto* buttonWidget = new ItemButton({{QIcon{":/icons/target.png"}, "Set position with mouse"}});
	QObject::connect(buttonWidget, &ItemButton::clicked, [this, window]() {
		treeWidget()->setCurrentItem(this);
		// Set pointer
		window->SetCanvasCursor(Qt::CrossCursor);
		window->SetStatusText("Click to set position");
		// Set setter
		QObject::connect(window, &MainWindow::onCanvasClick, [this, window](int x, int y) {
			setter(QPoint{x, y});
			emitDataChanged();
			// Unset setter
			Disconnect(window, treeWidget());
		});
		QObject::connect(treeWidget(), &QTreeWidget::currentItemChanged, std::bind(&Disconnect, window, treeWidget()));
	});
	treeWidget()->setItemWidget(this, 1, buttonWidget);
}

QVariant ItemProperty<QPoint>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			QPoint p = getter();
			return QString{"(%1, %2)"}.arg(p.x()).arg(p.y());
		}
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QPoint list specialization
 * 
 *****************************************************************************/

ItemProperty<QList<QPoint>>::ItemProperty(QTreeWidgetItem* parent, QString name, get_size_t get_size_in, get_item_t get_item_in, set_item_t set_item_in, insert_t insert_in, erase_t erase_in)
    : QTreeWidgetItem(parent, PropNone),
      name{std::move(name)},
      get_size{std::move(get_size_in)},
      get_item{std::move(get_item_in)},
      set_item{std::move(set_item_in)},
      insert{std::move(insert_in)},
      erase{std::move(erase_in)}
{
	size_t i = 0, count = get_size();
	for (; i < count; ++i) {
		new ItemProperty<QPoint>(
		            this,
		            QString{"[%1]"}.arg(i),
		            std::bind(get_item, i),
		            std::bind(set_item, i, std::placeholders::_1)
		);
	}
	
	auto* buttons = new ItemButton{{
	        {QIcon{":/icons/add.png"}, "Begin appending points"},
	        {QIcon{":/icons/remove.png"}, "Remove last point"}
	}};
	
	buttons->button(1)->setEnabled(count != 0);
	QObject::connect(buttons, &ItemButton::clicked, [this](int i) {
		switch (i) {
		case 0: add(); break;
		case 1: remove(); break;
		}
	});
	treeWidget()->setItemWidget(this, 1, buttons);
}

void ItemProperty<QList<QPoint>>::add()
{
	auto* window = GetWindow(this);
	treeWidget()->setCurrentItem(this);
	
	// Set pointer
	window->SetCanvasCursor(Qt::CrossCursor);
	window->SetStatusText("Click to add points");
	
	// Set setter
	QObject::connect(window, &MainWindow::onCanvasClick, [this](int x, int y) {
		size_t i = get_size();
		insert(i, QPoint{x, y});
		auto* prop = new ItemProperty<QPoint>(
		            this,
		            QString{"[%1]"}.arg(i),
		            std::bind(get_item, i),
		            std::bind(set_item, i, _1)
		);
		treeWidget()->expandItem(prop);
		emitDataChanged();
		dynamic_cast<ItemButton*>(treeWidget()->itemWidget(this, 1))->button(1)->setEnabled(true);
	});
	QObject::connect(treeWidget(), &QTreeWidget::currentItemChanged, std::bind(&Disconnect, window, treeWidget()));
}

void ItemProperty<QList<QPoint>>::remove()
{
	auto* window = GetWindow(this);
	
	Disconnect(window, treeWidget());
	
	size_t i = get_size() - 1;
	erase(i);
	removeChild(child(static_cast<int>(i)));
	dynamic_cast<ItemButton*>(treeWidget()->itemWidget(this, 1))->button(1)->setEnabled(i != 0);
	emitDataChanged();
}

QVariant ItemProperty<QList<QPoint>>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			return QString{"Size: %1"}.arg(get_size());
		}
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QRect specialization
 * 
 *****************************************************************************/

ItemProperty<QRect>::ItemProperty(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new ItemProperty<int>(
	            this,
	            "X",
	            [this]() -> int { return getter().left(); },
	            [this](int x) { auto v = getter(); v.moveLeft(x); setter(v); }
	);
	new ItemProperty<int>(
	            this,
	            "Y",
	            [this]() -> int { return getter().top(); },
	            [this](int x) { auto v = getter(); v.moveTop(x); setter(v); }
	);
	new ItemProperty<int>(
	            this,
	            "Width",
	            [this]() -> int { return getter().width(); },
	            [this](int x) { auto v = getter(); v.setWidth(x); setter(v); }
	);
	new ItemProperty<int>(
	            this,
	            "Height",
	            [this]() -> int { return getter().height(); },
	            [this](int x) { auto v = getter(); v.setHeight(x); setter(v); }
	);
	
	auto* window = GetWindow(this);
	
	auto* buttons = new ItemButton{{
	        {QIcon{":/icons/corner.png"}, "Move the upper-left corner with the mouse (size stays the same)"},
	        {QIcon{":/icons/size.png"}, "Set the bottom-right corner with the mouse (changes size)"}
	}};
	QObject::connect(buttons, &ItemButton::clicked, [this, window](int i) {
		window->SetCanvasCursor(Qt::CrossCursor);
		switch (i) {
		case 0:
			treeWidget()->setCurrentItem(this->child(0));
			// Set pointer
			window->SetStatusText("Click to move the top-left corner");
			// Set setter
			QObject::connect(window, &MainWindow::onCanvasClick, [this, window](int x, int y) {
				QRect r = getter();
				r.moveTopLeft(QPoint{x, y});
				setter(r);
				emitDataChanged();
				// Unset setter
				Disconnect(window, treeWidget());
			});
			break;
		case 1:
			treeWidget()->setCurrentItem(this->child(2));
			// Set pointer
			window->SetStatusText("Click to set the bottom-right corner");
			// Set setter
			QObject::connect(window, &MainWindow::onCanvasClick, [this, window](int x, int y) {
				QRect r = getter();
				r.setBottomRight(QPoint{x, y});
				setter(r.normalized());
				emitDataChanged();
				// Unset setter
				Disconnect(window, treeWidget());
			});
		}
		QObject::connect(treeWidget(), &QTreeWidget::currentItemChanged, std::bind(&Disconnect, window, treeWidget()));
	});
	treeWidget()->setItemWidget(this, 1, buttons);
}

QVariant ItemProperty<QRect>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			QRect r = getter();
			return QString{"[(%1, %2), %3x%4]"}.arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height());
		}
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QPen specialization
 * 
 *****************************************************************************/

ItemProperty<QPen>::ItemProperty(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new ItemProperty<int>(
	            this,
	            "Width",
	            [this]() { return getter().width(); },
	            [this](int w) { auto v = getter(); v.setWidth(w); setter(v); }
	);
	new ItemProperty<QString>(
	            this,
	            "Color",
	            [this]() { return COLOR_NAMES.key(getter().color()); },
	            [this](QString s) { auto v = getter(); v.setColor(COLOR_NAMES[s]); setter(v); },
	            PropColor
	);
	new ItemProperty<QString>(
	            this,
	            "Style",
	            [this]() { return PEN_STYLE_NAMES[getter().style()]; },
	            [this](QString s) { auto v = getter(); v.setStyle(PEN_STYLE_NAMES.key(s)); setter(v); },
	            PropPenStyle
	);
	new ItemProperty<QString>(
	            this,
	            "Cap Style",
	            [this]() { return PEN_CAP_STYLE_NAMES[getter().capStyle()]; },
	            [this](QString s) { auto v = getter(); v.setCapStyle(PEN_CAP_STYLE_NAMES.key(s)); setter(v); },
	            PropPenCapStyle
	);
	new ItemProperty<QString>(
	            this,
	            "Join Style",
	            [this]() { return PEN_JOIN_STYLE_NAMES[getter().joinStyle()]; },
	            [this](QString s) { auto v = getter(); v.setJoinStyle(PEN_JOIN_STYLE_NAMES.key(s)); setter(v); },
	            PropPenJoinStyle
	);
}

QVariant ItemProperty<QPen>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QBrush specialization
 * 
 *****************************************************************************/

ItemProperty<QBrush>::ItemProperty(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new ItemProperty<QString>(
	            this,
	            "Color",
	            [this]() { return COLOR_NAMES.key(getter().color()); },
	            [this](QString s) { auto v = getter(); v.setColor(COLOR_NAMES[s]); setter(v); },
	            PropColor
	);
	new ItemProperty<QString>(
	            this,
	            "Style",
	            [this]() { return BRUSH_STYLE_NAMES[getter().style()]; },
	            [this](QString s) { auto v = getter(); v.setStyle(BRUSH_STYLE_NAMES.key(s)); setter(v); },
	            PropBrushStyle
	);
}

QVariant ItemProperty<QBrush>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QFont specialization
 * 
 *****************************************************************************/

ItemProperty<QFont>::ItemProperty(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new ItemProperty<QString>(
	            this,
	            "Family",
	            ([this]() { return getter().family(); }),
	            ([this](QString s) { QFont f = getter(); f.setFamily(s); setter(f); }),
	            PropFont
	);
	new ItemProperty<int>(
	            this,
	            "Size",
	            ([this]() { return getter().pointSize(); }),
	            ([this](int s) { QFont f = getter(); f.setPointSize(s); setter(f); }),
	            PropFontSize
	);
	new ItemProperty<QString>(
	            this,
	            "Style",
	            ([this]() { return FONT_STYLE_NAMES[getter().style()]; }),
	            ([this](QString s) { QFont f = getter(); f.setStyle(FONT_STYLE_NAMES.key(s)); setter(f); }),
	            PropFontStyle
	);
	new ItemProperty<QString>(
	            this,
	            "Weight",
	            ([this]() { return FONT_WEIGHT_NAMES[static_cast<QFont::Weight>(getter().weight())]; }),
	            ([this](QString s) { QFont f = getter(); f.setWeight(FONT_WEIGHT_NAMES.key(s)); setter(f); }),
	            PropFontWeight
	);
}

QVariant ItemProperty<QFont>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}
	
	return QVariant{};
}


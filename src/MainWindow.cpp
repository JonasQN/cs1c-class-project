/* ==================================================
+				CS1C Final Project:
+				Group Members - 6
+				Date: 5/14/2019
+               Spring Semester
+               Professor: John Kath
+				Members (6):
+	Joshua Yang (jmyphotographybooking@gmail.com)
+	Qian tai Chen (qiantaichen0303@gmail.com)
+	x (Jdu9572@gmail.com)
+	x (jonasqiang8@gmail.com)
+	x
+	x
+	
+
+
===================================================== */


#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "About.h"
#include "DetailView.h"
#include "saveFile.h"
#include "ItemButton.h"
#include "login.h"
#include "ItemProperty.h"
#include "PropertySetting.h"
#include "arrange.h"
#include "Shapes.h"
#include "Sort.h"

#include <QAction>
#include <QCloseEvent>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>
#include <QStatusBar>

#include <fstream>
#include <sstream>

static const char* filename = "myShapes.txt";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle(filename);
	
	ui->statusBar->addWidget(&statusL);
	
	onlyAdmin = {
	    ui->actionAdd_Ellipse,
	    ui->actionAdd_Line,
	    ui->actionAdd_Polygon,
	    ui->actionAdd_Polyline,
	    ui->actionAdd_Rectangle,
	    ui->actionAdd_Text,
	    ui->actionSave,
	    ui->PropTree,
	    ui->remove
	};
	
	SetAdmin(false);
	
	save.shapes = LoadShapeFile();

	ui->canvas->set_storage(&save.shapes);

	ui->ShapeList->setModel(&save.model);
	ui->ShapeList->setEnabled(save.shapes.size());
	
	ui->PropTree->setHeaderLabels({"Property", "Value"});
	ui->PropTree->setItemDelegate(new PropertySettings());
	ui->PropTree->setEditTriggers(QAbstractItemView::AllEditTriggers);
	
	saveTimer.setSingleShot(true);
	connect(&saveTimer, &QTimer::timeout, this, &MainWindow::Save);
	modified = false;
}

MainWindow::~MainWindow()
{
	delete ui->PropTree->itemDelegate();
	delete ui;
}

void MainWindow::SetCanvasCursor(const QCursor &c)
{
	ui->canvas->setCursor(c);
}

void MainWindow::SetStatusText(const QString &str, int timeout)
{
	if (timeout == 0) {
		ui->statusBar->clearMessage();
		statusL.setText(str);
		if (str.isEmpty()) {
			statusL.hide();
		}
		else {
			statusL.show();
		}
	}
	else {
		ui->statusBar->showMessage(str, timeout);
	}
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if (!modified) {
		event->accept();
	}
	else {
		QMessageBox::StandardButtons buttons = QMessageBox::Cancel | QMessageBox::Yes;
		if (ui->actionSave->isEnabled()) {
			buttons |= QMessageBox::Save;
		}
		QMessageBox* warn = new QMessageBox(
		            QMessageBox::Warning,
		            "Unsaved Changes",
                    "You have unsaved changes, do you wish to quit?",
		            buttons,
		            this
		);
		warn->exec();
		switch (warn->result()) {
		case QMessageBox::Save:
			Save();
			event->accept();
			break;
		case QMessageBox::Cancel:
			event->ignore();
			break;
		case QMessageBox::Yes:
			event->accept();
			break;
		}
	}
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape) {
		Disconnect();
	}
}

void MainWindow::on_ShapeList_currentIndexChanged(int index)
{
	disconnect(ui->PropTree, &QTreeWidget::itemChanged, nullptr, nullptr);
	QTreeWidgetItem* old = ui->PropTree->topLevelItem(0);
	if (old) {
		ui->PropTree->removeItemWidget(old, 0);
		delete old;
	}
	
	if (index < save.shapes.size()) {
		Shape* s = save.shapes[index];
		new ItemProperty<Shape>(ui->PropTree->invisibleRootItem(), *s);
		ui->PropTree->expandAll();
	}
	
	ui->canvas->setSelected(index);
	ui->PropTree->update();
	
	connect(ui->PropTree, &QTreeWidget::itemChanged, this, &MainWindow::onDataChanged);
}

void MainWindow::onDataChanged()
{
	ui->canvas->update();
	modified = true;
	this->setWindowTitle(QString{"%1*"}.arg(filename));
	
	ui->ShapeList->setEnabled(save.shapes.size());
	ui->remove->setEnabled(save.shapes.size());
}

void MainWindow::on_remove_clicked()
{
	int index = ui->ShapeList->currentIndex();
	auto it = save.shapes.begin();
	for (int i = 0; i < index; ++i) {
		++it;
	}
	delete *it;
	
	save.shapes.erase(it);
	save.model.itemsChanged();
	
	onDataChanged();
	
	if (save.shapes.size() == 0) {
		on_ShapeList_currentIndexChanged(0);
	}
	else if (index >= save.shapes.size()) {
		ui->ShapeList->setCurrentIndex(save.shapes.size() - 1);
	}
	else {
		ui->ShapeList->setCurrentIndex(index);
	}
}

void MainWindow::on_actionSave_triggered()
{
	saveTimer.start(0);
}

void MainWindow::on_actionExit_triggered()
{
	this->close();
}

void MainWindow::on_actionAdd_Ellipse_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click to add an ellipse");
	
	using namespace std::placeholders;
	
	connect(this, &MainWindow::onCanvasClick, std::bind(&MainWindow::AddRect<Ellipse>, this, _1, _2));
}

void MainWindow::on_actionAdd_Line_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
    SetStatusText("Starting point for the line");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		auto* line = new Line{QPoint{x, y}, QPoint{x, y}};
		save.shapes.push_back(line);
		save.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(save.shapes.size() - 1);
		
		disconnect(this, &MainWindow::onCanvasClick, nullptr, nullptr);
        SetStatusText("Ending point for the line");
		connect(this, &MainWindow::onCanvasClick, [this, line](int x, int y) {
			Disconnect();
			
			line->setEnd(QPoint{x, y});
			onDataChanged();
		});
	});
}

void MainWindow::on_actionAdd_Polygon_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
    SetStatusText("First point for the polygon");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		auto* poly = new Polygon{{QPoint{x, y}}};
		
		save.shapes.push_back(poly);
		save.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(save.shapes.size() - 1);

		auto* item = ui->PropTree->topLevelItem(0)->child(3)->child(0);
		auto* propitem = dynamic_cast<ItemProperty<QList<QPoint>>*>(item);
		propitem->add();
	});
}

void MainWindow::on_actionAdd_Polyline_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
    SetStatusText("Click first point");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		auto* poly = new PolyLine{{QPoint{x, y}}};
		
		save.shapes.push_back(poly);
		save.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(save.shapes.size() - 1);
		
		auto* item = ui->PropTree->topLevelItem(0)->child(2)->child(0);
		auto* propitem = dynamic_cast<ItemProperty<QList<QPoint>>*>(item);
		propitem->add();
	});
}

void MainWindow::on_actionAdd_Rectangle_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click to add a rectangle");
	
	using namespace std::placeholders;
	
	connect(this, &MainWindow::onCanvasClick, std::bind(&MainWindow::AddRect<Rectangle>, this, _1, _2));
}

void MainWindow::on_actionAdd_Text_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click to add a text box");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		save.shapes.push_back(new Text{"", QFont{}, -1, -1, Qt::AlignCenter, QPoint{x, y}});
		save.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(save.shapes.size() - 1);
		
		auto* item = ui->PropTree->topLevelItem(0)->child(1)->child(0);
		ui->PropTree->setCurrentItem(item);
		ui->PropTree->editItem(item, 1);
	});
}

#define ALL(item) item.begin(), item.end()

void MainWindow::on_actionBy_ID_triggered()
{
	vector_t copy(save.shapes.size());
    auto end = copy_if(ALL(save.shapes), copy.begin(), validID);
    selection_sort(copy.begin(), end, compareID);
	std::stringstream text;
	text << copy;
	
	auto* view = new DetailView(QString::fromStdString(text.str()).replace(": ", ":\t"), this);
	view->open();
}
void MainWindow::on_actionBy_Area_triggered()
{
    vector_t copy(save.shapes.size());
    auto end = copy_if(ALL(save.shapes), copy.begin(), validArea);
    selection_sort(copy.begin(), end, compareArea);

    QStringList text;

    for (auto it = copy.begin(); it != end; ++it) {
        Shape* shape = *it;
        text << QString{"Id:\t%1"}.arg(shape->getID());
        text << QString{"Type:\t%1"}.arg(SHAPE_NAMES[shape->getType()]);
        text << QString{"Area:\t%1"}.arg(shape->getArea(), 0, 'f', 2);
        text << "";
    }

    auto* view = new DetailView(text.join('\n'), this);
    view->open();
}

void MainWindow::on_actionBy_Perimeter_triggered()
{
    vector_t copy(save.shapes.size());
    auto end = copy_if(ALL(save.shapes), copy.begin(), validPerimeter);
    selection_sort(copy.begin(), end, comparePerimeter);

    QStringList text;

    for (auto it = copy.begin(); it != end; ++it) {
        Shape* shape = *it;
        text << QString{"Id:\t%1"}.arg(shape->getID());
        text << QString{"Type:\t%1"}.arg(SHAPE_NAMES[shape->getType()]);
        text << QString{"Perimeter:\t%1"}.arg(shape->getPerimeter(), 0, 'f', 2);
        text << "";
    }

    auto* view = new DetailView(text.join('\n'), this);
    view->open();
}
void MainWindow::on_actionAbout_triggered()
{
	(new About(this))->show();
}

template<class RectType>
void MainWindow::AddRect(int x, int y)
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click to set size");
	auto* rect = new RectType{QRect{x, y, 0, 0}};
	save.shapes.push_back(rect);
	save.model.itemsChanged();
	onDataChanged();
	
	ui->ShapeList->setCurrentIndex(save.shapes.size() - 1);
	
	// Use existing size setter
	auto* item = ui->PropTree->topLevelItem(0)->child(3);
	auto* widget = dynamic_cast<ItemButton*>(ui->PropTree->itemWidget(item, 1));
	widget->clicked(1);
}

void MainWindow::Disconnect()
{
	QObject::disconnect(this, &MainWindow::onCanvasClick, nullptr, nullptr);
	SetCanvasCursor(Qt::ArrowCursor);
	SetStatusText("");
}

void MainWindow::Save()
{
	if (!ui->actionSave->isEnabled()) {
		return;
	}
    SetStatusText("Saving shapes");
	{
		std::ofstream file{filename};
		file << save.shapes;
	}
	SetStatusText("");
	SetStatusText("Saved shapes file", 2000);
	modified = false;
	this->setWindowTitle(filename);
}

void MainWindow::SetAdmin(bool val)
{
	for (auto* o : onlyAdmin) {
		if (auto* w = dynamic_cast<QWidget*>(o)) {
			w->setEnabled(val);
		}
		else if (auto* a = dynamic_cast<QAction*>(o)) {
			a->setEnabled(val);
		}
	}
	Disconnect();
}


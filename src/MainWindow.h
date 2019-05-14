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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Storage.h"

#include <QLabel>
#include <QMainWindow>
#include <QTimer>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
    void callSetAdmin(bool flag)
    {
        SetAdmin(flag);
    }
	explicit MainWindow(QWidget *parent = nullptr);

	~MainWindow() override;
	
	void SetCanvasCursor(const QCursor&);
	void SetStatusText(const QString&, int timeout = 0);
	
protected:

	void closeEvent(QCloseEvent *event) override;
	
	void keyPressEvent(QKeyEvent* event) override;
	
signals:

	void onCanvasClick(int x, int y);
	
private slots:

	void on_ShapeList_currentIndexChanged(int index);

    void on_actionBy_ID_triggered();

    void on_actionBy_Area_triggered();

    void on_actionBy_Perimeter_triggered();

    void on_actionAbout_triggered();
	
	void onDataChanged();

	void on_remove_clicked();
	
	void on_actionSave_triggered();
	
	void on_actionExit_triggered();

	void on_actionAdd_Ellipse_triggered();
	
	void on_actionAdd_Line_triggered();
	
	void on_actionAdd_Polygon_triggered();
	
	void on_actionAdd_Polyline_triggered();
	
	void on_actionAdd_Rectangle_triggered();
	
	void on_actionAdd_Text_triggered();

	
private:
	template<class RectType>
	void AddRect(int x, int y);
	void Disconnect();
	void Save();
	void SetAdmin(bool);
	
    Storage save;
	Ui::MainWindow *ui;
    QLabel statusL;
	QTimer saveTimer;
    QList<QObject*> onlyAdmin;
	bool modified;
};

#endif // MAINWINDOW_H

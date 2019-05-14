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

#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}
class About : public QDialog
{
	Q_OBJECT
	
public:

	explicit About(QWidget *parent = nullptr);

	~About();
	
private:
	Ui::About *ui;
};

#endif // ABOUT_H

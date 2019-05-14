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

#include "About.h"
#include "ui_About.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
	ui->setupUi(this);
}

About::~About()
{
	delete ui;
}

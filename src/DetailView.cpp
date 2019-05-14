#include "DetailView.h"
#include "ui_DetailView.h"

#include <QTextEdit>

DetailView::DetailView(const QString &text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailView)
{
	ui->setupUi(this);
	
	ui->text->setText(text);
}

DetailView::~DetailView()
{
	delete ui;
}

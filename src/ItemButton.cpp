#include "ItemButton.h"
#include "ui_ItemButton.h"

ItemButton::ItemButton(const QList<QPair<QIcon, QString>> &buttons, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemButton)
{
	ui->setupUi(this);
	
	int i = 0;
	for (auto& pair : buttons) {
		auto* button = new QPushButton{pair.first, "", this};
		this->buttons.push_back(button);
		button->setToolTip(pair.second);
		button->setStatusTip(pair.second);
		button->setMaximumSize(QSize(20, 20));
		ui->horizontalLayout->addWidget(button);
		connect(button, &QPushButton::clicked, std::bind(&ItemButton::clicked, this, i));
		++i;
	}
}

ItemButton::~ItemButton()
{
	delete ui;
}

QPushButton* ItemButton::button(int i)
{
	return buttons[i];
}


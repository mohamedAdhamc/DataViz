#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
	//make main layout
	QVBoxLayout* mainBox = new QVBoxLayout(this);
	label = new QLabel(helpText);
	label->setWordWrap(true);
	mainBox->addWidget(label);
	setLayout(mainBox);



	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	setMaximumSize(parent->size());


}

HelpDialog::~HelpDialog()
{
    delete ui;
}

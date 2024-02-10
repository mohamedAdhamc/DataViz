#ifndef HELPDIALOG_H
#define HELPDIALOG_H

/********************************
 *
 *  This class is defined for the "Help" dialog,
 *  an object of this class is the window of the "Help" dialog in the app
 *
**********************************/


#include <QDialog>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

private:
    Ui::HelpDialog *ui;
	QLabel* label;

	//Text Sections
	QString loadingDataSetSection = "Loading a Dataset:\nLoading a file can be done by clicking on File menu -> Load Dataset\n"
									"Alternatively, by clicking on the page symbol in the toolbar at the top of the app.";

	QString datasetFormSection = "\n\nThe form of dataset:\nThe app currently is designed to work with datasets saved in txt file,"
								 " where the data is listed in two columns. "
								 "The first column is the x coordinate of the data point while the second is the y- coordinate of "
								 "the datapoints.\nThe x and y coordinates can be either separated by a tap or a comma.   ";

	QString plottingDatasetSection = "\n\nPlotting a dataset:\nThe app currently has only one way of plotting a dataset, that is by right-clicking "
									 "on the dataset window-> plot-> XY plot. \n";

	//Text displayed
	QString helpText = loadingDataSetSection + datasetFormSection + plottingDatasetSection;
};

#endif // HELPDIALOG_H

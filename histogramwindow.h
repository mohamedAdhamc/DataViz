#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

/********************************
 *
 *  This class is defined to show a histogram in a window,
 *  an object of this class is the window in which a histogram is plotted
 *
**********************************/



#include <QDialog>
#include "dataset.h"
#include <QMenu>
#include <qcustomplot.h>

namespace Ui {
class HistogramWindow;
}

class HistogramWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HistogramWindow(DataSet *DataSet,QWidget *parent = nullptr);
    ~HistogramWindow();
    void SetHistogramSetting(DataSet *DataSet); // Function to control the setting of the curve (dataset represenation in the figure)
    void SetFigureSetting(); // Function to control the setting of the figure itself

private:
    Ui::HistogramWindow *ui;
    static int FigureCounter; // Number of Figures created in the app ( defined as static because it is shared among all objects of this class)
};

#endif // HISTOGRAMWINDOW_H

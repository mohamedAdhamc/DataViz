#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

/********************************
 *
 *  This class is defined to show a graph in a window,
 *  an object of this class is the window in which a graph is plotted
 *
 *  In this class, a figure is the frame of the plot of the curves, its
 *  properties include the axes, the grid, the title, the legend.
 *
 *  In this class, a graph is the curve plotted, its properties include
 *  the width of the line, its style, and its colour.
 *
 *
**********************************/



#include <QDialog>
#include "dataset.h"



namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphWindow(DataSet *DataSet,QWidget *parent = nullptr);
    ~GraphWindow();
    void SetGraphSetting(DataSet *DataSet); // Function to control the setting of the curve (dataset represenation in the figure)
    void SetFigureSetting(); // Function to control the setting of the figure itself

private:
    Ui::GraphWindow *ui;
    static int FigureCounter; // Number of Figures created in the app ( defined as static because it is shared among all objects of this class)
};

#endif // GRAPHWINDOW_H

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
#include <QMenu>
#include <vector>
#include <qcustomplot.h>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphWindow(DataSet *DataSet,QWidget *parent = nullptr);
    explicit GraphWindow(std::vector<DataSet *>DataSet,QWidget *parent = nullptr);
    ~GraphWindow();
    void SetGraphSetting(DataSet *DataSet); // Function to control the setting of the curve (dataset represenation in the figure)
    void SetGraphVectorSetting(std::vector<DataSet *>DataSet);
    void SetFigureSetting(); // Function to control the setting of the figure itself
	void contextMenuEvent(QContextMenuEvent *event);
	void ConstructContextMenu(QMenu *);

	void changeGraphColor(int graphIndex, Qt::GlobalColor color);
	void changeGraphLineWidth(int graphIndex, int width);
	void changeGraphStyle(int graphIndex, QCPGraph::LineStyle lineStyle);

private:
    Ui::GraphWindow *ui;
    static int FigureCounter; // Number of Figures created in the app ( defined as static because it is shared among all objects of this class)

	// List of actions in the app (defined in the code rather than the UI)

	//colors: red green yellow black
	QAction* changeColorRed=new QAction("red", this);
	QAction* changeColorGreen= new QAction("green", this);
	QAction* changeColorYellow= new QAction("yellow", this);
	QAction* changeColorBlack= new QAction("black", this);

	//linewidth
	QAction* changeWidth1=new QAction("1", this);
	QAction* changeWidth3=new QAction("3", this);
	QAction* changeWidth5=new QAction("5", this);
	QAction* changeWidth10=new QAction("10", this);

	//lineStyle
	QAction* lineStyleNone=new QAction("none",this);
	QAction* lineStyleLine=new QAction("line",this);
	QAction* lineStyleStepLeft=new QAction("step left",this);
	QAction* lineStyleStepCenter=new QAction("step center",this);
	QAction* lineStyleImpulse=new QAction("impulse",this);

	//Creating the menus (all accessable from the context menu):
	QMenu *ContextMenu=new QMenu(this);
	QMenu *Graph1SubMenu=new QMenu("Graph1"); // Plot section
	QMenu *colorGrpah1=new QMenu("Color");
	QMenu *styleGrpah1=new QMenu("Line Style");
	QMenu *widthGrpah1=new QMenu("Line Width");

protected:
	bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // GRAPHWINDOW_H

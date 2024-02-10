#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H

#include <QDialog>
#include <vector>

namespace Ui {
class DrawGraph;
}

class DrawGraph : public QDialog
{
	Q_OBJECT

public:
	explicit DrawGraph(QWidget *parent = nullptr);
	~DrawGraph();

	void setGraphSettings();
	void SetFigureSetting(); // Function to control the setting of the figure itself


private:
	Ui::DrawGraph *ui;
	//better refactored into a point class
	QVector<double> xpoints;
	QVector<double> ypoints;
	bool draw = true;

private slots:
	void clickedGraph(QMouseEvent* event);
	void plot();
	void addPoint(double x, double y);

	void on_pushButton_clicked();
	void on_checkBox_toggled(bool checked);
};

#endif // DRAWGRAPH_H

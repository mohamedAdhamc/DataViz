#ifndef PARENTWINDOW_H
#define PARENTWINDOW_H

/********************************
 *
 *  This class is the base of the entire app,
 *  an object of this class is the app when it is runnning
 *
 *  All windows and dialogs in the app are children to this window
 *
 *  This class organises the datasets and the graphs
 *
 *
**********************************/


#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <QMdiSubWindow>
#include <QAction>
#include <QMenu>
#include "dataset.h"
#include "datasetwindow.h"
#include "graphwindow.h"
#include "histogramwindow.h"
#include "aboutdialog.h"
#include "helpdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ParentWindow; }
QT_END_NAMESPACE

class ParentWindow : public QMainWindow
{
    Q_OBJECT

public:
    ParentWindow(QWidget *parent = nullptr);
    ~ParentWindow();


private slots:
    void on_actionLoad_Dataset_triggered();
	void on_actionShow_DataSets_triggered();
    void GraphWindowToBePlotted(DataSet *ptr); // A slot to plot a new graph window
    void HistogramWindowToBePlotted(DataSet *ptr); // A slot to plot a new graph window

    void on_actionAbout_triggered();

    void on_actionHelp_triggered();

private:
    Ui::ParentWindow *ui;
    QList<DataSet*> AllDataSets; // A List of all datasets loaded in the app
    QMdiSubWindow* subWindow=nullptr; // Temporary variable for subwindows (whether datasetwindow or graphwindow)
    DataSet *AddedDataSet=nullptr; // Temporary variable for dataset (usally has the latest added dataset)
    DataSetWindow *AddedDataSetWindow=nullptr;// Temporary variable for datasetwindow (usually has the latest created datasetwidnow)







};
#endif // PARENTWINDOW_H

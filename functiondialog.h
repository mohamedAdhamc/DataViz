#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H

#include <QDialog>
#include <QVector>
#include "atmsp.h"
#include "qmath.h"
#include "dataset.h"

namespace Ui {
class FunctionDialog;
}

class FunctionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FunctionDialog(QWidget *parent = nullptr);
    ~FunctionDialog();

private:
    Ui::FunctionDialog *ui;
    void on_okButtonClicked(QString function);
    DataSet *ds = nullptr;

signals:
    void Plot_Function_SIGNAL(DataSet *ptr);

public slots:
    void FunctionToBePlotted();

private slots:
    void on_okButtonClicked();
};

#endif // FUNCTIONDIALOG_H

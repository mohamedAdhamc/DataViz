#include "functiondialog.h"
#include "ui_functiondialog.h"
#include "parentwindow.h"

FunctionDialog::FunctionDialog(QWidget *parent, QList<DataSet*> *DataSets) :
    QDialog(parent),
    ui(new Ui::FunctionDialog)
{
    ui->setupUi(this);
    AllDataSets = DataSets;

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_okButtonClicked()));
}

FunctionDialog::~FunctionDialog()
{
    delete ui;
}

void FunctionDialog::on_okButtonClicked() {
    QList<DataSet*> usedDataSets = {};

    QString text = ui->textEdit->toPlainText();
    for (int i = 0; i < AllDataSets->count(); i++) {
        if (text.contains(AllDataSets->at(i)->getName())) {
            usedDataSets.append(AllDataSets->at(i));
        }
    }

    QString usedDataSetsString = "";
    for (int i = 0; i < usedDataSets.count(); i++) {
        usedDataSetsString.append(usedDataSets.at(i)->getName()).append(",");
    }
    usedDataSetsString.chop(1);

    // Parsing: converting the text expression into a mathematical formula then evaluating it:
    ATMSP<double> ParserObj; // An object to convert the expression string to bytecode (parsing)
    ATMSB<double> ByteCodeObj; // An object to evaluate the codebyte into numbers

    //Converting the text expression into a mathematicall formula:
    ParserObj.parse(ByteCodeObj, text.toStdString(), usedDataSetsString.toStdString()); // Telling the parser what is the formula and what the datasets are


    // Computing the result:
    QVector<double> ResultX; // QVector to hold the results
    QVector<double> ResultY; // QVector to hold the results

    for (int i = 0; i < usedDataSets.at(0)->Size(); i++)
    {
        for (int j = 0; j < usedDataSets.count(); j++) {
            double* ValuePtr = usedDataSets.at(j)->getPoint(i);
            double x_value=*ValuePtr;
            ByteCodeObj.var[j] = x_value;
        }
        ResultX.push_back(ByteCodeObj.run());
    }

    for (int i = 0; i < usedDataSets.at(0)->Size(); i++)
    {
        for (int j = 0; j < usedDataSets.count(); j++) {
            double* ValuePtr = usedDataSets.at(j)->getPoint(i);
            double y_value= *(++ValuePtr);
            ByteCodeObj.var[j] = y_value;
        }
        ResultY.push_back(ByteCodeObj.run());
    }


    DataSet *ResultDataSet = new DataSet(ResultX, ResultY);
    FunctionToBePlotted(ResultDataSet);

    // what if the parser encountered a problem (unknown symbol for example in the expression)
    size_t err;

    if ((err = ParserObj.parse(ByteCodeObj, text.toStdString(), usedDataSetsString.toStdString()))) {
        // you can expand this
        QString string=QString::fromStdString(ParserObj.errMessage(err));
        qCritical() << string;
    }
}

void FunctionDialog::FunctionToBePlotted(DataSet *ds)
{// A signal to tell the parent widnow that the dataset must be plotted when the user choses XYPlot
    // from the context Menu of the DatSetWidnow

    emit Plot_Function_SIGNAL(ds);
}

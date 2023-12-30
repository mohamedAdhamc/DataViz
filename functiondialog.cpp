#include "functiondialog.h"
#include "ui_functiondialog.h"
#include "parentwindow.h"

FunctionDialog::FunctionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunctionDialog)
{
    ui->setupUi(this);

    QString file_name = QString::fromStdString("/home/mahmoud/Work/Freelancing/CPP/Qt/DataViz/sinx.txt");
    ds = new DataSet(file_name);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_okButtonClicked()));
}

FunctionDialog::~FunctionDialog()
{
    delete ui;
}

void FunctionDialog::on_okButtonClicked() {
    qDebug() << ds->Size();
    QString text = ui->textEdit->toPlainText();
    qDebug() << "called";
    qDebug() << text;
    QVector<double> D1;
    for (int i=0;i<100;i++)D1.push_back(qCos(i));

    QVector<double> D2;
    for (int i=0;i<100;i++)D2.push_back(qSin(i));

    // Define the expression to be avaluated from the two datsets as a text:
    std::string exps("D1*exp(D2)");

    // Parsing: converting the text expression into a mathematical formula then evaluating it:
    ATMSP<double> ParserObj; // An object to convert the expression string to bytecode (parsing)
    ATMSB<double> ByteCodeObj; // An object to evaluate the codebyte into numbers

    //Converting the text expression into a mathematicall formula:
    ParserObj.parse(ByteCodeObj, exps, "D1,D2"); // Telling the parser what is the formula and what the datasets are


    // Computing the result:
    QVector<double> Result; // QVector to hold the results

    for (int i = 0; i < D1.size(); i++)
    {
        ByteCodeObj.var[0] = D1[i]; // Passing the values of D1 as the first variable in the expression
        ByteCodeObj.var[1] = D2[i]; // Passing the valuesof D2 as the second variable in the expression
        // Evaluating the mathematical formula for each point:
        Result.push_back(ByteCodeObj.run()) ;

    }


    // what if the parser encountered a problem (unknown symbol for example in the expression)
    size_t err;

    if ((err = ParserObj.parse(ByteCodeObj, exps, "D1,D2"))) {
        // you can expand this
        QString string=QString::fromStdString(ParserObj.errMessage(err));
        qCritical() << string;
    }
}

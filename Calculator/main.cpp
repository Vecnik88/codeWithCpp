#include <QtWidgets>
#include <QApplication>
#include "Calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Calculator calculator;

    calculator.setWindowTitle("Calculator v.1.0 by Vecnik88");
    calculator.resize(330,250);
    calculator.show();


    return a.exec();
}

#include "BudgetApp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BudgetApp w;
    w.show();
    return a.exec();
}

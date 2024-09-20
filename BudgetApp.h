#ifndef BUDGETAPP_H
#define BUDGETAPP_H

/*
 * Plan :
 * Create an application that will store the users monthly income, expenses, and calculate
 * how much money will be left over (net profit).
 *
 * Define:
 * Budget Storage : Store the users monthy income, expenses.
 * Calculate Budget : Calculate the net profit of the budget for the month
 *
 * Design:
 * Budget Storage : Use a QSqlDatabase to store the data into a database file.
 * Use a QSqlTabelModel to access and store the data to the database.
 * Create a table called budget with the following colums "budget_id", "name".
 * Create a table called expense with the following colums "expense_id", "name", "amount".
 * Create a table called income with the follwoing colums "income_id", "name", "amount".
 * Create a Widget called ShowBudgetsForm that will Use QSqlTableModel with a QListView to show the budgets that are available.
 * use QPushButton's to insert, remove and select budgets.
 *
 * Calculate Budget : Use the current selected budget_id and use this to populate the UI.
 * Create a Widget called BudgetForm Widget that will user QSqlTabelModel for expenses with a QTabelView to display and modify the
 * expenses name and amount. Use another QSqlTableModel for income with a QTableView to display and
 * modify income name and amount. Show the net profit of the budget at the bottom of the widget.
 *
*/

#include <QMainWindow>
#include <QSqlDatabase>
#include "showbudgetsform.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class BudgetApp;
}
QT_END_NAMESPACE

class BudgetApp : public QMainWindow
{
    Q_OBJECT

public:
    BudgetApp(QWidget *parent = nullptr);
    ~BudgetApp();

private:
    Ui::BudgetApp *ui;
    QSqlDatabase db;

    ShowBudgetsForm* showBudgetsForm;


    void SetupDB();
    void SetupTables();
};
#endif // BUDGETAPP_H

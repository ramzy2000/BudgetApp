#ifndef BUDGETAPP_H
#define BUDGETAPP_H

/*
 * *************************************************************************************************************
 * Plan :
 * Create an application that will store the users monthly income, expenses, and calculate
 * how much money will be left over (net profit).
 *
 * Create a menu that allows users to input their income frequency and the amount they earn per paycheck.
 * Additionally, include options for entering expenses per paycheck, providing a clear overview of monthly
 * and yearly expenses.
 *
 * Design a menu to store users' net profit distribution goals. Provide insights into how long it will take to
 * achieve these goals, based on the rate and amount of monthly payments allocated towards them.
 ***************************************************************************************************************
 * Define:
 * Budget Storage : Store the users monthy income, expenses.
 *
 * Calculate Budget : Calculate the net profit of the budget for the month
 *
 *
 *
 **User Input for Income**
   - Allow users to select their income frequency (e.g., weekly, bi-weekly, monthly).
   - Provide an input field for users to enter the amount they earn per paycheck.

 **User Input for Expenses**
   - Include an option for users to enter multiple expense categories (e.g., rent, utilities, groceries).
   - Provide an input field for users to enter the amount for each expense category per paycheck.

 **Expense Overview**
   - Calculate total expenses per paycheck based on user inputs.
   - Generate a monthly expense summary by multiplying the paycheck expenses by the number of pay periods in a month.
   - Generate a yearly expense summary by multiplying the monthly expenses by 12.

 **User Interface**
   - Create a user-friendly menu layout for inputting income and expenses.
   - Ensure the interface is intuitive, with clear labels and guidance for each input field.

 **Data Validation**
   - Implement validation checks for income and expense inputs to ensure they are numeric and positive values.
   - Provide error messages for invalid inputs.

 **Reporting Functionality**
   - Offer a summary report displaying total income, total expenses, and net income on a monthly and yearly basis.
   - Allow users to export or print the summary report.

 **User Experience**
   - Ensure the menu is easily navigable and allows users to update their inputs as needed.
   - Include help or tooltips for additional information on income frequency and expense categories.

 **User Input for Net Profit Goals**
   - Provide an input field for users to enter their net profit distribution goal amount.
   - Allow users to specify a target date for achieving their goal.

 **User Input for Monthly Payments**
   - Include an input field for users to enter the amount they plan to contribute monthly towards their net profit goal.
   - Allow users to specify a frequency for these payments (e.g., monthly, quarterly).

 **Calculation of Time to Goal**
   - Implement a calculation that determines the number of months required to reach the net profit goal based on the monthly payment amount.
   - If applicable, provide insights on how adjustments in payment amounts or frequencies can impact the timeline.

 **User Interface**
   - Design a clear and user-friendly menu layout for inputting net profit goals and payment amounts.
   - Ensure the interface includes clear labels and instructions for each input field.

 **Data Validation**
   - Implement validation checks to ensure that goal amounts and monthly payments are numeric and positive values.
   - Provide error messages for invalid inputs to guide the user.

 **Progress Tracking**
   - Display a visual representation of progress towards the net profit goal (e.g., a progress bar).
   - Include a summary of total contributions made and the remaining amount needed to reach the goal.

 **Reporting Functionality**
   - Generate a report that summarizes the net profit goal, monthly payment amount, estimated time to achieve the goal, and any relevant insights.
   - Allow users to export or print the summary report for their records.

 **User Experience**
   - Ensure easy navigation within the menu, allowing users to update their goals and payment amounts as needed.
   - Include help or tooltips to explain terms related to net profit distribution and goal-setting.
 *
 ***************************************************************************************************************
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
 * Create a Widget called BudgetForm Widget that will use QSqlTabelModel for expenses with a QTabelView to display and modify the
 * expenses name and amount. Use another QSqlTableModel for income with a QTableView to display and
 * modify income name and amount. Show the net profit of the budget at the bottom of the widget.
 *
 ***************************************************************************************************************
*/

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlRecord>
#include "showbudgetsform.h"
#include "budgetform.h"

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

public slots:
    void budgetSelected(const QSqlRecord& record);

private:
    Ui::BudgetApp *ui;
    QSqlDatabase db;

    ShowBudgetsForm* showBudgetsForm = nullptr;
    BudgetForm* budgetForm = nullptr;

    void SetupDB();
    void SetupTables();

    void deleteBudgetForm();
};
#endif // BUDGETAPP_H

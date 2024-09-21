#include "budgetform.h"
#include "ui_budgetform.h"
#include <QInputDialog>
#include <QSqlRecord>
#include <QPushButton>

BudgetForm::BudgetForm(QWidget *parent, const QVariant& budgetId)
    : QWidget(parent)
    , ui(new Ui::BudgetForm)
{
    ui->setupUi(this);
    this->budgetId = budgetId;

    // load the data form the database to ui
    expensesModel = new QSqlTableModel(this);
    expensesModel->setTable("expense");
    expensesModel->setFilter("budget_id="+budgetId.toString());
    expensesModel->select();
    ui->expenseTableView->setModel(expensesModel);
    ui->expenseTableView->setColumnHidden(0, true);
    ui->expenseTableView->setColumnHidden(1, true);
    ui->expenseTableView->resizeColumnsToContents();
    incomeModel = new QSqlTableModel(this);
    incomeModel->setTable("income");
    incomeModel->setFilter("budget_id="+budgetId.toString());
    incomeModel->select();
    ui->incomeTableView->setModel(incomeModel);
    ui->incomeTableView->setColumnHidden(0, true);
    ui->incomeTableView->setColumnHidden(1, true);
    ui->incomeTableView->resizeColumnsToContents();

    calculateNetProfit(); // calculate the net profit from the data


    // connect signals to slots
    connect(ui->insertExpenseButton, &QPushButton::clicked,
            this, &BudgetForm::insertNewExpense);
    connect(ui->removeExpenseButton, &QPushButton::clicked,
            this, &BudgetForm::removeExpense);

    connect(ui->insertIncomeButton, &QPushButton::clicked,
            this, &BudgetForm::insertNewIncome);
    connect(ui->removeIncomeButton, &QPushButton::clicked,
           this, &BudgetForm::removeIncome);

    connect(expensesModel, &QSqlTableModel::dataChanged, this, [this]{
        calculateNetProfit();
        ui->expenseTableView->resizeColumnsToContents();
    });

    connect(incomeModel, &QSqlTableModel::dataChanged, this, [this]{
        calculateNetProfit();
        ui->incomeTableView->resizeColumnsToContents();
    });
}

void BudgetForm::insertNewExpense()
{
    // gather the users input of the name of the expense
    QString name = QInputDialog::getText(this, "Expense", "Expense Name : ");
    if(name.isEmpty())
        return;
    double amount = QInputDialog::getDouble(this, "Amount", "Expense Amount : ");
    QSqlRecord record = expensesModel->record();
    record.setValue(1, budgetId);
    record.setValue(2, name);
    record.setValue(3, amount);
    expensesModel->insertRecord(0, record);
    expensesModel->select();
    calculateNetProfit();
}

void BudgetForm::removeExpense()
{
    if(!ui->expenseTableView->currentIndex().isValid())
        return;
    expensesModel->removeRow(ui->expenseTableView->currentIndex().row());
    expensesModel->select();
    calculateNetProfit();
}

void BudgetForm::insertNewIncome()
{
    // gather the users input of the name of the expense
    QString name = QInputDialog::getText(this, "Income", "Income Name : ");
    if(name.isEmpty())
        return;
    double amount = QInputDialog::getDouble(this, "Income", "Income Amount : ");
    QSqlRecord record = incomeModel->record();
    record.setValue(1, budgetId);
    record.setValue(2, name);
    record.setValue(3, amount);
    incomeModel->insertRecord(0, record);
    incomeModel->select();
    calculateNetProfit();
}

void BudgetForm::removeIncome()
{
    if(!ui->incomeTableView->currentIndex().isValid())
        return;
    incomeModel->removeRow(ui->incomeTableView->currentIndex().row());
    incomeModel->select();
    calculateNetProfit();
}

void BudgetForm::calculateNetProfit()
{
    // take all of the amounts of the expenses add them
    double totalExpenseAmount = 0.00f;
    for(int i = 0; i < expensesModel->rowCount(); i++)
    {
        QSqlRecord record = expensesModel->record(i);
        double amount = record.value(3).toDouble();
        totalExpenseAmount += amount;
    }

    // take all of the incomes and add them
    double totalIncomeAmount = 0.00f;
    for(int i = 0; i < incomeModel->rowCount(); i++)
    {
        QSqlRecord record = incomeModel->record(i);
        double amount = record.value(3).toDouble();
        totalIncomeAmount += amount;
    }

    // subtract using income - expenses = net profit
    ui->netProfitLabel->setText(QString::number(totalIncomeAmount - totalExpenseAmount));
}

QPushButton* BudgetForm::getExitButton()
{
    return ui->exitButton;
}

BudgetForm::~BudgetForm()
{
    delete ui;
}

#include "showbudgetsform.h"
#include "ui_showbudgetsform.h"
#include "budgetform.h"
#include <QPushButton>
#include <QInputDialog>
#include <QSqlRecord>
#include <QSqlError>
#include <QItemSelectionModel>
#include <QString>

ShowBudgetsForm::ShowBudgetsForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShowBudgetsForm)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("budget");
    model->select();
    qDebug() << model->lastError().text();

    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);

    connect(ui->newButton, &QPushButton::clicked, this, [this]{
        QString name = QInputDialog::getText(this, "New Budget", "Budget Name");
        insertNewBudget(name);
    });

    connect(ui->removeButton, &QPushButton::clicked,
            this, &ShowBudgetsForm::removeBudget);

    connect(ui->selectButton, &QPushButton::clicked, this, [this]{

        // check if the has a selection or not
        QItemSelectionModel* selectionModel = ui->listView->selectionModel();
        QModelIndexList modelIndexList = selectionModel->selectedIndexes();
        if(modelIndexList.empty())
            return;

        // capture the selected record and get the id
        QSqlRecord record = model->record(ui->listView->currentIndex().row());

        // create the budgetform and make it the central widget
        emit selectBudget(record);
    });
}

void ShowBudgetsForm::RefreshList()
{
    model->select();
    ui->listView->setModel(model);
}

void ShowBudgetsForm::insertNewBudget(const QString& name)
{
    qDebug() << name;
    if(name.isEmpty())
        return;
    QSqlRecord record = model->record();
    record.setValue(1, name);
    model->insertRecord(0, record);

    RefreshList();
}

void ShowBudgetsForm::removeBudget()
{
    // only remove if something is selected
    QItemSelectionModel* selectionModel = ui->listView->selectionModel();
    if(selectionModel->selectedIndexes().isEmpty())
        return;


    // make sure to remove all of the expenses and incomes from the selected budget
    QSqlRecord incomeRecord = model->record(ui->listView->currentIndex().row());
    QSqlTableModel* incomeModel = new QSqlTableModel();
    incomeModel->setTable("income");
    incomeModel->select();
    incomeModel->setFilter("budget_id = "+incomeRecord.value(0).toString());

    for(int i = 0; i < incomeModel->rowCount(); i++)
    {
        incomeModel->removeRow(i);
    }

    delete incomeModel;
    incomeModel = nullptr;

    QSqlRecord expenseRecord = model->record(ui->listView->currentIndex().row());
    QSqlTableModel* expenseModel = new QSqlTableModel();
    expenseModel->setTable("expense");
    expenseModel->select();
    expenseModel->setFilter("budget_id = "+expenseRecord.value(0).toString());

    for(int i = 0; i < expenseModel->rowCount(); i++)
    {
        expenseModel->removeRow(i);
    }


    delete expenseModel;
    expenseModel = nullptr;

    model->removeRow(ui->listView->currentIndex().row());
    model->select();
}

ShowBudgetsForm::~ShowBudgetsForm()
{
    delete ui;
}

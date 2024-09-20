#include "showbudgetsform.h"
#include "ui_showbudgetsform.h"
#include <QPushButton>
#include <QInputDialog>
#include <QSqlRecord>
#include <QSqlError>

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

ShowBudgetsForm::~ShowBudgetsForm()
{
    delete ui;
}

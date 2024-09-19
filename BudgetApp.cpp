#include "BudgetApp.h"
#include "ui_BudgetApp.h"
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QSqlQuery>

BudgetApp::BudgetApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BudgetApp)
{
    ui->setupUi(this);
    setWindowTitle("Budget App");

    SetupDB();
}

void BudgetApp::SetupDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("budget.db");
    if(!db.open())
    {
        QSqlError error = db.lastError();
        if(error.isValid())
        {
            qDebug() << "ERROR : " << error.text();
        }
    }
    else
    {
        SetupTables();
        qDebug() << "Connected to DB";
    }
}

void BudgetApp::SetupTables()
{
    QFile file(":/sql/setup.sql");
    QString script = "";
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        script = file.readAll();
        file.close();
    }
    QSqlQuery query;
    QStringList scripts = script.split(';');
    for(const QString& script : scripts)
    {
        query.exec(script);
    }
}

BudgetApp::~BudgetApp()
{
    delete ui;
}

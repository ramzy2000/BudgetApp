#ifndef BUDGETFORM_H
#define BUDGETFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QPushButton>

namespace Ui {
class BudgetForm;
}

class BudgetForm : public QWidget
{
    Q_OBJECT

public:
    explicit BudgetForm(QWidget *parent = nullptr, const QVariant& budgetId = QVariant());
    ~BudgetForm();


    QPushButton* getExitButton();

public slots:
    void insertNewExpense();

    void removeExpense();

    void insertNewIncome();

    void removeIncome();

    void calculateNetProfit();

private:
    Ui::BudgetForm *ui;

    QVariant budgetId;
    QSqlTableModel* expensesModel;
    QSqlTableModel* incomeModel;
};

#endif // BUDGETFORM_H

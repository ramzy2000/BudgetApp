#ifndef SHOWBUDGETSFORM_H
#define SHOWBUDGETSFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlRecord>

namespace Ui {
class ShowBudgetsForm;
}

class ShowBudgetsForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowBudgetsForm(QWidget *parent);
    ~ShowBudgetsForm();

public slots:
    void insertNewBudget(const QString& name);

    void removeBudget();

signals:
    void selectBudget(const QSqlRecord& record);

private:
    Ui::ShowBudgetsForm *ui;
    QSqlTableModel* model;

    void RefreshList();
};

#endif // SHOWBUDGETSFORM_H

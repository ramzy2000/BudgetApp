--Create the Budget table

CREATE TABLE "budget" (
        "budget_id"	INTEGER,
        "name"	TEXT NOT NULL UNIQUE,
        PRIMARY KEY("budget_id" AUTOINCREMENT)
);

--Create the Expense table

CREATE TABLE "expense" (
        "expense_id"	INTEGER,
        "budget_id"     INTEGER NOT NULL,
        "name"	TEXT NOT NULL,
        "amount"	NUMERIC NOT NULL,
        PRIMARY KEY("expense_id" AUTOINCREMENT)
);

--Create the Income table
CREATE TABLE "income" (
        "income_id"	INTEGER,
        "budget_id"     INTEGER NOT NULL,
        "name"	TEXT NOT NULL,
        "amount"	NUMERIC NOT NULL,
        PRIMARY KEY("income_id" AUTOINCREMENT)
);

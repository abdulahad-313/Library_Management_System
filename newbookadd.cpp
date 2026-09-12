#include "newbookadd.h"
#include "ui_newbookadd.h"
#include"librarian_panal.h"
#include<QMessageBox>
#include <qsqlerror.h>
#include <qsqlquery.h>

NewBookAdd::NewBookAdd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewBookAdd)
{
    ui->setupUi(this);
}

NewBookAdd::~NewBookAdd()
{
    delete ui;
}




void NewBookAdd::on_Confirm_clicked()
{
    QString bookName    = ui->lineEditBookName->text().trimmed();
    QString author       = ui->lineEditAuthor->text().trimmed();
    QString publication  = ui->lineEditPublication->text().trimmed();
    QString totalCopyStr = ui->lineEditTotalCopy->text().trimmed();
    QString availCopyStr = ui->lineEditAvailableCopy->text().trimmed();

    if (bookName.isEmpty() || author.isEmpty() || publication.isEmpty() ||
        totalCopyStr.isEmpty() || availCopyStr.isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please fill in all fields.");
        return;
    }

    bool ok1, ok2;
    int totalCopy = totalCopyStr.toInt(&ok1);
    int availCopy = availCopyStr.toInt(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Invalid Input", "Total Copy and Available Copy must be numbers.");
        return;
    }

    if (availCopy > totalCopy) {
        QMessageBox::warning(this, "Invalid Input", "Available Copy cannot exceed Total Copy.");
        return;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT Book_id FROM Book WHERE Book_name = ? AND Author_name = ? AND Publication_name = ? AND Total_copy = ? AND Available_copy = ?");
    checkQuery.addBindValue(bookName);
    checkQuery.addBindValue(author);
    checkQuery.addBindValue(publication);
    checkQuery.addBindValue(totalCopy);
    checkQuery.addBindValue(availCopy);

    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Database Error", checkQuery.lastError().text());
        return;
    }

    if (checkQuery.next()) {
        QMessageBox::warning(this, "Duplicate Book", "This exact book already exists in the database.");
        return;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Book (Book_name, Author_name, Publication_name, Total_copy, Available_copy) VALUES (?, ?, ?, ?, ?)");
    insertQuery.addBindValue(bookName);
    insertQuery.addBindValue(author);
    insertQuery.addBindValue(publication);
    insertQuery.addBindValue(totalCopy);
    insertQuery.addBindValue(availCopy);

    if (insertQuery.exec()) {
        QMessageBox::information(this, "Success", "Book added successfully!");
        ui->lineEditBookName->clear();
        ui->lineEditAuthor->clear();
        ui->lineEditPublication->clear();
        ui->lineEditTotalCopy->clear();
        ui->lineEditAvailableCopy->clear();

        Librarian_panal *panel = qobject_cast<Librarian_panal *>(this->parentWidget());
        if (panel) {
            panel->refreshBooksTable();
        }

        this->close();
    } else {
        QMessageBox::critical(this, "Database Error", insertQuery.lastError().text());
    }
}
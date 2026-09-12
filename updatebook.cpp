#include "updatebook.h"
#include "ui_updatebook.h"
#include "librarian_panal.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

UpdateBook::UpdateBook(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateBook)
{
    ui->setupUi(this);
}

UpdateBook::~UpdateBook()
{
    delete ui;
}

void UpdateBook::on_OK_clicked()
{
    QString bookIdStr = ui->bookid->text().trimmed();

    if (bookIdStr.isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please enter a Book ID.");
        return;
    }

    bool ok;
    int bookId = bookIdStr.toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Book ID must be a number.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT Book_id, Book_name, Author_name, Publication_name, Total_copy, Available_copy FROM Book WHERE Book_id = ?");
    query.addBindValue(bookId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    if (!query.next()) {
        QMessageBox::warning(this, "Not Found", "No book exists with this ID.");
        return;
    }

    ui->newbookid->setText(query.value(0).toString());
    ui->lineEditBookName->setText(query.value(1).toString());
    ui->lineEditAuthor->setText(query.value(2).toString());
    ui->lineEditPublication->setText(query.value(3).toString());
    ui->lineEditTotalCopy->setText(query.value(4).toString());
    ui->lineEditAvailableCopy->setText(query.value(5).toString());
}

void UpdateBook::on_Confirm_clicked()
{
    QString originalIdStr = ui->bookid->text().trimmed();
    QString newIdStr      = ui->newbookid->text().trimmed();
    QString bookName      = ui->lineEditBookName->text().trimmed();
    QString author        = ui->lineEditAuthor->text().trimmed();
    QString publication   = ui->lineEditPublication->text().trimmed();
    QString totalCopyStr  = ui->lineEditTotalCopy->text().trimmed();
    QString availCopyStr  = ui->lineEditAvailableCopy->text().trimmed();

    if (originalIdStr.isEmpty() || newIdStr.isEmpty() || bookName.isEmpty() ||
        author.isEmpty() || publication.isEmpty() || totalCopyStr.isEmpty() || availCopyStr.isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please fill in all fields.");
        return;
    }

    bool ok0, ok1, ok2, ok3;
    int originalId = originalIdStr.toInt(&ok0);
    int newId      = newIdStr.toInt(&ok1);
    int totalCopy  = totalCopyStr.toInt(&ok2);
    int availCopy  = availCopyStr.toInt(&ok3);

    if (!ok0 || !ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Invalid Input", "Book ID, Total Copy, and Available Copy must be numbers.");
        return;
    }

    if (availCopy > totalCopy) {
        QMessageBox::warning(this, "Invalid Input", "Available Copy cannot exceed Total Copy.");
        return;
    }

    if (newId != originalId) {
        QSqlQuery idCheck;
        idCheck.prepare("SELECT Book_id FROM Book WHERE Book_id = ?");
        idCheck.addBindValue(newId);

        if (!idCheck.exec()) {
            QMessageBox::critical(this, "Database Error", idCheck.lastError().text());
            return;
        }

        if (idCheck.next()) {
            QMessageBox::warning(this, "ID Already Exists", "Another book already uses this Book ID.");
            return;
        }
    }

    QSqlQuery dupCheck;
    dupCheck.prepare("SELECT Book_id FROM Book WHERE Book_name = ? AND Author_name = ? AND Publication_name = ? AND Total_copy = ? AND Available_copy = ? AND Book_id != ?");
    dupCheck.addBindValue(bookName);
    dupCheck.addBindValue(author);
    dupCheck.addBindValue(publication);
    dupCheck.addBindValue(totalCopy);
    dupCheck.addBindValue(availCopy);
    dupCheck.addBindValue(originalId);

    if (!dupCheck.exec()) {
        QMessageBox::critical(this, "Database Error", dupCheck.lastError().text());
        return;
    }

    if (dupCheck.next()) {
        QMessageBox::warning(this, "Duplicate Book", "Another book with identical details already exists.");
        return;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Book SET Book_id = ?, Book_name = ?, Author_name = ?, Publication_name = ?, Total_copy = ?, Available_copy = ? WHERE Book_id = ?");
    updateQuery.addBindValue(newId);
    updateQuery.addBindValue(bookName);
    updateQuery.addBindValue(author);
    updateQuery.addBindValue(publication);
    updateQuery.addBindValue(totalCopy);
    updateQuery.addBindValue(availCopy);
    updateQuery.addBindValue(originalId);

    if (updateQuery.exec()) {
        QMessageBox::information(this, "Success", "Book updated successfully!");

        Librarian_panal *panel = qobject_cast<Librarian_panal *>(this->parentWidget());
        if (panel) {
            panel->refreshBooksTable();
        }

        this->close();
    } else {
        QMessageBox::critical(this, "Database Error", updateQuery.lastError().text());
    }
}


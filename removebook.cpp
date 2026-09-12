#include "removebook.h"
#include "librarian_panal.h"
#include "ui_removebook.h"
#include<qmessagebox.h>
#include <qsqlerror.h>
#include <qsqlquery.h>

RemoveBook::RemoveBook(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveBook)
{
    ui->setupUi(this);
}

RemoveBook::~RemoveBook()
{
    delete ui;
}

void RemoveBook::on_Confirm_clicked()
{
    QString bookIdStr = ui->Bookid->text().trimmed();

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

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT Book_id FROM Book WHERE Book_id = ?");
    checkQuery.addBindValue(bookId);

    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Database Error", checkQuery.lastError().text());
        return;
    }

    if (!checkQuery.next()) {
        QMessageBox::warning(this, "Not Found", "No book exists with this ID.");
        return;
    }

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM Book WHERE Book_id = ?");
    deleteQuery.addBindValue(bookId);

    if (deleteQuery.exec()) {
        QMessageBox::information(this, "Success", "Book removed successfully!");
        ui->Bookid->clear();

        Librarian_panal *panel = qobject_cast<Librarian_panal *>(this->parentWidget());
        if (panel) {
            panel->refreshBooksTable();
        }

        this->close();
    } else {
        QMessageBox::critical(this, "Database Error", deleteQuery.lastError().text());
    }
}


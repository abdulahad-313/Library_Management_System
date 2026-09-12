#include "add_book.h"
#include "ui_add_book.h"
#include "member_panel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QVector>

Add_Book::Add_Book(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_Book)
{
    ui->setupUi(this);
}

Add_Book::~Add_Book()
{
    delete ui;
}

void Add_Book::on_Confirm_clicked()
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

    Member_Panel *panel = qobject_cast<Member_Panel *>(this->parentWidget());
    if (!panel) {
        QMessageBox::critical(this, "Error", "Could not identify logged-in member.");
        return;
    }
    int memberId = panel->loggedInMemberId;


    QSqlQuery bookCheck;
    bookCheck.prepare("SELECT Available_copy FROM Book WHERE Book_id = ?");
    bookCheck.addBindValue(bookId);

    if (!bookCheck.exec()) {
        QMessageBox::critical(this, "Database Error", bookCheck.lastError().text());
        return;
    }

    if (!bookCheck.next()) {
        QMessageBox::warning(this, "Not Found", "No book exists with this ID.");
        return;
    }

    int availableCopy = bookCheck.value(0).toInt();
    if (availableCopy <= 0) {
        QMessageBox::warning(this, "Unavailable", "This book has no available copies right now.");
        return;
    }


    QSqlQuery memberQuery;
    memberQuery.prepare("SELECT Book_1, Book_2, Book_3, Book_4, Book_5 FROM li_m WHERE m_id = ?");
    memberQuery.addBindValue(memberId);

    if (!memberQuery.exec()) {
        QMessageBox::critical(this, "Database Error", memberQuery.lastError().text());
        return;
    }

    if (!memberQuery.next()) {
        QMessageBox::critical(this, "Error", "Could not find your member record.");
        return;
    }

    QVector<QVariant> bookSlots(5);
    QVector<QString> columnNames = {"Book_1", "Book_2", "Book_3", "Book_4", "Book_5"};
    int emptySlotIndex = -1;

    for (int i = 0; i < 5; ++i) {
        bookSlots[i] = memberQuery.value(i);


        if (!bookSlots[i].isNull() && bookSlots[i].toInt() == bookId) {
            QMessageBox::warning(this, "Already Borrowed", "You already have this book.");
            return;
        }

        if (emptySlotIndex == -1 && bookSlots[i].isNull()) {
            emptySlotIndex = i;
        }
    }

    if (emptySlotIndex == -1) {
        QMessageBox::warning(this, "Limit Reached", "You can't have more than 5 books at a time.");
        return;
    }


    QSqlQuery updateMember;
    QString updateSql = QString("UPDATE li_m SET %1 = ? WHERE m_id = ?").arg(columnNames[emptySlotIndex]);
    updateMember.prepare(updateSql);
    updateMember.addBindValue(bookId);
    updateMember.addBindValue(memberId);

    if (!updateMember.exec()) {
        QMessageBox::critical(this, "Database Error", updateMember.lastError().text());
        return;
    }


    QSqlQuery updateBook;
    updateBook.prepare("UPDATE Book SET Available_copy = Available_copy - 1 WHERE Book_id = ?");
    updateBook.addBindValue(bookId);

    if (!updateBook.exec()) {
        QMessageBox::critical(this, "Database Error", updateBook.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Book borrowed successfully!");
    ui->bookid->clear();
    this->close();
}


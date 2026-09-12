#include "return_book.h"
#include "ui_return_book.h"
#include "member_panel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QVector>
Return_Book::Return_Book(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Return_Book)
{
    ui->setupUi(this);
}

Return_Book::~Return_Book()
{
    delete ui;
}

void Return_Book::on_Confirm_clicked()
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

    QVector<QString> columnNames = {"Book_1", "Book_2", "Book_3", "Book_4", "Book_5"};
    int matchedSlotIndex = -1;

    for (int i = 0; i < 5; ++i) {
        QVariant slotValue = memberQuery.value(i);
        if (!slotValue.isNull() && slotValue.toInt() == bookId) {
            matchedSlotIndex = i;
            break;
        }
    }

    if (matchedSlotIndex == -1) {
        QMessageBox::warning(this, "Not Found", "You don't currently have this book borrowed.");
        return;
    }

    QSqlQuery updateMember;
    QString updateSql = QString("UPDATE li_m SET %1 = NULL WHERE m_id = ?").arg(columnNames[matchedSlotIndex]);
    updateMember.prepare(updateSql);
    updateMember.addBindValue(memberId);

    if (!updateMember.exec()) {
        QMessageBox::critical(this, "Database Error", updateMember.lastError().text());
        return;
    }

    QSqlQuery updateBook;
    updateBook.prepare("UPDATE Book SET Available_copy = Available_copy + 1 WHERE Book_id = ?");
    updateBook.addBindValue(bookId);

    if (!updateBook.exec()) {
        QMessageBox::critical(this, "Database Error", updateBook.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Book returned successfully!");
    ui->bookid->clear();

    panel = qobject_cast<Member_Panel *>(this->parentWidget());
    if (panel) {
        panel->refreshMyBooksTable();
    }

    this->close();
}


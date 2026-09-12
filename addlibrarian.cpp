#include "addlibrarian.h"
#include "ui_addlibrarian.h"
#include <qsqlerror.h>
#include <qsqlquery.h>
#include<qmessagebox.h>

AddLibrarian::AddLibrarian(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddLibrarian)
{
    ui->setupUi(this);
}

AddLibrarian::~AddLibrarian()
{
    delete ui;
}

void AddLibrarian::on_Confirm_clicked()
{
        QString memberIdStr = ui->lineEditMemberId->text().trimmed();

        if (memberIdStr.isEmpty()) {
            QMessageBox::warning(this, "Missing Information", "Please enter a Member ID.");
            return;
        }

        bool ok;
        int memberId = memberIdStr.toInt(&ok);

        if (!ok) {
            QMessageBox::warning(this, "Invalid Input", "Member ID must be a number.");
            return;
        }


        QSqlQuery memberCheck;
        memberCheck.prepare("SELECT m_id FROM li_m WHERE m_id = ?");
        memberCheck.addBindValue(memberId);

        if (!memberCheck.exec()) {
            QMessageBox::critical(this, "Database Error", memberCheck.lastError().text());
            return;
        }

        if (!memberCheck.next()) {
            QMessageBox::warning(this, "Not Found", "No registered member exists with this ID.");
            return;
        }


        QSqlQuery libCheck;
        libCheck.prepare("SELECT id FROM Lib WHERE id = ?");
        libCheck.addBindValue(memberId);

        if (!libCheck.exec()) {
            QMessageBox::critical(this, "Database Error", libCheck.lastError().text());
            return;
        }

        if (libCheck.next()) {
            QMessageBox::warning(this, "Already a Librarian", "This member is already a librarian.");
            return;
        }


        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO Lib (id) VALUES (?)");
        insertQuery.addBindValue(memberId);

        if (insertQuery.exec()) {
            QMessageBox::information(this, "Success", "Librarian added successfully!");
            ui->lineEditMemberId->clear();
            this->close();
        } else {
            QMessageBox::critical(this, "Database Error", insertQuery.lastError().text());
        }

}


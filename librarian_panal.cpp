#include "librarian_panal.h"
#include "alternatingrowdelegate.h"
#include"mainwindow.h"
#include "ui_librarian_panal.h"
#include "updatebook.h"
#include <QSqlQueryModel>
#include <qsqlerror.h>
#include<QMessageBox>

Librarian_panal::Librarian_panal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Librarian_panal)
{
    ui->setupUi(this);
}

Librarian_panal::~Librarian_panal()
{
    delete ui;
}

void Librarian_panal::refreshBooksTable()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT Book_id, Book_name, Author_name, Publication_name, Total_copy, Available_copy FROM Book");

    if (model->lastError().isValid()) {
        QMessageBox::critical(this, "Database Error", model->lastError().text());
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, "Book ID");
    model->setHeaderData(1, Qt::Horizontal, "Book Name");
    model->setHeaderData(2, Qt::Horizontal, "Author");
    model->setHeaderData(3, Qt::Horizontal, "Publication");
    model->setHeaderData(4, Qt::Horizontal, "Total Copies");
    model->setHeaderData(5, Qt::Horizontal, "Available Copies");

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new AlternatingRowDelegate(ui->tableView));
}

void Librarian_panal::on_AllBook_clicked()
{
    refreshBooksTable();
}

void Librarian_panal::on_AddBook_clicked()
{
    NewBookAdd *i = new NewBookAdd(this);
    i->show();
}


void Librarian_panal::on_LogOut_clicked()
{
    MainWindow *w = new MainWindow();
    w->show();
    this->close();
}



void Librarian_panal::on_RemoveBook_clicked()
{
    RemoveBook *j=new RemoveBook(this);
    j->show();
}


void Librarian_panal::on_AddLibrarian_clicked()
{
    AddLibrarian *k=new AddLibrarian(this);
    k->show();
}


void Librarian_panal::on_AllMembers_clicked()
{
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery("SELECT m_id, Full_name, username, phone, Book_1, Book_2, Book_3, Book_4, Book_5 FROM li_m");

        if (model->lastError().isValid()) {
            QMessageBox::critical(this, "Database Error", model->lastError().text());
            return;
        }

        model->setHeaderData(0, Qt::Horizontal, "Member ID");
        model->setHeaderData(1, Qt::Horizontal, "Full Name");
        model->setHeaderData(2, Qt::Horizontal, "Username");
        model->setHeaderData(3, Qt::Horizontal, "Phone");
        model->setHeaderData(4, Qt::Horizontal, "Book 1");
        model->setHeaderData(5, Qt::Horizontal, "Book 2");
        model->setHeaderData(6, Qt::Horizontal, "Book 3");
        model->setHeaderData(7, Qt::Horizontal, "Book 4");
        model->setHeaderData(8, Qt::Horizontal, "Book 5");

        ui->tableView->setModel(model);
        ui->tableView->setItemDelegate(new AlternatingRowDelegate(ui->tableView));

}


void Librarian_panal::on_UpdateBook_clicked()
{
    UpdateBook *l=new UpdateBook(this);
    l->show();
}


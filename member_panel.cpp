#include "member_panel.h"
#include "alternatingrowdelegate.h"
#include "return_book.h"
#include "ui_member_panel.h"
#include"mainwindow.h"
#include <qsqlerror.h>
#include <qsqlquerymodel.h>
#include<QMessageBox>
#include"add_book.h"

Member_Panel::Member_Panel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Member_Panel)
{
    ui->setupUi(this);
}

Member_Panel::~Member_Panel()
{
    delete ui;
}

Member_Panel::Member_Panel(int memberId, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Member_Panel)
    , loggedInMemberId(memberId)
{
    ui->setupUi(this);
}

void Member_Panel::on_AllBook_clicked()
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


void Member_Panel::on_AddBook_clicked()
{
    Add_Book *h=new Add_Book(this);
    h->show();
}


void Member_Panel::on_LogOut_clicked()
{
    MainWindow *w = new MainWindow();
    w->show();
    this->close();
}

void Member_Panel::on_AllMembers_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT m_id, Full_name, username FROM li_m");

    if (model->lastError().isValid()) {
        QMessageBox::critical(this, "Database Error", model->lastError().text());
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, "Member ID");
    model->setHeaderData(1, Qt::Horizontal, "Full Name");
    model->setHeaderData(2, Qt::Horizontal, "Username");

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new AlternatingRowDelegate(ui->tableView));
}

void Member_Panel::refreshMyBooksTable()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString sql = QString(
                      "SELECT b.Book_id, b.Book_name, b.Author_name, b.Publication_name, b.Total_copy, b.Available_copy "
                      "FROM Book b "
                      "WHERE b.Book_id IN (SELECT Book_1 FROM li_m WHERE m_id = %1) "
                      "OR b.Book_id IN (SELECT Book_2 FROM li_m WHERE m_id = %1) "
                      "OR b.Book_id IN (SELECT Book_3 FROM li_m WHERE m_id = %1) "
                      "OR b.Book_id IN (SELECT Book_4 FROM li_m WHERE m_id = %1) "
                      "OR b.Book_id IN (SELECT Book_5 FROM li_m WHERE m_id = %1)"
                      ).arg(loggedInMemberId);

    model->setQuery(sql);

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

void Member_Panel::on_MyBook_clicked()
{
    refreshMyBooksTable();
}

void Member_Panel::on_ReturnBook_clicked()
{
    Return_Book *m=new Return_Book(this);
    m->show();
}


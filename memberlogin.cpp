#include "memberlogin.h"
#include "member_panel.h"
#include "ui_memberlogin.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

memberlogin::memberlogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::memberlogin)
{
    ui->setupUi(this);
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("p0o9i8u7y6t5r4e3w2q1");
    db.setDatabaseName("Library_Management_System");

    if(db.open()){
        qDebug()<<"Database connected successfully";
    }
    else{
        qDebug()<<"Connection Failed";
    }
}

memberlogin::~memberlogin()
{
    delete ui;
}

void memberlogin::on_Confirm_clicked()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please enter both username and password.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT m_id, Pass_key FROM li_m WHERE username = ?");
    query.addBindValue(username);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    if (!query.next()) {
        QMessageBox::warning(this, "Login Failed", "Username not found.");
        return;
    }

    int memberId = query.value(0).toInt();
    QString storedPassword = query.value(1).toString();

    if (storedPassword != password) {
        QMessageBox::warning(this, "Login Failed", "Incorrect password.");
        return;
    }


    Member_Panel *f = new Member_Panel(memberId);
    f->setAttribute(Qt::WA_DeleteOnClose);
    f->show();

    if (this->parentWidget()) {
        this->parentWidget()->close();
    }
    this->close();
}

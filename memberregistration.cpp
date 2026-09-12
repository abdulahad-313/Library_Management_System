#include "memberregistration.h"
#include "ui_memberregistration.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

MemberRegistration::MemberRegistration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MemberRegistration)
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

MemberRegistration::~MemberRegistration()
{
    delete ui;
}



void MemberRegistration::on_pushButton_MR_clicked()
{
        QString fullName = ui->lineEditFullName->text().trimmed();
        QString username = ui->lineEditUsername->text().trimmed();
        QString phone     = ui->lineEditPhone->text().trimmed();
        QString password  = ui->lineEditPassword->text();


        if (fullName.isEmpty() || username.isEmpty() || phone.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Missing Information", "Please fill in all fields.");
            return;
        }


        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT username FROM li_m WHERE username = ?");
        checkQuery.addBindValue(username);

        if (!checkQuery.exec()) {
            QMessageBox::critical(this, "Database Error", checkQuery.lastError().text());
            return;
        }

        if (checkQuery.next()) {
            QMessageBox::warning(this, "Username Taken", "This username already exists. Please choose another.");
            return;
        }


        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO li_m (Full_name, username, Pass_key, phone) VALUES (?, ?, ?, ?)");
        insertQuery.addBindValue(fullName);
        insertQuery.addBindValue(username);
        insertQuery.addBindValue(password);
        insertQuery.addBindValue(phone);

        if (insertQuery.exec()) {
            QMessageBox::information(this, "Success", "Member registered successfully!");
            ui->lineEditFullName->clear();
            ui->lineEditUsername->clear();
            ui->lineEditPhone->clear();
            ui->lineEditPassword->clear();
        } else {
            QMessageBox::critical(this, "Database Error", insertQuery.lastError().text());
        }

}


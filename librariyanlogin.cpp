#include "librariyanlogin.h"
#include "ui_librariyanlogin.h"


LibrariyanLogin::LibrariyanLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LibrariyanLogin)
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

LibrariyanLogin::~LibrariyanLogin()
{
    delete ui;
}

void LibrariyanLogin::on_Confirm_clicked()
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

    QSqlQuery libCheck;
    libCheck.prepare("SELECT id FROM Lib WHERE id = ?");
    libCheck.addBindValue(memberId);

    if (!libCheck.exec()) {
        QMessageBox::critical(this, "Database Error", libCheck.lastError().text());
        return;
    }

    if (!libCheck.next()) {
        QMessageBox::warning(this, "Access Denied", "This account is not authorized as a librarian.");
        return;
    }


    Librarian_panal *g = new Librarian_panal();
    g->setAttribute(Qt::WA_DeleteOnClose);
    g->show();

    if (this->parentWidget()) {
        this->parentWidget()->close();
    }
    this->close();
}

